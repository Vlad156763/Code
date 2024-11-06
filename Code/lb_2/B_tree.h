#ifndef B_tree
#define B_tree
#include <iostream>
#include "../lb_1/Data_structures.h"
#include "Exception_for_lb_2.h"

using std::string;
using namespace my_exceptions_2;
using data_struct::dl_list;
using std::ostream;
using std::cout;
using std::cin;
using std::endl;
using std::pair;
using std::make_pair;
using std::numeric_limits;
using std::streamsize;
namespace data_struct_b_tree {
	template<typename T> class b_tree {
	private:
		/*
		порядок дерева t
		кількість ключів у вузлі 2t - 1
		кількість покажчиків на нащадків 2t
		мінімальна кількість ключів у вузлі t - 1
		*/
		int t = 0;
		int max_num_keys = 0;
		int max_num_children = 0;
		int min_num_keys = 0;
		struct node{
		public:
			int t = 0; //порядок дерева (потрібно для видалення 
			T* array_keys = nullptr; //масив ключів
			node** children = nullptr; //масив покажчиків node*
			bool leaf = false; //true якщо вузол листок, і  false якщо ні
			int num_keys = 0; //кількість ключів означає 2*t це не порядок дерева
			node* father = nullptr; //покажчик на батька
			node(const int &, const bool&, node*);
			~node();
		}*root = nullptr;

		node* split_node(node*); //розділення вузлів
		node* key_is_in(const T&); //перевірка чи ключ є в дереві
		void del_all_nodes(node*);//рекурсивне видалення всіх вузлів

		//об'єднання вузлів
		void merge(node*, const int&, const int&);
		//позика у брата (перший параметр це покажчик на поточний вузол, другий параметр це індекс вузла відносно батька
		void borrow(node*, const int&, const int&);
		//видалення з листка
		void deletedKeyFromLeaf(node*, const int&, const int&);
		void deletedKeyFromNotLeaf(node*, const int&);
	public:
		void add_key(const T&);
		void del_key(const T&);
		void print(ostream&);
		b_tree(const int&); //параметр const int& для передачі t
		~b_tree(); 
	};
}
static ostream& tab(ostream& os);

static ostream& tab(ostream& os) {
	return os << '\t';
}
using namespace data_struct_b_tree;
template <typename T> b_tree<T>::node::node(const int& order, const bool& leaf, node* father) {
		this->array_keys = new T[2 * order - 1]; //кількість ключів 2t - 1
		this->children = new node * [2 * order]; //кількісxть дітей 2t
		this->leaf = leaf;
		for (int i = 0; i < (2 * order); i++) {
			this->children[i] = nullptr;
		}
		this->father = father;
	}
template <typename T> b_tree<T>::b_tree(const int& order) {
		if (order <= 1 || order * 2 >= INT_MAX) throw error_2("FatalError: the number of keys is not valid for b-tree", 201);
		this->t = order;
		this->max_num_keys = 2 * order - 1;
		this->max_num_children = 2 * order;
		this->min_num_keys = order - 1;
		this->root = new node(order, true, nullptr);
	}
template <typename T> void b_tree<T>::add_key(const T& key) {
		node* node_must_have_new_key = this->key_is_in(key);
		//метод пошуку ключа повертає покажчик на вузол, який має переданий ключ, якщо ключа немає, повертається nullptr
		if (node_must_have_new_key != nullptr) throw error_2("AddError: there cannot be more than one identical value in the b-tree", 13);
		node* ptr_node_sort = node_must_have_new_key = this->root;
		int i = 0;
		bool search_child = false;
		if (!node_must_have_new_key->leaf) { // якщо поточний вузол не листок 
			// цикл, для пошуку батька, який має дитину-листка яка повинна мати ключ
			while (!node_must_have_new_key->children[0]->leaf) {
				i = 0;
				while (i < node_must_have_new_key->num_keys && key > node_must_have_new_key->array_keys[i]) i++;
				node_must_have_new_key = node_must_have_new_key->children[i]; //рухаюсь до дитини, яка може мати ключ
			}
			//шукаю вже у поточного батька дитину яка повинна мати ключ
			i = node_must_have_new_key->num_keys - 1;
			while (i >= 0 && key < node_must_have_new_key->array_keys[i]) i--; //індекс дитини, яка повинна мати ключ		
			i++;
			//і - це покажчик на дитину, яка повинна мати ключ
			ptr_node_sort = node_must_have_new_key->children[i];
			if (node_must_have_new_key->children[i]->num_keys == this->max_num_keys) {
				ptr_node_sort = split_node(node_must_have_new_key->children[i]);
				//знайти дитину, яка повинна мати key
				search_child = !search_child;
			}
		}
		else {
			if (node_must_have_new_key->num_keys == this->max_num_keys) {
				ptr_node_sort = split_node(node_must_have_new_key);
				//знайти дитину, яка повинна мати key
				search_child = !search_child;
			}
		}

		//так як реалізація методу розбиття НЕ передбачає вставку нового ключа в дитину, метод просто
		//розбиває заповнений вузол (якщо ключ не можна буде вставити у батька, тоді робивається і батько і так далі.
		//після завершення виконання методу розбиття він повертає покажчик на батька для розбитого вузла 
		//шукаю вузлі, який повернтає метод split_node дитину яка може мати ключ
		if (search_child) {
			int i = ptr_node_sort->num_keys - 1;
			while (key < ptr_node_sort->array_keys[i]) i--; i++;
			ptr_node_sort = ptr_node_sort->children[i];
		}
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
		node* new_node = new node(this->t, full_node->leaf, nullptr);
		if (full_node == this->root) {
			node* new_root = new node(this->t, false, nullptr);
			new_node->father = new_root;
			new_root->array_keys[0] = full_node->array_keys[full_node->num_keys / 2];//записую центральний ключ в новий вузол
			full_node->num_keys--; //контролюю тілкьи розмір, незважаючи на значення 
			new_root->num_keys++;
			new_root->children[0] = full_node; //в новий вузол який буде коренем записую лівого і правого нащадка (покажчики на батька для дітей майбутнього кореня встановлені раніше при створені вузлів)
			new_root->children[1] = new_node;
			this->root = new_root; //призначення нового вузла коренем
			full_node->father = new_root;

		}
		//ділення вузлів, які не є коренем відбуваються за допомогою рекурсії доти, доки не з'явиться можливість вставити ключ у батька
		else {
			//якщо у батька кількість ключів максимальна, рекурсивно рухаюсь доти, доки не буде можливість вставити ключ в батька
			if (full_node->father->num_keys == this->max_num_keys) {
				split_node(full_node->father);

			}
			//переписую всіх дітей що більші центрального ключа  з заповненого вузла в новий вузол
			//методом сортування вставкою шукаю місце куди вставити ключ і вставляю його зміннючи розміри для вузлів
			int i = full_node->father->num_keys - 1;
			while (full_node->array_keys[full_node->num_keys / 2] < full_node->father->array_keys[i]) {
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
		}
		//якщо корінь це не листок (переписую всіх дітей з заповненого вузла в новий правий вузол) якщо ж листок, дітей не переписую
		if (!full_node->leaf) {
			for (int i = full_node->num_keys / 2 + 1, index_array = 0; i <= full_node->num_keys + 1; i++, index_array++) {
				//після розбиття вузол може мати менше дітей, тому треба перевіряти дитину на nullptr бо інакше буде попередження 6011
				if (full_node->children[i] != nullptr) { // Перевіряю, чи дитина існує
					new_node->children[index_array] = full_node->children[i]; // Копіюю дитину
					new_node->children[index_array]->father = new_node; // Міняю батька
					full_node->children[i] = nullptr; // Очищую старий покажчик
				}
			}

		}
		//переписую ключі в новий вузол
		for (int i = full_node->num_keys / 2 + 1, index_array = 0; i < this->max_num_keys; i++, index_array++) {
			new_node->array_keys[index_array] = full_node->array_keys[i]; //в новий вузол переписую всі ключі що більші цетрального 
			//контролюю кількість ключів на поточній ітерації
			new_node->num_keys++;
			full_node->num_keys--;
		}
		return full_node->father; //для цього елементу треба знайти місце де можна вставити ключ
	}
template <typename T> void b_tree<T>::print(ostream& os) {
		node* current_node = this->root;
		if (current_node->num_keys == 0) throw error_2("PrintError: b-tree is empty", 14);
		dl_list<pair<pair<int, int>, node*>> list;
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
		for (int ptr_next_node = 0; ptr_next_node < this->max_num_children; ptr_next_node++)
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
				os << tab << '(' << list.front().first.first << '_' << "\033[38;2;255;127;0m" << list.front().first.second << "\033[0m" << '_' << index_node + 1 << ')' << endl;
				// Виведення даних вузла
				if (current_node->num_keys > 0) {
					os << tab;
					for (int keys = 0; keys < current_node->num_keys; keys++)
						os << "\033[38;2;255;0;0m|\033[0m" << current_node->array_keys[keys] << "\033[38;2;255;0;0m|\033[0m";
					os << endl;
				}
				// Виведення покажчиків на нащадків вузла
				for (int ptr_next_node = 0; ptr_next_node < this->max_num_children && !current_node->leaf; ptr_next_node++)
					if (current_node->children[ptr_next_node] != nullptr)
						os << tab << '[' << rows << '_' << node_in_row << '_' << ptr_next_node + 1 << ']' << endl;
				os << '}' << endl;
				// Якщо поточний вузол не листок, додаю його до списку
				if (!current_node->leaf) list.push_back(make_pair(make_pair(rows, node_in_row), current_node));
				index_node++;
			}
		}
		os << rows + 1 << "*. --------------------------" << endl;
		os << "nullptr" << endl;
	}
template <typename T> typename b_tree<T>::node* b_tree<T>::key_is_in(const T& data) {
		//метод пошуку за ключем повертає покажчик на вузол, який має цей ключ.
		//якщо дерево пусте, викликається помилка, якщо ключа в дереві немає повертаю nullptr
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
				if (tmp->array_keys[i] == data) return tmp;  // Знайдено шуканий ключ
				if (tmp->array_keys[i] < data) l_side = i + 1;
				else r_side = i - 1;
			}
			// Якщо дійшли до листа і ключ не знайдено
			if (tmp->leaf) break;
			// Переміщуємося до відповідної дитини
			tmp = tmp->children[l_side];
		}
		return nullptr;
	}
template <typename T> b_tree<T>::~b_tree() {
		if (this->root != nullptr) {
			del_all_nodes(this->root);
		}
	}
template <typename T> void b_tree<T>::del_all_nodes(node* current_node_del) {
		// Якщо вузол не є листком, рекурсивно видаляю дітей
		if (!current_node_del->leaf)
			for (int i = 0; i <= current_node_del->num_keys; i++)
				if (current_node_del->children[i] != nullptr) {
					del_all_nodes(current_node_del->children[i]);
					delete current_node_del->children[i];
				}

		// Видаляю масив ключів і масив покажчиків на дітей
		//масив покажчиків у листку завжди nullptr, тому видаляти дітей для нього не має сенсу
		delete[] current_node_del->array_keys;
		delete[] current_node_del->children;
		current_node_del->array_keys = nullptr;
		current_node_del->children = nullptr;

		//father не видаляю бо не можна. Це порушить рекурсивне видалення
	}
template <typename T> b_tree<T>::node::~node() {
		delete[] this->array_keys;
		delete[] this->children;
	}
template <typename T> void b_tree<T>::del_key(const T& _d_key) {

		//_d_node повинен мати ключ який треба видалити  
		node* _d_node = this->key_is_in(_d_key); //шукаю вузол який має видаляючий ключ
		if (_d_node == nullptr) throw error_2("DeleteError: b-tree has no delete key", 15); //якщо вузол не знайдено, помилка
		int index_d_key = 0; //це індекс ключа, який видаляється (у вузлі)
		//шукаю ключ який треба видалити
		while (index_d_key < _d_node->num_keys && _d_node->array_keys[index_d_key] != _d_key) index_d_key++;

		int index_target_node_parent = -1; //це індекс цільового вузла, який має видляючий ключ
		//шукаю індекс поточного вузла відносно батька
		//якщо батько є - шукаю індекс у батька для поточного вузла 
		//якщо батька немає, індекс вузла для поточного вузла буде -1
		if (_d_node->father != nullptr) {
			int index_tmp = 0;
			for (; index_tmp < _d_node->father->num_keys && _d_node->father->children[index_tmp] != _d_node; index_tmp++);
			index_target_node_parent = index_tmp;
		}

		//якщо поточний вузол це листок
		if (_d_node->leaf) {
			deletedKeyFromLeaf(_d_node, index_target_node_parent, index_d_key);
		}
		//якщо поточний вузол не листок
		else {
			deletedKeyFromNotLeaf(_d_node, index_d_key);

		}
	}
template <typename T> void b_tree<T>::deletedKeyFromNotLeaf(node* current_node, const int& indexCurrentDeletedKey) {
		auto searchPrev = [current_node, indexCurrentDeletedKey]()->node* {
			node* nodeHavePrevious = current_node;
			//починаю з лівого піддерева відносно видаляючого ключа
			nodeHavePrevious = nodeHavePrevious->children[indexCurrentDeletedKey];
			//рухаюсь до листового рівня, і шукаю попередника для ключа
			for (; !nodeHavePrevious->leaf;) nodeHavePrevious = nodeHavePrevious->children[nodeHavePrevious->num_keys];
			return nodeHavePrevious;
			};
		auto searchNext = [current_node, indexCurrentDeletedKey]()->node* {
			node* nodeHaveNext = current_node;
			//починаю з правого піддерева відносно видаляючого ключа
			nodeHaveNext = nodeHaveNext->children[indexCurrentDeletedKey + 1];
			//рухаюсь до листового рівня, і шукаю наступника для ключа 
			for (; !nodeHaveNext->leaf;) nodeHaveNext = nodeHaveNext->children[0];
			return nodeHaveNext;
			};
		auto GetIndexCurrentNode = [](const node* father, const node* child)->int {
			int index_tmp = 0;
			for (; father->children[index_tmp] != child; index_tmp++);
			return index_tmp;
			};

		//спочатку перевіряю чи можна взяти безпечно наступника
		node* nodeHaveNext = searchNext();
		if (nodeHaveNext->num_keys > this->min_num_keys) {
			//беру наступника і записую у поточний вузол
			current_node->array_keys[indexCurrentDeletedKey] = nodeHaveNext->array_keys[0];
			//сортую всі ключі у вузлі який мав наступника
			for (int i = 0; i < nodeHaveNext->num_keys - 1; i++) nodeHaveNext->array_keys[i] = nodeHaveNext->array_keys[i + 1];
			//зменшую розмір вузла який мав наступника
			nodeHaveNext->num_keys--;
		}
		else {
			node* nodeHavePrev = searchPrev();
			//беру ключ (без перевірок) записую у поточний вузол, і перевіряю чи вузол, який має попередника має менше мінімуму ключів
			current_node->array_keys[indexCurrentDeletedKey] = nodeHavePrev->array_keys[nodeHavePrev->num_keys - 1];
			if (nodeHavePrev->num_keys > this->min_num_keys) {
				nodeHavePrev->num_keys--;
			}
			else {
				//викликаю видалення для листка
				deletedKeyFromLeaf(nodeHavePrev, GetIndexCurrentNode(nodeHavePrev->father, nodeHavePrev), nodeHavePrev->num_keys - 1);
			}
		}
	}
template <typename T> void b_tree<T>::merge(node* current_node, const int& indexCurrentNodeInFather, const int& indexCurrentDeletedKey) {
		int indexDeletedKeyForRekursion;
		node* father = nullptr;
		auto GetIndexCurrentNode = [](const node* father, const node* child)->int {
			int index_tmp = 0;
			for (; father->children[index_tmp] != child; index_tmp++);
			return index_tmp;
			};
		auto sortKeyInFather = [](node* current_nodeSort, const int& indexCurrentDeletedKey, const int& size)->void {
			//сортую ключі починаючи з видаляючого ключа
			for (int i = indexCurrentDeletedKey; i < size; i++)
				current_nodeSort->array_keys[i] = current_nodeSort->array_keys[i + 1];
			current_nodeSort->num_keys--;
			};
		//сортую ключі і зменшую розмір
		sortKeyInFather(current_node, indexCurrentDeletedKey, current_node->num_keys);


		//лівий брат
		if (indexCurrentNodeInFather - 1 >= 0) {
			node* leftBro = current_node->father->children[indexCurrentNodeInFather - 1];
			father = leftBro->father;
			//записую ключ з батька (між братами) у лівого брата
			leftBro->array_keys[leftBro->num_keys] = current_node->father->array_keys[indexCurrentNodeInFather - 1];
			//переписую ключі з поточного вузла у лівий вузол
			for (int i_LeftBro = leftBro->num_keys + 1, i_current = 0; i_current < current_node->num_keys; i_LeftBro++, i_current++) {
				leftBro->array_keys[i_LeftBro] = current_node->array_keys[i_current];
			}
			//якщо поточний вузол не листок переписую всі покажчики починаючи з 0 і встановлюю для дітей нового батька
			if (!current_node->leaf) {
				for (int i_LeftBro = leftBro->num_keys + 1, i_current = 0; i_current <= current_node->num_keys; i_current++, i_LeftBro++) {
					leftBro->children[i_LeftBro] = current_node->children[i_current];
					leftBro->children[i_LeftBro]->father = leftBro;
				}
			}
			//встановлюю розмір лівого брата
			leftBro->num_keys = leftBro->num_keys + current_node->num_keys + 1;
			// видаляю покажчик на пустий вузол
			delete father->children[indexCurrentNodeInFather];

			indexDeletedKeyForRekursion = indexCurrentNodeInFather - 1;
			//якщо батько корінь і має 0 ключів
			if (this->root == father && father->num_keys - 1 == 0) {
				//новим корнем ставля лівого брата, а корінь видаляю
				this->root = leftBro;
				delete leftBro->father;
				father = leftBro->father = nullptr;
			}
			else
				//якщо батько має менше мінімуму ключів
				if (father->num_keys - 1 < this->min_num_keys) {
					//знаходжу індекс батька у діда, і викликаю рекурсивне видалення
					this->deletedKeyFromLeaf(father, GetIndexCurrentNode(father->father, father), indexDeletedKeyForRekursion);
				} //в іншому випадку сортую ключі батька і зменшую йому розмір
				else {
					//у батька сортую покажчики 
					for (int i_child = indexCurrentNodeInFather; i_child < father->num_keys; i_child++) {
						father->children[i_child] = father->children[i_child + 1];
					}
					//очищаю покажчик на останню дитину у батька
					father->children[father->num_keys] = nullptr;

					sortKeyInFather(father, indexCurrentDeletedKey, father->num_keys - 1);
				}
		}
		//правий брат
		else if (indexCurrentNodeInFather + 1 <= current_node->father->num_keys) {
			node* rightBro = current_node->father->children[indexCurrentNodeInFather + 1];
			father = current_node->father;
			//записую ключ між братами у поточний вузол
			current_node->array_keys[current_node->num_keys] = father->array_keys[indexCurrentNodeInFather];
			//переписую всі ключі з права у поточний вузол
			for (int i_current = current_node->num_keys + 1, i_right = 0; i_right < rightBro->num_keys; i_current++, i_right++) {
				current_node->array_keys[i_current] = rightBro->array_keys[i_right];
			}
			//якщо потончий вузол не листок переписую всі покажчикики з правого брата починаючи з 0 і для цих покажчиків встановлюю нового батька 
			if (!current_node->leaf) {
				for (int i_current = current_node->num_keys + 1, i_right = 0; i_right <= rightBro->num_keys; i_current++, i_right++) {
					current_node->children[i_current] = rightBro->children[i_right];
					current_node->children[i_current]->father = current_node;
				}
			}
			// встановлюю розмір для поточного вузла
			current_node->num_keys = current_node->num_keys + rightBro->num_keys + 1;
			//видаляю покажчик на правого брата (так як він пустий)
			delete father->children[indexCurrentNodeInFather + 1];

			indexDeletedKeyForRekursion = indexCurrentNodeInFather;
			//якщо батько корінь і має 0 ключів
			if (this->root == father && father->num_keys - 1 == 0) {
				//новим корнем ставля лівого брата, а корінь видаляю
				this->root = current_node;
				delete current_node->father;
				father = current_node->father = nullptr;
			}
			else if (father->num_keys - 1 < this->min_num_keys) {
				this->deletedKeyFromLeaf(father, GetIndexCurrentNode(father->father, father), indexDeletedKeyForRekursion);
			}
			else {
				//у батька сортую покажчики 
				for (int i_child = indexCurrentNodeInFather + 1; i_child < father->num_keys; i_child++) {
					father->children[i_child] = father->children[i_child + 1];
				}
				//очищаю покажчик на останню дитину у батька
				father->children[father->num_keys] = nullptr;

				sortKeyInFather(father, indexCurrentDeletedKey, father->num_keys - 1);
			}
		}
	}
template <typename T> void b_tree<T>::borrow(node* current_node, const int& indexCurrentNodeInFather, const int& indexCurrentDeletedKey) {
		if (
			indexCurrentNodeInFather - 1 >= 0 && //перевірка чи є лівий брат
			current_node->father->children[indexCurrentNodeInFather - 1]->num_keys > this->min_num_keys) {
			//лівий брат
			node* leftBro = current_node->father->children[indexCurrentNodeInFather - 1];
			//зміщую ключі у поточному вузлі починаючи з видаляючого ключа і рухаючись до початку вузла
			for (int i = indexCurrentDeletedKey; i - 1 >= 0; i--) {
				current_node->array_keys[i] = current_node->array_keys[i - 1];
			}

			if (!current_node->leaf) {
				//зміщую покажчики на дітей починаючи з початку і до кінця вузла
				for (int i = current_node->num_keys; i - 1 >= 0; i--)
					current_node->children[i] = current_node->children[i - 1];
				//останній покажчик на вузол у лівому браті переміщаю у поточний вузол на початок і для нього встановлюю нового батю 
				current_node->children[0] = leftBro->children[leftBro->num_keys];
				current_node->children[0]->father = current_node;
			}
			//ключ між братами записую на нульове місце у поточний вузол
			current_node->array_keys[0] = current_node->father->array_keys[indexCurrentNodeInFather - 1];
			//останній ключ з лівого брата записую на місце батька
			current_node->father->array_keys[indexCurrentNodeInFather - 1] = leftBro->array_keys[leftBro->num_keys - 1];
			//очищаю покажчик на зайву дитину
			leftBro->children[leftBro->num_keys] = nullptr;
			//зменшую розмір лівого брата 
			leftBro->num_keys--;
		}
		else if (
			indexCurrentNodeInFather + 1 <= current_node->father->num_keys &&
			current_node->father->children[indexCurrentNodeInFather + 1]->num_keys > this->min_num_keys) {
			//правий брат
			node* rightBro = current_node->father->children[indexCurrentNodeInFather + 1];
			//зміщую ключі у поточному вузлі починаючи з видаляючого ключа і до кінця вузла
			for (int i = indexCurrentDeletedKey; i + 1 < current_node->num_keys; i++) {
				current_node->array_keys[i] = current_node->array_keys[i + 1];
			}
			//записую ключ з батька у кінець поточного вузла 
			current_node->array_keys[current_node->num_keys - 1] = current_node->father->array_keys[indexCurrentNodeInFather];

			//записую у батька ключ з правого вузла (наймнший)
			current_node->father->array_keys[indexCurrentNodeInFather] = rightBro->array_keys[0];

			//сортую ключі у брата на початок
			for (int i = 0; i < rightBro->num_keys - 1; i++) {
				rightBro->array_keys[i] = rightBro->array_keys[i + 1];
			}
			//якщо є діти, зсуваю всіх дітей на початок
			if (!rightBro->leaf) {
				//додаю першу дитину з правого вузла в кінець поточного і для неї роблю батьком поточний вузол
				current_node->children[current_node->num_keys] = rightBro->children[0];
				current_node->children[current_node->num_keys]->father = current_node;
				for (int i = 0; i < rightBro->num_keys; i++) {
					rightBro->children[i] = rightBro->children[i + 1];
				}
				//роблю останній покажчик у правого брата пустим
				rightBro->children[rightBro->num_keys] = nullptr;

			}
			//зменшую кількість ключів у правого брата на -1
			rightBro->num_keys--;
		}
		else {
			//об'єдную
			this->merge(current_node, indexCurrentNodeInFather, indexCurrentDeletedKey);
		}
	}
template <typename T> void b_tree<T>::deletedKeyFromLeaf(node* current_node, const int& indexCurrentNodeInFather, const int& indexCurrentDeletedKey) {
		//якщо вузол має більше мінімуму ключів - просто видаляю
		//якщо ні, викликаю метод позики

		//вузол має більше мінімальної кількості ключів або поточний вузол це корінь - просто видаляю з можливим сортуванням
		if (current_node->num_keys > this->min_num_keys || current_node->father == nullptr) {
			//якщо "index_d_key" не останній ключ в списку,пересуваю ключі (indexCurrentDeletedKey+1) на (index_d_key) 
			for (int i = indexCurrentDeletedKey; i < current_node->num_keys; i++) current_node->array_keys[i] = current_node->array_keys[i + 1];
			// якщо "index_d_key" останній, просто зменшую розмір масиву ключів
			//Або якщо я був у циклі і змістив ключі теж зменшую розмір
			current_node->num_keys--;
		}
		//в іншому випадку коли ключів у листку мінімальна кількість
		else {
			//позичаю у брата
			//VLAD: якщо не можна позичити у брата позика у брата сама викличе метод об'єднання (дивно, згоден, але є як є)
			borrow(current_node, indexCurrentNodeInFather, indexCurrentDeletedKey);
		}
	}

#endif // !B_tree