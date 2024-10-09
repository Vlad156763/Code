#ifndef B_tree
#define B_tree
#include <iostream>
using std::ostream;

namespace data_struct_b_tree {
	void test_b_tree();

	template<typename T> class b_tree {
	private:
		int max_num_keys = 0;
		struct node{
		public:
			T* array_keys = nullptr; //масив ключів
			node** children = nullptr; //масив покажчиків node*
			bool leaf = false; //true якщо вузол листок, і  false якщо ні
			int num_keys = 0;
			node* father = nullptr;
			node(const int &, const bool&, node*);
			~node();
			
		}*root = nullptr;
		
		void insert_non_full(node*, const T&);
		void split_child(node*, const int&);


		void split_node(node*, const T&);
	public:

		b_tree(const int&); //параметр const int& для передачі t

		void add_keys(const T&);
		void print(ostream&);
		T& operator[](const T&);//шукаю елемент за значенням
		~b_tree(); 


		void add_key(const T&);

	};
}
#endif // !B_tree

