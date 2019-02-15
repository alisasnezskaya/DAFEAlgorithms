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
#include <cstdint>

uint64_t least_prime_divisor(uint64_t N) {
	if (N % 2 == 0) { return 2; }
	for (int i = 3; i <= std::sqrt(N); i += 2) {
		if (N % i == 0) { return i; }
	}
	return N;
}

int main() {
	uint64_t N; std::cin >> N;
	// N = K * (A + B)
	// Let's bruteforce the sum A + B

	uint64_t multiplier = least_prime_divisor(N);
	uint64_t K = N / multiplier;
	std::cout << K * 1 << " " << K * (multiplier - 1);
}