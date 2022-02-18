#ifndef METHOD_OPTIONS_CPP
#define METHOD_OPTIONS_CPP
enum HTTPMethod { GET, POST };
void set_curl_options_for_method(const HTTPMethod method, curl_tools* tools) {
	switch(method) {
		case GET:
			curl_easy_setopt(tools->curl, CURLOPT_HTTPGET, 1L);
			break;
		case POST:
			curl_easy_setopt(tools->curl, CURLOPT_POST, 1L);
			curl_easy_setopt(tools->curl, CURLOPT_POSTFIELDS, tools->req->data);
			break;
	}
}
#endif // METHOD_OPTIONS_CPP
