#ifndef ROOMS_CPP_INCLUDE_
#define ROOMS_CPP_INCLUDE_
#include "Room.cpp"
struct Rooms {
	std::map<std::string, Room> invite;
	std::map<std::string, Room> join;
	std::map<std::string, Room> knock;
	std::map<std::string, Room> leave;

	Rooms() {}

	Rooms(json rooms_json) {
		json invite_json = rooms_json["invite"];
		json join_json   = rooms_json["join"];
		json knock_json  = rooms_json["knock"];
		json leave_json  = rooms_json["leave"];

		for(const auto& room : invite_json.items())
			invite[room.key()] = Room(room.value());

		for(const auto& room : join_json.items())
			join[room.key()] = Room(room.value());

		for(const auto& room : knock_json.items())
			knock[room.key()] = Room(room.value());

		for(const auto& room : leave_json.items())
			leave[room.key()] = Room(room.value());
	}
};
#endif // ROOMS_CPP_INCLUDE_
