#include <climits>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

#define ERROR -INT_MAX

// Secuencia del ejemplo
// std::vector<int> secuencia = {1, 2, 2, 2, 3, 5, 6, 8, 9, 10, 15, -4, -13,
// -20, -100};

// Secuencia balanceada
// std::vector<int> secuencia = {49, 50, 51, 62, 65, 99, 112, 151, 194, 220,
// 233, 236, 279, 280, 283, 323, 358, 359, 363, 397, 454, 526, 568, 571, 586,
// 593, 596, 600, 604, 606, 673, 687, 688, 690, 713, 717, 767, 801, 818, 828,
// 829, 858, 871, 898, 939, 988, 999, 1001, 1020, 1041, 1066, 1089, 1150, 1179,
// 1204, 1275, 1275, 1281, 1321, 1364, 1398, 1423, 1430, 1434, 1439, 1451, 1463,
// 1499, 1528, -14, -20, -22, -24, -29, -163, -166, -186, -210, -219, -251,
// -254, -258, -276, -287, -300, -307, -314, -326, -349, -377, -388, -396, -397,
// -407, -420, -424, -428, -450, -486, -499};

// Secuencia con muchos numeros negativos
// std::vector<int> secuencia = {
//     19,   26,   66,   67,   67,   70,   74,   83,   97,   99,   -3,   -25,
//     -26,  -29,  -39,  -46,  -47,  -63,  -78,  -78,  -79,  -81,  -91,  -109,
//     -145, -147, -169, -179, -180, -181, -183, -220, -224, -232, -236, -258,
//     -262, -289, -290, -293, -293, -304, -323, -328, -329, -356, -368, -374,
//     -383, -383, -403, -407, -416, -418, -431, -452, -455, -466, -473, -473,
//     -481, -490, -492, -494, -495, -502, -530, -539, -546, -556, -560, -560,
//     -565, -570, -572, -583, -600, -611, -615, -623, -629, -629, -638, -641,
//     -645, -654, -654, -673, -679, -692, -693, -694, -701, -709, -722, -726,
//     -732, -733, -738, -741, -749, -766, -769, -775, -781, -803, -811, -813,
//     -816, -820, -821, -831, -843, -859, -867, -871, -873, -901, -909, -909,
//     -912, -928, -929, -931, -935, -955, -957, -960, -981, -981};

// Secuencia con muchos numeros positivos
/* std::vector<int> secuencia = {
    0,   1,   1,   2,   6,   9,   10,  12,  12,  12,  13,  13,  14,  14,  15,
    17,  18,  20,  22,  25,  26,  26,  26,  28,  28,  28,  31,  33,  35,  39,
    40,  40,  41,  42,  43,  43,  45,  45,  47,  48,  51,  56,  56,  57,  58,
    58,  60,  62,  66,  67,  67,  67,  69,  70,  72,  75,  77,  78,  80,  80,
    82,  84,  85,  86,  89,  89,  90,  91,  91,  92,  92,  93,  93,  93,  94,
    97,  99,  104, 109, 109, 110, 110, 112, 112, 113, 114, 115, 115, 116, 117,
    118, 119, 121, 121, 121, 122, 122, 122, 123, 126, 127, 127, 127, 130, 133,
    133, 134, 134, 134, 136, 137, 137, 137, 140, 140, 141, 145, 146, 146, 149,
    150, 150, 150, 151, 151, 156, 157, 161, 166, 169, 171, 172, 173, 176, 176,
    176, 176, 178, 178, 179, 179, 180, 182, 185, 185, 186, 187, 191, 195, 195,
    197, 199, 201, 203, 203, 203, 204, 205, 208, 210, 210, 211, 213, 215, 220,
    221, 221, 223, 227, 227, 227, 229, 229, 232, 232, 232, 234, 235, 241, 242,
    244, 244, 245, 245, 245, 246, 247, 247, 248, 248, 250, 251, 251, 251, 252,
    253, 254, 254, 255, 256, -1};
 */
// //////////////////////////////////////////////////////////////////////////////

int seqElem(int i) {
  // Devuelve el elemento i de la secuencia
  if (i < 0 || i >= secuencia.size()) {
    return ERROR;
  }
  return secuencia[i];
}

int main() {
  int min = 0, max = 0, exp = 0, num;
  num = seqElem(min);
  while (num >= 0) { // Encontramos el intervalo
    min = max;
    max = max + pow(2, exp);
    if (seqElem(max) != ERROR) {
      num = seqElem(max);
      exp++;
    } else {
      max = min;
      exp /= 2;
    }
  }
  while (max - min > 1) { // búsqueda biaria en el intervalo
    num = (max + min) / 2;
    if (seqElem(num) > 0) {
      min = num;
    } else {
      max = num;
    }
  }
  cout << "idx: " << min << " num: " << seqElem(min) << "\n";

  return 0;
}