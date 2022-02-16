#ifndef PRESENCE_CPP_INCLUDE_
#define PRESENCE_CPP_INCLUDE_
#include "Event.cpp"
struct Presence {
	std::vector<Event> events;
	
	Presence() {}

	Presence(json j) {
		for(auto event_json : j["events"])
			events.push_back( Event(event_json) );
	}

};
#endif // PRESENCE_CPP_INCLUDE_
