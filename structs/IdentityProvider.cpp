#ifndef IDENTITYPROVIDER_CPP
#define IDENTITYPROVIDER_CPP
struct IdentityProvider {
	std::string id;
	std::string name;
	std::string icon;
	std::string brand;

	IdentityProvider(json j) :
		id(j["id"]),
		name(j["name"]),
		icon(j["icon"]),
		brand(j["brand"]) {}
};
#endif // IDENTITYPROVIDER_CPP
