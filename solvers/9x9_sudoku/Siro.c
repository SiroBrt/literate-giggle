#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

char aux_str[1000];
int iteracion = 0;

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
      if (tablero.posibilidades[i][j] == 1) {
        printf("%d ", j + 1);
        suma++;
      }
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

int unica_opcion(struct board *tablero) {
  int cambio = 0, suma;
  for (int i = 0; i < 81; i++) {
    if (tablero->real[i] != 0) {
      continue;
    }
    suma = 0;
    for (int j = 0; j < 9; j++) {
      suma += tablero->posibilidades[i][j];
    }
    if (suma == 1) {
      for (int j = 0; j < 9; j++) {
        if (tablero->posibilidades[i][j] == 1) {
          marcar(tablero, i, j + 1);
          cambio = 1;
        }
      }
    }
  }
  return cambio;
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
  }
  return cambio;
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
              if (tablero->posibilidades[pos_cuad][k] == aux[k] &&
                  aux[k] == 1) {
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
              if (tablero->posibilidades[pos_fila][k] == aux[k] &&
                  aux[k] == 1) {
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
              if (tablero->posibilidades[pos_col][k] == aux[k] && aux[k] == 1) {
                cambio = 1;
                tablero->posibilidades[pos_col][k] -= aux[k];
              }
            }
          }
        }
      }
    }
  }
  return cambio;
}

int cuad_linea(struct board *tablero) {
  int cambio = 0;
  int fila1[9], fila2[9], fila3[9], suma_fila[9], fila;
  int col1[9], col2[9], col3[9], suma_col[9], col;
  for (int cuad = 0; cuad < 9; cuad++) {
    for (int i = 0; i < 9; i++) {
      fila1[i] = 0;
      fila2[i] = 0;
      fila3[i] = 0;
      suma_fila[i] = 0;
      col1[i] = 0;
      col2[i] = 0;
      col3[i] = 0;
      suma_col[i] = 0;
    }
    for (int i = 0; i < 3; i++) {
      for (int num = 0; num < 9; num++) {
        if (tablero->posibilidades[cuad_it(cuad, i)][num] == 1) {
          fila1[num] = 1;
        }
        if (tablero->posibilidades[cuad_it(cuad, i + 3)][num] == 1) {
          fila2[num] = 1;
        }
        if (tablero->posibilidades[cuad_it(cuad, i + 6)][num] == 1) {
          fila3[num] = 1;
        }
        suma_fila[num] = fila1[num] + fila2[num] + fila3[num];

        if (tablero->posibilidades[cuad_it(cuad, i * 3)][num] == 1) {
          col1[num] = 1;
        }
        if (tablero->posibilidades[cuad_it(cuad, i * 3 + 1)][num] == 1) {
          col2[num] = 1;
        }
        if (tablero->posibilidades[cuad_it(cuad, i * 3 + 2)][num] == 1) {
          col3[num] = 1;
        }
        suma_col[num] = col1[num] + col2[num] + col3[num];
      }
    }

    for (int i = 0; i < 9; i++) {
      if (suma_fila[i] == 1) {
        if (fila1[i] == 1) {
          fila = 0 + (cuad / 3) * 3;
        } else if (fila2[i] == 1) {
          fila = 1 + (cuad / 3) * 3;
        } else {
          fila = 2 + (cuad / 3) * 3;
        }
        for (int j = 0; j < 9; j++) {
          if ((cuad % 3) * 3 <= j && j < ((cuad % 3) + 1) * 3) {
            continue;
          }
          if (tablero->posibilidades[fila * 9 + j][i] == 1) {
            tablero->posibilidades[fila * 9 + j][i] = 0;
            cambio = 1;
          }
        }
      }

      if (suma_col[i] == 1) {
        if (col1[i] == 1) {
          col = 0 + (cuad % 3) * 3;
        } else if (col2[i] == 1) {
          col = 1 + (cuad % 3) * 3;
        } else {
          col = 2 + (cuad % 3) * 3;
        }
        for (int j = 0; j < 9; j++) {
          if ((cuad / 3) * 3 <= j && j < ((cuad / 3) + 1) * 3) {
            continue;
          }
          if (tablero->posibilidades[col + 9 * j][i] == 1) {
            tablero->posibilidades[col + 9 * j][i] = 0;
            cambio = 1;
          }
        }
      }
    }
  }

  return cambio;
}

int fila_cuad(struct board *tablero) {
  int cambio = 0;
  int cuad1[9], cuad2[9], cuad3[9], cuad;
  for (int set = 0; set < 9; set++) {
    for (int i = 0; i < 9; i++) {
      cuad1[i] = 0;
      cuad2[i] = 0;
      cuad3[i] = 0;
    }
    for (int num = 0; num < 9; num++) {
      for (int pos = 0; pos < 3; pos++) {
        if (tablero->posibilidades[cuad_it((set / 3) * 3 + 0,
                                           pos + (set % 3) * 3)][num] == 1) {
          cuad1[num] = 1;
        }
        if (tablero->posibilidades[cuad_it((set / 3) * 3 + 1,
                                           pos + (set % 3) * 3)][num] == 1) {
          cuad2[num] = 1;
        }
        if (tablero->posibilidades[cuad_it((set / 3) * 3 + 2,
                                           pos + (set % 3) * 3)][num] == 1) {
          cuad3[num] = 1;
        }
      }
      if (cuad1[num] + cuad2[num] + cuad3[num] == 1) {
        if (cuad1[num] == 1) {
          cuad = 0 + (set / 3) * 3;
        } else if (cuad2[num] == 1) {
          cuad = 1 + (set / 3) * 3;
        } else {
          cuad = 2 + (set / 3) * 3;
        }
        for (int i = 0; i < 9; i++) {
          if ((set % 3) * 3 <= i && i < ((set % 3) + 1) * 3) {
            continue;
          }
          if (tablero->posibilidades[cuad_it(cuad, i)][num] == 1) {
            tablero->posibilidades[cuad_it(cuad, i)][num] = 0;
            cambio = 1;
          }
        }
      }
    }
  }
  return cambio;
}

// Si en una columna todos los {num} ocurren en el mismo cuadrado, ese cuadrado
// solo tiene {num} en esa columna
int col_cuad(struct board *tablero) {
  int cambio = 0;
  int cuad1[9], cuad2[9], cuad3[9], cuad;
  for (int set = 0; set < 9; set++) {
    for (int i = 0; i < 9; i++) {
      cuad1[i] = 0;
      cuad2[i] = 0;
      cuad3[i] = 0;
    }
    for (int num = 0; num < 9; num++) {
      for (int pos = 0; pos < 3; pos++) {
        if (tablero->posibilidades[cuad_it(0 + set / 3, pos * 3 + set % 3)]
                                  [num] == 1) {
          cuad1[num] = 1;
        }
        if (tablero->posibilidades[cuad_it(3 + set / 3, pos * 3 + set % 3)]
                                  [num] == 1) {
          cuad2[num] = 1;
        }
        if (tablero->posibilidades[cuad_it(6 + set / 3, pos * 3 + set % 3)]
                                  [num] == 1) {
          cuad3[num] = 1;
        }
      }
      if (cuad1[num] + cuad2[num] + cuad3[num] == 1) {
        if (cuad1[num] == 1) {
          cuad = 0 + (set / 3);
        } else if (cuad2[num] == 1) {
          cuad = 3 + (set / 3);
        } else {
          cuad = 6 + (set / 3);
        }
        for (int i = 0; i < 9; i++) {
          if ((set - i) % 3 == 0) {
            continue;
          }
          if (tablero->posibilidades[cuad_it(cuad, i)][num] == 1) {
            tablero->posibilidades[cuad_it(cuad, i)][num] = 0;
            cambio = 1;
          }
        }
      }
    }
  }
  return cambio;
}

void copiar_tablero(struct board *tablero, struct board *copia) {
  for (int pos = 0; pos < 81; pos++) {
    copia->real[pos] = tablero->real[pos];
    for (int num = 0; num < 9; num++) {
      copia->posibilidades[pos][num] = tablero->posibilidades[pos][num];
    }
  }
}

int errores(struct board tablero) {
  int suma, vistos_cuad[9], vistos_fila[9], vistos_col[9], num_cuad, num_col,
      num_fila;
  for (int pos = 0; pos < 81; pos++) {
    suma = 0;
    for (int i = 0; i < 9; i++) {
      suma += tablero.posibilidades[pos][i];
    }
    if (suma == 0 && tablero.real[pos] == 0) {
      return 1;
    }
  }
  for (int set = 0; set < 9; set++) {
    for (int i = 0; i < 9; i++) {
      vistos_cuad[i] = 0;
      vistos_fila[i] = 0;
      vistos_col[i] = 0;
    }
    for (int i = 0; i < 9; i++) {
      num_cuad = tablero.real[cuad_it(set, i)];
      num_fila = tablero.real[set * 9 + i];
      num_col = tablero.real[set + 9 * i];
      if (num_cuad != 0) {
        if (vistos_cuad[num_cuad - 1] == 1) {
          return 1;
        }
        vistos_cuad[num_cuad - 1]++;
      }
      if (num_fila != 0) {
        if (vistos_fila[num_fila - 1] == 1) {
          return 1;
        }
        vistos_fila[num_fila - 1]++;
      }
      if (num_col != 0) {
        if (vistos_col[num_col - 1] == 1) {
          return 1;
        }
        vistos_col[num_col - 1]++;
      }
    }
  }
  return 0;
}

void heuristica(struct board tablero, int *recommendation) {
  int suma, candidatos2[81], candidatos3[81],
      index2 = 0, index3 = 0, puntos_best = 1, pos = 0, cuad, fila, col;

  for (pos = 0; pos < 81; pos++) { // inicializamos recommendation
    for (int i = 0; i < 9; i++) {
      if (tablero.posibilidades[pos][i] != 0) {
        recommendation[0] = pos;
        recommendation[1] = i;
        break;
      }
    }
  }

  for (pos = 0; pos < 81; pos++) {
    suma = 0;
    for (int i = 0; i < 9; i++) {
      suma += tablero.posibilidades[pos][i];
    }
    if (suma == 2) {
      candidatos2[index2] = pos;
      index2++;
    } else if (suma == 3) {
      candidatos3[index3] = pos;
      index3++;
    }
  }
  if (index2 != 0) {
    for (int cand = 0; cand < index2; cand++) {
      pos = candidatos2[cand];
      for (int value = 0; value < 9; value++) {
        if (tablero.posibilidades[pos][value] == 0) {
          continue;
        }
        fila = pos / 9;
        col = pos % 9;
        cuad = col / 3 + (fila / 3) * 3;

        suma = -3;

        // i es posible en pos, vamos a ver cuantos quitaria
        for (int it = 0; it < 9; it++) {
          suma += tablero.posibilidades[cuad_it(cuad, it)][value];
          suma += tablero.posibilidades[col + 9 * it][value];
          suma += tablero.posibilidades[fila * 9 + it][value];
        }

        if (suma > puntos_best) {
          recommendation[0] = pos;
          recommendation[1] = value;
          puntos_best = suma;
        }
      }
    }

    return;
  }
  if (index3 != 0) {
    printf("Hay un 3\n");
    for (int cand = 0; cand < index3; cand++) {
      pos = candidatos3[cand];
      for (int value = 0; value < 9; value++) {
        if (tablero.posibilidades[pos][value] == 0) {
          continue;
        }
        fila = pos / 9;
        col = pos % 9;
        cuad = col / 3 + (fila / 3) * 3;

        suma = -3;

        for (int it = 0; it < 9; it++) {
          suma += tablero.posibilidades[cuad_it(cuad, it)][value];
          suma += tablero.posibilidades[col + 9 * it][value];
          suma += tablero.posibilidades[fila * 9 + it][value];
        }

        if (suma > puntos_best) {
          recommendation[0] = pos;
          recommendation[1] = value;
          puntos_best = suma;
        }
      }
    }

    return;
  }
}

int solve(struct board *tablero, int prof) {
  int cambio = 0;
  for (int pos = 0; pos < 81; pos++) {
    if (tablero->real[pos] == 0) {
      cambio = 1;
      break;
    }
  }
  if (cambio == 0) {
    if (errores(*tablero)) {
      return -1;
    }
    return 1;
  }

  while (1) {
    cambio = 1;
    while (cambio != 0) {
      cambio = 0;
      iteracion++;
      cambio += unico_en_set(tablero);
      cambio += unica_opcion(tablero);
      // cambio += naked_subset(tablero);
      cambio += cuad_linea(tablero);
      cambio += fila_cuad(tablero);
      cambio += col_cuad(tablero);
      if (errores(*tablero)) {
        return -1;
      }
    }
    for (int i = 0; i < 81; i++) {
      if (tablero->real[i] == 0) {
        cambio = 1;
        break;
      }
    }
    if (cambio == 0) {
      return 1;
    }
    struct board prueba;
    copiar_tablero(tablero, &prueba);

    int recommendation[2]; // pos, valor
    heuristica(prueba, recommendation);
    marcar(&prueba, recommendation[0], recommendation[1] + 1);
    int output;
    output = solve(&prueba, prof + 1);
    if (output == -1) {
      tablero->posibilidades[recommendation[0]][recommendation[1]] = 0;
      if (errores(*tablero)) {
        return -1;
      }
    } else if (output == 1) {
      copiar_tablero(&prueba, tablero);
      return 1;
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc == 2) {
    int output;
    struct board tablero;
    poblar(&tablero, argv[1]);
    tablero.posibilidades[21][8] = 0;
    output = solve(&tablero, 0);
    if (output == 1) {
      myprint(tablero);
      printf("iteraciones: %d\n", iteracion);
    }
  }
}
