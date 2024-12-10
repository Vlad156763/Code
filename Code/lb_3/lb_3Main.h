#ifndef LB_3MAIN_H
#define LB_3MAIN_H
#include <iostream>
#include <string>
#include <vector>
#include <limits.h>
#include <limits>
#include "../lib/ConsoleOut.h"
#include "../lib/exceptions.h"
using std::cout;
using std::cin;
using std::numeric_limits;
using std::streamsize;
using std::string;
using std::vector;
using std::pair;
using std::make_pair;
using std::getline;
using std::stod;
using std::invalid_argument;

/*
Капітан корабля, що зупинився на закинутому острові, вирішив
придбати у туземців спеції та заповнити ними всі вільні трюми, щоб
заробити якомога більше грошей.
Однак всі спеції вмістити у трюми
було неможливо, а туземці всі їх продавали за одну й ту саму ціну.

Знайшовши у одного з матросів записи про те, скільки коштує кожний
вид спецій на континенті, приблизно оцінивши наявну кількість
кожного виду спецій та знаючи, яку кількість вантажу вмістять вільні
трюми, капітан пішов на переговори з туземцями. Визначте
оптимальне рішення для капітана.
*/

class ui {

public:
	static void show(); 
};



#endif // !LB_3MAIN_H
