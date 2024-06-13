#pragma once
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
// using std::move;

namespace mv {
template <class Item>
using Vector_ = std::vector<Item>;
auto concat(Vector_<int> v, int const x)
    -> Vector_<int> {
  v.push_back(x);
  // warning: moving a local object in a return statement prevents copy elision [-Wpessimizing-
  // move]
  // See https://stackoverflow.com/documentation/c%2b%2b/2489/copy-elision
  // return move( v );
  return v;
}
auto collatz_aux(int const n, Vector_<int> result)
    -> Vector_<int> {
  std::cout << result.data() << std::endl;
  if (n == 1) {
    return result;
  }
  auto new_result = concat(std::move(result), n);
  // struct result;
  // Make absolutely sure no use of `result` after this.
  if (n % 2 == 0) {
    return collatz_aux(n / 2, std::move(new_result));
  } else {
    return collatz_aux(3 * n + 1, std::move(new_result));
  }
}
auto collatz(int const n)
    -> Vector_<int> {
  assert(n != 0);
  return collatz_aux(n, Vector_<int>());
}
} // namespace mv
