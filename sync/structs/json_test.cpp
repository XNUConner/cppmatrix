#include<bits/stdc++.h>
#define JSON_DIAGNOSTICS 1
#include "json/all.hpp"
#include "AccountData.cpp"
#include "Presence.cpp"
#include "Rooms.cpp"
int main(void) {
	std::ifstream f("sync.json");
	std::string raw;
	std::stringstream buffer;
	buffer << f.rdbuf();
	raw = buffer.str();
	json obj;
	try {
		obj = json::parse(raw.c_str());
	}
	catch(json::exception& e) {
		std::cout << "[ERROR]: " << e.what() << "\n";
	}
	
	f.close();

	AccountData acc_data(obj["account_data"]);
	std::cout << acc_data << "\n";
	std::string next_batch = obj["next_batch"];
	Presence presence(obj["presence"]);
	Rooms rooms(obj["rooms"]);
	
}
