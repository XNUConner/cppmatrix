#ifndef STATE_CPP_INCLUDE_
#define STATE_CPP_INCLUDE_
#include "SyncStateEvent.cpp"
class State {
public:
	std::vector<SyncStateEvent> events;

	State() {}

	State(json state_json) {
		for(auto event_json : state_json["events"])
			events.push_back(SyncStateEvent(event_json));
	}
};
#endif // STATE_CPP_INCLUDE_
