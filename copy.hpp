#pragma once
#include <cassert>
#include <format>
#include <iostream>
#include <vector>
using namespace std;

namespace cp {
template <class Item>
using Vector_ = std::vector<Item>;
auto concat(Vector_<int> const &v, int const x)
    -> Vector_<int> {
  auto result{v};
  result.push_back(x);
  return result;
}
auto collatz_aux(int const n, Vector_<int> const &result)
    -> Vector_<int> {
  std::cout << result.data() << std::endl;
  if (n == 1) {
    return result;
  }

  auto const new_result = concat(result, n);
  if (n % 2 == 0) {
    return collatz_aux(n / 2, new_result);
  } else {
    return collatz_aux(3 * n + 1, new_result);
  }
}
auto collatz(int const n)
    -> Vector_<int> {
  assert(n != 0);

  return collatz_aux(n, Vector_<int>());
}
} // namespace cp
