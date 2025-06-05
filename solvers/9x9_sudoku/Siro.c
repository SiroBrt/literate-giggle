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

int serializar_posibilidades(struct board *tablero, int pos) {
  if (tablero->real[pos] != 0) {
    return 0;
  }
  int output = 0, pow = 1;
  for (int i = 0; i < 9; i++) {
    output += tablero->posibilidades[pos][i] * pow;
    pow = pow * 2;
  }
  return output;
}
void deserializar_posibilidades(int *output, int num) {
  int pow = 2;
  for (int i = 0; i < 9; i++) {
    output[i] = (num % pow == pow / 2);
    num -= num % pow;
    pow = pow * 2;
  }
}

int naked_subset(struct board *tablero) {
  int patrones_cuad[9], cuenta_cuad[9], composicion_cuad[9], pos_cuad, num_cuad,
      index_cuad, found_cuad;
  int patrones_fila[9], cuenta_fila[9], composicion_fila[9], pos_fila, num_fila,
      index_fila, found_fila;
  int patrones_col[9], cuenta_col[9], composicion_col[9], pos_col, num_col,
      index_col, found_col;
  int cambio = 0, pow, aux[9];
  for (int set = 0; set < 9; set++) {
    index_cuad = 1;
    index_fila = 1;
    index_col = 1;
    for (int i = 0; i < 9; i++) {
      patrones_cuad[i] = 0;
      patrones_fila[i] = 0;
      patrones_col[i] = 0;
      cuenta_cuad[i] = 0;
      cuenta_fila[i] = 0;
      cuenta_col[i] = 0;
      composicion_cuad[i] = 0;
      composicion_fila[i] = 0;
      composicion_col[i] = 0;
    }

    for (int i = 0; i < 9; i++) {
      pos_cuad = cuad_it(set, i);
      pos_fila = 9 * set + i;
      pos_col = set + 9 * i;
      num_cuad = serializar_posibilidades(tablero, pos_cuad);
      num_fila = serializar_posibilidades(tablero, pos_fila);
      num_col = serializar_posibilidades(tablero, pos_col);
      found_cuad = 0;
      found_fila = 0;
      found_col = 0;
      for (int j = 0; j < 9; j++) {
        if ((patrones_cuad[j] == num_cuad) && (found_cuad == 0)) {
          found_cuad = 1;
          cuenta_cuad[j]++;
        }
        if ((patrones_fila[j] == num_fila) && (found_fila == 0)) {
          found_fila = 1;
          cuenta_fila[j]++;
        }
        if ((patrones_col[j] == num_col) && (found_col == 0)) {
          found_col = 1;
          cuenta_col[j]++;
        }
      }

      if (found_cuad == 0) {
        patrones_cuad[index_cuad] = num_cuad;
        cuenta_cuad[index_cuad]++;
        for (int j = 0; j < 9; j++) {
          composicion_cuad[index_cuad] += tablero->posibilidades[pos_cuad][j];
        }
        index_cuad++;
      }
      if (found_fila == 0) {
        patrones_fila[index_fila] = num_fila;
        cuenta_fila[index_fila]++;
        for (int j = 0; j < 9; j++) {
          composicion_fila[index_fila] += tablero->posibilidades[pos_fila][j];
        }
        index_fila++;
      }
      if (found_col == 0) {
        patrones_col[index_col] = num_col;
        cuenta_col[index_col]++;
        for (int j = 0; j < 9; j++) {
          composicion_col[index_col] += tablero->posibilidades[pos_col][j];
        }
        index_col++;
      }
    }

    for (int i = 0; i < index_cuad; i++) {
      if (cuenta_cuad[i] == composicion_cuad[i]) {
        deserializar_posibilidades(aux, patrones_cuad[i]);
        for (int j = 0; j < 9; j++) {
          pos_cuad = cuad_it(set, j);
          num_cuad = serializar_posibilidades(tablero, pos_cuad);
          if (num_cuad != patrones_cuad[i]) {
            for (int k = 0; k < 9; k++) {
              if (tablero->posibilidades[pos_cuad][k] == aux[k]) {
                cambio = 1;
                tablero->posibilidades[pos_cuad][k] -= aux[k];
              }
            }
          }
        }
      }
    }
    for (int i = 0; i < index_fila; i++) {
      if (cuenta_fila[i] == composicion_fila[i]) {
        deserializar_posibilidades(aux, patrones_fila[i]);
        for (int j = 0; j < 9; j++) {
          pos_fila = 9 * set + j;
          num_fila = serializar_posibilidades(tablero, pos_fila);
          if (num_fila != patrones_fila[i]) {
            for (int k = 0; k < 9; k++) {
              if (tablero->posibilidades[pos_fila][k] == aux[k]) {
                cambio = 1;
                tablero->posibilidades[pos_fila][k] -= aux[k];
              }
            }
          }
        }
      }
    }
    for (int i = 0; i < index_col; i++) {
      if (cuenta_col[i] == composicion_col[i]) {
        deserializar_posibilidades(aux, patrones_col[i]);
        for (int j = 0; j < 9; j++) {
          pos_col = set + 9 * j;
          num_col = serializar_posibilidades(tablero, pos_col);
          if (num_col != patrones_col[i]) {
            for (int k = 0; k < 9; k++) {
              if (tablero->posibilidades[pos_col][k] == aux[k]) {
                cambio = 1;
                tablero->posibilidades[pos_col][k] -= aux[k];
              }
            }
          }
        }
      }
    }
  }
  if (cambio == 1) {
    return 1;
  }
  return 0;
}

void solve(struct board *tablero) {
  int cambio = 1;
  while (cambio != 0) {
    cambio = 0;
    cambio += unico_en_set(tablero);
    cambio += naked_subset(tablero);
  }
}

int main(int argc, char *argv[]) {
  if (argc == 2) {
    struct board tablero;
    poblar(&tablero, argv[1]);
    solve(&tablero);
    myprint(tablero);
  }
}
