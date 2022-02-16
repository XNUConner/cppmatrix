#include<map>
std::string getRoomSelection(const Rooms& rooms) {
	// Create array of rooms.join.first (Room address) 
	std::vector<std::string> j;
	for(const auto& room : rooms.join) {
		j.push_back(room.first);
		std::cout << j.size() << ") " << j.back() << std::endl;
	}

	int x = -1;
	while(x <= 0 && x > rooms.join.size()) {
		std::cout << "Select room to enter:" << std::endl;
		std::cin >> x;
	}

	return j[x-1];
}
