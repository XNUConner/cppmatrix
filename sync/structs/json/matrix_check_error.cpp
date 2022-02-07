#ifndef MATRIX_CHECK_ERROR_CPP_INCLUDE_
#define MATRIX_CHECK_ERROR_CPP_INCLUDE_
#include "json.hpp"
// check if JSON contains error information
bool matrix_check_error(json data) {
	if(data.contains("errorcode") && data.contains("error")) { 
		std::cerr << "errorcode: " << data["errorcode"] << std::endl;
		std::cerr << "error: "     << data["error"]     << std::endl;
		return true;
	}
	return false;
}
#endif // MATRIX_CHECK_ERROR_CPP_INCLUDE_
