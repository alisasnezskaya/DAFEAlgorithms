/****************************************************************************
Написать структуру данных, обрабатывающую команды push* и pop*.

*Формат входных данных.*
В первой строке количество команд n. n ≤ 1000000.
Каждая команда задаётся как 2 целых числа: a b.
a = 1 - push front
a = 2 - pop front
a = 3 - push back
a = 4 - pop back

Для очереди используются команды 2 и 3. Для дека используются все четыре команды.

Если дана команда pop*, то число b - ожидаемое значение.Если команда
pop вызвана для пустой структуры данных, то ожидается "-1".

*Формат выходных данных.*
Требуется напечатать YES - если все ожидаемые значения совпали. Иначе,
если хотя бы одно ожидание не оправдалось, то напечатать NO.
****************************************************************************/

/****************************************************************************
 Задача 4_1.

Реализовать очередь с динамическим зацикленным буфером.

  in    | out
  ------|-----
  3     | YES
  3 44  | 
  3 50  | 
  2 44  | 

  in    | out
  ------|-----
  2     | YES
  2 -1  | 
  3 10  | 

  in    | out
  ------|-----
  2     | NO
  3 44  | 
  2 66  | 

****************************************************************************/

#include <iostream>
#include <memory>
#include <exception>

#if __cplusplus >= 201703
#include <optional>
#else
namespace std { // yes i'm aware it's UB
  struct nullopt_t {} nullopt;

  template<class T>
  struct optional {
    T value;
    bool has_value = false;

    template<class U>
    optional(U&& value) : value(std::forward<U>(value)), has_value(true) {}
    optional(nullopt_t) : has_value(false) {};

    T operator*() {
      if (!has_value) throw std::logic_error("empty optional");
      return value;
    }
  };
};
#endif


template<class T>
struct ring_queue {
  size_t capacity; // grows by factor of two

  std::unique_ptr<T[]> ring;
  size_t begin = 0; size_t end = 0;

  explicit ring_queue(size_t n) : capacity(1 + n), ring(std::make_unique<T[]>(capacity * sizeof(T))) {}

  uint64_t size() const noexcept {
    return (end - begin + capacity) % capacity;
  }

  template<class U>
  void push(U&& value) {
    if (size() == capacity - 1) {
      const size_t elems_n = size();
      std::unique_ptr<T[]> new_ring = std::make_unique<T[]>(capacity * sizeof(T));
      if (end > begin) std::move(ring.get() + begin, ring.get() + end, new_ring.get());
      else {
        std::move(ring.get() + begin, ring.get() + capacity, new_ring.get());
        std::move(ring.get() + 0, ring.get() + end, new_ring.get() + capacity - begin);
      }
      ring = std::move(new_ring);
      capacity *= 2;
      begin = 0, end = elems_n;
    }

    ring.get()[end % capacity] = std::forward<U>(value);
    end = (end + 1) % capacity;
  }

  std::optional<T> pop() {
    if (size() == 0) return std::nullopt;
    T value = std::move(ring.get()[begin]);
    begin = (begin + 1) % capacity;
    return value;
  }
};

int main() {
  enum cmds { push_front = 1, pop_front, push_back, pop_back };

  int n; std::cin >> n;
  ring_queue<int> queue(1);

  bool ok = true;
  for (int i = 0; std::cin && i < n; ++i) {
    int cmd, operand;
    std::cin >> cmd >> operand; if (!cmd) throw std::invalid_argument("invalid input");
    switch (cmd) {
      case pop_front: {
        int value;
        try {
          value = *queue.pop();
        } catch (std::exception& e) {
          value = -1;
        }
        ok = ok && value == operand;
        break;
      }
      case push_back: queue.push(operand); break;
      default: throw std::invalid_argument("invalid input");
    }
  }

  std::cout << (ok ? "YES" : "NO");
}
