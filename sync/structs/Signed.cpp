#ifndef SIGNED_CPP_INCLUDE_
#define SIGNED_CPP_INCLUDE
#include "Signatures.cpp"
class Signed {
public:
	std::optional<std::string> mxid;
	Signatures signatures;
	std::optional<std::string> token;

	Signed() {}
	
	Signed(json j) {
		if(j.contains("mxid"))
			mxid = j["mxid"];
		else
			mxid = {};

		signatures = Signatures(j["signatures"]);

		if(j.contains("token"))
			token = j["token"];
		else
			token = {};
	}
};
#endif // SIGNED_CPP_INCLUDE_
