#ifndef SYNCDATA_CPP
#define SYNCDATA_CPP
#include "../AccountData.cpp"
#include "../Presence.cpp"
#include "../Rooms.cpp"
/* Represents deserialized JSON from the response to our sync request. */
struct SyncData {
	AccountData accountdata;
	std::string next_batch;
	Presence    presence;
	Rooms       rooms;

	SyncData(json j) : 
		accountdata(j["account_data"]), 
		next_batch(j["next_batch"]),
		presence(j["presence"]),
		rooms(j["rooms"]) {}

	SyncData() {}
};
#endif // SYNCDATA_CPP
