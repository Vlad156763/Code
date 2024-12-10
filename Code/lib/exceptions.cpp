#include "exceptions.h"
ex::ex(const int& errorCode = -1, const char* errorMsg = "") : errorCode(errorCode), errorMsg(errorMsg) {}
int ex::getErrorCode() const { return this->errorCode; }
const char* ex::getErrorMsg() const { return this->errorMsg; }