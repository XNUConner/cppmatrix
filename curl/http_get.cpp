#ifndef HTTP_GET_CPP_INCLUDE_
#define HTTP_GET_CPP_INCLUDE_
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<curl/curl.h>

#include "http_response.cpp"

// Returns response status code
int get_request(std::string homeserver, std::string endpoint, CURL *curl) {
	std::string url = homeserver + endpoint;
	CURLcode res;
	long status_code;

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);

	res = curl_easy_perform(curl);

	if(res != CURLE_OK) {
		std::cerr << "[ERROR] get_request(): curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
		return -1;
	}

	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status_code);
	return status_code;
}

int get_request(std::string homeserver, std::string endpoint, std::map<std::string, std::string> fields, CURL *curl) {
	std::string url = homeserver + endpoint;
	CURLcode res;
	long status_code;

	curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);

	// Create list
	struct curl_slist *slist = NULL;
	for(auto field : fields) {
		std::string s = field.first + ": " + field.second;
		auto head = curl_slist_append( slist, s.c_str() );
		if(!slist) slist = head;
	}

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, slist);

	res = curl_easy_perform(curl);

	curl_slist_free_all(slist);

	if(res != CURLE_OK) {
		std::cerr << "[ERROR] get_request(): curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
		return -1;
	}

	curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &status_code);
	return status_code;
}
#endif // HTTP_GET_CPP_INCLUDE_
