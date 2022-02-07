#ifndef ACCESS_TOKEN_CPP_INCLUDE_
#define ACCESS_TOKEN_CPP_INCLUDE_
#include <iostream>
#include <fstream>
void write_access_token_file(std::string token) {
	std::ofstream f (".access_token");
	if(!f.is_open()) return;

	f << token;
	f.close();
}

std::string read_access_token_file() {
	std::string token;
	std::ifstream f (".access_token");
	if(!f.is_open())
		std::cerr << "[ERROR] read_access_token_file(): Failed to open .access_token file" << std::endl;
	else
		std::getline(f, token);

	return token;
}

#endif // ACCESS_TOKEN_CPP_INCLUDE_
