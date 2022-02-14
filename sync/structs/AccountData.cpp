#ifndef ACCOUNTDATA_CPP_INCLUDE_
#define ACCOUNTDATA_CPP_INCLUDE_
#include "Event.cpp"
struct AccountData {
	std::vector<Event> events;

	AccountData() {}
	
	AccountData(json j) {
		for(auto event_json : j["events"])
			events.push_back( Event(event_json) );
	}
};
#endif // ACCOUNTDATA_CPP_INCLUDE_
