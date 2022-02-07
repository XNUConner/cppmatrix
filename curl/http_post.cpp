#ifndef HTTP_POST_CPP_INCLUDE_
#define HTTP_POST_CPP_INCLUDE_
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<curl/curl.h>

#include "http_response.cpp"
#include "http_request.cpp"

// Returns response status code
int post_request(std::string homeserver, std::string endpoint, curl_tools* tools) {
	std::string url = homeserver + endpoint;
	std::cout << url << std::endl;
	CURLcode res;
	long status_code;

	curl_easy_setopt(tools->curl, CURLOPT_URL, url.c_str());
	curl_easy_setopt(tools->curl, CURLOPT_POST, 1L);
	curl_easy_setopt(tools->curl, CURLOPT_POSTFIELDS, tools->req->data);

	res = curl_easy_perform(tools->curl);

	if(res != CURLE_OK) {
		std::cerr << "[ERROR] post_request(): curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
		return -1;
	}

	curl_easy_getinfo(tools->curl, CURLINFO_RESPONSE_CODE, &status_code);
	return status_code;
}
#endif // HTTP_POST_CPP_INCLUDE_
