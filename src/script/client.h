//
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
//

#ifndef __cplusplus
#error __file__ " is only available to C++"
#endif

#ifndef SCRIPT_CLIENT_H
#define SCRIPT_CLIENT_H

#include <iostream>

// #include "../client/client.h"

namespace sol {
		class state;
};

extern "C" void CL_AddReliableCommand(const char *cmd, qboolean isDisconnectCmd);

namespace script {
		// no Exceptions at this time

		struct Client {};
		namespace client 
		{
				static inline void init(sol::state * lua) {
						lua->new_usertype < Client > ("client", "addReliableCommand", &CL_AddReliableCommand
										// "disconnect", &CL_Disconnect_f, // "reconnect", &CL_Reconnect_f, );
				}
		};
};

#endif
