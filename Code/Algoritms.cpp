#include "Algoritms.h"
#include <iostream>
using std::ofstream;

namespace algoritms {
	void main_test_piramidal_sort(ostream& os) {
		os << "Пірамідальне сортування: \n";
		for (int i = 0; i < 20; i++) os << "==="; os << '\n';
		int arr[10]{ 98, 12, 45, -7, 63, 0, 23, -55, 71, 36 };
		os << "Початковий масив: ";
		for (int i = 0; i < 10; i++) {
			os << arr[i] << ' ';
		}
		os << '\n';
		os << "Відсортований масив: ";
		pyramidal_sort(arr, 10);
		for (int i = 0; i < 10; i++) {
			os << arr[i] << ' ';
		} 
		os << '\n';
		for (int i = 0; i < 20; i++) os << "==="; os << '\n';
	}


	static void sift_down(int* array, int& size, int current) {
		while (true) {
			int left_child = 2 * current + 1;
			if (left_child >= size) break;
			int right_child = 2 * current + 2;
			int largest = left_child;
			// Якщо правий нащадок більший за найбільшого нащадка
			if (right_child < size && array[right_child] > array[largest]) largest = right_child;
			if (array[current] >= array[largest]) break;
			int tmp = array[current];
			array[current] = array[largest];
			array[largest] = tmp;
			current = largest;
		}
	}
	void pyramidal_sort(int* array, int size) {
		// 1. Створення купи (перетворюємо масив у макс-купу)
		for (int i = size / 2 - 1; i >= 0; i--) sift_down(array, size, i);
		for (int i = size - 1; i > 0; i--) {
			int tmp = array[0];
			array[0] = array[i];
			array[i] = tmp;
			sift_down(array, i, 0);
		}
	}
}