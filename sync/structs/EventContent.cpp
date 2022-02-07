#ifndef EVENTCONTENT_CPP_INCLUDE_
#define EVENTCONTENT_CPP_INCLUDE_
#include "Membership.cpp"
#include "Invite.cpp"
class EventContent {
public:
	std::optional<std::string> avatar_url;
	std::optional<std::string> displayname;
	bool is_direct;
	std::optional<Membership> membership;
	std::string reason;
	Invite third_party_invite;

	EventContent() {}

	EventContent(json j) {
		if(j.contains("avatar_url"))
			avatar_url = j["avatar_url"];
		else
			avatar_url = {};

		if(j.contains("displayname"))
			displayname = j["displayname"];
		else
			displayname = {};

		if(j["is_direct"] == "true") 
			is_direct = true;
		else
			is_direct = false;

		if(j.contains("membership")) {
			std::string membership_type = j["membership"];
			if (membership_type == "invite")
				membership = invite;
			else if (membership_type == "join")
				membership = join;
			else if (membership_type == "knock")
				membership = knock;
			else if (membership_type == "leave")
				membership = leave;
			else if (membership_type == "ban")
				membership = ban;
		} else {
			membership = {};
		}

		if(j.contains("reason"))
			reason = j["reason"];
		else
			reason = {};

		third_party_invite = Invite(j["third_party_invite"]);
	}
};
#endif // EVENTCONTENT_CPP_INCLUDE_
