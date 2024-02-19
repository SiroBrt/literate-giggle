#include <iostream>
#include <ostream>
#include <string>

std::string divisible (int num) {
  if (num == 2 || num == 5) {
    return "";
  }

  std::string s = "1";
  int mul = 1;
  while (true) {
    if (mul % num == 0) {
      return s;
    }
    mul = mul * 10 + 1;
    mul = mul % num;
    s.push_back('1');
  }
}

int main () {
  int n;
  while (std::cin >> n) {
    if (n == 0) {
      break;
    } else {
      std::cout << divisible(n) << std::endl;
    }
  }
  return 0;
}
