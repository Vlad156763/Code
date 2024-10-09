#ifndef Exception_for_lb_2
#define Exception_for_lb_2
namespace my_exceptions_2 {
	class error_2 {
	private:
		int error_code;
		const char* error_msg;
	public:
		error_2(const char*, const int&);
		int get_error_code();
		const char* get_error_msg();
	};
	void My_exception_codes_file();
}
#endif //!Exception_for_lb_2