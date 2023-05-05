#include <cmath>
#include <iostream>

void printPrimeFact(int n);

int main() {
  int userNum;

  std::cout << "Enter a number: ";
  std::cin >> userNum;

  printPrimeFact(userNum);
}

// Pre-condition: n >= 2.
// Post-condition: Prints prime factorization of n.
void printPrimeFact(int n) {
  // note: i is essentially x in the equation n=x*y
  for (int i = 2; i * i <= n; i++) {
    std::cout << "testing " << i << "^2";
    if (n % i != 0)
      std::cout << " - failed" << std::endl;
    while (n % i == 0) {
      std::cout << " - success" <<std::endl << std::endl;
      std::cout << "prime factors found..." << std::endl;
      std::cout << i << "^2 ";
      n /= i;
      // after n updates to (n/x)=y, both loops will exit
    }
  }
  if (n > 1)
    // n is now essentially y
    std::cout << n << "^2" << std::endl;
}