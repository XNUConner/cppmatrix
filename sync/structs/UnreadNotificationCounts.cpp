#ifndef UNREADNOTIFICATIONCOUNTS_CPP_INCLUDE_
#define UNREADNOTIFICATIONCOUNTS_CPP_INCLUDE_
class UnreadNotificationCounts {
public:
	std::optional<unsigned int> highlight_count;
	std::optional<unsigned int> notification_count;

	UnreadNotificationCounts() {}

	UnreadNotificationCounts(json j) {
		if(j.contains("highlight_count"))
			highlight_count = (unsigned int)j["highlight_count"];
		else
			highlight_count = {};

		if(j.contains("notification_count"))
			notification_count = (unsigned int)j["notification_count"];
		else
			notification_count = {};
	}
};
#endif // UNREADNOTIFICATIONCOUNTS_CPP_INCLUDE_
