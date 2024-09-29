#ifndef task_lb1
#define task_lb1
#include <iostream>
using std::ostream;
using std::istream;
using std::string;

namespace task {
	using std::ostream;
	void main_test_task(ostream&, istream&);
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