#include <stdio.h>

void affineEncryption(char* str, int size, int a, int b);

int main(void) {
  char str[] = "artemisonemoonrocketarrivesatlaunchpadaheadofhistoricmission"; //decrypted string
  int size = sizeof(str)/sizeof(str[0])-1; //remove end char with -1...
  int a = 5;
  int b = 21;

  printf("\nQuestion 4 encryption:\n");
  affineEncryption(str, size, a, b);
  printf("  %s\n", str);
  
  return 0;
}

void affineEncryption(char* str, int size, int a, int b) {
  if(size == 0) return;
    
  else {
    //subtract ASCII value 'a' to get decimal value, then perform affine
    //algorithm (ax+b)%26, finally add back 'a' after mod operation...
    str[size-1] = ((a*(str[size-1]-'a') + b) % 26) + 'a';
  }
  affineEncryption(str, size-1, a, b);
}