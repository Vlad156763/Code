#ifndef CONSOLEOUT_H
#define CONSOLEOUT_H

#define NOMINMAX // Запобігання визначенню макросів max і min в Windows.h

#include <iostream>
#include <string>
#include <Windows.h>
#include "exceptions.h"
using std::to_string;
using std::string;

class out {
public:
	static string rgb(const int& red, const int& green, const int& blue);
	static string moveTo(const int& row, const int& col);
	static int* getCoord();
	static int getCol();
	static int getRow();
	static string reset;
	static string space;
	static string tab;
	static string endl;
private:
	static CONSOLE_SCREEN_BUFFER_INFO getConsoleScreenBufferInfo();
};

#endif // !CONSOLEOUT_H
