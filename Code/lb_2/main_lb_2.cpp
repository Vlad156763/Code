#include "main_lb_2.h"
#include "Exception_for_lb_2.h"
#include "B_tree.h"
using data_struct_b_tree::test_b_tree;
using my_exceptions_2::My_exception_codes_file;
namespace task {
	void main_test_all_files() {
		My_exception_codes_file();
		test_b_tree();

	}
}