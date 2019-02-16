//
// Решение предполагает использование кучи.
//

/****************************************************************************
Задача 6_2. Быстрое сложение.

Для сложения чисел используется старый компьютер. Время, затрачиваемое
на нахождение суммы двух чисел равно их сумме.

Таким образом для нахождения суммы чисел 1,2,3 может потребоваться
разное время, в зависимости от порядка вычислений.

((1+2)+3) -> 1+2 + 3+3 = 9

((1+3)+2) -> 1+3 + 4+2 = 10

((2+3)+1) -> 2+3 + 5+1 = 11

Требуется написать программу, которая определяет минимальное время,
достаточное для вычисления суммы заданного набора чисел.

*Формат входных данных.* Вначале вводится n - количество чисел. Затем
вводится n строк - значения чисел (значение каждого числа не превосходит
10^9, сумма всех чисел не превосходит 2*10^9).

*Формат выходных данных.* Натуральное число - минимальное время.

  in         | out
  -----------| -----
  5          | 45
  5 2 3 4 6  | 

  in         | out
  -----------| -----
  5          | 56
  3 7 6 1 9  | 

****************************************************************************/

#include <iostream>
#include <vector>
#include <algorithm>

template<class T, class Cmp = std::less_equal<T>>
struct Heap {
	std::vector<T> store;
	size_t last_elem = -1;
	Cmp cmp{};

	Heap() : store(1) {}

	size_t size() const noexcept { return last_elem + 1; }

	template<class U>
	void insert(U&& value) {
		if (size() == store.size()) store.resize(store.size() * 2);
		store[++last_elem] = std::forward<U>(value);

		int idx = last_elem;
		int parent = (idx - 1) / 2;
		while (cmp(store[idx], store[parent]) && idx) {
			std::swap(store[idx], store[parent]);
			idx = std::exchange(parent, (idx - 1) / 2);
		}
	}

	T pop() {
		if (last_elem == 0) return store[last_elem--];
		T result = std::exchange(store[0], store[last_elem--]);

		int idx = 0;
		int left_c, right_c;
		while (left_c = idx * 2 + 1, right_c = idx * 2 + 2, left_c <= last_elem) {
			int idx_of_interest = (right_c > last_elem || cmp(store[left_c], store[right_c]) ? left_c : right_c);
			if (!cmp(store[idx], store[idx_of_interest])) {
				std::swap(store[idx], store[idx_of_interest]);
				idx = idx_of_interest;
			} else break;
		}
		return result;
	}
};

int main() {
	int n; std::cin >> n;
	Heap<int> heap;
	for (int i = 0; i < n; ++i) {
		int tmp; std::cin >> tmp;
		heap.insert(tmp);
	}

	// so essentially at each step we replace the two least
	// numbers with their sum while mantaining the invariant
	int result = 0;
	while (heap.size() > 1) {
		int a = heap.pop(), b = heap.pop();
		result += a + b;
		heap.insert(a + b);
	}

	std::cout << result;
}
