#include "ConsoleOut.h"
string out::rgb(const int& r,const int& g,const int& b) {
	return "\033[38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m"; 
}

string out::moveTo(const int& row, const int& col) {
	return "\033[" + to_string(row + 1) + ";" + to_string(col + 1) + "H"; 
}

int* out::getCoord() {
    static int coord[2]{
        getConsoleScreenBufferInfo().dwCursorPosition.Y,
        getConsoleScreenBufferInfo().dwCursorPosition.X 
    };
    return coord;
}

int out::getCol() {
    return getConsoleScreenBufferInfo().dwCursorPosition.X;
}

int out::getRow() {
    return getConsoleScreenBufferInfo().dwCursorPosition.Y;
}
string out::reset = "\033[0m";
string out::space = " ";
string out::tab = "    ";
string out::endl = "\n";

CONSOLE_SCREEN_BUFFER_INFO out::getConsoleScreenBufferInfo() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        throw ex(1, "Помилка отримання десктриптора консолі");
    }
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) {
        throw ex(2, "Помилка отримання інформації про буфер екрана консолі");
    }
    return csbi;
}