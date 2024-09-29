#include "My_exceptions.h"
#include <fstream>
#include <iostream>
using std::ofstream;

namespace my_exceptions {
	error::error(const char* er_msg, const int& er_code) : error_msg(er_msg), error_code(er_code) {}
	const char* error::get_error_msg() { return error_msg; }
	int error::get_error_code() { return error_code;}
	void My_exception_codes_file() {
		ofstream My_exception_codes("My_exception_codes.txt");
		if (!My_exception_codes.is_open()) throw error("FileError: could not open file for writing", 207);
		My_exception_codes
			<< "Цей файл має коди виключень, та їх пояснення\n" 
			<< "This file has exception codes and their explanations\n"
			<<"\n"
			<< "201 {\n"
			<< "    Індекс поза межами діапазону. Переконайтесь, що не відбувається доступу"
			<<"     до неіснуючого елементу списку.\n"
			<< "    IndexError: list index out of range\n"
			<<"}\n"
			<< "\n"
			<< "202 {\n"
			<< "    Не має що видаляти. Спроба видалити неіснуючий елемент.\n"
			<< "    DeleteError: attempting to delete a non-existent element\n"
			<< "}\n"

			<< "\n"
			<< "203 {\n"
			<< "    Список пустий. Спроба вивести порожній список.\n"
			<< "    DisplayError: list is empty\n"
			<< "}\n"

			<< "\n"
			<< "204 {\n"
			<< "    Куча порожня, спроба отримати елемент у пустій купі.\n"
			<< "    GetError: heap is empty\n"
			<< "}\n"

			<< "\n"
			<< "205 {\n"
			<< "    Індекс поза межами діапазону. Переконайтесь, що не відбувається доступу\n"
			<< "    до неіснуючого елементу купи.\n"
			<< "    IndexError: heap index out of range\n"
			<< "}\n"

			<< "\n"
			<< "206 {\n"
			<< "    Куча пуста. Спроба вивести порожню купу.\n"
			<< "    DisplayError: heap is empty\n"
			<< "}\n"

			<< "\n"
			<< "207 {\n"
			<< "    Помилка відкриття файлу для запису.\n"
			<< "    FileError: could not open file for writing\n"
			<< "}\n"
			
			<< "\n"
			<<"208 {\n"
			<< "    Помилка відкриття файлу для читання.\n"
			<< "    FileError: could not open file for reading\n"
			<<"}\n";
		My_exception_codes.close();
	}
}