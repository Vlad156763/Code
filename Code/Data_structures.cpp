#include "Data_structures.h"

namespace data_struct {
	void main_test_dl_list(ostream& os) {
		dl_list<int> test;
		os << "Перевірка двозв'язного списку:\n";
		test.push_back(1); // 1
		test.push_front(0); // 0 1
		test.insert(100,1); // 0 100 1
		test.insert(200, 1); // 0 200 100 1
		for (int i = 0; i < 20; i++) os << "==="; os << '\n';
		os << "\tосновний список: ";
		test.print_from_start(os); // 0 200 100 1
		os << '\n';
		os << "\tсписок, з кінця: ";
		test.print_from_end(os); // 1 100 200 0
		os << '\n' << "\tрозмір: " << test.get_size() << '\n'; // 4
		os << "\tЕлемент з індексом 2: " << test[2] << '\n'; // 100

		test.remove_at(1); // 0 100 1
		os << "\tremove_at(1): ";
		test.print_from_start(os); // 0 100 1
		os << '\n';
		test.pop_front(); // 100 1
		os << "\tpop_front(): ";
		test.print_from_start(os); // 100 1
		os << '\n';
		test.pop_back(); // 100
		os << "\tpop_back(): ";
		test.print_from_start(os); //  100 
		os << '\n'; for(int i = 0; i <20; i++) os << "---"; os << '\n';
		os << "\tCпроба обнагліти, і видалити елемент з неіснуючим індексом...\n";
		try {
			test.remove_at(1); //помилка: 202
		}
		catch (error& er) {
			os << "\tСпроба обнагліти провалилась! \n\tВ чому причина: " << er.get_error_msg();
			os << "\n\tДля більш детальної інформації прочитайте у файлі: My_exeption_codes.txt " <<
				"Код помилки: " << er.get_error_code();
		}
		os << '\n'; for (int i = 0; i < 20; i++) os << "---"; os << '\n';
		test.pop_front();
		os << "\tpop_front(): ";
		os << "\tCпроба обнагліти, і вивести пустий список...\n";
		try {
			test.print_from_start(os);
		}
		catch (error& er) {
			os << "\tСпроба обнагліти провалилась! \n\tВ чому причина: " << er.get_error_msg();
			os << "\n\tДля більш детальної інформації прочитайте у файлі: My_exeption_codes.txt " <<
				"Код помилки: " << er.get_error_code();
		}
		os << '\n'; for (int i = 0; i < 20; i++) os << "---"; os << '\n';
		os << "\tCпроба обнагліти, i отримати доступ до неіснуючого елементу...\n";
		try {
			os << test[100];
		}
		catch (error& er) {
			os << "\tСпроба обнагліти провалилась! \n\tВ чому причина: " << er.get_error_msg();
			os << "\n\tДля більш детальної інформації прочитайте у файлі: My_exeption_codes.txt " <<
				"Код помилки: " << er.get_error_code();
		}
		os << '\n'; for (int i = 0; i < 20; i++) os << "---"; os << '\n';
		os << "\tПеревірка списку пройшла з обробленими помилками, це означає, що список" <<
			"\n\tкоректно працює і кидає виключення для подальшої їхньої обробки.\n";
		for (int i = 0; i < 20; i++) os << "==="; os << '\n';
	}

	void main_test_priory_queue_heap(ostream& os) {
		//невідсортований масив
		os << "Перевірка купи з пріорітетами:\n";
		const int size_array = 12;
		priory_queue_heap<int>::node array[size_array]{
			{23, 5},
			{ 11, 47 },
			{ 35, 19 },
			{ 6, 88 },
			{ 50, 33 },
			{ 9, 17 },
			{ 42, 73 },
			{ 18, 4 },
			{ 27, 94 },
			{ 61, 8 },
			{ 30, 22 },
			{ 14, 66 }

		};
		priory_queue_heap<int> test_0;
		test_0.add(1,19); // 19
		test_0.add(1, 1); // 19 1
		test_0.add(-10000, 200); // 200 1 19
		test_0.add(1, 0); // 200 1 19 0
		test_0.add(1, -1); // 200 1 19 0 -1
		for (int i = 0; i < 20; i++) os << "==="; os << '\n';
		os << "\tосновна купа [значення (пріорітет)]: " << test_0 << '\n';
		os << "\tотримання елементу з найбільшим пріорітетом: " << test_0.get() << '\n';
		os << "\tперевірка що сталось з купою: " << test_0 << '\n'; //19 1 -1 0
		test_0.del(3); 
		os << "\tвидалення елементу під індексом 3: " << test_0 << '\n'; // 19 1 -1
		test_0.del(1);
		os << "\tвидалення елементу під індексом 1: " << test_0 << '\n'; // 19  -1
		test_0.del(1);
		os << "\tвидалення елементу під індексом 1: " << test_0 << '\n'; // 19 
		test_0.del(0);
		os << "\tвидалення останнього і єдиного елементу купи";
		os << '\n'; for (int i = 0; i < 20; i++) os << "---"; os << '\n';
		os << "\tСпроба обнагліти, і отримати елемент з пустої купи...\n";
		try {
			test_0.get();
		} catch (error& er) {
			os << "\tСпроба обнагліти провалилась! \n\tВ чому причина: " << er.get_error_msg();
			os << "\n\tДля більш детальної інформації прочитайте у файлі: My_exeption_codes.txt " <<
				"Код помилки: " << er.get_error_code();
		}
		os << '\n'; for (int i = 0; i < 20; i++) os << "---"; os << '\n';

		os << "\tСпроба обнагліти, і видалити елемент з пустої купи...\n";
		try {
			test_0.del(100);
		}
		catch (error& er) {
			os << "\tСпроба обнагліти провалилась! \n\tВ чому причина: " << er.get_error_msg();
			os << "\n\tДля більш детальної інформації прочитайте у файлі: My_exeption_codes.txt " <<
				"Код помилки: " << er.get_error_code();
		}
		os << '\n'; for (int i = 0; i < 20; i++) os << "---"; os << '\n';

		os << "\tСпроба обнагліти, і вивести пусту купу...\n";
		try {
			os << test_0;
		}
		catch (error& er) {
			os << "\tСпроба обнагліти провалилась! \n\tВ чому причина: " << er.get_error_msg();
			os << "\n\tДля більш детальної інформації прочитайте у файлі: My_exeption_codes.txt " <<
				"Код помилки: " << er.get_error_code();
		}
		os << '\n'; for (int i = 0; i < 20; i++) os << "---"; os << '\n';
		priory_queue_heap<int> test_1(array, size_array);
		os << "\tперевірка, чи відсортувався масив за правилами купи: \n\t" << test_1;
		//правильно відсортована купа:
		/*
		         +-   94  -+
		        /           \
		      88             73
			/   \          /    \
		  47     33      66      19
         /  \   /  \    /  
		4    5 8   22  17
		*/
		os << '\n'; for (int i = 0; i < 20; i++) os << "---"; os << '\n';
		os << "\tПеревірка купи пройшла з обробленими помилками, це означає, що купа" <<
			"\n\tкоректно працює і кидає виключення для подальшої їхньої обробки.\n";
		for (int i = 0; i < 20; i++) os << "==="; os << '\n';
	}
}
