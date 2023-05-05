#include <stdio.h>

void shiftFunction(char* str, int size);
void repFuncts(char* str, int size, int reps);
void shiftByNum(char* str, int size, int reps);

int main(void) {
  char str1[] = "hpwnzxpezncjaeznwldd"; //encrypted string...
  char str2[] = "chnbcmwfummqyqcffvlyuewixymugihainbylnbchamohzilnohunyfsnbylyqcffvyhivolcyxnlyumolymvonnbylygcabnvyujlctyilnqi";
  int size1 = sizeof(str1)/sizeof(str1[0])-1; //remove end char with -1...
  int size2 = sizeof(str2)/sizeof(str2[0])-1;
  int numRecalls = 26; //#times to shift and print = #letters possible...

  printf("\nQuestion 1 decryption possibilities:\n");
  repFuncts(str1, size1, numRecalls);

  printf("\nQuestion 2 decryption possibilities:\n");
  repFuncts(str2, size2, numRecalls);

  printf("\nQuestion 1 Final Decrytpion (after 11 shifts):\n");
  shiftByNum(str1, size1, 11);
  printf("  %s\n", str1);
  printf("\nQuestion 2 Final Decrytpion (after 20 shifts):\n");
  shiftByNum(str2, size2, 20);
  printf("  %s\n", str2);
  
  return 0;
}

void shiftFunction(char* str, int size) {
  if(size == 0) return;
    
  else {
    //shift left by 1...
    str[size-1] -= 1;
    //check if left shift is within ASCII bounds...
    if(str[size-1] < 'a') {
      str[size-1] += 26;
    }
  }
  shiftFunction(str, size-1);
}

void repFuncts(char* str, int size, int reps) {
  if(reps == 0) return;
    
  else {
    shiftFunction(str, size);
    //NOTE: instead of printing here, could compare with dictionary...
    printf("  %s\n", str);
  }

  repFuncts(str, size, reps-1);
}

void shiftByNum(char* str, int size, int num) {
  if(num == 0) return;
    
  else {
    shiftFunction(str, size);
  }

  shiftByNum(str, size, num-1);
}