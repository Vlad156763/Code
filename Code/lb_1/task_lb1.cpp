

#include "task_lb1.h"
#include "Algoritms.h"
#include "Data_structures.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace algoritms;
using namespace data_struct;
using namespace task;
using std::stringstream;
using std::fstream;
using std::ios;
using std::pair;
using std::cout;
using std::endl;
using std::cin;

using namespace data_struct;
using namespace algoritms;
namespace task {
	student::student(
        const string& pib,
        const string& adres,
		double bal,
        const string& sex,
		int day,
		int month,
		int year) :
		PIB(pib), 
		adress(adres),
		middle_bal(bal),
		sex(sex) {
		birthday[0] = day;
		birthday[1] = month;
		birthday[2] = year;
	}
    string student::get_PIB() const { return this->PIB; }
    string student::get_adress() const { return this->adress; }
    double student::get_middle_bal() const { return this->middle_bal; }
    string student::get_sex() const { return this->sex; }
    int student::get_year() const { return this->birthday[2]; }
    int student::get_month() const { return this->birthday[1]; }
    int student::get_day() const { return this->birthday[0]; }


    void sift_do(pair<string, int>* array, int& size, int current) {
        while (true) {
            int left_child = 2 * current + 1;
            if (left_child >= size) break; // Немає дітей - виходимо
            int right_child = 2 * current + 2;
            int largest = left_child;

            // Перевірю правого нащадка
            if (right_child < size && array[right_child].second > array[largest].second) 
                largest = right_child;
            
            // Якщо діти мають однакові значення int, порівнюю місяці
            if (right_child < size && array[right_child].second == array[largest].second) 
                if (array[right_child].first < array[largest].first) 
                    largest = right_child;

            // Перевірю, чи батько більший за найбільшого нащадка за значенням int
            if (array[current].second > array[largest].second) break;

            // Якщо батько і найбільший нащадок мають однакові значення int, порівнюю рядки
            if (array[current].second == array[largest].second) 
                if (array[current].first < array[largest].first) break; // Батько має правильне місце

            // Перестановка елементів
            pair<string, int> tmp = array[current];
            array[current] = array[largest];
            array[largest] = tmp;
            current = largest; // Переходжу далі
        }
    }

    void pyramid_so(pair<string, int>* array, int size) {
        // 1. Створення купи (перетворюємо масив у макс-купу)
        for (int i = size/2 - 1; i >= 0; i--) sift_do(array, size, i);
        for (int i = size - 1; i > 0; i--) {
            pair<string, int> tmp = array[0];
            array[0] = array[i];
            array[i] = tmp;
            sift_do(array, i, 0);
        }
    }
    void main_test_task(ostream& os, istream& is) {
        dl_list<student> group;
        char tmp, tmp_1, tmp_2;
        do {
            os << "Зчитати файл для отримання попередніх данних? [n/y]: ";
            is >> tmp_2;
            if (tmp_2 == 'n') {
                do {
                    os << "Випадково заповнювати інформацію про студентів? [n/y]: ";
                    is >> tmp;
                    if (tmp == 'n') {
                        do {
                            os << "Хочете додати студента? [n/y]: ";
                            is >> tmp_1;
                            if (tmp_1 == 'n') {
                                os << "В такому випадку зчитується файл: \n";
                                break;
                            }
                            else if (tmp_1 == 'y') {
                                fstream students("lb_1/students.txt", ios::out);
                                if (!students.is_open()) throw error("FileError: could not open file for writing", 207);
                                string pib, address, gender;
                                double middle_bal;
                                int day, month, year;
                                os << "ПІБ: "; is >> pib;
                                os << "Адрес: "; is >> address;
                                os << "Середній бал: "; is >> middle_bal;
                                os << "Стать: "; is >> gender;
                                os << "День народження: "; is >> day;
                                os << "Місяць народження: "; is >> month;
                                os << "Рік народження: "; is >> year;
                                students << pib << " | " << address << " | " << middle_bal << " | " << gender << " | " << day << '.' << month << '.' << year << '\n';
                                students.close();
                            }
                            else continue;
                        } while (true);
                        break;
                    }
                    else if (tmp == 'y') {
                        //всі збіги випадкові!!!
                        fstream students("lb_1/students.txt", ios::out);
                        if (!students.is_open()) throw error("FileError: could not open file for writing", 207);
                        students
                            << "Ivanov Ivan Ivanovych" << " | " << "Address 1" << " | " << 4.5 << " | " << "man" << " | " << "10.03.2000\n"
                            << "Petrov Petr Petrovych" << " | " << "Address 2" << " | " << 3.2 << " | " << "man" << " | " << "15.04.2001\n"
                            << "Sidorov Sidor Sidorovych" << " | " << "Address 3" << " | " << 4.8 << " | " << "man" << " | " << "20.05.1999\n"
                            << "Kovalenko Oksana Olegivna" << " | " << "Address 4" << " | " << 4.1 << " | " << "woman" << " | " << "02.06.1998\n"
                            << "Shevchenko Anna Anatoliivna" << " | " << "Address 5" << " | " << 3.7 << " | " << "woman" << " | " << "12.07.2002\n"
                            << "Kuzmenko Oleksandr Mykhailovych" << " | " << "Address 6" << " | " << 4.9 << " | " << "man" << " | " << "25.08.1997\n"
                            << "Berezovskyi Maksym Volodymyrovych" << " | " << "Address 7" << " | " << 3.5 << " | " << "man" << " | " << "18.09.2000\n"
                            << "Holub Liubov Ivanivna" << " | " << "Address 8" << " | " << 4.0 << " | " << "woman" << " | " << "30.10.1995\n"
                            << "Moroz Mykola Serhiiovych" << " | " << "Address 9" << " | " << 3.8 << " | " << "man" << " | " << "07.11.1996\n"
                            << "Tkachenko Andrii Volodymyrovych" << " | " << "Address 10" << " | " << 4.6 << " | " << "man" << " | " << "01.12.2003\n"
                            << "Shapoval Kateryna Olexandrivna" << " | " << "Address 11" << " | " << 4.3 << " | " << "woman" << " | " << "14.01.1994\n"
                            << "Prykhodko Valentyna Petroivna" << " | " << "Address 12" << " | " << 3.6 << " | " << "woman" << " | " << "21.02.2002\n"
                            << "Mykhailenko Oleksii Volodymyrovych" << " | " << "Address 13" << " | " << 4.4 << " | " << "man" << " | " << "06.03.1997\n"
                            << "Lysenko Viktoria Hryhorivna" << " | " << "Address 14" << " | " << 4.7 << " | " << "woman" << " | " << "19.04.2001\n"
                            << "Fedorov Andrii Yuriiovych" << " | " << "Address 15" << " | " << 3.9 << " | " << "man" << " | " << "11.05.1998\n"
                            << "Havryliuk Diana Oleksandrivna" << " | " << "Address 16" << " | " << 4.2 << " | " << "woman" << " | " << "26.06.2000\n"
                            << "Zakharchenko Yurii Volodymyrovych" << " | " << "Address 17" << " | " << 3.4 << " | " << "man" << " | " << "08.07.1999\n"
                            << "Yurchenko Alina Dmytrivna" << " | " << "Address 18" << " | " << 4.1 << " | " << "woman" << " | " << "17.08.2003\n"
                            << "Krutko Dmytro Mykolaiovych" << " | " << "Address 19" << " | " << 3.7 << " | " << "man" << " | " << "22.09.2002\n"
                            << "Kyrychenko Iryna Oleksiivna" << " | " << "Address 20" << " | " << 4.9 << " | " << "woman" << " | " << "28.10.1995\n"
                            << "Taranov Roman Valeriiovych" << " | " << "Address 21" << " | " << 4.3 << " | " << "man" << " | " << "03.11.2001\n"
                            << "Kravchenko Oleg Andriiovych" << " | " << "Address 22" << " | " << 3.3 << " | " << "man" << " | " << "09.12.2003\n"
                            << "Bodnar Anastasiia Oleksiivna" << " | " << "Address 23" << " | " << 4.6 << " | " << "woman" << " | " << "16.01.1996\n"
                            << "Makarenko Oleh Viktorovych" << " | " << "Address 24" << " | " << 4.2 << " | " << "man" << " | " << "24.02.1997\n"
                            << "Radchenko Svitlana Vasylivna" << " | " << "Address 25" << " | " << 3.8 << " | " << "woman" << " | " << "13.03.1999\n"
                            << "Drozd Valentyn Ivanovych" << " | " << "Address 26" << " | " << 4.7 << " | " << "man" << " | " << "29.04.1995\n";
                        students.close();
                        break;
                    }
                    else continue;
                } while (true);
                
            }
            else if (tmp_2 != 'y')continue;
            fstream students("lb_1/students.txt", ios::in);
            if (!students.is_open()) error("FileError: could not open file for reading", 208);
            string line;
            while (getline(students, line)) {
                stringstream ss(line);
                string pib, address, gender;
                double middle_bal;
                int day, month, year;
                getline(ss, pib, '|');
                getline(ss, address, '|');
                ss >> middle_bal;
                ss.ignore(3);  // Пропустити " | "
                getline(ss, gender, '|');
                ss >> day;
                ss.ignore(1);  // Пропустити крапку
                ss >> month;
                ss.ignore(1);  // Пропустити крапку
                ss >> year;
                // Видалення зайвих пробілів на початку і в кінці
                pib.erase(0, pib.find_first_not_of(' ')); pib.erase(pib.find_last_not_of(' ') + 1);
                address.erase(0, address.find_first_not_of(' ')); address.erase(address.find_last_not_of(' ') + 1);
                gender.erase(0, gender.find_first_not_of(' ')); gender.erase(gender.find_last_not_of(' ') + 1);
                // Додаємо студента в групу
                group.push_back(student(pib, address, middle_bal, gender, day, month, year));
            }
            os << "Данні файлу:\n";
            for (int i = 0; i < 20; i++) os << "==="; os << '\n';
            for (int i = 0; i < group.get_size(); i++) {
                os
                    << group[i].get_PIB() << " | "
                    << group[i].get_adress() << " | "
                    << group[i].get_middle_bal() << " | "
                    << group[i].get_sex() << " | "
                    << group[i].get_day() << " | "
                    << group[i].get_month() << " | "
                    << group[i].get_year() << '\n';

            }
            for (int i = 0; i < 20; i++) os << "==="; os << '\n';
            students.close();
            pair<string, int> tmp[12];
            tmp[0].first = "January";   // Січень
            tmp[1].first = "February";  // Лютий
            tmp[2].first = "March";     // Березень
            tmp[3].first = "April";     // Квітень
            tmp[4].first = "May";       // Травень
            tmp[5].first = "June";      // Червень
            tmp[6].first = "July";      // Липень
            tmp[7].first = "August";    // Серпень
            tmp[8].first = "September";  // Вересень
            tmp[9].first = "October";   // Жовтень
            tmp[10].first = "November";  // Листопад
            tmp[11].first = "December";  // Грудень
            for (int i = 0; i < group.get_size(); i++) {
                tmp[group[i].get_month() - 1].second++;
            }
            pyramid_so(tmp, 12);

            os
                << "Відсортовані місяці за кількістю студентів, які народились в цей місяць\n"
                << "(Якщо кільксть студентів однакова - ортування відбувалось за алфавітом)\n";
            for (int i = 0; i < 12; i++) {
                os << tmp[i].first << ' ' << tmp[i].second << '\n';
            }
            break;
        } while (true);      
    }
	void main_test_all_files() {
		My_exception_codes_file(); //якщо користувач видалить в каталозі файл txt з кодами, помилок, він знову створиться
		//ТЕСТ!!!
		main_test_dl_list(cout); cout << endl;
		main_test_priory_queue_heap(cout); cout << endl;
		//main_test_piramidal_sort(cout); cout << endl;
		cout << "СПИСОК,КУПА З ПРІОРІТЕТАМИ ТА ПІРАМІДАЛЬНЕ СОРТУВАННЯ УСПІШНО ПРОЙШЛИ ТЕСТ!" << endl << endl << endl;
		main_test_task(cout, cin);
	
	}
}
