#include <iostream>
#include <vector>

struct posicion {
  int x;
  int y;
};

// Variables globales
#define WIDTH 6
#define HEIGHT 6

bool visitados[WIDTH * HEIGHT] = {false};
std::vector<posicion> camino;
int no_visitados = WIDTH * HEIGHT;

// Imprime un tablero de ajedrez con arte ASCII
void imprimir_tablero (int tablero[HEIGHT][WIDTH]) {
  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      std::cout << "+--";
    }
    std::cout << "+" << std::endl;
    for (int j = 0; j < WIDTH; j++) {
      // Imprimir el número con un ancho de 2
      std::cout << "|";
      if (tablero[i][j] < 10) {
        std::cout << " ";
      }
      std::cout << tablero[i][j];
    }
    std::cout << "|" << std::endl;
  }
  for (int j = 0; j < WIDTH; j++) {
    std::cout << "+--";
  }
  std::cout << "+" << std::endl;
}

// Devuelve el índice de la posición en el tablero
int indice_de(posicion pos) {
  return pos.x + pos.y * WIDTH;
}

// Devuelve true si la posición está dentro del tablero y no ha sido visitada
bool es_valida(posicion pos) {
  return (pos.x >= 0) && (pos.x < WIDTH) && (pos.y >= 0) && (pos.y < HEIGHT)
    && (visitados[indice_de(pos)] == false);
}

// Devuelve un vector con las posiciones válidas y sin aún sin visitar
// a las que se puede mover el caballo desde pos
std::vector<posicion> sucesores(posicion pos) {
  std::vector<posicion> res = {};
  if (es_valida({pos.x - 1, pos.y - 2})) {
    res.push_back({pos.x - 1, pos.y - 2});
  }
  if (es_valida({pos.x + 1, pos.y - 2})) {
    res.push_back({pos.x + 1, pos.y - 2});
  }
  if (es_valida({pos.x + 2, pos.y - 1})) {
    res.push_back({pos.x + 2, pos.y - 1});
  }
  if (es_valida({pos.x + 2, pos.y + 1})) {
    res.push_back({pos.x + 2, pos.y + 1});
  }
  if (es_valida({pos.x + 1, pos.y + 2})) {
    res.push_back({pos.x + 1, pos.y + 2});
  }
  if (es_valida({pos.x - 1, pos.y + 2})) {
    res.push_back({pos.x - 1, pos.y + 2});
  }
  if (es_valida({pos.x - 2, pos.y - 1})) {
    res.push_back({pos.x - 2, pos.y - 1});
  }
  if (es_valida({pos.x - 2, pos.y + 1})) {
    res.push_back({pos.x - 2, pos.y + 1});
  }
  return res;
}

// Comprueba si se puede recorrer el tablero con un recorrido en profundidad
// empezando en la posición pos
bool dfs(posicion pos) {
  // Caso base: si no hay posiciones sin visitar, se encontró solución
  if (no_visitados == 0) {
    return true;
  }

  // Caso base: si no hay movimientos válidos, no se encontró solución
  std::vector<posicion> s = sucesores(pos);
  if (s.size() == 0) {
    return false;
  }

  // Llamada recursiva
  for (int i = 0; i < s.size(); i++) {
    // Marca el movimiento en el tablero
    visitados[indice_de(s[i])] = true;
    no_visitados--;
    camino.push_back(s[i]);
    if (dfs(s[i])) {
      return true;
    }
    // Si no se encontró solución, se deshace el movimiento
    visitados[indice_de(s[i])] = false;
    no_visitados++;
    camino.pop_back();
  }
  return false;
}


int main () {
  posicion pos;
  std::cin >> pos.x >> pos.y;
  if (!es_valida(pos)) {
    std::cout << "Posición no válida" << std::endl;
    return 1;
  }
  camino.push_back(pos);
  visitados[indice_de(pos)] = true;
  no_visitados--;

  bool res = dfs(pos);
  if (dfs(pos)) {
    int tablero[HEIGHT][WIDTH] = {0};
    // Si se encontró solución, se imprime el camino
    std::cout << "Solución encontrada" << std::endl;
    for (int i = 0; i < camino.size(); i++) {
      tablero[camino[i].y][camino[i].x] = i + 1;
      
    }
    imprimir_tablero(tablero);
  } else {
    std::cout << "No se encontró solución" << std::endl;
  }
  return 0;
}
