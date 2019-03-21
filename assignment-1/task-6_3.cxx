//
// Решение предполагает использование кучи.
//

/****************************************************************************
Задача 6_3. Тупики.

На вокзале есть некоторое количество тупиков, куда прибывают
электрички. Этот вокзал является их конечной станцией. Дано расписание
движения электричек, в котором для каждой электрички указано время ее
прибытия, а также время отправления в следующий рейс. Электрички в
расписании упорядочены по времени прибытия. Когда электричка прибывает,
ее ставят в свободный тупик с минимальным номером. При этом если
электричка из какого-то тупика отправилась в момент времени X, то
электричку, которая прибывает в момент времени X, в этот тупик ставить
нельзя, а электричку, прибывающую в момент X+1 — можно.

В данный момент на вокзале достаточное количество тупиков для работы по
расписанию.

Напишите программу, которая по данному расписанию определяет, какое
минимальное количество тупиков требуется для работы вокзала.

*Формат входных данных.* Вначале вводится n - количество электричек в
расписании. Затем вводится n строк для каждой электрички, в строке -
время прибытия и время отправления. Время - натуральное число от 0 до
10\^9. Строки в расписании упорядочены по времени прибытия.

*Формат выходных данных.* Натуральное число - минимальное количеством
тупиков.

*Максимальное* время: 50мс, память: 5Мб.

  in     | out
  -------|-----
  1      | 1
  10 20  | 

  in     | out
  -------|-----
  2      | 2
  10 20  | 
  20 25  | 

  in     | out
  -------|-----
  3      | 2
  10 20  | 
  20 25  | 
  21 30  | 

****************************************************************************/

#include <iostream>
#include <vector>

struct Min_Heap {
	void shiftDown(int);
	void shiftUp(int);
	void add(int data) { buffer.push_back(data); shiftUp(size() - 1); }
	int getMin();
	int size() { return buffer.size(); }
private:
	std::vector<int> buffer;
	int getAt(int i) { if (i >= size()) return -1; return buffer[i]; }
	int c1(int i) { return 2 * i + 1; }
	int c2(int i) { return 2 * i + 2; }
	int p(int i) { return (i - 1) / 2; }
};

void Min_Heap::shiftDown(int index) {
	if (c1(index) < size() && getAt(index) > getAt(c1(index)) || c2(index) < size() && getAt(index) > getAt(c2(index))) {
		if (getAt(c1(index)) < getAt(c2(index))) {
			std::swap(buffer[index], buffer[c1(index)]);
			shiftDown(c1(index));
		}
		else {
			std::swap(buffer[index], buffer[c2(index)]);
			shiftDown(c2(index));
		}
	}
}

void Min_Heap::shiftUp(int index) {
	if (p(index) >= 0 && getAt(p(index)) > getAt(index)) {
		std::swap(buffer[index], buffer[p(index)]);
		shiftUp(p(index));
	}
}

int Min_Heap::getMin() {
	if (size() == 0) return -1;
	int result = buffer[0];
	std::swap(buffer[0], buffer[size() - 1]);
	buffer.pop_back();
	shiftDown(0);
	return result;
}

int main() {
	Min_Heap heap;
	int n;
	std::cin >> n;
	for (int i = 0; i < n; i++) {
		int arrival;
		int departure;
		std::cin >> arrival;
		std::cin >> departure;
		if (heap.size() == 0)
			heap.add(departure);
		else {
			int min_now = heap.getMin();
			if (arrival <= min_now) heap.add(min_now);
			heap.add(departure);
		}
	}
	std::cout << heap.size() << std::endl;
}
