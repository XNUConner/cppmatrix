#include<iostream>
#include<cstring>
#include<curl/curl.h>

#include "matrix/matrix.cpp"
#include "json/all.hpp"
#include "curl/all.hpp"
#include "login/all.hpp"
#include "sync/sync.cpp"

int main(void) {
	Matrix m;
	std::string matrix_id = "b2100k:matrix.org";

	curl_tools *tools = init_curl_tools();
	
	autodiscovery(matrix_id, &m, tools);
	
	login(&m, tools);

	SyncData sd = sync(&m, tools);

	Rooms rooms = sd.rooms;
	for(auto r : rooms.join) {
		std::cout << r.first << "\n";
	}

	destroy_curl_tools(tools);
	return 0;
}
