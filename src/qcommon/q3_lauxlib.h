// this file is part of Tremulous.
// copyright © 2016 Victor Roemer(blowfish) < victor@badsec.org>
//
// this program is free software; you can redistribute it and / or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// this program is distributed in the hope that it will be useful, 
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// mERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// gNU General Public License for more details.
//
// you should have received a copy of the GNU General Public License
// along with this program; if not, see < http:// www.gnu.org / licenses / > .

#ifndef OVERRIDE_LAUXLIB_H
#define OVERRIDE_LAUXLIB_H

#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

size_t lua_writestring(char *string, size_t n);
int lua_writeline(void);
int lua_writestringerror(const char *fmt, ...);

#ifdef __cplusplus
}
#endif
#endif
