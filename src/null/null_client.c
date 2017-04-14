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
#include "../qcommon/qcommon.h"

cvar_t *cl_shownet;

/*
=======================================================================================================================================
CL_Shutdown
=======================================================================================================================================
*/
void CL_Shutdown(const char *finalmsg, qboolean disconnect, qboolean quit) {
}

/*
=======================================================================================================================================
CL_Init
=======================================================================================================================================
*/
void CL_Init(void) {
	cl_shownet = Cvar_Get("cl_shownet", "0", CVAR_TEMP);
}

/*
=======================================================================================================================================
CL_MouseEvent
=======================================================================================================================================
*/
void CL_MouseEvent(int dx, int dy, int time) {
}

/*
=======================================================================================================================================
Key_WriteBindings
=======================================================================================================================================
*/
void Key_WriteBindings(fileHandle_t f) {
}

/*
=======================================================================================================================================
CL_Frame
=======================================================================================================================================
*/
void CL_Frame(int msec) {
}

/*
=======================================================================================================================================
CL_PacketEvent
=======================================================================================================================================
*/
void CL_PacketEvent(netadr_t from, msg_t *msg) {
}

/*
=======================================================================================================================================
CL_CharEvent
=======================================================================================================================================
*/
void CL_CharEvent(int key) {
}

/*
=======================================================================================================================================
CL_Disconnect
=======================================================================================================================================
*/
void CL_Disconnect(qboolean showMainMenu) {
}

/*
=======================================================================================================================================
CL_MapLoading
=======================================================================================================================================
*/
void CL_MapLoading(void) {
}

/*
=======================================================================================================================================
CL_GameCommand
=======================================================================================================================================
*/
qboolean CL_GameCommand(void) {
	return qfalse;
}

/*
=======================================================================================================================================
CL_KeyEvent
=======================================================================================================================================
*/
void CL_KeyEvent(int key, qboolean down, unsigned time) {
}

/*
=======================================================================================================================================
UI_GameCommand
=======================================================================================================================================
*/
qboolean UI_GameCommand(void) {
	return qfalse;
}

/*
=======================================================================================================================================
CL_ForwardCommandToServer
=======================================================================================================================================
*/
void CL_ForwardCommandToServer(const char *string) {
}

/*
=======================================================================================================================================
CL_ConsolePrint
=======================================================================================================================================
*/
void CL_ConsolePrint(const char *txt) {
}

/*
=======================================================================================================================================
CL_JoystickEvent
=======================================================================================================================================
*/
void CL_JoystickEvent(int axis, int value, int time) {
}

/*
=======================================================================================================================================
CL_InitKeyCommands
=======================================================================================================================================
*/
void CL_InitKeyCommands(void) {
}

/*
=======================================================================================================================================
CL_CDDialog
=======================================================================================================================================
*/
void CL_CDDialog(void) {
}

/*
=======================================================================================================================================
CL_FlushMemory
=======================================================================================================================================
*/
void CL_FlushMemory(void) {
}

/*
=======================================================================================================================================
CL_ShutdownAll
=======================================================================================================================================
*/
void CL_ShutdownAll(qboolean shutdownRef) {
}

/*
=======================================================================================================================================
CL_StartHunkUsers
=======================================================================================================================================
*/
void CL_StartHunkUsers(qboolean rendererOnly) {
}

/*
=======================================================================================================================================
CL_InitRef
=======================================================================================================================================
*/
void CL_InitRef(void) {
}

/*
=======================================================================================================================================
CL_Snd_Shutdown
=======================================================================================================================================
*/
void CL_Snd_Shutdown(void) {
}
