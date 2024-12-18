#include <cstdio>
#include <iostream>

// Representa las distintas cantidades de soldados en una batalla
struct batalla {
  int antes;
  int bajas;
  int reten;
  int total; // bajas + reten
};

int main() {
  int n;
  while (std::cin >> n) {
    if (n == 0) {
      break;
    }
    printf("%d\n", n);
    // std::cout << "n: " << n << std::endl;
    batalla b;
    for (int i = 0; i < n; i++) {
      std::cin >> b.antes >> b.bajas >> b.reten;
      b.total = b.bajas + b.reten;
      printf("%d %d %d %d\n", b.antes, b.bajas, b.reten, b.total);
    }
  }
  return 0;
}
