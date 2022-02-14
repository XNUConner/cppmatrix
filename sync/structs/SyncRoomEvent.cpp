#ifndef SYNCROOMEVENT_CPP_INCLUDE_
#define SYNCROOMEVENT_CPP_INCLUDE_
#include "UnsignedData.cpp"
struct SyncRoomEvent {
	json content;
	std::string event_id;
	int origin_server_ts;
	std::optional<std::string> sender;
	std::optional<std::string> type;
	UnsignedData _unsigned;

	SyncRoomEvent() {}

	SyncRoomEvent(json j) {
		content = j["content"];
		event_id = j["event_id"];
		origin_server_ts = (int)j["origin_server_ts"];

		if(j.contains("sender"))
			sender = j["sender"];
		else
			sender = {};
		
		if(j.contains("type"))
			type = j["type"];
		else
			type = {};

		_unsigned = UnsignedData(j["unsigned"]);
	}
};
#endif // SYNCROOMEVENT_CPP_INCLUDE_
