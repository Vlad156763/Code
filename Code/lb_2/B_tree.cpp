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
		if (t < 0 || t * 2 >= INT_MAX) throw error_2("FatalError: the number of keys is not valid for b-tree", 201);
		this->max_num_keys = 2 * t;
		/*передаю number_of_keys один раз, далі можна не передавати так як він є параметорм за 
		замовчуванням.*/
		this->root = new node(max_num_keys, true,nullptr); 
	}




	template<typename T> void b_tree<T>::add_keys(const T& data) {
		if (this->root->num_keys == this->max_num_keys - 1) {
			node* tmp = new node(this->max_num_keys, false, nullptr);
			tmp->children[0] = this->root;
			this->root = tmp;
			this->split_child(tmp, 0);
			this->insert_non_full(tmp, data);
		}
 		else this->insert_non_full(this->root, data);
	}
	template <typename T> void b_tree<T>::split_child(node* current_node, const int& i) {
		node* tmp = current_node->children[i];
		node* new_node = new node (this->max_num_keys, tmp->leaf, nullptr);
		new_node->num_keys = this->max_num_keys / 2 - 1;
		for (int j = 0; j < this->max_num_keys / 2 - 1; j++)
			new_node->array_keys[j] = tmp->array_keys[j + this->max_num_keys / 2];
		if (!tmp->leaf)
			for (int j = 0; j < this->max_num_keys / 2; j++)
				new_node->children[j] = tmp->children[j + this->max_num_keys / 2];
		tmp->num_keys = this->max_num_keys / 2 - 1;
		for (int j = current_node->num_keys; j >= i + 1; j--)
			current_node->children[j + 1] = current_node->children[j];
		current_node->children[i + 1] = new_node;
		for (int j = current_node->num_keys - 1; j >= i; j--)
			current_node->array_keys[j + 1] = current_node->array_keys[j];
		current_node->array_keys[i] = tmp->array_keys[this->max_num_keys / 2 - 1];
		current_node->num_keys++;
	}
	template <typename T> void b_tree<T>::insert_non_full(node* current_node, const  T& data) {
		int i = current_node->num_keys - 1;
		//якщо поточний вузол листок 
		if (current_node->leaf) {
			//переміщаю ключі вправо на 1 доти, доки незнайду місце для нового ключа
 			while (i >= 0 && data < current_node->array_keys[i]) {
				current_node->array_keys[i + 1] = current_node->array_keys[i]; i--; 
			}
			//вставляю ключ на це місце
			current_node->array_keys[i + 1] = data;
			current_node->num_keys++;
		}
		//якщо поточний вузол не листок
		else {
			while (i >= 0 && data < current_node->array_keys[i]) i--;
			i++;
			if (current_node->children[i]->num_keys == this->max_num_keys - 1) {
				split_child(current_node, i);
				if (data > current_node->array_keys[i]) i++;
			}
			insert_non_full(current_node->children[i], data);
		}
	}
	/*
	add_key(data) {
		node* father = this->root;
		if(!father->leaf) { // якщо батько не листок, 
			int i = 0;
			while(!father-children[0]->leaf) { // цикл, для пошуку батька, який має дитину-листка яка повинна мати ключ
			//цикл для пошуку дитини, відносно батька яка повинна мати ключ. 
			//Тут все коректно, якщо data менше найменшого, i = 0 , якщо ж data більше найбільшого, 
			//i = кількості ключів у дитині

				while(data > father->children[i]) {
					i++; //індекс дитини, яка повинна мати ключ.
				}
				father = father->children[i];
			} // нащадки батька це листки, 
			//шукаю вже у поточного батька дитину яка повинна мати ключ
			while(data > father->children[i]) {
					i++; //індекс дитини, яка повинна мати ключ.
				}

			
		}
		else { //якщо батько листок, 

		}
	}
	*/
	template<typename T> void b_tree<T>::add_key(const T& key) {
		node* father = this->root;
		int i = 0;
		if (!father->leaf) { // якщо батько не листок 
			// цикл, для пошуку батька, який має дитину-листка яка повинна мати ключ
			while (!father->children[0]->leaf) { 
				//цикл для пошуку дитини, відносно батька яка повинна мати ключ. 
				//Тут все коректно, якщо data менше найменшого, i = 0 , якщо ж data більше найбільшого, 
				//i = кількості ключів у дитині

				while (key > father->children[i]) i++; //індекс дитини, яка повинна мати ключ.
				father = father->children[i]; //рухаюсь до дитини, яка може мати ключ
			} 
			
			//шукаю вже у поточного батька дитину яка повинна мати ключ
			while (key > father->children[i]) i++; //індекс дитини, яка повинна мати ключ			
			//і - це покажчик на дитину, яка повинна мати ключ
		}
		else {
			if (father->num_keys == this->max_num_keys) {
				//викликаю ділення для батька (якщо вважати батьком коріневий елемент)
				//МОМЕНТО! 
				return;
			}
		}
		/*
		перевірка чи father->children[i] не повний
		Якщо повний, розділяю його.
		Якщо ні, методом сортування вставкою вставляю на місце ключ.
		*/
	
		if (father->children[i]->num_keys == this->max_num_keys) {
			//викликаю ділення для дитини батька			
			//МОМЕТНО! так як при поділу вузла спроба відсортувати масив і додати ключ може завершитись
			//невдало, так як вузли можуть змінитись, для цього треба якщо вже зайшли сюди, сортувати
			//в методі ділення вузла, але сортування для не заповнених комірок треба залишити, так як 
			//якщо я сюди не зайду, треба ключ у tmp помістити. і додай. покажчик на батька, так як рекурсія в такому
			//випадку не можлива, бо в мене не буде доступу до діда, якщо батько буде повний. 
			return;
		}
		//сортую tmp так як сортування треба в будь-якому випадку і для вузла, якщо він єдиний, 
		//і для листів, якщо вузоли не повні
		
	}
	template <typename T> void b_tree<T>::split_node(node* full_node, const T& key) {
		
		//При діленні вузлів, кореневий ділиться інакше, тому для нього інші умови трохи
		if (full_node == this->root) {
			node* new_root = new node(this->max_num_keys, false, nullptr);
			node* right_node = new node(this->max_num_keys, full_node->leaf, new_root);
			//full_node  - лівий вузол
			//якщо корінь це не листок (переписую всіх дітей з заповненого вузла в новий правий вузол) якщо ж листок, дітей не переписую
			if (!full_node->leaf) {
				for (int i = full_node->num_keys / 2 + 1, index_array = 0; i <= full_node->num_keys; i++, index_array++) {
					right_node->children[index_array] = full_node->children[i];//в новий вузол переписую всі покажчики на нащадків які стоять після центрального + 1 так як наступинй від центрального я записав перед списком
					full_node->children[i] = nullptr; //той покажчик, який перенесено до нового вузла у поточнову вузлі видаляю його.
					right_node->children[index_array]->father = right_node; // для переміщених нащадків змінюю батька
				}
			}
			//переписую тільки ключі в новий вузол
			for (int i = full_node->num_keys / 2 + 1, index_array = 0; i < full_node->num_keys; i++, index_array++) {
				right_node->array_keys[index_array] = full_node->array_keys[i]; //в новий вузол переписую всі ключі що більші цетрального 
				//контролюю розмір вузлів у поточному циклі
				right_node->num_keys++;
				full_node->num_keys--;
			}
			new_root->array_keys[0] = full_node->array_keys[full_node->num_keys / 2];//записую центральний ключ в новий вузол
			full_node->num_keys--; //контролюю тілкьи розмір, незважаючи на значення 
			new_root->num_keys++;
			new_root->children[0] = full_node; //в новий вузол який буде коренем записую лівого і правого нащадка (покажчики на батька для дітей майбутнього кореня встановлені раніше при створені вузлів)
			new_root->children[1] = right_node;
			this->root = new_root; //призначення нового вузла коренем
			full_node->father = new_root; 
		}
		//ділення вузлів, які не є коренем відбуваються за допомогою рекурсії доти, доки є можливість вставити ключ у батька, якщо можливості немає, викликається ця ж функція
		else {
			//якщо
			if (full_node->father->num_keys == this->max_num_keys) {

			}
		}

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
		os << tab << "(0_0_0)" << endl;
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
						os << tab << '[' << rows << '_' << index_node + 1 << '_' << ptr_next_node + 1 << ']' << endl;
				os << '}' << endl;
				// Якщо поточний вузол не листок, додаю його до списку
				if (!current_node->leaf) list.push_back(make_pair(make_pair(rows, index_node + 1), current_node));
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



	template <typename T> b_tree<T>::~b_tree() {
		
	}



	void test_b_tree() {
		b_tree<int> qa(2); //size aray = 3, кількість нащадків = 4
		qa.add_keys(1);
		qa.add_keys(3);
		qa.add_keys(156);
		qa.add_keys(63);
		qa.add_keys(122);
		qa.add_keys(11);
		qa.add_keys(0);
		qa.add_keys(-1);
		qa.add_keys(-111);
		qa.add_keys(23);
		qa.add_keys(1991);
		qa.add_keys(10);
		qa.add_keys(4);
		qa.add_keys(6);
		qa.add_keys(7);





		
		qa.print(cout);
	}
}

ostream& tab(ostream& os) {
	return os << '\t';
}
