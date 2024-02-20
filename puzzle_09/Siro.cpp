#include <iostream>
#include <vector>
using namespace std;

struct batalla {
  int soldados, perdidas;
};

void solve(vector<batalla> escenario) {
  for (int i = 0; i < escenario.size(); i++) {
    cout << escenario[i].perdidas << " ";
  }
  cout << "\n";
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
