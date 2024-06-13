#pragma once

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <ostream>
#include <vector>

void printVector(const std::vector<int> &vec) {
  for (const auto &elem : vec) {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

class Billetera {
public:
  int soles{};

  Billetera() = default;

  Billetera &operator=(const Billetera &otra) = default;

  Billetera(Billetera &&otra) {
    soles = otra.soles;
    otra.soles = 0;
  }
};

class Caja {
public:
  int n{};
  Billetera *billeteras{};

  void asignar(const std::initializer_list<int> &soles) {
    delete[] billeteras;
    n = soles.size();
    billeteras = new Billetera[n];

    int i{};
    for (const auto &e : soles) {
      billeteras[i].soles = e;
      ++i;
    }
  }

  // Constructores estandar
  explicit Caja(int n) : n(n) {
    billeteras = new Billetera[n];
  }

  Caja(const std::initializer_list<int> &soles) {
    asignar(soles);
  }

  // Constructor copia
  Caja(const Caja &otra) {
    delete[] billeteras;
    n = otra.n;
    std::copy(otra.billeteras, otra.billeteras + n - 1, billeteras);
  }

  // Constructor move
  Caja(Caja &&otra) noexcept {
    n = otra.n;
    billeteras = otra.billeteras;
    otra.n = 0;
    otra.billeteras = new Billetera[0];
  }

  // Asignación copia
  Caja &operator=(const Caja &otra) {
    if (!(this == &otra)) {
      delete[] billeteras;
      n = otra.n;
      std::copy(otra.billeteras, otra.billeteras + n, billeteras);
    }
    return *this;
  }

  // Asignación move
  Caja &operator=(Caja &&otra) noexcept {
    delete[] billeteras;
    n = otra.n;
    billeteras = otra.billeteras;

    otra.n = 0;
    otra.billeteras = new Billetera[0];
    return *this;
  }

  ~Caja() {
    delete[] billeteras;
  }
};

std::ostream &operator<<(std::ostream &os, const Caja &caja) {
  for (int i{}; i < caja.n; ++i) {
    os << "(Billetera " << i + 1 << ": " << caja.billeteras[i].soles << ")  ";
  }
  return os;
}

int main() {
  Caja caja1({5, 6, 24, 67}), caja2({9, 45}), caja3({56, 21, 12});
  // std::cout << "Caja1: \n"
  //           << caja1 << std::endl;

  // Move constructor
  std::cout << "Move constructor" << std::endl;
  Caja caja4(std::move(caja1));

  std::cout << "Caja1: \n"
            << caja1 << std::endl;
  std::cout << "Caja Movida: \n"
            << caja4 << std::endl;

  // Re-use moved
  std::cout << "\n\nReusar moved" << std::endl;
  caja1.asignar({10, 10, 10});
  std::cout << "Caja1: \n"
            << caja1 << std::endl;

  // Move assignment
  std::cout << "\n\nMove assignment" << std::endl;

  caja2 = std::move(caja3);
  std::cout << "Caja2: \n"
            << caja2 << std::endl;

  std::cout << "Caja3: \n"
            << caja3 << std::endl;

  // Containers
  std::vector<int> vec1 = {1, 2, 3, 4, 5};
  std::vector<int> vec2;

  // Antes de la movida
  std::cout << "Antes de la movida:" << std::endl;
  std::cout << "vec1: ";
  printVector(vec1);
  std::cout << "vec2: ";
  printVector(vec2);

  // Mover vec1 a vec2
  vec2 = std::move(vec1);

  // Después de la movida
  std::cout << "despues de usar move" << std::endl;
  std::cout << "vec1: ";
  printVector(vec1); // vec1 está en un estado indeterminado(vec1 dio sus recursos interno)
  std::cout << "vec2: ";
  printVector(vec2);

  // Intentando utilizar vec1 después de la movida
  std::cout << "intendo agregar elementos" << std::endl;
  vec1.push_back(10);
  std::cout << "vec1: ";
  printVector(vec1);

  return 0;
}
