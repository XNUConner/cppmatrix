#ifndef INVITE_CPP_INCLUDE_
#define INVITE_CPP_INCLUDE_
#include "Signed.cpp"
class Invite {
public:
	std::optional<std::string> display_name;
	Signed _signed;

	Invite() {}

	Invite(json j) {
		if(j.contains("display_name"))
			display_name = j["display_name"];
		else
			display_name = {};
		_signed      = Signed(j["signed"]);
	}
};
#endif // INVITE_CPP_INCLUDE_
