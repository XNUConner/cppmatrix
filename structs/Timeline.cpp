#ifndef TIMELINE_CPP_INCLUDE_
#define TIMELINE_CPP_INCLUDE_
#include "SyncRoomEvent.cpp"
struct Timeline {
	std::vector<SyncRoomEvent> events;
	bool limited;
	std::string prev_batch;

	Timeline() {}

	Timeline(json j) {
		for(auto sre_json : j["events"])
			events.push_back( SyncRoomEvent(sre_json) );
		
		if(j["limited"] == "true")
			limited = true;
		else
			limited = false;

		prev_batch = j["prev_batch"];
	}
};
#endif // TIMELINE_CPP_INCLUDE_
