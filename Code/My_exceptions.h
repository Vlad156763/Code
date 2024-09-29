#ifndef My_exeptions
#define My_exeptions
namespace my_exceptions {
	class error {
	private:
		const char* error_msg;
		int error_code;
	public:
		error(const char*, const int&);
		const char* get_error_msg();
		int get_error_code();
	};
	void My_exception_codes_file();
}
#endif //My_exeptions