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

void poblar(struct board *tablero) {
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

void marcar(struct board *tablero, int pos, int valor) {
  printf("%d ", pos);
  int fila, col, cuad, sum_fila, sum_col, sum_cuad, pos_fila, pos_col, pos_cuad;
  fila = pos / 9;
  col = pos % 9;
  cuad = col / 3 + (fila / 3) * 3;

  for (int i = 0; i < 9; i++) {
    tablero->posibilidades[pos][i] = 0;
  }
  tablero->real[pos] = valor;
  for (int i = 0; i < 9; i++) {
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

void unico_col(struct board *tablero) {
  int vistos[9], pos;
  for (int col = 0; col < 9; col++) {
    // printf("\ncuad: %d\n", cuad);
    for (int it = 0; it < 9; it++) {
      vistos[it] = 0;
    }

    for (int it = 0; it < 9; it++) {
      pos = col + 9 * it;
      for (int i = 0; i < 9; i++) { // vistos += posibilidades[cuad_it(cuad,it)]
        vistos[i] += tablero->posibilidades[pos][i];
      }
    }

    for (int i = 0; i < 9; i++) {
      // printf("%ds vistos: %d\n", i + 1, vistos[i]);
      if (vistos[i] != 1) {
        continue;
      }
      for (int it = 0; it < 9; it++) {
        pos = col + 9 * it;
        if (tablero->posibilidades[pos][i] == 1) {
          marcar(tablero, pos, i + 1);
        }
      }
    }
  }
}

void unico_fila(struct board *tablero) {
  int vistos[9], pos;
  for (int fila = 0; fila < 9; fila++) {
    // printf("\ncuad: %d\n", cuad);
    for (int it = 0; it < 9; it++) {
      vistos[it] = 0;
    }

    for (int it = 0; it < 9; it++) {
      pos = fila * 9 + it;
      for (int i = 0; i < 9; i++) { // vistos += posibilidades[cuad_it(cuad,it)]
        vistos[i] += tablero->posibilidades[pos][i];
      }
    }

    for (int i = 0; i < 9; i++) {
      // printf("%ds vistos: %d\n", i + 1, vistos[i]);
      if (vistos[i] != 1) {
        continue;
      }
      for (int it = 0; it < 9; it++) {
        pos = fila * 9 + it;
        if (tablero->posibilidades[pos][i] == 1) {
          marcar(tablero, pos, i + 1);
        }
      }
    }
  }
}

void unico_cuadrado(struct board *tablero) {
  int vistos[9], pos;
  for (int cuad = 0; cuad < 9; cuad++) {
    // printf("\ncuad: %d\n", cuad);
    for (int it = 0; it < 9; it++) {
      vistos[it] = 0;
    }

    for (int it = 0; it < 9; it++) {
      pos = cuad_it(cuad, it);
      for (int i = 0; i < 9; i++) { // vistos += posibilidades[cuad_it(cuad,it)]
        vistos[i] += tablero->posibilidades[pos][i];
      }
    }

    for (int i = 0; i < 9; i++) {
      // printf("%ds vistos: %d\n", i + 1, vistos[i]);
      if (vistos[i] != 1) {
        continue;
      }
      for (int it = 0; it < 9; it++) {
        pos = cuad_it(cuad, it);
        if (tablero->posibilidades[pos][i] == 1) {
          marcar(tablero, pos, i + 1);
        }
      }
    }
  }
}

int main() {
  struct board tablero;
  poner_a_cero(&tablero);
  read(&tablero, "sudoku2.txt");
  poblar(&tablero);
  // marcar(&tablero, 34, 5);
  // marcar(&tablero, 51, 4);
  // marcar(&tablero, 52, 7);
  // marcar(&tablero, 65, 8);
  // marcar(&tablero, 69, 9);
  // marcar(&tablero, 71, 7);
  unico_cuadrado(&tablero);
  unico_col(&tablero);
  unico_fila(&tablero);
  myprint(tablero);
}
