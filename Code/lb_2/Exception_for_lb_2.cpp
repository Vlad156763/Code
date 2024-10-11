#include "Exception_for_lb_2.h"
#include <iostream>
#include <fstream>
using std::ofstream;
namespace my_exceptions_2 {
	error_2::error_2(const char* msg, const int& code)
	: error_msg(msg), error_code(code) {}
	int error_2::get_error_code() {return this->error_code;}
	const char* error_2::get_error_msg() {return this->error_msg;}
	void My_exception_codes_file () {
		ofstream My_exception_codes("lb_2/My_exception_codes.txt");
		if (!My_exception_codes.is_open()) throw error_2("FileError: could not open file for writing", 207);
		My_exception_codes
			<< "Цей файл має коди виключень, та їх пояснення\n"
			<< "This file has exception codes and their explanations\n"
			<< "\n"
			<< "201 {\n"
			<< "    Кількість ключів для вузла не допустима.\n"
			<< "    FatalError: the number of keys is not valid for b-treee\n"
			<< "}\n"
			<< "\n"
			<< "12 {\n"
			<< "    Помилка пошуку, дерево пусте\n"
			<< "    SearchError: b-tree is empty\n"
			<< "}\n"
			<< "\n"
			<< "11 {\n"
			<< "    Помилка пошуку, ключа немає у дереві\n"
			<< "    SearchError: there is no such element in the b-tree\n"
			<< "}\n"
			<< "\n"
			<< "13 {\n"
			<< "    Помилка пошуку, в дереві не може бути більше одного однакових значень\n"
			<< "    SearchError: there cannot be more than one identical value in the b-tree \n"
			<< "}\n";
		My_exception_codes.close();
	}
}