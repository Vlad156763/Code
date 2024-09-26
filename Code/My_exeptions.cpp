#include "My_exeptions.h"

namespace my_exeptions {
	error::error(const char* er_msg, const int& er_code) : error_msg(er_msg), error_code(er_code) {}
	const char* error::get_error_msg() { return error_msg; }
	int error::get_error_code() { return error_code; }
}