#include "main_lb_2.h"
#include "Exception_for_lb_2.h"
#include "B_tree.h"
#include <iostream>
using std::cout;
using std::endl;
using data_struct_b_tree::test_b_tree;
using my_exceptions_2::My_exception_codes_file;

namespace task_2 {
	void main_test_all_files() {
		My_exception_codes_file();
		test_b_tree();
		cout
			<< endl
			<< "\033[38;2;0;255;0m"
			<< "+----------------------------+" << endl
			<< "| Програма завершила роботу! |" << endl
			<< "+----------------------------+"
			<< "\033[0m";
	}
}