#include "Data_structures.h"
using namespace std;
using namespace data_struct;

int main() {
	dl_list<int> a;
	a.push_back(1);
	a.print_from_start(cout);
	
	return 0;
}