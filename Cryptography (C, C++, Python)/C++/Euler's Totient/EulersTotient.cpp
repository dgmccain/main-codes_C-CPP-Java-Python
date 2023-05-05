#include <iostream>

int phi(int currNum);

int main() {
  /*
  int userNum;
  int phiNum;
  */
  int staticNum = 1561032000;
  int staticPhiNum;

  /*
  // Find phi based upon user input
  std::cout << "Enter a number: ";
  std::cin >> userNum;
  phiNum = phi(userNum);
  */
  // Find phi based upon predetermined data
  std::cout << "Original number: " << staticNum << std::endl;
  staticPhiNum = phi(staticNum);
  std::cout << "Phi: " << staticPhiNum << std::endl;
}

int phi(int currNum) {
  int tempNum = currNum;

  for (int i = 2; i * i <= currNum; i++) {
    if (currNum % i == 0) {
      tempNum -= tempNum / i;
      while (currNum % i == 0) {
        currNum /= i;
      }
    }
  }
  
  tempNum -= tempNum / currNum;
  
  return tempNum;
}