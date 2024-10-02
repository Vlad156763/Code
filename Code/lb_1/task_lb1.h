#ifndef task_lb1
#define task_lb1
#include <iostream>
using std::ostream;
using std::istream;
using std::string;

/*
Двозв'язний список
додавання вузла в початок списку,
додавання вузла,
пошук вузла в списку,
видалення вузла,
виведення вузлів на екран з початку та з кінця.
*/

/*
Купа(черга з пріорітетами)
вставлення елементу,
сортування елементів,
побудова купи з невпорядкованого масиву,
видалення елементу, 
сортування елементів із використанням купи,
виведення елементів на екран.
*/
/*
Пірамідальне сортування
*/



/*
Варіант No 3
Інформація про студентів групи включає наступну інформацію:
– прізвище, ім’я, по батькові;
– адреса;
– середній бал;
– стать;
– дата народження.
Вивести перелік місяців, відсортований за кількістю студентів
групи, які народилися в даний місяць. У випадку однакової кількості
за абеткою.
*/
//Масиви данних зберігаються у файлах

namespace task {
	using std::ostream;
	void main_test_task(ostream&, istream&);
	void main_test_all_files();
	class student {
	private:
		string PIB; // прізвище, ім’я, по батькові
		string adress; //адреса
		double middle_bal; //середнй бал
		string sex;
		int birthday[3]; //дата народження 01.01.0001
	public:
		student (
			const string&,
			const string&,
			double,
			const string&,
			int,
			int,
			int 
		);
		string get_PIB() const;
		string get_adress() const;
		double get_middle_bal() const;
		string get_sex() const;
		int get_day() const;
		int get_month() const;
		int get_year() const;
	};

}
#endif //task_lb1