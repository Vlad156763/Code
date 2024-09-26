#ifndef Data_structures_h
#define Data_structures_h
#include "My_exeptions.h"
#include <ostream>
#include <iostream>
using namespace my_exeptions;
using std::ostream;
namespace data_struct {
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
		node* search(const int&); //повернення вузла за індексом
	public:
		dl_list();
		~dl_list();
		void push_front(const T&); //додавання вузла на початок
		void insert(const T&, const int&); //вставка вузла за індексом 
		void push_back(const T&);//додавання вузла в кінець

		void pop_front(); //видалення вузла на початку
		void remove_at(const int&); //видалення вузла за індексом
		void pop_back(); //видалення вузла в кінці

		void print_from_end(ostream&) const;
		void print_from_start(ostream&) const;

		T& operator [] (const int&);
	};

	template <typename T> dl_list<T>::node::node
	(const T& data, node* next_node_pa, node* prev_node_pa)
		:value(data), next_node(next_node_pa), prev_node(prev_node_pa) {}

	template<typename T> dl_list<T>::node::~node() {
		this->next_node = nullptr;
		this->prev_node = nullptr;
	}

	template<typename T> dl_list<T>::dl_list() {}
	template<typename T> dl_list<T>::~dl_list() {
		while (this->first_node != nullptr)
			this->pop_front();
	}

	template<typename T> void dl_list<T>::push_front(const T& data) {
		node* new_node = new node(data, this->first_node);
		if (this->first_node != nullptr) this->first_node->prev_node = new_node;
		else  this->last_node = new_node;
		this->first_node = new_node;
		this->size++;
	}
	template<typename T> void dl_list<T>::pop_front() {
		if (this->first_node != nullptr) {
			node* tmp = this->first_node;
			this->first_node = this->first_node->next_node;
			if (this->first_node != nullptr) this->first_node->prev_node = nullptr;
			else this->last_node = nullptr;
			delete tmp;
			this->size--;
		}
		else throw error("DeleteError: list is empty", 202);
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
		else throw error("DeleteError: list is empty", 202);
	}

	template<typename T> void dl_list<T>::insert(const T& data, const int& index) {
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
					for (int i = this->size - 1; i > index - 1; --i) tmp = tmp->prev_node;
				}
				// Вставка нового вузла між tmp і tmp->next_node
				node* new_node = new node(data, tmp->next_node, tmp);
				tmp->next_node->prev_node = new_node;
				tmp->next_node = new_node;
				this->size++;
			}
		}
		else throw error("IndexError: list index out of range", 201);
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
		else throw error("IndexError: list index out of range", 201);
	}

	template <typename T> void dl_list<T>::remove_at(const int& index) {
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

	template <typename T> void dl_list<T>::print_from_start(ostream& os) const {
		if (this->first_node != nullptr) {
			typename dl_list<T>::node* tmp = this->first_node;
			while (tmp != nullptr) {
				os << tmp->value << ' ';
				tmp = tmp->next_node;
			}
		}
		else throw error("DisplayError: list is empty", 203);
	}
	template <typename T> void dl_list<T>::print_from_end(ostream& os) const {
		if (this->last_node != nullptr) {
			typename dl_list<T>::node* tmp = this->last_node;
			while (tmp != nullptr) {
				os << tmp->value << ' ';
				tmp = tmp->prev_node;
			}
		}
		else throw error("DisplayError: list is empty", 203);
	}
	template <typename T> T& dl_list<T>::operator [] (const int& index) {
		return search(index)->value;
	}
}
#endif //Data_structures