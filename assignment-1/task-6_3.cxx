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
