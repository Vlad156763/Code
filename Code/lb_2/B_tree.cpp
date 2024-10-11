#include "B_tree.h"
#include "Exception_for_lb_2.h"
using namespace my_exceptions_2;
#include <iostream>
#include "../lb_1/Data_structures.h"
using data_struct::dl_list; 
using std::ostream;
using std::cout;
using std::endl;
using std::pair;
using std::make_pair;


ostream& tab(ostream& os);
namespace data_struct_b_tree {

	template <typename T> b_tree<T>::node::node(const int& max_number_of_keys, const bool& leaf, node* father) {
		this->array_keys = new T[max_number_of_keys - 1]; //кількість ключів 2t - 1
		this->children = new node * [max_number_of_keys]; //кількісxть дітей 2t
		this->leaf = leaf;
		for (int i = 0; i < max_number_of_keys; i++) {
			this->children[i] = nullptr;
		}
		this->father = father;
	}
	template <typename T> b_tree<T>::node::~node() {
		/*При створенні вузла, розір масивів одразу задається, тому не треба перевіряти
		чи покажчики не дорівнюють nullptr*/
		delete[] array_keys;
		for (int i = 0; i < this->max_number_of_keys; i++)
			delete this->children[i];
		delete[] this->children;
	}

	template <typename T> b_tree<T>::b_tree(const int& t) {
		/*перевірка параметра t, ящко він не відповідає умові викликається виключення.
		створюю новий вузол з розміром 2t і вказую що цей вузол листок (так як він є перший)*/
		if (t <= 1 || t * 2 >= INT_MAX) throw error_2("FatalError: the number of keys is not valid for b-tree", 201);
		this->max_num_keys = 2 * t;
		/*передаю number_of_keys один раз, далі можна не передавати так як він є параметорм за 
		замовчуванням.*/
		this->root = new node(max_num_keys, true,nullptr); 
	}

	template<typename T> void b_tree<T>::add_key(const T& key) {
		
		if (this->key_is_in(key)) throw error_2("SearchError: there cannot be more than one identical value in the b-tree", 13);
		node* father = this->root;
		node* ptr_node_sort = father; // вузол, в який за допомогою сорутвання вставлятиму ключ
		int i = 0;
		bool search_child = false;
		if (!father->leaf) { // якщо батько не листок 
			// цикл, для пошуку батька, який має дитину-листка яка повинна мати ключ
			while (!father->children[0]->leaf) {
				//цикл для пошуку дитини, відносно батька яка повинна мати ключ. 
				//Тут все коректно, якщо data менше найменшого, i = 0 , якщо ж data більше найбільшого, 
				//i = кількості ключів у дитині
				i = 0;
				while (i < father->num_keys && key > father->array_keys[i]) i++; //індекс дитини, яка повинна мати ключ.
				father = father->children[i]; //рухаюсь до дитини, яка може мати ключ
			}
			//шукаю вже у поточного батька дитину яка повинна мати ключ
			i = father->num_keys - 1;
			while (i >= 0 && key < father->array_keys[i]) i--; //індекс дитини, яка повинна мати ключ		
			i++;
			//і - це покажчик на дитину, яка повинна мати ключ
 			ptr_node_sort = father->children[i];
			if (father->children[i]->num_keys == this->max_num_keys - 1) {
				ptr_node_sort = split_node(father->children[i]);
				//знайти дитину, яка повинна мати key
				search_child = !search_child;
			}
		}
		else {
			if (father->num_keys == this->max_num_keys - 1) {
				ptr_node_sort = split_node(father);
				//знайти дитину, яка повинна мати key
				search_child = !search_child;
			}
		}
		//так як реалізація методу розбиття НЕ передбачає вставку нового ключа в дитину, метод просто
		//розбиває заповнений вузол (якщо ключ не можна буде вставити у батька, тоді робивається і батько і так далі.
		//після завершення виконання методу розбиття він повертає покажчик на батька для розбитого вузла 
		if (search_child) {
			int i = ptr_node_sort->num_keys - 1;
			while (key < ptr_node_sort->array_keys[i]) i--; i++;
			ptr_node_sort = ptr_node_sort->children[i];
		}
		//сортую ptr_node_sort так як сортування треба в будь-якому випадку і для кореня
		//якщо він не заповнений, і для листків, які не заповнені, і навіть після розділу ptr_node_sort теж треба відсортувати щоб вставити ключ
		/*if (!ptr_node_sort->children->leaf) {
			int i = ptr_node_sort->num_keys;
			while (i >= 0 && key < ptr_node_sort->array_keys[i -1]) {
				ptr_node_sort->children[i + 1] = ptr_node_sort->children[i];
				i--;
			}
		}*/
		//вставка ключів не може бути десь в середині дерева, ключі вставляються тілкьи в листки які не мають нащаків, а тому перевірки на нащадків зайві
		i = ptr_node_sort->num_keys - 1;
		while (i >= 0 && key < ptr_node_sort->array_keys[i]) {
			//вийти за межі індексації не вийде, так як у батька хоча б ОДИН ключ можна буде вставити тому що перед цим я перевіряю це
			ptr_node_sort->array_keys[i + 1] = ptr_node_sort->array_keys[i];
			i--;
		} i++;
		ptr_node_sort->array_keys[i] = key;
		ptr_node_sort->num_keys++;
	}
	template <typename T> typename b_tree<T>::node* b_tree<T>::split_node(node* full_node) {
		//При діленні вузлів, кореневий ділиться інакше, тому для нього інші умови трохи
		node* new_node = new node(this->max_num_keys, full_node->leaf, nullptr);
		if (full_node == this->root) {
			node* new_root = new node(this->max_num_keys, false, nullptr);
			new_node->father = new_root;
			//full_node  - лівий вузол
			new_root->array_keys[0] = full_node->array_keys[full_node->num_keys / 2];//записую центральний ключ в новий вузол
			full_node->num_keys--; //контролюю тілкьи розмір, незважаючи на значення 
			new_root->num_keys++;
			new_root->children[0] = full_node; //в новий вузол який буде коренем записую лівого і правого нащадка (покажчики на батька для дітей майбутнього кореня встановлені раніше при створені вузлів)
			new_root->children[1] = new_node;
			this->root = new_root; //призначення нового вузла коренем
			full_node->father = new_root; 
			
		}
		//ділення вузлів, які не є коренем відбуваються за допомогою рекурсії доти, доки є можливість вставити ключ у батька, якщо можливості немає, викликається ця ж функція
		else {
			//якщо у батька кількість ключів максимальна, рекурсивно рухаюсь доти, доки не буде можливість вставити ключ в батька
			if (full_node->father->num_keys == this->max_num_keys -1 ) {
				split_node(full_node->father);

			} 
			/*тут повинна бути реалізація розділу вузла якщо він не листок*/
			//покроково записувати ключі у right_node починаючи з центрального full_node ключа
			//якщо корінь це не листок (переписую всіх дітей з заповненого вузла в новий правий вузол) якщо ж листок, дітей не переписую
			//методом сортування вставкою шукаю місце куди вставити 
			int i = full_node->father->num_keys - 1;
			while (full_node->array_keys[full_node->num_keys/2] < full_node->father->array_keys[i]) {
				//вийти за межі індексації не вийде, так як у батька хоча б ОДИН ключ можна буде вставити
				full_node->father->array_keys[i + 1] = full_node->father->array_keys[i]; 
				full_node->father->children[i + 2] = full_node->father->children[i + 1];
				i--;
			}
			i++;
			full_node->father->array_keys[i] = full_node->array_keys[full_node->num_keys / 2];//записую у батька поточного вузла центр 
			full_node->father->children[i + 1] = new_node;
			full_node->father->num_keys++;
			full_node->num_keys--;
			new_node->father = full_node->father; //для нового правого вузла роблю батька таким самим як і для лівого вузла
			int index_child = 0;
		}
		//якщо корінь це не листок (переписую всіх дітей з заповненого вузла в новий правий вузол) якщо ж листок, дітей не переписую

		if (!full_node->leaf) {
			for (int i = full_node->num_keys / 2 + 1, index_array = 0; i <= full_node->num_keys + 1; i++, index_array++) {
				//після розбиття вузол може мати менше дітей, тому треба перевіряти дитину на nullptr бо інакше буде попередження 6011
				if (full_node->children[i] != nullptr) { // Перевіряю, чи дитина існує
					new_node->children[index_array] = full_node->children[i]; // Копіюю дитину
					new_node->children[index_array]->father = new_node; // Міняю батька, якщо дитина не NULL
					full_node->children[i] = nullptr; // Очищую старий вказівник
				}
			}

		}
		//переписую тільки ключі в новий вузол
		for (int i = full_node->num_keys / 2 + 1, index_array = 0; i < this->max_num_keys - 1; i++, index_array++) {
			new_node->array_keys[index_array] = full_node->array_keys[i]; //в новий вузол переписую всі ключі що більші цетрального 
			//контролюю розмір вузлів у поточному циклі
			new_node->num_keys++;
			full_node->num_keys--;
		}	
		return full_node->father; //для цього елементу треба знайти місце де можна вставити ключ
	}

	template <typename T> void b_tree<T>::print(ostream& os) {
		dl_list<pair<pair<int, int>, node*>> list;
		node* current_node = this->root;
		int rows = 1;
		int index_node = 1;
		int node_in_row = 0;
		os << rows << "*. --------------------------" << endl;
		os << "\033[38;2;100;128;255m" << 1 << "\033[0m \033[38;2;214;157;133mroot\033[0m";
		if (current_node->leaf) os << "\033[38;2;0;200;0m leaf \033[0m";
		else os << ' ';
		os << '{' << endl;
		// Виведення даних
		if (current_node->num_keys > 0) {
			os << tab;
			for (int keys = 0; keys < current_node->num_keys; keys++)
				os << "\033[38;2;255;0;0m|\033[0m" << current_node->array_keys[keys] << "\033[38;2;255;0;0m|\033[0m";
			os << endl;
		}
		// Виведення покажчиків на нащадків
		for (int ptr_next_node = 0; ptr_next_node < this->max_num_keys; ptr_next_node++) 
			if (current_node->children[ptr_next_node] != nullptr)
				os << tab << '[' << rows << '_' << index_node << '_' << ptr_next_node + 1 << ']' << endl;
		os << '}' << endl;
		// Якщо вузол не листок, додаю його до списку
		if (!current_node->leaf) list.push_back(make_pair(make_pair(rows, index_node), current_node));

		while (!list.is_empty()) {
			rows++;
			index_node = 0;
			os << rows << "*. --------------------------" << endl;
			node_in_row = 0;
			// Цикл для виведення всіх вузлів у рядку працює доти, доки в списку є вузол з попереднього рядка.
			while (!list.is_empty() && (list.front().first.first == rows - 1)) {
				node_in_row++;
				if (index_node < list.front().second->num_keys + 1)
					current_node = list.front().second->children[index_node];
				else {
					index_node = 0;
					list.pop_front(); // Видаляю вузол, який вже не треба
					node_in_row--;
					continue;
				}
				// Виведення вузла
				os << "\033[38;2;100;128;255m" << node_in_row << "\033[0m";
				if (current_node->leaf) os << "\033[38;2;0;200;0m leaf \033[0m";
				else os << ' ';
				os << '{' << endl;
				os << tab << '(' << list.front().first.first << '_' << list.front().first.second << '_' << index_node + 1 << ')' << endl;
				// Виведення даних вузла
				if (current_node->num_keys > 0) {
					os << tab;
					for (int keys = 0; keys < current_node->num_keys; keys++)
						os << "\033[38;2;255;0;0m|\033[0m" << current_node->array_keys[keys] << "\033[38;2;255;0;0m|\033[0m";
					os << endl;
				}
				// Виведення покажчиків на нащадків вузла
				for (int ptr_next_node = 0; ptr_next_node < this->max_num_keys && !current_node->leaf; ptr_next_node++) 
					if (current_node->children[ptr_next_node] != nullptr)
						os << tab << '[' << rows << '_' << node_in_row << '_' << ptr_next_node + 1 << ']' << endl;
				os << '}' << endl;
				// Якщо поточний вузол не листок, додаю його до списку
				if (!current_node->leaf) list.push_back(make_pair(make_pair(rows, node_in_row), current_node));
				index_node++;
			}
			
		}
		os << rows + 1 << "*. --------------------------" << endl;
		os << "\033[38;2;86;156;214mnullptr\033[0m" << endl;

	}

	template<typename T> T& b_tree<T>::operator[](const T& data) {
		node* tmp = this->root;
		if (tmp == nullptr) throw error_2("SearchError: b-tree is empty", 12);
		while (tmp != nullptr) {
			int l_side = 0;
			int r_side = tmp->num_keys - 1;
			// Якщо data менше за найменший ключ у вузлі
			if (data < tmp->array_keys[l_side]) {
				tmp = tmp->children[l_side];
				continue;
			}
			// Якщо data більше за найбільший ключ у вузлі
			if (data > tmp->array_keys[r_side]) {
				tmp = tmp->children[tmp->num_keys];
				continue;
			}
			// Бінарний пошук в межах ключів вузла
			while (l_side <= r_side) {
				int i = l_side + (r_side - l_side) / 2;
				if (tmp->array_keys[i] == data) return tmp->array_keys[i];  // Знайдено шуканий ключ
				if (tmp->array_keys[i] < data) l_side = i + 1;
				else r_side = i - 1;
			}
			// Якщо дійшли до листа і ключ не знайдено
			if (tmp->leaf) break;
			// Переміщуємося до відповідної дитини
			tmp = tmp->children[l_side];
		}
		throw error_2("SearchError: there is no such element in the b-tree", 11);
	}
	template<typename T> bool b_tree<T>::key_is_in(const T& data) {
		node* tmp = this->root;
		if (tmp == nullptr) throw error_2("SearchError: b-tree is empty", 12);
		while (tmp != nullptr) {
			int l_side = 0;
			int r_side = tmp->num_keys - 1;
			// Якщо data менше за найменший ключ у вузлі
			if (data < tmp->array_keys[l_side]) {
				tmp = tmp->children[l_side];
				continue;
			}
			// Якщо data більше за найбільший ключ у вузлі
			if (data > tmp->array_keys[r_side]) {
				tmp = tmp->children[tmp->num_keys];
				continue;
			}
			// Бінарний пошук в межах ключів вузла
			while (l_side <= r_side) {
				int i = l_side + (r_side - l_side) / 2;
				if (tmp->array_keys[i] == data) return true;  // Знайдено шуканий ключ
				if (tmp->array_keys[i] < data) l_side = i + 1;
				else r_side = i - 1;
			}
			// Якщо дійшли до листа і ключ не знайдено
			if (tmp->leaf) break;
			// Переміщуємося до відповідної дитини
			tmp = tmp->children[l_side];
		}
		return false;
	}


	template <typename T> b_tree<T>::~b_tree() {
		
	}
	int ID = 1;
	template<typename T> void print(b_tree<T>& qa) {
		cout << "\033[38;2;128;255;128mSTART: " << ID << "\033[38;2;0;0;255m";
		for (int i = 0; i < 15; i++) cout << "|||"; cout << "\033[0m" << endl;
		qa.print(cout);
		cout << "\033[38;2;128;255;128mEND: " << ID << "\033[38;2;0;0;255m";
		for (int i = 0; i < 15; i++) cout << "|||"; cout << "\033[0m" << endl;
		cout << endl << endl << endl;
		ID++;
	}

	void test_b_tree() {



		b_tree<int> qa(2); // Створюємо B-дерево з t=2

		// Вставляємо ключі в дерево
		qa.add_key(1);
		print(qa);
		qa.add_key(3);
		print(qa);
		qa.add_key(156);
		print(qa);
		qa.add_key(63);
		print(qa);
		qa.add_key(122);
		print(qa);
		qa.add_key(11);
		print(qa);
		qa.add_key(0);
		print(qa);
		qa.add_key(-1);
		print(qa);
		qa.add_key(-111);
		print(qa);
		qa.add_key(23);
		print(qa);
		qa.add_key(1991);
		print(qa);
		qa.add_key(10);
		print(qa);
		// Додаємо ключі, що змусять дерево виконати кілька розбиттів
		qa.add_key(15);
		print(qa);
		qa.add_key(50);
		print(qa);
		qa.add_key(5);
		print(qa);
		qa.add_key(9);
		print(qa);
		qa.add_key(200);
		print(qa);
		qa.add_key(150);
		print(qa);
		qa.add_key(75);
		print(qa);
		qa.add_key(18);
		print(qa);
		// Перевірка для від'ємних та граничних значень
		qa.add_key(-200);
		print(qa);
		qa.add_key(100);
		print(qa);
		qa.add_key(300);
		print(qa);
		qa.add_key(-50);
		print(qa);
		qa.add_key(-10);
		print(qa);
		try
		{
			cout << "Намагаюсь додати ключ, який вже є в дереві" << endl;
			qa.add_key(0);  // Перевірка на дублювання (передбачається, що дублювання заборонено)
			cout << "Ключ додався! Але не повинен був!" << endl;
		}
		catch (error_2& ex)
		{
			cout << "вставка ключа викликала помилку: " << ex.get_error_msg() << endl;
		}
		qa.add_key(250);
		print(qa);
		qa.add_key(60);
		print(qa);
		qa.add_key(85);
		print(qa);
		qa.add_key(99);
		print(qa);
		qa.add_key(101);
		print(qa);

		// Додаємо більше випадкових ключів
		qa.add_key(500);
		print(qa);
		qa.add_key(-500);
		print(qa);
		qa.add_key(350);
		print(qa);
		qa.add_key(175);
		print(qa);
		qa.add_key(225);
		print(qa);
		qa.add_key(30);
		print(qa);
		qa.add_key(130);
		print(qa);
		qa.add_key(40);
		print(qa);
		qa.add_key(220);
		print(qa);
		qa.add_key(-300);
		print(qa);

		try
		{
			cout << "Намагаюсь додати ключ, який вже є в дереві" << endl;
			qa.add_key(0);  // Перевірка на дублювання (передбачається, що дублювання заборонено)
			cout << "Ключ додався! Але не повинен був!" << endl;
		}
		catch (error_2& ex)
		{
			cout << "вставка ключа викликала помилку: " << ex.get_error_msg() << endl;
		}

		// Перевіряємо ще одну серію ключів для впевненості
		qa.add_key(999);
		print(qa);
		qa.add_key(888);
		print(qa);
		qa.add_key(777);
		print(qa);
		qa.add_key(555);
		print(qa);
		qa.add_key(333);
		print(qa);
		qa.add_key(111);
		print(qa);
		qa.add_key(222);
		print(qa);
		qa.add_key(444);
		print(qa);


		


		
		
	}
}

ostream& tab(ostream& os) {
	return os << '\t';
}
