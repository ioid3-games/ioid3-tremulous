#include "q3_lauxlib.h"
#include <iostream>
#include <sys/types.h>
#include "q_shared.h"
#include "qcommon.h"

/*
=======================================================================================================================================
lua_writestring
=======================================================================================================================================
*/
size_t lua_writestring(char *string, size_t n) {
	// if (n > MAXPRINTMSG) {
	// 		n -= MAXPRINTMSG;
	// 		string[MAXPRINTMSG] = '\0';
	// }
#ifndef DEDICATED
	CL_ConsolePrint(string);
#endif
	Q_StripIndentMarker(string);
	Sys_Print(string);

	return n;
}

/*
=======================================================================================================================================
lua_writeline
=======================================================================================================================================
*/
int lua_writeline(void) {
#ifndef DEDICATED
	CL_ConsolePrint("\n");
#endif
	Sys_Print("\n");
	return 0;
}

/*
=======================================================================================================================================
lua_writestringerror
=======================================================================================================================================
*/
int lua_writestringerror(const char *fmt, ...) {
	va_list ap;
	va_start(ap, fmt);
	char m[MAXPRINTMSG];

	Q_vsnprintf(m, sizeof(m), fmt, ap);
	va_end(ap);
	Com_Printf(S_COLOR_YELLOW "%s\n", m);
	return 0;
}
