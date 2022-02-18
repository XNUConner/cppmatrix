#ifndef APICALL_CPP
#define APICALL_CPP
#include "curl/all.hpp"
#include "json/all.hpp"

// Base APICall(), overloads will call this function.
json APICall(const HTTPMethod method, const std::string homeserver, const std::string endpoint, curl_tools* tools) {
	// Set CURL method
	set_curl_options_for_method(method, tools);

	// Set API call URL
	std::string url = homeserver + endpoint;
	curl_easy_setopt( tools->curl, CURLOPT_URL, url.c_str() ); 

	// Perform API call
	CURLcode res = curl_easy_perform(tools->curl);

	json j;
	if(res != CURLE_OK) {
		std::cerr << "[ERROR] call_API(): curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
		clear_HTTP_Response(tools->res);
		return j;
	}
	
	// Get status code from response
	int status_code;
	curl_easy_getinfo(tools->curl, CURLINFO_RESPONSE_CODE, &status_code);
	if(status_code != 200) {
		std::cerr << "[ERROR] call_API(): status_code != 200 (" << homeserver << endpoint << ") sent " << status_code << std::endl;
		clear_HTTP_Response(tools->res);
		return j;
	}

	// get json from response
	try {
		j = json::parse(tools->res->data);
	} catch (std::exception& e) {
		std::cerr << "[ERROR] call_API(): json::parse() failed: " << e.what() << std::endl;
	}

	clear_HTTP_Response(tools->res);
	return j;
}

// OVERLOAD: Meant for GET only + HTTP fields
json APICall(const HTTPMethod method, const std::map<std::string, std::string> http_fields, const std::string homeserver, const std::string endpoint, curl_tools* tools) {

	// set curl HTTP headers:
	struct curl_slist* slist = create_slist(http_fields);
	curl_easy_setopt(tools->curl, CURLOPT_HTTPHEADER, slist);

	// Perform request:
	json j = APICall(method, homeserver, endpoint, tools);

	// Free HTTP headers:
	curl_slist_free_all(slist);

	return j;
}

// OVERLOAD: Meant for GET only + HTTP fields + URL Query Parameters
json APICall(const HTTPMethod method, const std::map<std::string, std::string> http_fields, const std::vector<std::pair<std::string, std::string>> queryParams, const std::string homeserver, const std::string endpoint, curl_tools* tools) {
	if(method != GET) std::cerr << "[WARNING]: APICall(): Using POST on an overload meant for GET" << std::endl;
	
	std::string query;
	for(int i=0;i<queryParams.size();i++) {
		std::string key = queryParams[i].first;
		std::string val = queryParams[i].second;

		// TODO: test +=
		if(i == 0)
			query = "?";
		else
			query = query + "&";

		query = query + key + "=" + val;
	}

	return APICall(method, http_fields, homeserver, endpoint+query, tools);
}


// OVERLOAD: Meant for POST only + JSON postfields
json APICall(const HTTPMethod method, json postfields, const std::string homeserver, const std::string endpoint, curl_tools* tools) {
	if(method != POST) std::cerr << "[WARNING]: APICall(): Using GET on an overload meant for POST" << std::endl;

	// Set request to serialized json postfields:
	std::string serialized = postfields.dump();
	tools->req->data = (char*)serialized.c_str();
	tools->req->size = serialized.size(); // TODO: Why do we need size in request? It will always be a char*

	// Perform request:
	json j = APICall(method, homeserver, endpoint, tools);

	return j;
}
#endif // APICALL_CPP
