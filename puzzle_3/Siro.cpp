#include <iostream>
#include <vector>
using namespace std;

int solve(vector<int> data){
  int g1, g2, l = data.size();
  int matrix[l][l];
  for (int i = 0; i < l; i++){  // rellenamos la matriz por diagonales
    for (int j = 0; j < l - i; j++){
      if (i == 0){matrix[j][j] = data[j];}
      else if (i == 1) {matrix[j][j + 1] = max(data[j], data[j + 1]);}
      else {
        if (matrix[j][j] > matrix[j+i-1][j+i-1]){
          g1 = matrix[j+1][j+i-1];
        } else {
          g1 = matrix[j][j+i-2];
        }
        if (matrix[j+1][j+1] > matrix[j+i][j+i]){
          g2 = matrix[j+2][j+i];
        } else {
          g2 = matrix[j+1][j+i-1];
        }
        matrix[j][j+i] = max(g1 + matrix[j+i][j+i], g2 + matrix[j][j]);
      }
    }
  }
  return matrix[0][l - 1];
}

int main(){
  int num;
  while (cin >> num){
    if (num == 0) {
      break;
    }
    vector<int> data(num);
    for (int i = 0; i < num; i++) {
      cin >> data[i];
    }
    cout << solve(data) <<"\n";
  }
} 
