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
			<< "13 {\n"
			<< "    Помилка додавання, в дереві не може бути більше одного однакових значень\n"
			<< "    AddError: there cannot be more than one identical value in the b-tree \n"
			<< "}\n"
			<< "\n"
			<< "14 {\n"
			<< "    Помилка відображення. Дерево пусте\n"
			<< "    PrintError: b-tree is empty\n"
			<< "}\n"
			<< "\n"
			<< "15 {\n"
			<< "    Помилка видалення. Ключа не має\n"
			<< "    DeleteError: b-tree has no delete key\n"
			<< "}\n"
			<< " -1 {\n"
			<< "    Фатальна помилка. Перевірте, чи правильно ви видаляєте\n"
			<< "	вузол, тому що видаляючий вузол має дітей!"
			<< "    FatalError: The node that tried to delete has children, which is not allowed!\n"
			<< "}\n";
		My_exception_codes.close();
	}
}