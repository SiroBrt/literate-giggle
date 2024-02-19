// lo bueno sería no usar un árbol y hacerlo con una pirámide, pero no sé cómo
#include <cstdint>
#include <iostream>
using namespace std;

int n1 = 2, n2 = 9;

struct node {
  int64_t value;
  node *izq, *der;
  int winner;
  node(int num) {
    value = num;
    winner = 0; // 0 -> indefinido; 1 -> Gana María; 2 -> Gana Juan
  }
};

void rellenar(struct node *nodo, int limit, bool turn) {
  int num = nodo->value;
  node izq(num * n1), der(num * n2);
  nodo->der = &der;
  nodo->izq = &izq;
  if (der.value <
      limit) { // si el valor de der es menor que el límite lo rellenamos
    rellenar(&der, limit, not turn);
  } else { // si no, podemos ganar directamente
    if (turn) {
      nodo->winner = 2;
    } else {
      nodo->winner = 1;
    }
  }
  if (izq.value < limit) {
    rellenar(&izq, limit, not turn);
  }
  if (nodo->winner == 0) { // no lo hemos rellenado -> hay que mirar los nodos
    if (turn) {            // le toca a Juan
      if (der.winner == 2 or izq.winner == 2) { // Juan puede ganar
        nodo->winner = 2;
      } else { // Juan no puede ganar
        nodo->winner = 1;
      }
    } else {                                    // le toca a Maria
      if (der.winner == 1 or izq.winner == 1) { // María puede ganar
        nodo->winner = 1;
      } else {
        nodo->winner = 2;
      }
    }
  }
}

int main() {
  int limit;
  node raiz(1);
  cin >> limit;
  bool turn = 0; // turn == 0 -> elige María
  rellenar(&raiz, limit, turn);
  if (raiz.winner == 1) {
    cout << "Gana María\n";
  } else {
    cout << "Gana Juan\n";
  }
  return 0;
}
