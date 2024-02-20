#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

struct batalla {
  int soldados, perdidas;
  bool operator<(batalla other) {
    if ((this->soldados - this->perdidas) < (other.soldados - other.perdidas)) {
      return 1;
    } else if ((this->soldados - this->perdidas) >
               (other.soldados - other.perdidas)) {
      return 0;
    } else {
      if (this->soldados < other.soldados) {
        return 1;
      } else {
        return 0;
      }
    }
    return 0;
  }
};

void solve(vector<batalla> escenario) {
  sort(escenario.begin(), escenario.end());
  int max = 0, resta = 0, aux;
  for (int i = escenario.size() - 1; i >= 0; i--) {
    aux = escenario[i].soldados + resta;
    if (max < aux) {
      max = aux;
    }
    resta += escenario[i].perdidas;
  }
  if (resta > max) {
    max = resta;
  }
  cout << max << "\n";
}

int main() {
  int lines, num;
  vector<batalla> escenario;
  while (cin >> lines) {
    escenario.clear();
    if (lines == 0) {
      break;
    } else {
      for (int i = 0; i < lines; i++) {
        batalla linea;
        cin >> linea.soldados;
        cin >> linea.perdidas;
        cin >> num;
        linea.perdidas += num;
        escenario.push_back(linea);
      }
    }
    solve(escenario);
  }
  return 0;
}
