#include <stdio.h>
#include <string.h>

void affineDecryption(char *str, int size, int a, int b, int n);
int searchStr(char* str, int k);

int main(void) {
  char origStr[] = "ptuellkrumkztuhotkjuripyumghuckxuyauerexurgupivhiemtrgavuhptuihwesuwmiazirurpilptkymjeyy";
  char str[] = "ptuellkrumkztuhotkjuripyumghuckxuyauerexurgupivhiemtrgavuhptuihwesuwmiazirurpilptkymjeyy";
  int size = sizeof(str) / sizeof(str[0]) - 1; // remove end char with -1...
  int n = 26; // mod #...

  /*
  //NOTE: to find exactly where i and j decrypted code...
  int aInv = 23; //23 in inverse of 17 which is actually a...
  int b = 4; //b and b inverse are the same...
  affineDecryption(str, size, aInv, b, n);
  printf("%s\n", str);
  */

  printf("\nDecryption text(s) containing the word 'the':\n");
  //i only needs to iterate through possible modular inverse integers...
  for(int i=1; i<n; i+=2) {
    for(int j=1; j<=n; j++) {
      if(i == 13) i+=2; //exclude 13 from modular inverse...
      affineDecryption(str, size, i, j, n);
      //check if the word "the" is in string...
      for(int k=0; k<n; k++) {
        if(searchStr(str, k))
          printf("\n  %s\n", str);
      }
      //reset str to original plaintext before each decryption...
      strcpy(str, origStr);
    }
  }

  return 0;
}

void affineDecryption(char *str, int size, int a, int b, int n) {
  if (size == 0)
    return;

  else {
    //affine decypher algorithm: y=a(x-b)mod n...
    //must subtract 'a' before algorithm, then add back at end...
    str[size - 1] = ((a * (str[size - 1] - b)) % n);
    //ensure that ASCII value is within a-z range...
    while(str[size-1] < 'a') str[size-1] += n;
    while(str[size-1] > 'z') str[size-1] -=n;
  }
  affineDecryption(str, size-1, a, b, n);
}

int searchStr(char* str, int k) {
  //check if str[k] exists, then check for expected letters...
  if(str[k] && str[k] == 't')
    if(str[k+1] && str[k+1] == 'h')
      if(str[k+2] && str[k+2] == 'e')
        return 1;
  return 0;
}