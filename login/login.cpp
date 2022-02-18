#ifndef LOGIN_CPP_INCLUDE_
#define LOGIN_CPP_INCLUDE_
#include<vector>
#include<unistd.h>
#include<map>
#include "device_id.cpp"
#include "access_token.cpp"

#include "../APICall.cpp"
#include "../structs/LoginFlow.cpp"

std::vector<LoginFlow> get_supported_login_types(Matrix* m, curl_tools* tools) {

	json j = APICall(GET, m->homeserver.base_url, "/_matrix/client/v3/login", tools);

	std::vector<LoginFlow> flows;
	for(json lf_json : j["flows"])
		flows.push_back(LoginFlow(lf_json));

	return flows;
}

LoginFlow prompt_user_for_login_type(std::vector<LoginFlow> flows) {

	int sel = -1;

	while(sel < 1 || sel > flows.size()) {
		for(int i=0;i<flows.size();i++)
			std::cout << i+1 << ") " << flows[i].type << std::endl;

		std::cout << "Select login type: ";
		std::cin >> sel;
	}

	LoginFlow flow = flows[sel-1];
	while(flow.type != "m.login.password" && flow.type != "m.login.token") {
		std::cerr << "[ERROR] login(): Selected login type unsupported by this client." << std::endl;
		std::cerr << "Please select a different login type:" << std::endl;
		flow = prompt_user_for_login_type(flows);
	}

	return flow;
}

std::string get_password() {
	std::string password;
	std::cout << "Enter password: ";
	std::cin >> password;
	return password;
}

json build_login_json(Matrix* m, LoginFlow flow) {

	std::map<std::string, std::string> logindata;
	logindata.insert( std::make_pair("user", m->id.user) );
	logindata.insert( std::make_pair("initial_device_display_name", "Matrix CLI") );
	logindata.insert( std::make_pair("type", flow.type) );

	if(flow.type == "m.login.password") {
		logindata.insert( std::make_pair("password", get_password()) );
	} else if(flow.type == "m.login.token") {
		logindata.insert( std::make_pair("token", read_access_token_file()) );
		logindata.insert( std::make_pair("device_id", read_device_id_file()) );
	}

	json login_json;
	if(flow.type == "m.login.password") {
		login_json["identifier"] = {};
		login_json["identifier"]["type"] = "m.id.user";
		login_json["identifier"]["user"] = logindata["user"];
		login_json["initial_device_display_name"] = logindata["initial_device_display_name"];
		login_json["password"] = logindata["password"];

	} else if(flow.type == "m.login.token") {
		login_json["token"] = logindata["token"];
	}

	login_json["type"] = flow.type;

	return login_json;
}

void login(Matrix* m, curl_tools* tools) {

	std::vector<LoginFlow> flows = get_supported_login_types(m, tools);
	LoginFlow flow = prompt_user_for_login_type(flows);

	json login_json = build_login_json(m, flow);
	json j = APICall(POST, login_json, m->homeserver.base_url, "/_matrix/client/v3/login", tools);

	std::string access_token = j["access_token"];
	std::string device_id = j["device_id"];

	m->login.token = access_token;

	write_device_id_file(device_id);
	write_access_token_file(access_token);

}
#endif // LOGIN_CPP_INCLUDE_
