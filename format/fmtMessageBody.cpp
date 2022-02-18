#ifndef FMTMESSAGEBODY_CPP
#define FMTMESSAGEBODY_CPP
// Indent every line of message body
void fmtMessageBody(std::string& body) {
	body = "\t" + body;

	size_t pos = 0;
	while(pos != std::string::npos) {

		pos = body.find("\n", pos);

		if( pos < body.size()-1 && pos != std::string::npos ) {
			body.insert(pos+1, "\t");
			pos++;
		}
	}
}
#endif // FMTMESSAGEBODY_CPP
