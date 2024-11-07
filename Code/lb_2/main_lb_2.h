#ifndef main_lb_2
#define main_lb_2
#include "Exception_for_lb_2.h"
#include "../lb_1/Data_structures.h"
#include "B_tree.h"
#include "hashTable.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using data_struct::dl_list;
using std::string;
using std::cout;
using std::endl;
using std::cin;
using namespace data_struct_b_tree;
using std::numeric_limits;
using std::streamsize;
namespace task_2 {
	void main_test_all_files();
	
	//todo: В-дерево
	/*
	Клас, що реалізує B-дерево, має дозволяти виконувати
	наступні операції на основі окремих методів: створення порожнього
	дерева, відображення структури дерева, пошук у дереві, вставлення
	ключа, видалення ключа.
	Завдання Г
	Щоденник погоди містить інформацію, що складається з дати,
	температури, вологості повітря, напрямку вітру, атмосферних явищ,
	атмосферного тиску, рівня опадів. На основі даних щоденника погоди
	сформувати дерево. Визначити інформацію про погоду за вказану
	користувачем дату. Визначити день заданого місяця, коли рівень
	опадів був найвищий.
	*/
	static void Fhome_Btree(dl_list<const char*>&, bool&);
	static void Fhome_testTree(b_tree<int>&, dl_list<const char*>&);
	static int Fhome_newTree(dl_list<const char*>&);
	static void Fhome_tree_methods(b_tree<int>&, bool&, dl_list<const char*>&, bool&);
	static void taskG_Btree(bool&, dl_list<const char*>&, bool&);
	class diary_weather {
	public: 	
		enum wind_direction {
		North,			//північ
		North_East,		//північний схід
		East,			//схід
		South_East,		//південний схід
		South,			//південь
		South_West,		//південний захід
		West,			//захід
		North_West,		//північний захід
		None			//вітру немає
	};
	private:
		struct data_s {
		public:
			int day = 0;
			int month = 0;
			data_s(const int&, const int&);
			data_s();
		};
		data_s data;
		double temperature = 0;
		double vologist = 0; // у відсотках
		wind_direction windDirection = wind_direction::None; //у сторонах світу
		string weatherEvents;
		int pressure = 0;
		double opady = 0; //в день
	public:
		//рік вважається 2024
		diary_weather(const int&, const int&, const double&, const double&, wind_direction, const string&, const int&, const double&);
		diary_weather();
		//даний конструктор треба для пошуку у дереві (так як порівняння елементів відбувається за допомогою дати 
		diary_weather(const int&, const int&);
		ostream& print(ostream&) const;
	
		bool operator > (const diary_weather&) const;
		bool operator < (const diary_weather&) const;
		bool operator ==(const diary_weather&) const;
		friend ostream& operator << (ostream&, const diary_weather&);
		friend ostream& operator << (ostream&, const wind_direction&);
		friend void taskG_Btree(bool&, dl_list<const char*>&, bool&);
	};
	//todo: Геш-таблиця
	/*
	Клас, що реалізує геш-таблицю, має дозволяти
	виконувати наступні операції на основі окремих методів: 
	вставлення елементу, видалення елементу, пошук елементу, відображення
	структури геш-таблиці на основі використання параметрів, обраних у
	відповідності з варіантом індивідуального завдання з п. 2.3.4.
	Завдання Г
	Створити геш-таблицю, що використовує метод відкритої
	адресації для розв’язання колізій, геш-функцію множення та метод
	квадратичного дослідження для обчислення послідовностей
	досліджень. Геш-таблицю заповнити на основі виділення інформації з
	текстового файлу, в якому містяться ідентифікаційні номери
	платників податків та їх прізвища, імена і по батькові. Визначити
	платника податку за заданим ідентифікаційним номером.
	*/
	static void Fhome_HachTable(dl_list<const char*>&, bool&);
}

#endif //!main_lb_2
