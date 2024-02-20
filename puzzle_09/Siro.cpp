#include <iostream>
#include <vector>
using namespace std;

struct batalla {
  int soldados, perdidas;
  bool operator<(batalla other) { // compara cuantos soldados salen vivos (100 -
                                  // 10) < (95 - 0)
    if ((this->soldados - this->perdidas) < (other.soldados - other.perdidas)) {
      return 1;
    } else if ((this->soldados - this->perdidas) >
               (other.soldados - other.perdidas)) {
      return 0;
    } else {
      // en caso de ser iguales ponemos primero el que más soldados requiere
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
  int max = 0, resta = 0, aux;
  // hacemos las inecuaciones en orden y nos quedamos con el mayor resultado
  for (int i = 0; i < escenario.size(); i++) {
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
  auto it = escenario.begin();
  bool found = false;
  while (cin >> lines) {
    if (lines == 0) {
      break;
    }
    escenario.clear();
    for (int i = 0; i < lines; i++) {
      batalla linea;
      found = false;
      it = escenario.begin();
      cin >> linea.soldados;
      cin >> linea.perdidas;
      cin >> num;
      linea.perdidas += num;
      for (int ii = 0; ii < escenario.size();
           ii++) { // insertamos la nueva linea manteniendo el orden
        if (escenario[ii] < linea) {
          escenario.insert(it, linea);
          found = true;
          break;
        }
        it++;
      }
      if (not found) {
        escenario.push_back(linea);
      }
    }
    solve(escenario);
  }
  return 0;
}
