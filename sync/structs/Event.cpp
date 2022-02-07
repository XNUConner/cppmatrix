#ifndef EVENT_CPP_INCLUDE_
#define EVENT_CPP_INCLUDE_
class Event {
public:
	json content;
	std::optional<std::string> type;
	std::optional<std::string> sender;

	Event() {}

	Event(json j) {
		content = j["content"];

		if(j.contains("type"))
			type = j["type"];
		else
			type = {};

		if(j.contains("sender"))
			sender = j["sender"];
		else
			sender = {};
	}
};
#endif // EVENT_CPP_INCLUDE_
