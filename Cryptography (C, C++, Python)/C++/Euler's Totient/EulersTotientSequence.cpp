#include <iostream>

void phiSequence(int n);
int phi(int currNum);
int gcd(int a, int b);

int main() {
  int userNum;

  // Find phi sequence based upon user input
  std::cout << "Enter a number: ";
  std::cin >> userNum;
  std::cout << "Phi Sequence: ";
  phiSequence(userNum);
}

void phiSequence(int n) {
  //base case
  if(n <= 1) {
    std::cout << n << std::endl;
    return;
  }

  //function
  std::cout << n << ", ";
  int phiNum = phi(n);

  //recursion
  return phiSequence(phiNum);
}

int phi(int n) {
  int count = 1;

  for(int i=2; i<n; i++)
    if(gcd(i, n) == 1)
      count++;

  return count;
}

int gcd(int a, int b) {
  if (a == 0)
    return b;

  return gcd(b % a, a);
}