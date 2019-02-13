//
// Решение предполагает использование стека.
// Способ реализации стека может быть любым (список/динамический массив).
//

/****************************************************************************
 Задача 5_1. Скобочная последовательность.

Дан фрагмент последовательности скобок, состоящей из символов (){}[].

Требуется определить, возможно ли продолжить фрагмент в обе стороны,
получив корректную последовательность.

Длина исходной последовательности ≤ 800000.

*Формат входных данных.* Строка, содержащая символы (){}[] и,
возможно, перевод строки.

*Формат выходных данных.* Если возможно - вывести минимальную корректную
последовательность, иначе - напечатать "IMPOSSIBLE".

  in          | out
  ------------|--------------------------
  {}[[[[{}[]  | {}[[[[{}[]]]]]
  {][[[[{}[]  | IMPOSSIBLE
  ]()}[](({}  | {[]()}[](({}))

****************************************************************************/

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

char complement(char ch) {
	switch (ch) {
		case '(': return ')';
		case '[': return ']';
		case '{': return '}';
		case ')': return '(';
		case ']': return '[';
		case '}': return '{';
	}
}

int main() {
	std::string s; std::cin >> s;
	std::string z = s;
	std::vector<char> q;
	for (int i = 0; i < s.size(); ++i) {
		char ch = s[i];
		if (ch == '(' || ch == '[' || ch == '{') q.push_back(ch);
		else if (q.size()) {
			if (q.back() == complement(ch)) {
				q.pop_back();
			} else {
				std::cout << "IMPOSSIBLE", exit(0);
			}
		}
		else z.insert(0, 1, complement(ch));
	}
	std::transform(q.rbegin(), q.rend(), std::back_inserter(z), complement);

	std::cout << z;
}
