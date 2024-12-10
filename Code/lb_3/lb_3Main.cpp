#include "lb_3Main.h"

void ui::show() {
	bool exit = false;
	do {
		vector<pair<string, double>> qa;
		double priceNatives;
		double budget;
		double tonns;
		bool exitLoopSetT = false;
		do {
			double t = 0;
			cout << "Капітане! Яка вмістимість ваших трюмів? (в тоннах): ";
			cin >> t;
			if (cin.fail() || t <= 0 || t >= INT_MAX) {
				cout
					<< out::rgb(255, 0, 0)
					<< "Капітане! Ви ввели щось не те. Треба число від 1 до INT_MAX."
					<< out::reset << "Спробуйте ще раз "
					<< out::rgb(128, 128, 255) << ";)" << out::reset << out::endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			tonns = t;
			cout << out::rgb(255, 255, 127) << "Капітане! Ваш трюм на " << t;
			if (t == 1) cout << " тонну";
			else if (t >= 2 && t <= 4) cout << " тонни";
			else cout << " тонн";
			cout << " дуже великий! Вигідний корабель маєте!" << out::endl << out::reset;

			cout << "Капітане! Який ваш бюджет? (в гривнях): ";
			cin >> budget;
			if (cin.fail() || budget < 0 || budget >= INT_MAX) {
				cout
					<< out::rgb(255, 0, 0)
					<< "Капітане! Ви ввели щось не те. Треба число від 0 до INT_MAX."
					<< out::reset << "Спробуйте ще раз "
					<< out::rgb(128, 128, 255) << ";)" << out::reset << out::endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			cout << out::rgb(255, 255, 127) << "Капітане! А я бачу ваш бюджет у " << budget;
			if (budget == 1) cout << " гривеню";
			else if (budget >= 2 && budget <= 4) cout << " гривні";
			else cout << " гривень";
			cout << " дуже великий! Ваш корабель дійсно вигідний!" << out::endl << out::reset;

			cout << "Яка ціна продукції за кілограм у туземців? (в гривнях): ";
			cin >> priceNatives;
			if (cin.fail() || priceNatives <= 0 || priceNatives >= INT_MAX) {
				cout
					<< out::rgb(255, 0, 0)
					<< "Капітане! Ви ввели щось не те. Треба число від 1 до INT_MAX."
					<< out::reset << "Спробуйте ще раз "
					<< out::rgb(128, 128, 255) << ";)" << out::reset << out::endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			cout << out::rgb(255, 255, 127) << "Оце ми зараз на тих тубільцях грошиків наваримо! Це ж треба кілограм продукції за " << priceNatives;
			if (priceNatives == 1) cout << " гривеню";
			else if (priceNatives >= 2 && priceNatives <= 4) cout << " гривні";
			else cout << " гривень";
			cout << " !" << out::endl << out::reset;

			cout << out::endl << out::rgb(128, 255, 128) << "**Введіть назву продукту, натисніть enter, введіть ціну продукту. Щоб завершити введіть \\END**" << out::endl << out::reset;
			bool exitLoopSetProductAndPrise = false;
			do {
				cout << "> ";
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				double price = 0;
				string productName;
				getline(cin, productName);
				if (productName == "\\END" || productName == "\\end") { exitLoopSetProductAndPrise = true; }
				else {
					cout << out::rgb(128, 128, 255) << "> ";
					cin >> price;
					cout << out::reset << out::endl;
					if (cin.fail() || price <= 0 || price >= INT_MAX) {
						cout
							<< out::rgb(255, 0, 0)
							<< "Капітане! Ви ввели щось не те. Ціна може бути більше 0 і до INT_MAX."
							<< out::reset << "Спробуйте ще раз "
							<< out::rgb(128, 128, 255) << ";)" << out::reset << out::endl;
						cin.clear();
						continue;
					}
					qa.push_back(make_pair(productName, price));
				}

			} while (!exitLoopSetProductAndPrise);
			exitLoopSetT = true;
		} while (!exitLoopSetT);
		cout << out::rgb(128, 255, 128) << out::endl << "**На переговорах з туземцями**" << out::reset << out::endl;
		cout << out::rgb(128, 128, 128) << "Чукча: " << out::reset << "Одже, ви знаєте що продукцію ми продаємо за однаковою ціною, а саме " << out::rgb(128, 128, 255) << priceNatives
			<< out::reset << " грн за кілограм? Сказав голова туземців." << out::endl;
		cout << out::rgb(128, 128, 128) << "Капітан: " << out::reset << "Так, знаю, мені матрос Ковальський доповів. \nОдже, я маю список продукції яка мені треба, і я хочу знати чи є вона у вас, і скільки." << out::endl;
		cout << out::rgb(128, 128, 128) << "Чукча: " << out::reset << "Поговоріть із Бандурою, він відповідає за склад і яка в нас є продукція і її кількість." << out::endl;
		cout << out::rgb(128, 128, 128) << "Бандура: " << out::reset << "Вітаю. Одже, я буду вам казати кількість продукції в тоннах, а ви записуйте або запам'ятовуйте.";
		cout << out::rgb(128, 255, 128) << out::endl << out::endl << "**записуйте те, що каже туземець (якщо продукту немає, вводьте 0, none, немає, або ставте дефіс \"-\") \nв іншому випадку записуйте скільки тонн є у туземців того, чи іншого продукту**" << out::reset << out::endl;
		vector < pair<string, double>> is_product(qa.size());
		for (int i = 0; i < qa.size(); i++) {
			is_product[i].first = qa[i].first;
			string isProductInNatives;
			bool exitLoop = false;
			do {
				cout << qa[i].first << out::tab;
				cin >> isProductInNatives;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				if (isProductInNatives == "0" || isProductInNatives == "none" || isProductInNatives == "None" ||
					isProductInNatives == "Немає" || isProductInNatives == "немає" || isProductInNatives == "-") {
					is_product[i].second = 0;
				}
				else {
					try {
						is_product[i].second = stod(isProductInNatives);
						if (is_product[i].second <= 0 || is_product[i].second >= INT_MAX)throw int(0);
					}
					catch (const invalid_argument ex) {
						cout << out::rgb(255, 0, 0) << "Капітане, або ви неправильно пишите, або Бандура не те говорить."
							<< out::reset << " Ну не може ж бути вага продукту " << isProductInNatives << ". Спробуйте ще раз" << out::endl;
						continue;
					}
					catch (const int ex) {
						cout << out::rgb(255, 0, 0) << "Капітане, або ви неправильно пишите, або Бандура не те говорить."
							<< out::reset << " Ну не може ж бути вага продукту " << isProductInNatives << ". Спробуйте ще раз" << out::endl;
						continue;
					}
				}
				exitLoop = true;
			} while (!exitLoop);
		}
		cout << out::rgb(128, 255, 128) << out::endl << "**Результат**" << out::reset << out::endl;
		cout << "Об'єм трюму: " << out::moveTo(out::getRow(), 40) << out::rgb(127, 127, 255) << tonns << out::reset << " т" << out::endl;
		cout << "Бюджет: " << out::moveTo(out::getRow(), 40) << out::rgb(127, 127, 255) << budget << out::reset << " грн" << out::endl;
		cout << "Ціна продукту у туземців: " << out::moveTo(out::getRow(), 40) << out::rgb(127, 127, 255) << priceNatives << out::reset << " грн" << out::endl;
		cout << "Продукція, туземців: " << out::endl;
		for (int i = 0; i < is_product.size(); i++) {
			cout << out::tab << is_product[i].first << ": " << out::rgb(127, 127, 255) << is_product[i].second << out::reset << " т" << out::endl;
		}
		cout << "Що треба купити виходячи з місткості, \nцін, бюджету та наявності продукції:" << out::endl;
		double priceAllProd = 0;
		double budgetMain = budget;
		while (true) {
			double maxPriceInHome = 0;
			int ImaxPrice = 0;
			for (int i = 0; i < qa.size(); i++) {
				if (qa[i].second > maxPriceInHome) { maxPriceInHome = qa[i].second; ImaxPrice = i; }
			}
			if (maxPriceInHome <= priceNatives || tonns == 0 || budget == 0 || is_product.size() == 0) break;
			double NumkgProduct = 0;
			NumkgProduct = tonns * 1000;
			NumkgProduct = ((budget / priceNatives) < NumkgProduct) ? budget / priceNatives : NumkgProduct;
			NumkgProduct = (NumkgProduct > (is_product[ImaxPrice].second * 1000)) ? is_product[ImaxPrice].second * 1000 : NumkgProduct;

			priceAllProd += (NumkgProduct * qa[ImaxPrice].second);
			budget -= (NumkgProduct * priceNatives);
			tonns -= (NumkgProduct / 1000);
			cout << out::tab << qa[ImaxPrice].first << ": " << out::rgb(127, 127, 255) << NumkgProduct / 1000 << out::reset << " т" << out::tab
				<< out::rgb(127, 255, 127) << "+" << (NumkgProduct * qa[ImaxPrice].second) << out::tab
				<< out::rgb(255, 127, 127) << "-" << (NumkgProduct * priceNatives) << out::reset << out::endl;

			qa.erase(qa.begin() + ImaxPrice); is_product.erase(is_product.begin() + ImaxPrice);
		}
		if (priceAllProd == 0) cout << out::rgb(255, 0, 0) << "Немає що купувати" << out::endl << out::reset;
		cout << "Об'єм трюму що залишився: " << out::moveTo(out::getRow(), 40) << out::rgb(127, 127, 255) << tonns << out::reset << " т" << out::endl;
		cout << "Бюджет що залишився: " << out::moveTo(out::getRow(), 40) << out::rgb(127, 127, 255) << budget << out::reset << " грн" << out::endl;
		cout << "Ціна всієї продукції: " << out::moveTo(out::getRow(), 40) << out::rgb(127, 127, 255) << priceAllProd << out::reset << " грн" << out::endl;
		cout << "Чистий заробіток: " << out::moveTo(out::getRow(), 40) << out::rgb(127, 127, 255) << budget - budgetMain + priceAllProd << out::reset << " грн" << out::endl;
		
		do
		{
			cout << out::endl << "Бажаєте повторити? [y/n] ";
			string again;
			cin >> again;
			if (again == "n" || again == "no" || again == "NO" || again == "No") { exit = true; break; }
			else if (again == "y" || again == "yes" || again == "YES" || again == "Yes") { exit = false; break; }
			else {
				cout << out::rgb(255, 0, 0) << "Помилка! Ви ввели щось не те. Спробуйте ще раз." << out::reset << out::endl; continue;
			}

		} while (true);
	} while (!exit);
}