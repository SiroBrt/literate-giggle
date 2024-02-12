// finds the stern-brocot representation of a fraction

#include <iostream>
#include <numeric>
#include <string>
using namespace std;

void solve(int num, int den) {
  int a[2] = {0, 1}, b[2] = {1, 1}, c[2] = {1, 0};
  string result("");
  while (num != b[0] or den != b[1]) {
    if (float(num) / float(den) > float(b[0]) / float(b[1])) {
      a[0] = b[0];
      a[1] = b[1];
      b[0] = b[0] + c[0];
      b[1] = b[1] + c[1];
      result.push_back('D');
    } else {
      c[0] = b[0];
      c[1] = b[1];
      b[0] = b[0] + a[0];
      b[1] = b[1] + a[1];
      result.push_back('I');
    }
  }
  cout << result << "\n";
}

int main() {
  int num, den, common;
  while (cin >> num >> den) {
    if (num == 0 and den == 0) {
      break;
    }
    if (num == 0 or den == 0) {
      cout << "error\n";
    } else {
      common = gcd(num, den);
      if (common != 1) {
        num = num / common;
        den = den / common;
      }
      solve(num, den);
    }
  }
  return 0;
}
