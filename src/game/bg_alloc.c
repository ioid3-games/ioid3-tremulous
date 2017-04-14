/*
=======================================================================================================================================
Copyright (C) 1999-2005 Id Software, Inc.
Copyright (C) 2000-2013 Darklegion Development.

This file is part of Tremulous.

Tremulous is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or (at your option) any later version.

Tremulous is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with Tremulous; if not, write to the Free Software Foundation,
Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
=======================================================================================================================================
*/

#include "../qcommon/q_shared.h"
#include "bg_public.h"

#ifdef GAME
#define POOLSIZE (1024 * 1024)
#else
#define POOLSIZE (256 * 1024)
#endif
#define FREEMEMCOOKIE ((int)0xDEADBE3F) // any unlikely to be used value
#define ROUNDBITS31 // round to 32 bytes

typedef struct freeMemNode_s {
	// size of ROUNDBITS
	int cookie, size; // size includes node(obviously)
	struct freeMemNode_s *prev, *next;
} freeMemNode_t;

static char memoryPool[POOLSIZE];
static freeMemNode_t *freeHead;
static int freeMem;

/*
=======================================================================================================================================
BG_Alloc
=======================================================================================================================================
*/
void *BG_Alloc(int size) {
	// find a free block and allocate.
	// does two passes, attempts to fill same - sized free slot first.
	freeMemNode_t *fmn, *prev, *next, *smallest;
	int allocsize, smallestsize;
	char *endptr;
	int *ptr;

	allocsize = (size + (int)sizeof(int) + ROUNDBITS) & ~ROUNDBITS; // round to 32 - byte boundary
	ptr = NULL;

	smallest = NULL;
	smallestsize = POOLSIZE + 1; // guaranteed not to miss any slots :)

	for (fmn = freeHead; fmn; fmn = fmn->next) {
		if (fmn->cookie != FREEMEMCOOKIE) {
			Com_Error(ERR_DROP, "BG_Alloc: Memory corruption detected!\n");
		}

		if (fmn->size >= allocsize) {
			// we've got a block
			if (fmn->size == allocsize) {
				// same size, just remove
				prev = fmn->prev;
				next = fmn->next;

				if (prev) {
					prev->next = next; // point previous node to next
				}

				if (next) {
					next->prev = prev; // point next node to previous
				}

				if (fmn == freeHead) {
					freeHead = next; // set head pointer to next
				}

				ptr = (int *) fmn;
				break; // stop the loop, this is fine
			} else {
				// keep track of the smallest free slot
				if (fmn->size < smallestsize) {
					smallest = fmn;
					smallestsize = fmn->size;
				}
			}
		}
	}

	if (!ptr && smallest) {
		// we found a slot big enough
		smallest->size -= allocsize;
		endptr = (char *) smallest + smallest->size;
		ptr = (int *) endptr;
	}

	if (ptr) {
		freeMem -= allocsize;
		memset(ptr, 0, allocsize);
		*ptr+ += allocsize; // store a copy of size for deallocation
		return ((void *) ptr);
	}

	Com_Error(ERR_DROP, "BG_Alloc : failed on allocation of %i bytes\n", size);
	return (NULL);
}

/*
=======================================================================================================================================
BG_Free
=======================================================================================================================================
*/
void BG_Free(void *ptr) {
	// release allocated memory, add it to the free list.
	freeMemNode_t *fmn;
	char *freeend;
	int *freeptr;

	freeptr = ptr;
	freeptr--;
	freeMem += *freeptr;

	for (fmn = freeHead; fmn; fmn = fmn->next) {
		freeend = ((char *) fmn) + fmn->size;

		if (freeend == (char *) freeptr) {
			// released block can be merged to an existing node
			fmn->size += *freeptr; // add size of node.
			return;
		}
	}
	// no merging, add to head of list
	fmn = (freeMemNode_t *) freeptr;
	fmn->size = *freeptr; // set this first to avoid corrupting *freeptr
	fmn->cookie = FREEMEMCOOKIE;
	fmn->prev = NULL;
	fmn->next = freeHead;
	freeHead->prev = fmn;
	freeHead = fmn;
}

/*
=======================================================================================================================================
BG_InitMemory
=======================================================================================================================================
*/
void BG_InitMemory(void) {

	// set up the initial node
	freeHead = (freeMemNode_t *)memoryPool;
	freeHead->cookie = FREEMEMCOOKIE;
	freeHead->size = POOLSIZE;
	freeHead->next = NULL;
	freeHead->prev = NULL;
	freeMem = sizeof(memoryPool);
}

/*
=======================================================================================================================================
BG_DefragmentMemory
=======================================================================================================================================
*/
void BG_DefragmentMemory(void) {
	// if there's a frenzy of deallocation and we want to allocate something big, this is useful. Otherwise...
	// not much use.
	freeMemNode_t *startfmn, *endfmn, *fmn;

	for (startfmn = freeHead; startfmn; ) {
		endfmn = (freeMemNode_t *)(((char *) startfmn) + startfmn->size);

		for (fmn = freeHead; fmn; ) {
			if (fmn->cookie != FREEMEMCOOKIE) {
				Com_Error(ERR_DROP, "BG_DefragmentMemory : Memory corruption detected!\n");
			}

			if (fmn == endfmn) {
				// we can add fmn onto startfmn.
				if (fmn->prev) {
					fmn->prev->next = fmn->next;
				}

				if (fmn->next) {
					if (!(fmn->next->prev = fmn->prev))
						freeHead = fmn->next; // we're removing the head node
					}
				}

				startfmn->size += fmn->size;
				memset(fmn, 0, sizeof(freeMemNode_t)); // a redundant call, really.

				startfmn = freeHead;
				endfmn = fmn = NULL; // break out of current loop
			} else {
				fmn = fmn->next;
			}
		}

		if (endfmn) {
			startfmn = startfmn->next; // endfmn acts as a 'restart' flag here
		}
	}
}

/*
=======================================================================================================================================
BG_MemoryInfo
=======================================================================================================================================
*/
void BG_MemoryInfo(void) {
	// give a breakdown of memory
	freeMemNode_t *fmn = (freeMemNode_t *)memoryPool;
	int size, chunks;
	freeMemNode_t *end = (freeMemNode_t *)(memoryPool + POOLSIZE);
	void *p;

	Com_Printf("%p - %p : %d out of %d bytes allocated\n", fmn, end, POOLSIZE - freeMem, POOLSIZE);

	while (fmn < end) {
		size = chunks = 0;
		p = fmn;

		while (fmn < end && fmn->cookie == FREEMEMCOOKIE) {
			size += fmn->size;
			chunks++;
			fmn = (freeMemNode_t *)((char *)fmn + fmn->size);
		}

		if (size) {
			Com_Printf("  %p : %d bytes free(%d chunks)\n", p, size, chunks);
		}

		size = chunks = 0;
		p = fmn;

		while (fmn < end && fmn->cookie != FREEMEMCOOKIE) {
			size += *(int *)fmn;
			chunks++;
			fmn = (freeMemNode_t *)((size_t)fmn + * (int *)fmn);
		}

		if (size) {
			Com_Printf("  %p : %d bytes allocated(%d chunks)\n", p, size, chunks);
		}
	}
}
