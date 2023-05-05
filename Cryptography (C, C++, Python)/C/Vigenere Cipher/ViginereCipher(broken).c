#include <stdio.h>
#include <stdlib.h>

typedef struct listOfLetters {
  int sizeOfGroup;
  int* groupOfLetters;
} listOfLetters;

int* countLetterOccurrences(char* str, int size);
double findIndexOfCoincidence(int* numLetters, int totalLetters);
int getKeywordLength(int* numLetters, int totalLetters);
double keywordHelperFunction(int* arr, int totalLetters, int keyLength);
int* createLettersGroup(int numElements);

int main(void) {
  char encMsg[] = "vvgvexzqjzzsiogqhrlawvmldznhipghnuqeuqbsplqoevoeecslmbpyqpegakexciwebzepglrhalfzosozzdavhryhyryhqachttnsrgawfrvskntwmeaokuekdsmfqyepghnnswrwoghmcewvhbulfzwiumjtymvsnpkfrniltmxwwqknvahvzrwavesmnesvhnuztwzbspagcbpkcrmmfqbqcwotugaogtrltmcpgqufjvucojazlesmeoqgiofvazukstaaohtwrzkixazopkqdvpntytweqadlogfvtztyztwrcwwgvhrebskzhamtdeihfqkknkeecqqe";
  int msgSize = sizeof(encMsg)/sizeof(encMsg[0])-1;
  int keywordLength;
  
  int* letterOccurrences = countLetterOccurrences(encMsg, msgSize);
  double indexOfCoincidence = findIndexOfCoincidence(letterOccurrences, msgSize);

  //printf("index of occurrence: %lf\n", indexOfCoincidence);
  keywordLength = getKeywordLength(letterOccurrences, msgSize);
  
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

int getKeywordLength(int* numLetters, int totalLetters) {
  int keyLength = 1;
  double currentIC = 0;
  double indexOfCoincidence;

  //determine most likely key length from 1 to 26...
  for(int i=1; i<26; i++) {
    indexOfCoincidence = keywordHelperFunction(numLetters, totalLetters, i);
    //update keylength based upon index of coincidence...
    if(indexOfCoincidence > currentIC) {
      currentIC = indexOfCoincidence;
      keyLength = i;
    }
    printf("Index of Coincidence for keylength %d: %lf\n", i, indexOfCoincidence);
  }

  return keyLength;
}

double keywordHelperFunction(int* arr, int totalLetters, int keyLength) {
  //avoid creating list if keyword length is < 2...
  if(keyLength == 1) return findIndexOfCoincidence(arr, totalLetters);
  
  double indexOfCoincidence = 0.0;
  int currNumLetters = 26;
  listOfLetters* list = (listOfLetters*)malloc(keyLength*sizeof(listOfLetters));
  int i;
  int j;

  //create list...
  for(i=0; i<keyLength; i++) {
    //create group of letter frequencies based upon key length...
    list[i].sizeOfGroup = (int)currNumLetters/(keyLength-i);
    currNumLetters -= list[i].sizeOfGroup;
    list[i].groupOfLetters = createLettersGroup(list[i].sizeOfGroup);
    //fill created group with correct letter frequencies...
    printf("Group #%d: ", i);
    for(j=0; j<list[i].sizeOfGroup; j++) {
      list[i].groupOfLetters[j] = arr[i+(j*keyLength)];
      printf("%d ", list[i].groupOfLetters[j]);
    }
    printf("\n");
    //find total number of letters in group...
    totalLetters = 0;
    for(j=0; j<list[i].sizeOfGroup; j++) {
      totalLetters += list[i].groupOfLetters[j];
    }
  }

  //find index of coincidence for key lengths using list...
  for(i=0; i<keyLength; i++) {
    indexOfCoincidence += findIndexOfCoincidence(list[i].groupOfLetters, totalLetters);
  }
  indexOfCoincidence /= keyLength;

  //free memory when done using list...
  for(int i=0; i<keyLength; i++) {
    free(list[i].groupOfLetters);
  }
  free(list);

  return indexOfCoincidence;
}

int* createLettersGroup(int numElements) {
  int* newGroup = (int*)malloc(numElements*sizeof(int));

  return newGroup;
}