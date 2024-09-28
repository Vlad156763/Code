#include "Data_structures.h"
namespace data_struct {
	max_heap::max_heap() {}

	max_heap::max_heap(const int* array, const int& size) {
		for (int i = 0; i < size; i++) this->add(array[i]);
	}

	void max_heap::print(ostream& os) { this->heap.print_from_start(os); }

	void max_heap::add(const int& data) {
		this->heap.push_back(data);
		this->sort();
	}

	//всі портібні перевірки відбуваються в класі  dl_list
	int& max_heap::get(const int& index) { return this->heap[index]; }

	void max_heap::del(const int& index) {
		this->heap[index] = this->heap[this->heap.get_size() - 1];
		this->heap.pop_back();
		this->sort();
	}
	void max_heap::sort() {
		/*
		сортування відбувається наступним чином:
		1. беру останній елемент 
		1.1 перевіряю його з батьком, якщо батько < нащадка, змінюю нащадка та батька місцями 
		1.2 повторюю операцію 1.1 доти, доки не буде батько > нащадка
		2. Переходжу до елементу (останній -1) і повторюю дії написані в пункті 1.1 та 1.2
		3. Повторюю дії 2 доти, доки не дійду до [0] елементу.
		*/
		int parent;
		for (int i = 0, index_heap = this->heap.get_size() -1; i < this->heap.get_size() - 1; ) {
			
			//якщо поточний елемент це корінь, який не має батька
			//або якщо поточний елемент менше батька
			//перевіряю останній елемент -i 
			if (index_heap == 0 || this->heap[index_heap] <= this->heap[(index_heap - 1) / 2]) {
				//перевіряю поточний елемент, якщо він дорівнює останньому -i
				//інкрементую i
				if (index_heap == (this->heap.get_size() - 1 - i)) i++;
				index_heap = this->heap.get_size() - 1 - i;
				
			}
			parent = (index_heap - 1) / 2;
			//якщо поточнй елемнт більше батька, змінюю місцями батька та дитину
			//і переставляю index_heap на батька
			if (this->heap[index_heap] > this->heap[parent]) {
				int tmp = this->heap[index_heap];
				this->heap[index_heap] = this->heap[parent];
				this->heap[parent] = tmp;
				index_heap = parent;
			}
		}
	}
}
