#ifndef SYNCSTATEEVENT_CPP_INCLUDE_
#define SYNCSTATEEVENT_CPP_INCLUDE_
#include "EventContent.cpp"
#include "UnsignedData.cpp"
struct SyncStateEvent {
	json content;
	std::string event_id;
	int origin_server_ts;
	EventContent prev_content;
	std::optional<std::string> sender;
	std::string state_key;
	std::optional<std::string> type;
	UnsignedData _unsigned;

	SyncStateEvent() {}

	SyncStateEvent(json j) {
		content   = j["content"];
		event_id  = j["event_id"];
		origin_server_ts = (int)j["origin_server_ts"];
		prev_content = EventContent(j["prev_content"]);

		if(j.contains("sender"))
			sender = j["sender"];
		else
			sender = {};

		state_key = j["state_key"];

		if(j.contains("type"))
			type = j["type"];
		else
			type = {};

		_unsigned = UnsignedData(j["unsigned"]);
	} 
};
#endif // SYNCSTATEEVENT_CPP_INCLUDE_
