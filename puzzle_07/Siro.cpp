#include <iostream>
using namespace std;

void solve(int n) {
  int num = 0, count = 0, potencia = 1;
  do {
    count++;
    potencia = (10 * potencia) % n;
    num = (num + potencia) % n;
  } while (num != 0);
  for (int i = 0; i < count; i++) {
    cout << "1";
  }
  cout << " % " << n << " = 0\n";
}

int main() {
  int n;
  while (cin >> n) {
    if (n == 0)
      return 0;
    if (n % 2 != 0 and n % 5 != 0) {
      solve(n);
    } else {
      cout << "no\n";
    }
  }
  return 0;
}
