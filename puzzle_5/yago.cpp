// IMPORTANTE
// El codigo asume que la fraccion esta en forma reducida

#include <iostream>
#include <string>

// Representacion de una fraccion
struct frac {
  int num;
  int den;
};

std::string sternBrocotPath(frac f) {
  std::string s = "";
  if ((f.num == 1) && (f.den == 1)) {
    return s;
  } else {
    // Inicialmente a la izquierda 0/1 y a la derecha 1/0
    frac izq, der;
    izq.num = 0;
    izq.den = 1;
    der.num = 1;
    der.den = 0;
    // Empezamos a buscar la fraccion
    bool found = false;
    frac mid;
    while (!found) {
      mid.num = izq.num + der.num;
      mid.den = izq.den + der.den;
      if ((mid.num == f.num) && (mid.den = f.den)) {
        found = true;
      } else {
        if (f.num * mid.den < f.den * mid.num) {
          s += "I";
          der.num = mid.num;
          der.den = mid.den;
        } else {
          s += "D";
          izq.num = mid.num;
          izq.den = mid.den;
        }
      }
    }
    return s;
  }
}

int main () {
  frac f;
  while (std::cin >> f.num >> f.den){
    if (f.num == 0 && f.den == 0) {
      break;
    } else if (f.num == 0 || f.den == 0) {
      std::cout << "" << std::endl;
    } else {
      std::cout << sternBrocotPath(f) << std::endl;

    }
  }
  return 0;
}
