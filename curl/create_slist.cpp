#ifndef CREATE_SLIST_CPP
#define CREATE_SLIST_CPP
struct curl_slist* create_slist(const std::map<std::string, std::string> http_fields) {

	struct curl_slist *slist = NULL;

	for(const auto kv : http_fields) {
		std::string field = kv.first + ": " + kv.second;
		
		if(!slist)
			slist = curl_slist_append( slist, field.c_str() );
		else
			curl_slist_append( slist, field.c_str() );

	}

	return slist;
}
#endif // CREATE_SLIST_CPP
