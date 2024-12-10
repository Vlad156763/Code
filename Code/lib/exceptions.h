#ifndef EXCEPTION_H
#define EXCEPTION_H
class ex {
private: 
	int errorCode = -1;
	const char* errorMsg = "";
public:
	ex(const int& ErrorCode, const char* ErrorMessage);
	int getErrorCode() const;
	const char* getErrorMsg() const;
};
#endif // !EXCEPTION_H

