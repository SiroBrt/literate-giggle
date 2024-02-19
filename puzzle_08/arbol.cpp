#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>
using namespace std;

int main() {
  int capas, digitos;
  cin >> capas;
  vector<int64_t> arbol = {1};
  for (int i = 1; i <= capas; i++) {
    for (int margen = 0; margen < (capas - i) * (capas + 2) / 2; margen++) {
      cout << " ";
    }
    cout << arbol[0];
    for (int ii = 1; ii < arbol.size(); ii++) {
      digitos = log10(arbol[ii]);
      for (int iii = 0; iii < capas - digitos; iii++) {
        cout << " ";
      }
      cout << " " << arbol[ii];
      arbol[ii - 1] *= 2;
    }
    cout << "\n";
    arbol.push_back(arbol[arbol.size() - 1] * 9);
    arbol[arbol.size() - 2] *= 2;
  }
  return 0;
}
