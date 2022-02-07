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
	
	// sets m.id.user
	// sets m.homeserver.base_url
	// sets m.identity_server.base_url
	autodiscovery(matrix_id, &m, tools);
	
	std::cout << m.id.user << std::endl;
	std::cout << m.homeserver.base_url << std::endl;
	std::cout << m.identity_server.base_url << std::endl;

	login(&m, tools);

	std::cout << m.login.token << std::endl;

	sync(&m, tools);

	std::cout << "[DEBUG] destroy_curl_tools()" << std::endl;
	destroy_curl_tools(tools);
	return 0;
}
