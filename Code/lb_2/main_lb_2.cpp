#include "main_lb_2.h"
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
			<< "+--------------------------+" << endl
			<< "|Програма завершила роботу!|" << endl
			<< "+--------------------------+"
			<< "\033[0m";
	}
	static void Fhome_Btree(dl_list<const char*>& way, bool& main_home_exit) {
		bool exit_loop_home = false; //зміна для контролю циклу
		way.push_back("Btree_home/");
		do {
			cout << "\033[38;2;100;100;255m";
			for (int i = 0; i < way.get_size(); i++) cout << way[i];
			cout << "\033[0m" << endl;
			cout
				<< "Завершити програму    \t0 Enter" << endl
				<< "Тестове B-дерево      \t1 Enter" << endl
				<< "Нове B-дерево         \t2 Enter" << endl
				<< "Завдання Г            \t3 Enter" << endl
				<< "Повернутись на /home/ \t4 Enter" << endl
				<< "> ";
			char b_tree_TestNew = cin.get();
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //ігнорую всі інші символи в буфері до наступного рядка
			switch (b_tree_TestNew) {
			case '0': {
				main_home_exit = true;
				return;
			}
			case '1': {
				b_tree<int> qa(2);
				Fhome_testTree(qa, way);
				Fhome_tree_methods(qa, exit_loop_home, way, main_home_exit); //передаю exit_loop_home якщо користувач захоче перейти до home і передаю шлях 
				break;
			}
			case '2': {
				b_tree<int> qa(Fhome_newTree(way));
				Fhome_tree_methods(qa, exit_loop_home, way, main_home_exit);
				break;
			}
			case '3': {
				taskG_Btree(exit_loop_home, way, main_home_exit);
				break;
			}
			case'4': {
				main_home_exit = false;
				way.pop_back();
				return;
			}
			default: {
				cout << "\033[38;2;255;0;0m" << "Помилка! Обрано не вірний пункт" << "\033[0m" << endl;
				continue;
			}
			}

		} while (!exit_loop_home);

	}
	static void Fhome_testTree(b_tree<int>& qa, dl_list<const char*>& way) {
		way.push_back("test_Btree/");
		cout << "\033[38;2;100;100;255m";
		for (int i = 0; i < way.get_size(); i++) cout << way[i];
		cout << "\033[0m" << endl << "Наповнення данними..." << endl;

		qa.add_key(1);
		qa.add_key(3);
		qa.add_key(156);
		qa.add_key(63);
		qa.add_key(122);
		qa.add_key(11);
		qa.add_key(0);
		qa.add_key(-1);
		qa.add_key(-111);
		qa.add_key(23);
		qa.add_key(1991);
		qa.add_key(10);
		qa.add_key(15);
		qa.add_key(50);
		qa.add_key(5);
		qa.add_key(9);
		qa.add_key(200);
		qa.add_key(150);
		qa.add_key(75);
		qa.add_key(18);
		qa.add_key(-200);
		qa.add_key(100);
		qa.add_key(300);
		qa.add_key(-50);
		qa.add_key(-10);

		//qa.add_key(0); перевірка на однакові ключі працює

		qa.add_key(250);
		qa.add_key(60);
		qa.add_key(85);
		qa.add_key(99);
		qa.add_key(101);
		qa.add_key(500);
		qa.add_key(-500);
		qa.add_key(350);
		qa.add_key(175);
		qa.add_key(225);
		qa.add_key(30);
		qa.add_key(130);
		qa.add_key(40);
		qa.add_key(220);
		qa.add_key(-300);
		qa.add_key(999);
		qa.add_key(888);
		qa.add_key(777);
		qa.add_key(555);
		qa.add_key(333);
		qa.add_key(111);
		qa.add_key(222);
		qa.add_key(444);
		cout << "Тестове дерево наповнене!" << endl;
	}
	static int Fhome_newTree(dl_list<const char*>& way) {
		int t;
		way.push_back("new_Btree/");
		do {
			cout << "\033[38;2;100;100;255m";
			for (int i = 0; i < way.get_size(); i++) cout << way[i];
			cout << "\033[0m" << endl;
			cout
				<< "Порядок дерева t " << endl
				<< "> ";
			cin >> t;
			if (cin.fail() || (t <= 1 || (2 * t) >= INT_MAX)) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cout << "\033[38;2;255;0;0m" << "Помилка! Bведіть ціле число, щоб задовольняло умову: \033[0m(t >= 2 && (2 * t) < INT_MAX)" << endl;
				continue;
			}
			cin.ignore(); //ігнорую /n який ставить користувач
			cout << "Тип з яким працює b-дерево: int" << endl;
			break;
		} while (true);
		return t;
	}
	static void Fhome_tree_methods(b_tree<int>& qa, bool& exit_loop_home, dl_list<const char*>& way, bool& main_home_exit) {
		bool exit_loop_methods = false;
		way.push_back("methods/");
		do {
			cout << "\033[38;2;100;100;255m";
			for (int i = 0; i < way.get_size(); i++) cout << way[i];
			cout << "\033[0m" << endl;
			cout
				<< "Завершити програму             \t 0 Enter" << endl
				<< "Додати ключ                    \t 1 Enter" << endl
				<< "Видалити ключ                  \t 2 Enter" << endl
				<< "Відобразити структуру b-дерева \t 3 Enter" << endl
				<< "Повернутись на /Btree_home/    \t 4 Enter" << endl
				<< "> ";
			char b_tree_AdddelPrint = cin.get();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			switch (b_tree_AdddelPrint) {
			case '0': {
				main_home_exit = true;
				exit_loop_home = true; //викоджу з циклу в /home/
				return;
			}
			case '1': {
				/*додати ключ*/
				do {
					cout << "\033[38;2;100;100;255m";
					for (int i = 0; i < way.get_size(); i++) cout << way[i]; cout << "add_key/";
					cout << "\033[0m" << endl;
					cout << "\033[38;2;0;255;0m" << "> ";
					int key;
					cin >> key;
					cout << "\033[0m";
					if (cin.fail() || (key <= INT_MIN || key >= INT_MAX)) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "\033[38;2;255;0;0m" << "Помилка! Bведіть ціле число, щоб задовольняло умову: \033[0m(key > INT_MIN && key < INT_MAX)" << endl;
						continue;
					}
					cin.ignore();
					try { qa.add_key(key); }
					catch (error_2& ex) { cout << "\033[38;2;255;0;0mКлюч не додано! Причина - " << ex.get_error_msg() << "\033[0m " << ex.get_error_code() << endl; }
					break;
				} while (true);
				continue;
			}
			case '2': {
				/*видалити ключ*/
				do {
					cout << "\033[38;2;100;100;255m";
					for (int i = 0; i < way.get_size(); i++) cout << way[i]; cout << "delete_key/";
					cout << "\033[0m" << endl;
					cout << "\033[38;2;255;0;0m" << "> ";
					int key;
					cin >> key;
					cout << "\033[0m";
					if (cin.fail() || (key <= INT_MIN || key >= INT_MAX)) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "\033[38;2;255;0;0m" << "Помилка! Bведіть ціле число, щоб задовольняло умову: \033[0m(key > INT_MIN && key < INT_MAX)" << endl;
						continue;
					}
					cin.ignore();
					try { qa.del_key(key); }
					catch (error_2& ex) { cout << "\033[38;2;255;0;0mКлюч не видалено! Причина - " << ex.get_error_msg() << "\033[0m " << ex.get_error_code() << endl; }
					break;
				} while (true);
				continue;
			}
			case '3': {

				cout << "\033[38;2;100;100;255m";
				for (int i = 0; i < way.get_size(); i++) cout << way[i]; cout << "print_Btree/";
				cout << "\033[0m" << endl;
				try { qa.print(cout); }
				catch (error_2& ex) { cout << "\033[38;2;255;0;0mНе можливо відобразити дерево! Причина - " << ex.get_error_msg() << "\033[0m " << ex.get_error_code() << endl; }
				continue;
			}
			case '4': {
				exit_loop_home = false;
				for (int i = way.get_size() - 1; i >= 0 && way[i] != "Btree_home/"; i--) way.pop_back();
				return;
			}
			default: {
				cout << "\033[38;2;255;0;0m" << "Помилка! Обрано не вірний пункт" << "\033[0m" << endl;
				continue;
			}
			}
		} while (!exit_loop_methods);
	}
	//TODO: B-tree Г
	/* Щоденник погоди містить інформацію, що складається з
	дати, температури, вологості повітря, напрямку вітру, атмосферних явищ, атмосферного тиску, рівня опадів.
	На основі даних щоденника погоди сформувати дерево.
	Визначити інформацію про погоду за вказану користувачем дату.
	Визначити день заданого місяця, коли рівень опадів був найвищий.*/
	/*
	користувач вказує дату - за цією датою мені треба знайти всю інформацію 
	користувач вказує /місяць, а я повинен повернути день, який мав найбільше опадів 

	приклад:
	створюється пусте дерево на 31 комірку (для днів)
	це дерево максимум може мати 12 вузлів, 
	*/
	diary_weather::data_s::data_s(const int& day, const int& month) {
		this->day = day;
		this->month = month;
	}
	diary_weather::data_s::data_s() {}
	diary_weather::diary_weather(
		const int& day,
		const int& month,
		const double& temperature,
		const double& vologist,
		wind_direction windDirection,
		const string& weatherEvents,
		const int& pressure,
		const double& opady) : data(data_s(day, month)) {
		this->temperature = temperature;
		this->vologist = vologist;
		this->windDirection = windDirection;
		this->weatherEvents = weatherEvents;
		this->pressure = pressure;
		this->opady = opady;
	}
	diary_weather::diary_weather() {}
	diary_weather::diary_weather(const int& day, const int& month) : data(data_s(day, month)) {}
	bool diary_weather::operator>(const diary_weather& other) const {
		//якщо поточний місяць, більше іншого - повертаю true
		//якщо місяці однакові, порівнюю дні, якщо this має дату більше ніж other - повертаю true
		//в іншому випадку повертається false
		return (this->data.month > other.data.month || (this->data.month == other.data.month && this->data.day > other.data.day));
	}
	bool diary_weather::operator<(const diary_weather& other) const {
		//якщо поточний місяць, менше - повертаю true
		//якщо місяці однакові, порівнюю дні, якщо this має дату менше ніж other - повертаю true
		//в іншому випадку повертається false
		return (this->data.month < other.data.month || (this->data.month == other.data.month && this->data.day < other.data.day));
	}
	bool diary_weather::operator == (const diary_weather& other) const {
		//якщо день, або місяць не співпадають, повертаю false
		return this->data.day == other.data.day && this->data.month == other.data.month;
	}
	ostream& operator<<(ostream& os, const diary_weather& obj) {
		os
			<< endl << "\033[38;2;63;143;139m"
			<< tab << tab << obj.data.day << "/" << obj.data.month << "/2024" << endl << "\033[0m"
			<< tab << tab << "Температура:    " << obj.temperature << " °C" << endl
			<< tab << tab << "Вологість:      " << obj.vologist << "%" << endl
			<< tab << tab << "Напрямок вітру: " << obj.windDirection << endl
			<< tab << tab << "Погодні явища:  " << obj.weatherEvents << endl
			<< tab << tab << "Тиск:           " << obj.pressure << " мм рт. ст." << endl
			<< tab << tab << "Опади:          " << obj.opady << " мм" << endl
			<< tab;
		return os;
	}
	ostream& operator<<(ostream& os, const diary_weather::wind_direction& obj) {
		switch (obj) {
		case 0:
			os << "північ";
			break;
		case 1:
			os << "північний схід";
			break;
		case 2:
			os << "схід";
			break;
		case 3:
			os << "південний схід";
			break;
		case 4:
			os << "південь";
			break;
		case 5:
			os << "південний захід";
			break;
		case 6:
			os << "захід";
			break;
		case 7:
			os << "північний захід";
			break;
		case 8:
			os << "вітру немає";
			break;

		}
		return os;
	}
	void taskG_Btree(bool& exit_loop_home, dl_list<const char*>& way, bool& main_home_exit) {
		bool exitLoopTask = false;
		way.push_back("task_G/");
		b_tree<diary_weather> diary(16);
		auto addfalshData = [&diary]() {
			/*
			день
			місяць
			температура
			вологість
			напрямок вітру
			погодні явища
			тиск
			опади
			*/
			srand(time(0));
			cout << "Наповнення щоденника фальшивими данними..." << endl;
			for (int month = 1; month < 12; month++) {
				for (int day = 1; day < 15; day++) {
					diary.add_key(
						diary_weather(
							day, month,
							rand() % 21 - 10,
							rand() % 101,
							static_cast<diary_weather::wind_direction>(rand() % 9),
							"Сонячно",
							rand() % 80 + 710,
							rand() % 11
						)
					);
				}
			}
			cout << "Наповнення пройшло успішно!" << endl;
			};
		bool printTestDiaryOnce = true;
		do {
			cout << "\033[38;2;100;100;255m";
			for (int i = 0; i < way.get_size(); i++) cout << way[i]; cout << "\033[0m" << endl;
			if (printTestDiaryOnce) { printTestDiaryOnce = false; addfalshData(); }
			cout
				<< "Завершити програму             \t 0 Enter" << endl
				<< "Надрукувати щоденник           \t 1 Enter" << endl
				<< "Погода в заданий день          \t 2 Enter" << endl
				<< "Max опади в заданий місяць     \t 3 Enter" << endl
				<< "Повернутись на /Btree_home/    \t 4 Enter" << endl
				<< "> ";
			char Task = cin.get();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			switch (Task) {
			case '0': {
				main_home_exit = true;
				exit_loop_home = true; //викоджу з циклу в /home/
				return;
			}
			case '1': {
				cout << "\033[38;2;100;100;255m";
				for (int i = 0; i < way.get_size(); i++) cout << way[i]; cout << "print_diary/";
				cout << "\033[0m" << endl;
				diary.print(cout);
				continue;
			}
			case '2': {
				bool exitLoopWeatherGivenDay = false;
				do {
					cout << "\033[38;2;100;100;255m";
					for (int i = 0; i < way.get_size(); i++) cout << way[i]; cout << "weater_on_given_day/";
					cout << "\033[0m" << endl;
					cout << "День: ";
					int given_day;
					cin >> given_day;
					if (given_day <= 0 || given_day > 31) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "\033[38;2;255;0;0m" << "Помилка! Bведіть день місяця в діапазоні від 1 до 31" << endl;
						continue;
					}
					cout << "Місяць: ";
					int given_month;
					cin >> given_month;
					if (given_month <= 0 || given_month > 12) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "\033[38;2;255;0;0m" << "Помилка! Bведіть місяць в діапазоні від 1 до 12" << endl;
						continue;
					}
					if (cin.fail()) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "\033[38;2;255;0;0m" << "Помилка! Bведіть ціле число!" << endl;
						continue;
					}
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					//Todo: зробити запит у b-дерево і виводити дані за днем і місяцем
					
					exitLoopWeatherGivenDay = true;
				} while (!exitLoopWeatherGivenDay);
				break;
			}
			case '3': {
				bool exitLoopMaxOpady = false;
				do {
					cout << "\033[38;2;100;100;255m";
					for (int i = 0; i < way.get_size(); i++) cout << way[i]; cout << "max_opady/";
					cout << "\033[0m" << endl;
					int month;
					cout << "Місяць: ";
					cin >> month;
					if (month <= 0 || month > 12) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "\033[38;2;255;0;0m" << "Помилка! Bведіть місяць в діапазоні від 1 до 12" << endl;
						continue;
					}
					if (cin.fail()) {
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "\033[38;2;255;0;0m" << "Помилка! Bведіть ціле число!" << endl;
						continue;
					}
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					//Todo: зробити пошук за заданим місяцем і повернути день, в який опадів було найбільше
					exitLoopMaxOpady = true;
				} while (!exitLoopMaxOpady);
				break;
			}
			case '4': {
				exit_loop_home = false;
				//в головному шляху очищаю шлях до Btree_home 
				for (int i = way.get_size() - 1; i >= 0 && way[i] != "Btree_home/"; i--) way.pop_back();
				return;
			}
			default: {
				cout << "\033[38;2;255;0;0m" << "Помилка! Обрано не вірний пункт" << "\033[0m" << endl;
				continue;
			}
			}
		} while (!exitLoopTask);
		
	}
}