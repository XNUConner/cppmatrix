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
#include "format/fmtMessageBody.cpp"

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
	std::map<std::string, std::string> fields;
	fields["Authorization"] = "Bearer " + m.login.token;

	std::cout << "Syncing..." << std::endl;
	json j = APICall(GET, fields, m.homeserver.base_url, "/_matrix/client/v3/sync", tools); 
	
	Rooms rooms(j["rooms"]);
	std::string next_batch = j["next_batch"];

	// Get room choice
	std::string room = getRoomSelection(rooms);

	while(1) {
		// Messages for room
		std::vector<SyncRoomEvent> sre_vec = rooms.join[room].timeline.events;
		for(SyncRoomEvent sre : sre_vec) {
			if(sre.type == "m.room.message") {
				if(sre.content["msgtype"] == "m.text") {
					std::string body = sre.content["body"];
					fmtMessageBody(body);
					std::cout << sre.content["displayname"] << "(" << sre.sender.value() << "):" << std::endl;
					std::cout << body << std::endl;
					std::cout << std::endl;
				}
			}
		}

		std::vector< std::pair<std::string, std::string> > queryParams = 
		{ 
			std::make_pair("since", next_batch),
			std::make_pair("timeout", "500")
		 };

		j = APICall(GET, fields, queryParams, m.homeserver.base_url, "/_matrix/client/v3/sync", tools);
		rooms = Rooms(j["rooms"]);
		next_batch = j["next_batch"];
	}

	destroy_curl_tools(tools);
}
