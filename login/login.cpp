#ifndef LOGIN_CPP_INCLUDE_
#define LOGIN_CPP_INCLUDE_
#include<vector>
#include<unistd.h>
#include<map>
#include "device_id.cpp"
#include "access_token.cpp"

std::vector<std::string> get_supported_login_types(Matrix* m, curl_tools* tools) {
	CURL *curl = tools->curl;
	HTTP_Response *res = tools->res;
	std::string homeserver = m->homeserver.base_url;
	std::string endpoint   = "/_matrix/client/v3/login";
	int status_code = get_request(homeserver, endpoint, curl);

	std::vector<std::string> supported_types;
	switch(status_code) {
		case 200:
			{
				// Server responded with login types it supports.
				json data = json::parse(res->data);
				if(!data.contains("flows")) break;
				json flows = data["flows"];
				for(int i=0;i<flows.size();i++) {
					if(flows[i].contains("type"))
						supported_types.push_back(flows[i]["type"]);
				}
				break;
			}
		case 429:
			{
				// 429: rate limited, try again in retry_after_ms milliseconds.
				json data = json::parse(res->data);
				long retry_ms = data["retry_after_ms"];
				std::cerr << "get_supported_login_types() was rate limited, retrying in " << retry_ms << "ms" << std::endl;
				usleep(retry_ms * 1000);
				return get_supported_login_types(m, tools);
				break;
			}
	}
	clear_HTTP_Response(tools->res);
	return supported_types;
}

std::string prompt_user_for_login_type(std::vector<std::string> types) {
	int sel = -1;
	while(sel < 1 || sel > types.size()) {
		for(int i=0;i<types.size();i++)
			std::cout << i+1 << ") " << types[i] << std::endl;
		std::cout << "Select login type: ";
		std::cin >> sel;
	}
	return types[sel-1];
}

json build_login_json(std::string login_type, std::map<std::string, std::string> logindata) {

	json login_json;

	if(login_type == "m.login.password") {
		login_json["identifier"] = {};
		login_json["identifier"]["type"] = "m.id.user";
		login_json["identifier"]["user"] = logindata["user"];
		login_json["initial_device_display_name"] = logindata["initial_device_display_name"];
		login_json["password"] = logindata["password"];

	} else if(login_type == "m.login.token") {
		login_json["token"] = logindata["token"];
	}

	login_json["type"] = login_type;

	return login_json;
}

std::string get_password() {
	std::string password;
	std::cout << "Enter password: ";
	std::cin >> password;
	return password;
}

void login(Matrix* m, curl_tools* tools) {

	std::string homeserver = m->homeserver.base_url;
	std::string identity_server = m->identity_server.base_url;
	std::string endpoint = "/_matrix/client/v3/login";
	std::string device_id;
	std::string access_token;
	json login_json;
	json login_response;
	
	std::map<std::string, std::string> logindata;
	std::vector<std::string> supported_login_types;
	std::string type;
	std::string post_data;

	supported_login_types = get_supported_login_types(m, tools);
	type = prompt_user_for_login_type(supported_login_types);


	// Create login request to POST to /_matrix/client/v3/login
	while(type != "m.login.password" && type != "m.login.token") {
		std::cerr << "[ERROR] login(): Selected login type unsupported by this client." << std::endl;
		std::cerr << "Please select a different login type:" << std::endl;
		type = prompt_user_for_login_type(supported_login_types);
	}

	logindata.insert( std::make_pair("user", m->id.user) );
	logindata.insert( std::make_pair("initial_device_display_name", "Matrix CLI") );
	logindata.insert( std::make_pair("type", type) );

	if(type == "m.login.password") {
		logindata.insert( make_pair("password", get_password()) );
	} else if(type == "m.login.token") {
		logindata.insert( make_pair("token", read_access_token_file()) );
		logindata.insert( make_pair("device_id", read_device_id_file()) );
	}

	login_json = build_login_json(type, logindata);

	// Set curl HTTP request body to our login json
	post_data = login_json.dump();
	std::cout << login_json.dump(4) << std::endl;

	// TODO: post_data should be like response, but request in http_request.cpp
	tools->req->data = post_data.c_str();
	tools->req->size = post_data.size();
	post_request(m->homeserver.base_url, "/_matrix/client/v3/login", tools);
	
	// TODO: Error check json response
	login_response = json::parse(tools->res->data);
	clear_HTTP_Response(tools->res);

	std::cout << "Response:\n" << login_response << "\n";
	access_token = login_response["access_token"];
	device_id = login_response["device_id"];

	write_device_id_file(device_id);
	write_access_token_file(access_token);

	m->login.token = access_token;

}
#endif // LOGIN_CPP_INCLUDE_
