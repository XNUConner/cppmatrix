#include<iostream>
#include<cstring>
#include<curl/curl.h>

#include "matrix/matrix.cpp"
#define JSON_DIAGNOSTICS 1
#include "json/all.hpp"
#include "curl/all.hpp"
#include "login/all.hpp"
#include "sync/sync.cpp"
#include "input/room_selection.cpp"

#include "APICall.cpp"

int main(void) {
	Matrix m;
	std::string matrix_id = "b2100k:matrix.org";

	curl_tools *tools = init_curl_tools();
	
	// Autodiscovery
	autodiscovery(matrix_id, &m, tools);
	
	// Login
	login(&m, tools);

	// Sync
	SyncData sd;

	std::map<std::string, std::string> fields;
	fields["Authorization"] = "Bearer " + m.login.token;

	APICall(GET, fields, sd, m.homeserver.base_url, "/_matrix/client/v3/sync", tools); 

	// Get room choice
	std::string room = getRoomSelection(sd.rooms);

	destroy_curl_tools(tools);
}
