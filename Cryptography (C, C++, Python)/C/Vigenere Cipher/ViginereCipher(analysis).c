#include <stdio.h>
#include <stdlib.h>


int* countLetterOccurrences(char* str, int size);
double findIndexOfCoincidence(int* numLetters, int totalLetters);
double letterFrequency(int a, int b);

int main(void) {
  char encMsg[] = "vvgvexzqjzzsiogqhrlawvmldznhipghnuqeuqbsplqoevoeecslmbpyqpegakexciwebzepglrhalfzosozzdavhryhyryhqachttnsrgawfrvskntwmeaokuekdsmfqyepghnnswrwoghmcewvhbulfzwiumjtymvsnpkfrniltmxwwqknvahvzrwavesmnesvhnuztwzbspagcbpkcrmmfqbqcwotugaogtrltmcpgqufjvucojazlesmeoqgiofvazukstaaohtwrzkixazopkqdvpntytweqadlogfvtztyztwrcwwgvhrebskzhamtdeihfqkknkeecqqe";
  int msgSize = sizeof(encMsg)/sizeof(encMsg[0])-1;
  
  int* letterOccurrences = countLetterOccurrences(encMsg, msgSize);
  double indexOfCoincidence = findIndexOfCoincidence(letterOccurrences, msgSize);
  double letterFreq;

  for(int i=0; i<26; i++) {
    letterFreq = letterFrequency(letterOccurrences[i], msgSize);
    printf("letter: %c  occurrences: %d  frequency: %lf%\n", ('a'+i), letterOccurrences[i], letterFreq*100);
  }
  printf("index of occurrence: %lf%%\n", indexOfCoincidence*100);
  
  return 0;
}

int* countLetterOccurrences(char* str, int size) {
  static int letters[26] = {0};

  for(int i=0; i<size; i++) {
    for(int j=0; j<26; j++) {
      if(str[i] == 'a' + j) letters[j]++;
    }
  }

  return letters;
}

double findIndexOfCoincidence(int* numLetters, int totalLetters) {
  int numerator = 0;
  int denominator = 0;

  for(int i=0; i<26; i++) {
    if(numLetters[i] > 0) {
      numerator += numLetters[i]*(numLetters[i]-1);
    }
  }
  denominator += totalLetters*(totalLetters-1);

  return (double)numerator/denominator;
}

double letterFrequency(int a, int b) {
  return (double)a/b;
}