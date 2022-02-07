void sync(Matrix* m, curl_tools* tools) {
	std::string endpoint = "/_matrix/client/v3/sync";
	std::string access_token = m->login.token;
	std::string homeserver = m->homeserver.base_url;

	/* Start send_sync_request() */
	std::map<std::string, std::string> fields;
	fields["Authorization"] = "Bearer " + access_token;
	get_request(homeserver, endpoint, fields, tools->curl);
	json sync_json = json::parse(tools->res->data);
	/* End */

	/*
	Optional JSON file output
	std::ofstream out;
	out.open("sync.json");
	out << sync_json.dump(4);
	out.close();
	*/

	json rooms = sync_json["rooms"]["join"];
	for(auto room : rooms.items()) {
		std::cout << room.key() << std::endl;
	}
}
