#ifndef MATRIX_CPP_INCLUDE_
#define MATRIX_CPP_INCLUDE_
typedef struct Email {
	std::string identity;
} Email;

typedef struct Login {
	std::string password;
	std::string recaptcha;
	std::string sso;
	std::string token;
	std::string application_service;
	Email email;
	std::string msisdn;
	std::string dummy;
} Login;

typedef struct ID {
	std::string user;
	std::string thirdparty;
	std::string phone;
} ID;

typedef struct Homeserver {
	std::string base_url;	
} Homeserver;

typedef struct Identity_Server {
	std::string base_url;
} Identity_Server;

typedef struct Matrix {
	Homeserver homeserver;
	Identity_Server identity_server;
	Login login;
	ID id;
} Matrix;
#endif // MATRIX_CPP_INCLUDE_
