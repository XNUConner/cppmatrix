#ifndef HTTP_RESPONSE_H_INCLUDE_
#define HTTP_RESPONSE_H_INCLUDE_
#include<cstring>
#include<stdlib.h>
#include<curl/curl.h>

typedef struct HTTP_Response {
  char *data;
  size_t size;
} HTTP_Response;

HTTP_Response* init_HTTP_Response(void) {
	struct HTTP_Response* res;
	res = (HTTP_Response*)malloc(sizeof(HTTP_Response));
	res->data = (char*)malloc(1);
	res->size = 0;
	return res;
}

void destroy_HTTP_Response(HTTP_Response* res) {
	if(!res) return;
	if(res->data) free(res->data);
	free(res);
}

void clear_HTTP_Response(HTTP_Response* res) {
	res->data = (char*)realloc(res->data, 1);
	res->size = 0;
}
 
// From https://curl.se/libcurl/c/getinmemory.html:
static size_t WriteMemoryCallback(char *src, size_t size, size_t nmemb, void *dest)
{
	HTTP_Response *dest_cast = (HTTP_Response*) dest;

	size_t dest_size = dest_cast->size;    // Number of bytes already in memory.
	size_t additional_size = size * nmemb; // Number of bytes to be written to memory.

	dest_cast->data = (char*) realloc( dest_cast->data, dest_size+additional_size+1 );
	memcpy( dest_cast->data+dest_size, src, additional_size );
	dest_cast->size += additional_size;
	dest_cast->data[dest_size+additional_size] = '\0';

	return additional_size;
}
#endif // HTTP_RESPONSE_H_INCLUDE_
