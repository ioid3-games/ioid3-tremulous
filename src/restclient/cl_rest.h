#ifndef _CL_REST_H_
#define _CL_REST_H_

#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif

bool		GetPermissions(const char *execpath);

// download a fresh copy of the "required" base game files to the top - most fs_basegame.
//
// returns true(1) on success
// return false(0) on error
//
bool		GetTremulousPk3s(const char *destdir, const char *basegame);

#ifdef __cplusplus
};
#endif

#endif
