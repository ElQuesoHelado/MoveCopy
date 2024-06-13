#include "copy.hpp"
#include "move.hpp"
#include <chrono>
#include <iostream>
#include <random>

using namespace std;

auto main() -> int {
  std::cout << "Copy" << std::endl;
  for (int const x : cp::collatz(44)) {
    cout << x << ' ';
  }
  cout << '\n';

  std::cout << "Move" << std::endl;
  for (int const x : mv::collatz(44)) {
    cout << x << ' ';
  }
  cout << '\n';

  // random_device dev;
  // mt19937 eng(dev());
  // uniform_int_distribution<int> dist(50000, 100000);
  // int veces = 10, val;
  //
  // std::cout << std::format("{:^21}\n{:^10}|{:^10}", "Nanosegundos", "Copy", "Move") << std::endl;
  //
  // for (int i{}; i < veces; ++i) {
  //   val = dist(eng);
  //   {
  //     auto start = std::chrono::steady_clock::now();
  //     cp::collatz(val);
  //     auto finish = std::chrono::steady_clock::now();
  //     long elapsed_seconds = std::chrono::duration_cast<
  //                                chrono::nanoseconds>(finish - start)
  //                                .count();
  //     std::cout << std::format("{:^10}|", elapsed_seconds);
  //   }
  //
  //   {
  //     auto start = std::chrono::steady_clock::now();
  //     mv::collatz(val);
  //     auto finish = std::chrono::steady_clock::now();
  //     long elapsed_seconds = std::chrono::duration_cast<
  //                                chrono::nanoseconds>(finish - start)
  //                                .count();
  //     // std::cout << "Move: " << elapsed_seconds << std::endl;
  //     std::cout << std::format("{:^10}", elapsed_seconds) << std::endl;
  //   }
  // }
}
