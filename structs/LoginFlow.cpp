#ifndef LOGINFLOW_CPP
#define LOGINFLOW_CPP
#include "IdentityProvider.cpp"
struct LoginFlow {
	std::string type;
	std::vector<IdentityProvider> identity_providers;
	
	LoginFlow(json j) {
		type = j["type"];
		if(j.contains("identity_providers")) {
			for(json ip_json : j["identity_providers"])
				identity_providers.push_back(IdentityProvider(ip_json));
		}
	}

	LoginFlow() {}
};
#endif // LOGINFLOW_CPP
