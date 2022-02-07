#ifndef UNSIGNEDDATA_CPP_INCLUDE_
#define UNSIGNEDDATA_CPP_INCLUDE_
class UnsignedData {
public:
	std::optional<int> age;
	Event redacted_because;
	std::optional<std::string> transaction_id;

	UnsignedData() {}

	UnsignedData(json j) {
		if(j.contains("age"))
			age = (int)j["age"];
		else
			age = {};

		redacted_because = Event(j["redacted_because"]);
		
		if(j.contains("transaction_id"))
			transaction_id = j["transaction_id"];
		else
			transaction_id = {};
	}
};
#endif // UNSIGNEDDATA_CPP_INCLUDE_
