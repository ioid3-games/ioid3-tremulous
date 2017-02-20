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

#ifndef QCOMMON_DIALOG_H
#define QCOMMON_DIALOG_H

#ifdef __cplusplus
extern "C" {
#endif
typedef enum {
	DR_YES = 0,
	DR_NO = 1,
	DR_OK = 0,
	DR_CANCEL = 1
} dialogResult_t;

typedef enum {
	DT_INFO,
	DT_WARNING,
	DT_ERROR,
	DT_YES_NO,
	DT_OK_CANCEL
} dialogType_t;

dialogResult_t Sys_Dialog(dialogType_t type, const char *message, const char *title);

#ifdef __cplusplus
}
#endif
#endif
