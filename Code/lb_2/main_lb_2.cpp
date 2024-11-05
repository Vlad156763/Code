#include "main_lb_2.h"
#include "Exception_for_lb_2.h"
#include "../lb_1/Data_structures.h"
#include "B_tree.h"
#include <iostream>
#include <string>
using data_struct::dl_list;
using std::string;
using std::cout;
using std::endl;
using std::cin;
using std::numeric_limits;
using std::streamsize;
/*
b-дерево:
Вивід 
додавання ключа
видалення ключа
пошук

*/
namespace task_2 {
	void main_test_all_files() {
		my_exceptions_2::My_exception_codes_file();
		bool exit_loop_home = false;
		dl_list<const char*> way;
		way.push_back("/home/");
		do {
			cout << "\033[38;2;100;100;255m";
			for (int i = 0; i < way.get_size(); i++) cout << way[i];
			cout << "\033[0m" << endl
				<< "Завершити програму \t0 Enter" << endl
				<< "B-дерево           \t1 Enter" << endl
				<< "Геш Таблиця        \t2 Enter" << endl
				<< "> ";

			char b_tree_TestNew = cin.get();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ігнорую всі інші символи в буфері до наступного рядка
			switch (b_tree_TestNew) {
			case '0': {
				exit_loop_home = true;
				break;
			}
			case'1': {
				Fhome_Btree(way, exit_loop_home);
				break;
			}
			case'2': {
				//Fhome_HachTable(way, exit_loop_home);
				//Fhome_HachTable(way, exit_loop_home);
				//Fhome_HachTable(way, exit_loop_home);
				cout << "\033[38;2;255;0;0mНе зроблено! Вибачте :(\033[0m" << endl;
#define NOT_IMPLEMENTED_1 0
				break;
			}
			default:
				cout << "\033[38;2;255;0;0m" << "Помилка! Обрано не вірний пункт" << "\033[0m" << endl;
				continue;
			}
		} while (!exit_loop_home);
		



		cout
			<< endl
			<< "\033[38;2;0;255;0m"
			<< "+----------------------------+" << endl
			<< "| Програма завершила роботу! |" << endl
			<< "+----------------------------+"
			<< "\033[0m";
		
	}
	
}