#ifndef APICALL_CPP
#define APICALL_CPP
#include<bits/stdc++.h>
#include "curl/all.hpp"
#include "json/all.hpp"
#include "structs/meta/SyncData.cpp"

enum HTTPMethod { GET, POST };
void set_curl_options_for_method(const HTTPMethod method, CURL* curl) {
	switch(method) {
		case GET:
			curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
			break;
		case POST:
			curl_easy_setopt(curl, CURLOPT_POST, 1L);
			break;
	}
}

template<typename T>
void APICall(const HTTPMethod method, T& obj, const std::string homeserver, const std::string endpoint, const curl_tools* tools) {
	// Set CURL method
	set_curl_options_for_method(method, tools->curl);

	// Set API call URL
	std::string url = homeserver + endpoint;
	curl_easy_setopt( tools->curl, CURLOPT_URL, url.c_str() ); 

	// Perform API call
	CURLcode res = curl_easy_perform(tools->curl);

	if(res != CURLE_OK) {
		std::cerr << "[ERROR] call_API(): curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
		return;
	}
	
	// Get status code from response
	int status_code;
	curl_easy_getinfo(tools->curl, CURLINFO_RESPONSE_CODE, &status_code);
	if(status_code != 200) {
		std::cerr << "[ERROR] call_API(): status_code != 200 (" << homeserver << endpoint << ")" << std::endl;
		return;
	}

	// get json from response
	json j;
	try {
		j = json::parse(tools->res->data);
	} catch (std::exception& e) {
		std::cerr << "[ERROR] call_API(): JSON::parse() failed: " << e.what() << std::endl;
		return;
	}

	// construct obj from json
	obj = T(j);

}

struct curl_slist* create_slist(const std::map<std::string, std::string> http_fields);

template<typename T>
void APICall(const HTTPMethod method, const std::map<std::string, std::string> http_fields, T& obj, const std::string homeserver, const std::string endpoint, const curl_tools* tools) {

	// set curl HTTP headers:
	struct curl_slist* slist = create_slist(http_fields);
	curl_easy_setopt(tools->curl, CURLOPT_HTTPHEADER, slist);

	// Perform request:
	APICall(method, obj, homeserver, endpoint, tools);

	// Free HTTP headers:
	curl_slist_free_all(slist);

}

struct curl_slist* create_slist(const std::map<std::string, std::string> http_fields) {

	struct curl_slist *slist = NULL;

	for(const auto kv : http_fields) {
		std::string field = kv.first + ": " + kv.second;
		
		if(!slist)
			slist = curl_slist_append( slist, field.c_str() );
		else
			curl_slist_append( slist, field.c_str() );

	}

	return slist;
}
#endif // APICALL_CPP
