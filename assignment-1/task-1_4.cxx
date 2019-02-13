/****************************************************************************
Задача 1_4.

Дано натуральное число N. Представить N в виде A + B, так, что
НОД(A, B) максимален, A ≤ B. Вывести A и B. Если возможно несколько
ответов - вывести ответ с минимальным A.
n ≤ 10^7.

  in  | out
  ----|------
  35  | 7 28
****************************************************************************/

#include <iostream>
#include <cmath>
#include <limits>
#include <numeric>
#include <cstdint>
#include <utility>

int main() {
	uint64_t N; std::cin >> N;
	// N = K * (A + B)
	// Let's bruteforce the sum A + B

	uint64_t multiplier = -1;
	if (N % 2 == 0) {
		multiplier = 2;
		goto finish;
	}
	for (int i = 3; i <= std::sqrt(N); ++i) {
		if (N % i == 0) {
			multiplier = i;
			goto finish;
		}
	}
	multiplier = N;
finish:
	uint64_t K = N / multiplier;
	std::cout << K * 1 << " " << K * (multiplier - 1);
}
