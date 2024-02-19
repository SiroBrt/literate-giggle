#include <cmath>
#include <iostream>
#include <vector>

// Representa un turno de un juego
struct turno {
	int num; 	// Numero actual
	int jugador; 	// 0: Maria, 1: Juan
	int ganador; 	// 0: Maria, 1: Juan
};

std::vector<std::vector<turno>> visitados;

// Rellena el vector de visitados
int ganador (int obj) {
	// Profundidad de la matriz
	int prof = 1 + ceil(log2((float) obj));
	// Rellenamos primero la primera columna de todas las filas
	// con las potencias de 2
	for (int i = 0; i < prof; i++) {
		std::vector<turno> fila;
		turno t;
		t.num = pow(2, i);
		t.jugador = (i + 1) % 2;
		fila.push_back(t);
		visitados.push_back(fila);
	}
	visitados[0][0].jugador = 0;
	// Nos saltamos la primera fila porque solo tiene un elemento
	for (int i = 1; i < visitados.size(); i++) {
		for (int j = 0; j < visitados[i - 1].size(); j++) {
			turno t;
			t.num = visitados[i - 1][j].num * 9;
			t.jugador = visitados[i][j].jugador;
			visitados[i].push_back(t);
		}
	}
	// Calculamos los ganadores desde la ultima fila hacia arriba
	// Primero calculamos el ganador de la ultima fila
	for (int i = 0; i < visitados[prof - 1].size(); i++) {
		visitados[prof - 1][i].ganador = visitados[prof - 1][i].jugador;
	}
	// Calculamos el ganador de las filas anteriores
	for (int i = visitados.size() - 2; i >= 0; i--) {
		for (int j = 0; j < visitados[i].size(); j++) {
			if (visitados[i][j].num >= obj) {
				visitados[i][j].ganador = visitados[i][j].jugador;
			} else {
				turno t1 = visitados[i + 1][j];
				turno t2 = visitados[i + 1][j + 1];
				// Si son iguales, el ganador es ese
				if (t1.ganador == t2.ganador) {
					visitados[i][j].ganador = t1.ganador;
				} else {
					// Si no, el ganador es el jugador que juega
					visitados[i][j].ganador = visitados[i][j].jugador;
				}
			}
		}
	}
	return visitados[0][0].ganador;
}

int main () {
	int n;
	std::cin >> n;
	int gana = ganador(n);
	// for (int i = 0; i < visitados.size(); i++) {
	// 	for (int j = 0; j < visitados[i].size(); j++) {
	// 		std::cout << visitados[i][j].ganador << " ";
	// 	}
	// 	std::cout << std::endl;
	// }
	// for (int i = 0; i < visitados.size(); i++) {
	// 	for (int j = 0; j < visitados[i].size(); j++) {
	// 		std::cout << visitados[i][j].jugador << " ";
	// 	}
	// 	std::cout << std::endl;
	// }
	// for (int i = 0; i < visitados.size(); i++) {
	// 	for (int j = 0; j < visitados[i].size(); j++) {
	// 		std::cout << visitados[i][j].num << " ";
	// 	}
	// 	std::cout << std::endl;
	// }
	if (gana == 0 || n == 1) {
		std::cout << "Maria" << std::endl;
	} else {
		std::cout << "Juan" << std::endl;
	}
	return 0;
}
