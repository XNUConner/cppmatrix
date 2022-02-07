#ifndef DEVICE_ID_CPP_INCLUDE_
#define DEVICE_ID_CPP_INCLUDE_
#include <iostream>
#include <fstream>
void write_device_id_file(std::string id) {
	std::ofstream f (".device_id");
	if(!f.is_open()) return;

	f << id;
	f.close();
}

std::string read_device_id_file() {
	std::string id;
	std::ifstream f (".device_id");
	if(!f.is_open())
		std::cerr << "[ERROR] read_device_id_file(): Failed to open .device_id file" << std::endl;
	else
		std::getline(f, id);

	return id;
}

#endif // DEVICE_ID_CPP_INCLUDE_
