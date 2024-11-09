#ifndef Data_structures_h
#define Data_structures_h
#include "My_exceptions.h"
#include <iostream>
using namespace my_exceptions;
using std::ostream;
using std::istream;

namespace data_struct {
	void main_test_dl_list(ostream&);
	void main_test_priory_queue_heap(ostream&);

	template<typename T> class dl_list {
	private:
		int size = 0;
		struct node {
		public:
			T value;
			node* next_node = nullptr;
			node* prev_node = nullptr;
			node(const T & = T(), node* = nullptr, node* = nullptr);
			~node();
		}*first_node = nullptr, * last_node = nullptr;
		node* search(const int&);
		const node* search(const int&) const;
	public:
		dl_list();
		dl_list(const dl_list<T>&);
		~dl_list();

		void push_front(const T&); //додавання вузла на початок
		void insert(const T&, const int&); //вставка вузла за індексом 
		void push_back(const T&);//додавання вузла в кінець
		bool is_empty(); //якщо голова пуста, повертаю false
		void pop_front(); //видалення вузла на початку
		void remove_at(const int&); //видалення вузла за індексом
		void pop_back(); //видалення вузла в кінці
		void clear(); //видалення всіх вузлів
		void print_from_end(ostream&) const;
		void print_from_start(ostream&) const;
		void print_withoutSpace(ostream&)const;
		dl_list& operator = (const dl_list<T>&);
		template<typename T1> friend ostream& operator << (ostream&, const dl_list<T1>&);

		T& front();
		int get_size();
		T& operator [] (const int&);
		const T& operator [] (const int&)const;
	};

	template <typename T> class priory_queue_heap {
	public:
		struct node {
		public:
			T value;
			int priory;
		};
		priory_queue_heap(const priory_queue_heap<T>::node*, const int&);
		void add(const T&, const int&);
		void del(const int&);
		~priory_queue_heap();
		priory_queue_heap();
		T get();

		priory_queue_heap(const priory_queue_heap<T>&);
		priory_queue_heap<T>& operator = (const priory_queue_heap<T>&);
		template<typename T1> friend ostream& operator << (ostream&, const priory_queue_heap<T1>&);
	private:
		int size = 0;
		node* array = nullptr;
		void sift_up();
		void sift_down(const int& = 0);
	};

	template <typename T> priory_queue_heap<T>::priory_queue_heap() {}
	template <typename T> priory_queue_heap<T>::priory_queue_heap(const priory_queue_heap<T>::node* array_pa, const int& size) {
		for (int i = 0; i < size; i++)
			this->add(array_pa[i].value, array_pa[i].priory);
	}
	template <typename T> priory_queue_heap<T>& priory_queue_heap<T>::operator=(const priory_queue_heap<T>& other) {
		if (this != &other) {  // Перевірка на самоприсвоєння
			delete[] this->array;
			this->size = other.size;
			if (other.array != nullptr) {
				this->array = new node[other.size];
				for (int i = 0; i < other.size; i++) this->array[i] = other.array[i];
			}
			else this->array = nullptr;
		}
		return this;
	}
	template <typename T> priory_queue_heap<T>::priory_queue_heap(const priory_queue_heap<T>& other) : size(other.size) {
		if (other.array != nullptr) {
			this->array = new node[other.size];
			for (int i = 0; i < other.size; i++)
				this->array[i] = other.array[i];
		}
	}
	template <typename T> void priory_queue_heap<T>::del(const int& index) {
		if (index >= 0 && index < this->size) {
			if (index != 0) {
				this->array[index] = this->array[this->size - 1];
				node* new_array = new node[this->size - 1];
				this->size--;
				new_array = this->array;
				sift_down(index);
			}
			else {
				this->array = nullptr;
				this->size = 0;
			}
		}
		else throw my_exceptions::error("DeleteError: attempting to delete a non-existent element", 202);
	}
	template <typename T> T priory_queue_heap<T>::get() {
		if (this->array != nullptr) {
			T value = this->array[0].value;
			this->array[0] = this->array[this->size - 1];
			this->del(this->size - 1);
			sift_down(); // можна не відправляти індекс, так як за замовчуванням стоїть 0
			return value;
		}
		else throw my_exceptions::error("GetError: heap is empty", 204);
	}
	template <typename T> priory_queue_heap<T>::~priory_queue_heap() {
		if (array != nullptr)  delete[] this->array;
	}
	template <typename T> void priory_queue_heap<T>::sift_up() {
		for (int current = this->size - 1; current > 0;) {
			int parent = (current - 1) / 2;
			if (this->array[current].priory > this->array[parent].priory) {
				node tmp = this->array[current];
				this->array[current] = this->array[parent];
				this->array[parent] = tmp;
				current = parent;
			}
			else break;
		}
	}
	template <typename T> void priory_queue_heap<T>::sift_down(const int& index) {
		int current = index;
		while (true) {
			int left_child = 2 * current + 1;
			if (left_child >= this->size) break;
			int right_child = 2 * current + 2;
			int largest = left_child;
			// Якщо правий нащадок більший за найбільшого нащадка
			if (right_child < size && this->array[right_child].priory > this->array[largest].priory) largest = right_child;
			if (this->array[current].priory >= this->array[largest].priory) break;
			node tmp = this->array[current];
			this->array[current] = this->array[largest];
			this->array[largest] = tmp;
			current = largest;
		}
	}
	template <typename T> void priory_queue_heap<T>::add(const T& data, const int& priory_pa) {
		if (this->array == nullptr) {
			this->array = new node[1];
			this->array[0].value = data;
			this->array[0].priory = priory_pa;
		}
		else {
			node* tmp = new node[this->size + 1];
			for (int i = 0; i < this->size; i++)
				tmp[i] = this->array[i];
			delete[] this->array;
			tmp[this->size].value = data;
			tmp[this->size].priory = priory_pa;
			this->array = tmp;
		}
		this->size++;
		this->sift_up();
	}
	template <typename T1> ostream& operator << (ostream& os, const priory_queue_heap<T1>& obj) {
		if (obj.array != nullptr) {
			for (int i = 0; i < obj.size; i++) os << '[' << obj.array[i].value << " (" << obj.array[i].priory << ')' << ']' << "  ";
		}
		else throw my_exceptions::error("DisplayError: heap is empty", 206);
		return os;
	}


	template <typename T> bool dl_list<T>::is_empty() {
		return (this->first_node == nullptr) ? true : false;
	}
	template <typename T> T& dl_list<T>::front() {
		if (this->first_node == nullptr) throw error(" GetError: list is empty", 209);
		return this->first_node->value;
	}
	template <typename T> dl_list<T>::node::node (const T& data, node* next_node_pa, node* prev_node_pa)
		:value(data), next_node(next_node_pa), prev_node(prev_node_pa) {}
	template <typename T> dl_list<T>::node::~node() {
		this->next_node = nullptr;
		this->prev_node = nullptr;
	}
	template <typename T> dl_list<T>::dl_list() {}
	template <typename T> dl_list<T>::~dl_list() {
		while (this->first_node != nullptr)
			this->pop_front();
	}
	template <typename T> dl_list<T>::dl_list(const dl_list<T>& other) {
		this->clear();
		for (int i = 0; i < other.size; i++) {
			this->push_back(other[i]);
		}
	}
	template <typename T> void dl_list<T>::push_front(const T& data) {
		node* new_node = new node(data, this->first_node);
		if (this->first_node != nullptr) this->first_node->prev_node = new_node;
		else  this->last_node = new_node;
		this->first_node = new_node;
		this->size++;
	}
	template <typename T> void dl_list<T>::pop_front() {
		if (this->first_node != nullptr) {
			node* tmp = this->first_node;
			this->first_node = this->first_node->next_node;
			if (this->first_node != nullptr) this->first_node->prev_node = nullptr;
			else this->last_node = nullptr;
			delete tmp;
			this->size--;
		}
		else throw my_exceptions::error("DeleteError: attempting to delete a non-existent element", 202);
	}
	template <typename T> void dl_list<T>::push_back(const T& data) {
		node* new_node = new node(data, nullptr, this->last_node);
		if (this->last_node != nullptr) this->last_node->next_node = new_node;
		else this->first_node = new_node;
		this->last_node = new_node;
		this->size++;
	}
	template <typename T> void dl_list<T>::pop_back() {
		if (this->last_node != nullptr) {
			node* tmp = this->last_node;
			this->last_node = this->last_node->prev_node;
			if (this->last_node != nullptr) this->last_node->next_node = nullptr;
			else this->first_node = nullptr;
			delete tmp;
			this->size--;
		}
		else throw my_exceptions::error("DeleteError: attempting to delete a non-existent element", 202);
	}
	template <typename T> void dl_list<T>::insert(const T& data, const int& index) {
		if (index >= 0 && index <= this->size) {
			if (index == 0) this->push_front(data);
			else if (index == this->size) this->push_back(data);
			//вставка вузла після index
			else {
				node* tmp;
				/*якщо новий елемент знаходиться ближче до початку*/
				if (index <= this->size / 2) {
					tmp = this->first_node;
					for (int i = 0; i < index - 1; ++i) tmp = tmp->next_node;
				}
				/*якщо новий елемент знаходиться ближче до кінця*/
				else {
					tmp = this->last_node;
					for (int i = this->get_size() - 1; i > index - 1; --i) tmp = tmp->prev_node;
				}
				// Вставка нового вузла між tmp і tmp->next_node
				node* new_node = new node(data, tmp->next_node, tmp);
				tmp->next_node->prev_node = new_node;
				tmp->next_node = new_node;
				this->size++;
			}
		}
		else throw my_exceptions::error("IndexError: list index out of range", 201);
	}
	template <typename T> typename dl_list<T>::node* dl_list<T>::search(const int& index) {
		if (index >= 0 && index < this->size) {
			node* tmp;
			/*якщо новий елемент знаходиться ближче до початку*/
			if (index <= this->size / 2) {
				tmp = this->first_node;
				/* tmp не може дорівнювати nullptr, тому що index вже є в діапазоні від 0 до this->size*/
				for (int i = 0; i < index; ++i) tmp = tmp->next_node;
			}
			else {
				tmp = this->last_node;
				for (int i = this->size - 1; i > index; --i) tmp = tmp->prev_node;
			}
			return tmp;
		}
		else throw my_exceptions::error("IndexError: list index out of range", 201);
	}
	template <typename T> const typename dl_list<T>::node* dl_list<T>::search(const int& index) const{
		if (index >= 0 && index < this->size) {
			node* tmp;
			/*якщо новий елемент знаходиться ближче до початку*/
			if (index <= this->size / 2) {
				tmp = this->first_node;
				/* tmp не може дорівнювати nullptr, тому що index вже є в діапазоні від 0 до this->size*/
				for (int i = 0; i < index; ++i) tmp = tmp->next_node;
			}
			else {
				tmp = this->last_node;
				for (int i = this->size - 1; i > index; --i) tmp = tmp->prev_node;
			}
			return tmp;
		}
		else throw my_exceptions::error("IndexError: list index out of range", 201);
	}
	template <typename T> void dl_list<T>::remove_at(const int& index) {
		try {
			node* tmp = this->search(index);
			if (tmp == first_node) this->pop_front();
			else if (tmp == last_node) this->pop_back();
			/*В іншому випадку все працюватиме коректно
			1. Якщо два вузла, викличеться один з методів pop_front або pop_back
			2. Якщо індекс більше розміру списку, або списку немає, this->search кине вийняток 201*/
			else {
				tmp->prev_node->next_node = tmp->next_node;
				tmp->next_node->prev_node = tmp->prev_node;
				delete tmp;
				this->size--;
			}
		}
		catch (my_exceptions::error& er) {
			//перевіряю чи точно мій метод кинув виключення, а не службова якась штучка
			if (er.get_error_code() == 201) throw my_exceptions::error("DeleteError: attempting to delete a non-existent element", 202);
		}
	}
	template <typename T> void dl_list<T>::print_from_start(ostream& os) const {
		if (this->first_node != nullptr) {
			typename dl_list<T>::node* tmp = this->first_node;
			while (tmp->next_node != nullptr) {
				os << tmp->value << ' ';
				tmp = tmp->next_node;
			}
			os << tmp->value;
		}
		else throw my_exceptions::error("DisplayError: list is empty", 203);
	}
	template <typename T> void dl_list<T>::print_from_end(ostream& os) const {
		if (this->last_node != nullptr) {
			typename dl_list<T>::node* tmp = this->last_node;
			while (tmp != nullptr) {
				os << tmp->value << ' ';
				tmp = tmp->prev_node;
			}
		}
		else throw my_exceptions::error("DisplayError: list is empty", 203);
	}
	template <typename T> void dl_list<T>::print_withoutSpace(ostream& os) const {
		if (this->first_node != nullptr) {
			typename dl_list<T>::node* tmp = this->first_node;
			while (tmp != nullptr) {
				os << tmp->value;
				tmp = tmp->next_node;
			}
		}
		else throw my_exceptions::error("DisplayError: list is empty", 203);
	}
	template <typename T> T& dl_list<T>::operator [] (const int& index) { return search(index)->value; }
	template <typename T> const T& dl_list<T>::operator [] (const int& index) const { return search(index)->value; }
	template <typename T> int dl_list<T>::get_size() { return this->size; }
	template <typename T> ostream& operator << (ostream& os, const dl_list<T>& obj) {
		obj.print_withoutSpace(os);
		return os;
	}
	template <typename T> void dl_list<T>::clear() {
		while (!this->is_empty()) {
			this->pop_front();
		}
	}
	template <typename T> dl_list<T>& dl_list<T>::operator=(const dl_list<T>& other) {
		if (this != &other) {
			this->clear();
			for (int i = 0; i < other.size; i++) 
				this->push_back(other[i]);
		}
		return *this;
	}

}

#endif //Data_structures