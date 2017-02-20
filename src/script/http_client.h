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

// it's quite possible this is _way over the top_ but I've been toying
// with several ideas. - Victor

#ifndef __cplusplus
#error __file__ " is only available to C++"
#endif

#ifndef SCRIPT_RESTCLIENT_H
#define SCRIPT_RESTCLIENT_H

#include <iostream>
#include "../restclient/restclient.h"

namespace sol {
		class state;
};

namespace script {
		// no Exceptions at this time

		struct HttpClient
		{};

		namespace http_client
		{
				// using namespace RestClient;
				static inline void init(sol::state * lua) {
						lua->new_usertype < RestClient::Response > ("HttpResponse", "code", &RestClient::Response::code, "body", &RestClient::Response::body
										// "headers", &RestClient::Response::headers
							);

						lua->new_usertype < HttpClient > ("http", "get", &RestClient::get, "post", &RestClient::post, "put", &RestClient::put, "delete", &RestClient::del
							);
				}
		};
};

#endif
