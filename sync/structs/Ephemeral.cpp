#ifndef EPHEMERAL_CPP_INCLUDE_
#define EPHEMERAL_CPP_INCLUDE_
#include "Event.cpp"
class Ephemeral {
public:
	std::vector<Event> events;

	Ephemeral() {}

	Ephemeral(json j) {
		for(auto event_json : j["events"])
			events.push_back( Event(event_json) );
	}
};
#endif // EPHEMERAL_CPP_INCLUDE_
