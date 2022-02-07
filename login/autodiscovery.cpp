#ifndef AUTODISCOVERY_CPP_INCLUDE_
#define AUTODISCOVERY_CPP_INCLUDE_
#include<iostream>
#include<cstring>
#include<algorithm>
#include<curl/curl.h>

std::string get_hostname_for_id(std::string matrix_id, Matrix* m) {

	// Extract userid and homeserver from matrix ID (split at last :)
	std::size_t index = matrix_id.find(":");
	std::string user_id = matrix_id.substr(0, index);
	std::string homeserver = matrix_id.substr(index+1);

	// set id.user in m struct
	m->id.user = user_id;

	// subdomain.homeserver.com -> homeserver.com
	std::size_t first_dot  = homeserver.find('.');
	std::size_t second_dot = homeserver.find(first_dot, '.');

	if(second_dot == std::string::npos) return homeserver;

	std::string hostname = homeserver.substr(first_dot+1);
	return hostname;
}

bool validateBaseURL(std::string base_url, std::string endpoint, CURL* curl) {
	int status_code = get_request(base_url, endpoint, curl);

	if(status_code == 200)
		return true;

	std::cerr << "[WARNING] validateBaseURL() failed. Likely a configuration error by the homeserver." << std::endl;
	return false;
}

void autodiscovery(std::string matrix_id, Matrix* m, curl_tools* tools) {
	std::string endpoint = "/.well-known/matrix/client";
	// https://spec.matrix.org/v1.1/client-server-api/#well-known-uri

	std::string hostname = get_hostname_for_id(matrix_id, m);

	int status_code = get_request(hostname, endpoint, tools->curl);

	switch(status_code) {
		case 200:
		{
			json res = json::parse(tools->res->data);
			clear_HTTP_Response(tools->res);

			std::string home_baseurl = res["m.homeserver"]["base_url"];
			if( validateBaseURL(home_baseurl, "/_matrix/client/versions", tools->curl) )
				m->homeserver.base_url = home_baseurl;
			else
				m->homeserver.base_url = hostname;

			std::string identity_baseurl = res["m.identity_server"]["base_url"];
			if( validateBaseURL(identity_baseurl, "/_matrix/identity/v2", tools->curl) )
				m->identity_server.base_url = identity_baseurl;

			clear_HTTP_Response(tools->res);
			break;
		}

		default:
		{
			std::cerr << "[WARNING] autodiscovery(): GET request was unsuccessful (" << status_code << ")" << std::endl;
			m->homeserver.base_url = hostname;
		}
	} 
}
#endif // AUTODISCOVERY_CPP_INCLUDE_
