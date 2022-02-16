#ifndef SYNC_CPP
#define SYNC_CPP
#include "../structs/meta/SyncData.cpp"
void sendSyncRequest(Matrix* m, curl_tools* tools) {
	std::string endpoint = "/_matrix/client/v3/sync";
	std::string access_token = m->login.token;
	std::string homeserver = m->homeserver.base_url;

	/* HTTP body must have access token, that is the only requirement for a sync request. */
	std::map<std::string, std::string> fields;
	fields["Authorization"] = "Bearer " + access_token;

	/* get_request() is overloaded to use HTTP key value fields */
	get_request(homeserver, endpoint, fields, tools->curl);

	json sync_json = json::parse(tools->res->data);
}

void debugDumpSyncJSON(json j) {
	std::ofstream out;
	out.open("sync.json");
	out << j.dump(4);
	out.close();
}

SyncData sync(Matrix* m, curl_tools* tools) {
	sendSyncRequest(m, tools);
	json sync_json = json::parse(tools->res->data);

	/* Deserialize JSON */
	return SyncData(sync_json);
}
#endif // SYNC_CPP
