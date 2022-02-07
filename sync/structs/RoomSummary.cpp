#ifndef ROOMSUMMARY_CPP_INCLUDE_
#define ROOMSUMMARY_CPP_INCLUDE_
class RoomSummary {
public:
	std::vector<std::string> m_heros;
	int m_invited_member_count;
	int m_joined_member_count;

	RoomSummary() {}

	RoomSummary(json j) {
		for(auto hero : j["m.heros"])
			m_heros.push_back(hero);

		if(j.contains("m.invited_member_count"))
			m_invited_member_count = (int) j["m.invited_member_count"];
		else
			m_invited_member_count = {};

		if(j.contains("m.joined_member_count"))
			m_joined_member_count  = (int) j["m.joined_member_count"];
		else
			m_joined_member_count = {};
	}
};
#endif // ROOMSUMMARY_CPP_INCLUDE_
