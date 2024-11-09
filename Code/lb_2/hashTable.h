#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <iostream>
#include <cmath>
using std::operator<<;
using std::ostream;
using std::sqrt;
/*
хеш таблиця з відкритою адресацією та квадратичним дослідженням повинна мати
розмір таблиці щоб число було просте, в іншому випадку буде виключення
*/
template<typename KEY, typename VAL> class hash_Table {
private:
	struct slot	{
		KEY key;
		VAL val;
		bool is_free = true;
		void print(ostream&);
	};
	slot* ArraySlots = nullptr;
	int size = 0;
	double A = 0.618033; 
	int numEl = 0;

public:
	hash_Table(const int&);
	~hash_Table();
	void insert(const KEY&, const VAL&);
	void del(const KEY&);
	VAL search(const KEY&);
	void print(ostream&);
	double loadFactor();

private:
	slot& searchSlot(const KEY&);
	int hash(const KEY&);
	bool isPrime(const int&);
};
template <typename KEY, typename VAL> hash_Table<KEY, VAL>::hash_Table(const int& size) {
	if (!this->isPrime(size)) throw error_2("FatalError: The size of the hash table is not prime", 20);
	this->size = size;
	//створюю масив розміром який був переданий як параметр 
	this->ArraySlots = new slot[this->size];
}
template <typename KEY, typename VAL> hash_Table <KEY, VAL>::~hash_Table() {
	if (numEl != 0) {
		delete[] this->ArraySlots;
	}
}
template <typename KEY, typename VAL> void hash_Table <KEY, VAL>::insert(const KEY& key, const VAL& val) {
	//якщо за певним індексом в таблиці можна записати значення - записую його
	int index = this->hash(key);
	bool keyIsNone = true;

	if(this->loadFactor() >= 80) throw error_2("Warning: Hash table is almost full!(So key not Added)", 18);
	//якщо поточний індекс має однаковий ключ - замінюю значення на нове
	//якщо за потончим індексом не можна вставити пару - використовую квадратичне дослідження
	//якщо пройшовши у всій таблиці не знайшлось вільного місця - кидаю виключення що таблиця повна
	if (!ArraySlots[index].is_free && this->ArraySlots[index].key != key) {
		for (int i = 1; i <= this->size; i++) {
			int new_index = (index + i * i) % this->size;
			if (this->ArraySlots[new_index].is_free) {
				keyIsNone = false;
				index = new_index;
				break;
			}
		}
	}
	//в іншому випадку вставляю ключ та значення під індексом
	else keyIsNone = false;
		
	if (keyIsNone) throw error_2("AddError: Hash table is full!", 17);
	this->ArraySlots[index].key = key;
	this->ArraySlots[index].val = val;
	this->ArraySlots[index].is_free = false;
	this->numEl++;
}
template <typename KEY, typename VAL> int hash_Table <KEY, VAL>::hash(const KEY& key) {
	return ((key * this->A) - (KEY)(key * this->A)) * this->size; //хеш функція множення 
}
template <typename KEY, typename VAL> void hash_Table <KEY, VAL>::slot::print(ostream& os) {
	os
		<< "(\033[38;2;0;255;0m" << this->key << "\033[0m)"
		<< "\033[38;2;255;0;0m" << "|" << "\033[0m"
		<< this->val 
		<< "\033[38;2;255;0;0m" << "|" << "\033[0m";
}
template <typename KEY, typename VAL> void hash_Table <KEY, VAL>::print(ostream& os) {
	bool is_empty = true;
	for (int i = 0; i < this->size; i++) {
		if (!this->ArraySlots[i].is_free) {
			os << "\033[38;2;255;127;0m[" << i << "]\033[0m - ";
			this->ArraySlots[i].print(os); 
			os << endl;
			is_empty = false;
		}
	}
	if (is_empty) throw error_2("PrintError: hash table is empty", 19);
}
template <typename KEY, typename VAL> typename hash_Table <KEY, VAL>::slot& hash_Table<KEY, VAL>::searchSlot(const KEY& key) {
	//пропускаю ключ через хеш фукнцію
	int index = this->hash(key);
	//перевіряю чи збігаються ключі у комірці, якщо так - повертаю комірку, якщо ні - використовую квадратичне дослідження
	if (!this->ArraySlots[index].is_free && this->ArraySlots[index].key == key) return this->ArraySlots[index];
	else
		for (int i = 1; i <= this->size; i++) {
			int new_index = (index + i * i) % this->size;
			if (!this->ArraySlots[new_index].is_free && this->ArraySlots[new_index].key == key)
				return this->ArraySlots[new_index];
		}
	throw error_2("SearchError: Hash Table has no target key", 18);
}
template <typename KEY, typename VAL> void hash_Table <KEY, VAL>::del(const KEY& key) {
	//за допомогою методу пошуку шукаю слот, який має відповідний ключ
	slot* tmp = &this->searchSlot(key);
	tmp->is_free = true;
	this->numEl--;
}
template <typename KEY, typename VAL> VAL hash_Table <KEY, VAL>::search(const KEY& key) {
	return this->searchSlot(key).val;
}
template <typename KEY, typename VAL> bool hash_Table <KEY, VAL>::isPrime(const int& key) {
	// Число менше 2 не просте
	if (key <= 1) return false;

	// 2 - єдине парне просте число
	if (key == 2) return true;

	// Всі інші парні числа не прості
	if (key % 2 == 0) return false;

	// Перевіряю числа від 3 до корінь n
	int limit = sqrt(key);
	for (int i = 3; i <= limit; i += 2) {
		if (key % i == 0) return false;
	}
	return true;
}
template <typename KEY, typename VAL> double hash_Table <KEY, VAL>::loadFactor() {
	return (static_cast<double>(this->numEl) / this->size) * 100;
}
#endif //!HASHTABLE_H