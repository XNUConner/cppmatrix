#ifndef SIGNATURES_CPP_INCLUDE_
#define SIGNATURES_CPP_INCLUDE_
#include<string>
#include <map>
class Signatures {
public:
	std::map<std::string, std::pair<std::string, std::string>> signatures;

	Signatures() {}

	Signatures(json j) {
		
		// for key in j signatures[<key>] = make_pair(value left, value right);
		/*
		{
		  "key":"06UzBknVHFMwgi7AVloY7ylC+xhOhEX4PkNge14Grl8",
		  "signatures": {
			"@user:example.com": {
			  "ed25519:EGURVBUNJP": "YbJva03ihSj5mPk+CHMJKUKlCXCPFXjXOK6VqBnN9nA2evksQcTGn6hwQfrgRHIDDXO2le49x7jnWJHMJrJoBQ"
			}
		  }
		}
		*/
	}
};
#endif // SIGNATURES_CPP_INCLUDE_
