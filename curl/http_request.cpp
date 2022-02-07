#ifndef HTTP_REQUEST_CPP_INCLUDE_
#define HTTP_REQUEST_CPP_INCLUDE_
#include<cstring>
#include<stdlib.h>
#include<curl/curl.h>

typedef struct HTTP_Request {
  char *data;
  size_t size;
} HTTP_Request;

HTTP_Request* init_HTTP_Request(void) {
	struct HTTP_Request* req;
	req = (HTTP_Request*)malloc(sizeof(HTTP_Request));
	req->data = (char*)malloc(1);
	req->size = 0;
	return req;
}

void destroy_HTTP_Request(HTTP_Request* req) {
	if(!req) return;
	if(req->data) free(req->data);
	free(req);
}
 
// From https://curl.se/libcurl/c/getinmemory.html:
static size_t ReadMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	char* readhere = (char*)userp;
	curl_off_t nread;
	
	strcpy((char*)contents, readhere);
	return strlen((char*)contents);
}
#endif // HTTP_REQUEST_CPP_INCLUDE_
