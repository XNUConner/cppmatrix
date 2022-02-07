#ifndef ROOM_CPP_INCLUDE_
#define ROOM_CPP_INCLUDE_
#include "AccountData.cpp"
#include "Ephemeral.cpp"
#include "State.cpp"
#include "RoomSummary.cpp"
#include "Timeline.cpp"
#include "UnreadNotificationCounts.cpp"
class Room {
public:
	AccountData account_data;
	Ephemeral ephemeral;
	std::optional<unsigned int> org_matrix_msc2654_unread_count;
	State state;
	RoomSummary summary;
	Timeline timeline;
	UnreadNotificationCounts unread_notifications;

	Room() {}

	Room(json j) {
		account_data = AccountData(j["account_data"]);
		ephemeral    = Ephemeral(j["ephemeral"]);

		if(j.contains("org.matrix.msc2654.unread_count"))
			org_matrix_msc2654_unread_count = (unsigned int)j["org.matrix.msc2654.unread_count"];
		else
			org_matrix_msc2654_unread_count = {};

		state        = State(j["state"]);
		summary      = RoomSummary(j["summary"]);
		timeline     = Timeline(j["timeline"]);
		unread_notifications = UnreadNotificationCounts(j["unread_notifications"]);
	}
};
#endif // ROOM_CPP_INCLUDE_
