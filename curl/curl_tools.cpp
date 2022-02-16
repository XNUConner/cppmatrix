#ifndef CURL_TOOLS_CPP_INCLUDE_
#define CURL_TOOLS_CPP_INCLUDE_
#include<iostream>
#include "http_response.cpp"
#include "http_request.cpp"
typedef struct curl_tools {
	CURL* curl;
	HTTP_Response* res;
	HTTP_Request* req;
} curl_tools;

void set_curl_tools_opts(curl_tools* tools) {
	CURL *curl = tools->curl;
	HTTP_Response *res = tools->res;
	HTTP_Request *req = tools->req;
	
	// Set options:
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void*)res);
	curl_easy_setopt(curl, CURLOPT_READFUNCTION, ReadMemoryCallback);
	curl_easy_setopt(curl, CURLOPT_READDATA, (void*)req->data);
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
}

static struct curl_tools* init_curl_tools() {
	CURL *curl;
	HTTP_Response *res;
	HTTP_Request *req;
	curl_tools* tools;

	curl = curl_easy_init();
	if(!curl) {
		std::cerr << "[FATAL] init_curl_tools(): Failed to initialize curl." << std::endl;
		return NULL;
	}

	res = init_HTTP_Response();
	req = init_HTTP_Request();

	// Put tools into struct and return
	tools = (curl_tools*)malloc(sizeof(curl_tools));
	tools->curl = curl;
	tools->res = res;
	tools->req = req;

	set_curl_tools_opts(tools);

	return tools;
}

void destroy_curl_tools(curl_tools* tools) {
	if(!tools) return;

	if(tools->req)
		destroy_HTTP_Request(tools->req);

	if(tools->res)
		destroy_HTTP_Response(tools->res);

	if(tools->curl)
		curl_easy_cleanup(tools->curl);
	
	free(tools);
}

#endif // CURL_TOOLS_CPP_INCLUDE_
