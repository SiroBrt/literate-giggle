#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

char aux_str[1000];

struct board {
  int posibilidades[81][9];
  int real[81];
};

void poner_a_cero(struct board *tablero) {
  for (int i = 0; i < 81; i++) {
    tablero->real[i] = 0;
    for (int j = 0; j < 9; j++) {
      tablero->posibilidades[i][j] = 0;
    }
  }
}

void myprint(struct board tablero) {
  printf("\n");
  int cero = 0;
  for (int i = 0; i < 81; i++) {
    if (tablero.real[i] == 0) {
      cero = 1;
      printf(" ");
    } else {
      printf("%d", tablero.real[i]);
    }
    if (i == 80) {
      printf("\n");
    } else if (i % 27 == 26) {
      printf("\n-----+-----+-----\n");
    } else if (i % 9 == 8) {
      printf("\n");
    } else if (i % 3 == 2) {
      printf("|");
    } else {
      printf(" ");
    }
  }

  if (cero == 0) {
    return;
  }
  int suma;

  for (int i = 0; i < 81; i++) {
    if (tablero.real[i] != 0) {
      continue;
    }
    suma = 0;
    printf("%d: ", i);
    for (int j = 0; j < 9; j++) {
      printf("%d ", tablero.posibilidades[i][j]);
      suma += tablero.posibilidades[i][j];
    }
    if (suma == 1) {
      printf(" ok ");
    }
    printf("\n");
  }
}

void read(struct board *tablero, char *file) {
  poner_a_cero(tablero);
  FILE *fi;
  fi = fopen(file, "r");

  if (fi == NULL) {
    printf("No hay archivo\n");
    exit(0);
  } else {
    for (int i = 0; i < 81; i++) {
      tablero->real[i] = getc(fi) - '0';
      getc(fi);
    }
  }

  fclose(fi);
}

int cuad_it(int cuad, int it) {
  int base = cuad * 3 + (cuad / 3) * 18;
  return base + it + (it / 3) * 6;
}

void poblar(struct board *tablero, char *file) {
  read(tablero, file);
  int fila, col, cuad;
  int vistos[9];
  for (int i = 0; i < 81; i++) {
    if (tablero->real[i] != 0) {
      continue;
    }
    for (int j = 0; j < 9; j++) {
      vistos[j] = 0;
    }

    // comprobamos
    fila = i / 9;
    col = i % 9;
    cuad = col / 3 + (fila / 3) * 3;
    for (int j = 0; j < 9; j++) {
      if (tablero->real[i - col + j] != 0) {
        vistos[tablero->real[i - col + j] - 1] = 1;
      }
      if (tablero->real[i - 9 * fila + 9 * j] != 0) {
        vistos[tablero->real[i - 9 * fila + 9 * j] - 1] = 1;
      }
      if (tablero->real[cuad_it(cuad, j)] != 0) {
        vistos[tablero->real[cuad_it(cuad, j)] - 1] = 1;
      }
    }

    // guardamos
    for (int j = 0; j < 9; j++) {
      if (vistos[j] == 0) {
        tablero->posibilidades[i][j] = 1;
      }
    }
  }
}

// Escribe un valor en una casilla y lo imposibiliza en las de alrededor
void marcar(struct board *tablero, int pos, int valor) {
  printf("%d ", pos);
  int fila, col, cuad, sum_fila, sum_col, sum_cuad, pos_fila, pos_col, pos_cuad;
  fila = pos / 9;
  col = pos % 9;
  cuad = col / 3 + (fila / 3) * 3;

  // metemos el valor y quitamos posibilidades
  for (int i = 0; i < 9; i++) {
    tablero->posibilidades[pos][i] = 0;
  }
  tablero->real[pos] = valor;

  for (int i = 0; i < 9; i++) { // quitamos posibilidades en los 3 sets
    for (int j = 0; j < 9; j++) {
      pos_fila = pos - col + i;
      pos_col = pos - 9 * fila + 9 * i;
      pos_cuad = cuad_it(cuad, i);
      if (j == valor - 1) {
        tablero->posibilidades[pos_fila][j] = 0;
        tablero->posibilidades[pos_col][j] = 0;
        tablero->posibilidades[pos_cuad][j] = 0;
      } else {
        sum_fila += tablero->posibilidades[pos_fila][j];
        sum_col += tablero->posibilidades[pos_col][j];
        sum_cuad += tablero->posibilidades[pos_cuad][j];
      }
    }

    // si alguna casilla solo puede tener un numero tambien lo marcamos
    if (sum_fila == 1) {
      for (int j = 0; j < 9; j++) {
        if (tablero->posibilidades[pos_fila][j] == 1) {
          marcar(tablero, pos_fila, j + 1);
          break;
        }
      }
    }
    if (sum_col == 1) {
      for (int j = 0; j < 9; j++) {
        if (tablero->posibilidades[pos_col][j] == 1) {
          marcar(tablero, pos_col, j + 1);
          break;
        }
      }
    }
    if (sum_cuad == 1) {
      for (int j = 0; j < 9; j++) {
        if (tablero->posibilidades[pos_cuad][j] == 1) {
          marcar(tablero, pos_cuad, j + 1);
          break;
        }
      }
    }
    sum_fila = sum_cuad = sum_col = 0;
  }
}

// Si algun numero solo puede ir en una posicion en su cuadrado/fila/columna lo
// ponemos. Devuelve 1 si ha cambiado algo
int unico_en_set(struct board *tablero) {
  int cambio = 0, vistos_cuad[9], vistos_fila[9], vistos_col[9], pos_cuad,
      pos_fila, pos_col;
  for (int set = 0; set < 9; set++) {
    for (int it = 0; it < 9; it++) {
      vistos_cuad[it] = 0;
      vistos_fila[it] = 0;
      vistos_col[it] = 0;
    }

    // contamos cuantos de cada numero puede haber en fila, columna y cuadrado
    for (int it = 0; it < 9; it++) {
      pos_cuad = cuad_it(set, it);
      pos_fila = set * 9 + it;
      pos_col = set + 9 * it;
      for (int i = 0; i < 9; i++) {
        vistos_cuad[i] += tablero->posibilidades[pos_cuad][i];
        vistos_fila[i] += tablero->posibilidades[pos_fila][i];
        vistos_col[i] += tablero->posibilidades[pos_col][i];
      }
    }

    // si hay numeros con una sola posicion posible lo marcamos
    for (int i = 0; i < 9; i++) {
      if (vistos_cuad[i] == 1) {
        for (int it = 0; it < 9; it++) {
          pos_cuad = cuad_it(set, it);
          if (tablero->posibilidades[pos_cuad][i] == 1) {
            marcar(tablero, pos_cuad, i + 1);
            cambio = 1;
          }
        }
      }
      if (vistos_fila[i] == 1) {
        for (int it = 0; it < 9; it++) {
          pos_fila = set * 9 + it;
          if (tablero->posibilidades[pos_fila][i] == 1) {
            marcar(tablero, pos_fila, i + 1);
            cambio = 1;
          }
        }
      }
      if (vistos_col[i] == 1) {
        for (int it = 0; it < 9; it++) {
          pos_col = set + 9 * it;
          if (tablero->posibilidades[pos_col][i] == 1) {
            marcar(tablero, pos_col, i + 1);
            cambio = 1;
          }
        }
      }
    }
  }
  if (cambio == 1) { // repetimos
    unico_en_set(tablero);
    return 1;
  }
  return 0;
}

int main() {
  struct board tablero;
  poblar(&tablero, "sudoku2.txt");
  unico_en_set(&tablero);
  myprint(tablero);
}
