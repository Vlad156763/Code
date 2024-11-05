#ifndef B_tree
#define B_tree
#include <iostream>
#include "../lb_1/Data_structures.h"
using data_struct::dl_list;
using std::ostream;

void Fhome_Btree(dl_list<const char*>&, bool&);
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
#endif // !B_tree

