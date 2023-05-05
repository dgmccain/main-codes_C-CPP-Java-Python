/* COP 3502C Assignment 4
This program is written by: David McCain */

#include <stdio.h>
#include <stdlib.h>
#include "leak_detector_c.h"

//structures
typedef struct book
{
  int bookID;
  long int numPages;
} book;

typedef struct library
{
  book* b;
  int numBooks;
  long long int maxNumPages;
} library;

//global variables
FILE* infile;
FILE* outfile;

//functions
library* readLibrary();
library** readLibraries(int numLibraries);
void quickSort(long int* arr, int low, int high);
int partition(long int* arr, int low, int high);
void swap(long int* a, long int* b);
void outputMaxBooks(library** libs, int size);
void display(library** libs, int size);
void freeLibraries(library** libs, int numLibraries);

//main
int main(void)
{
  atexit(report_mem_leak);
  
  int numLibraries;
  library** libs; //will store libraries of books
  long int* tempArr; //will store number of pages per book per library

  infile = fopen("in.txt", "r");
  outfile = fopen("out.txt", "w");

  //read in number of libraries
  fscanf(infile, "%d", &numLibraries);

  //create libraries
  libs = readLibraries(numLibraries);

  //sort libraries
  for(int i=0; i<numLibraries; i++)
  {
    //allocate memory for tempArr
    tempArr = (long int*)malloc(libs[i]->numBooks * sizeof(long int));

    //copy library books to tempArr
    for(int j=0; j<libs[i]->numBooks; j++)
    {
      tempArr[j] = libs[i]->b[j].numPages;
    }

    //sort through tempArr
    quickSort(tempArr, 0, libs[i]->numBooks-1);

    //set library books to the sorted tempArr
    for(int j=0; j<libs[i]->numBooks; j++)
    {
      libs[i]->b[j].numPages = tempArr[j];
    }

    //free memory for tempArr
    free(tempArr);
  }

  //output to console and file
  outputMaxBooks(libs, numLibraries);

  //free memory
  freeLibraries(libs, numLibraries);

  //close files
  fclose(infile);
  fclose(outfile);

  return 0;
}

library* readLibrary()
{
  //allocate memory space for library data
  library* lib = (library*)malloc(sizeof(library));

  //read number of books in library
  fscanf(infile, "%d", &lib->numBooks);
  //read max number of pages user can read
  fscanf(infile, "%lld", &lib->maxNumPages);

  //allocate memory space for book data
  lib->b = (book*)malloc(lib->numBooks * sizeof(book));

  //read number of pages per book
  for(int i=0; i<lib->numBooks; i++)
  {
    lib->b[i].bookID = i;
    fscanf(infile, "%ld", &lib->b[i].numPages);
  }

  return lib;
}

library** readLibraries(int numLibraries)
{
  //allocate memory for libraries
  library** libs = (library**)malloc(numLibraries * sizeof(library*));

  //read each library's data (and book data per library)
  for(int i=0; i<numLibraries; i++)
  {
    libs[i] = readLibrary();
  }

  return libs;
}

void quickSort(long int* numbers, int low, int high)
{
  if(low < high)
  {
    int split = partition(numbers, low, high);
    quickSort(numbers, low, split-1);
    quickSort(numbers, split+1, high);
  }
}

int partition(long int* vals, int low, int high)
{
  int i = low + rand()%(high-low+1);
  swap(&vals[low], &vals[i]);
  int pivot = low;
  low++;

  while(low<=high)
  {
    while(low<=high && vals[low]<=vals[pivot])
    {
      low++;
    }
    while(high>=low && vals[high]>vals[pivot])
    {
      high--;
    }
    if(low<high)
    {
      swap(&vals[low], &vals[high]);
    }
  }
  swap(&vals[pivot], &vals[high]);

  return high;
}

void swap(long int* a, long int* b)
{
  long long int temp = *a;
  *a = *b;
  *b = temp;
}

void outputMaxBooks(library** libs, int size)
{
  long int tempMax;
  int tempPlace;

  for(int i=0; i<size; i++)
  {
    //reset place holder
    tempMax = 0;
    tempPlace = 0;

    //calculate how many books until maximum number of pages is reached
    while(tempMax <= libs[i]->maxNumPages && tempPlace < libs[i]->numBooks)
    {
      tempMax += libs[i]->b[tempPlace].numPages;
      tempPlace++;
    }

    //subtract 1 book if maximum number of pages was reached
    if(tempMax > libs[i]->maxNumPages)
    {
      tempPlace--;
    }

    printf("%d\n", tempPlace);
    fprintf(outfile, "%d\n", tempPlace);
  }
}

void display(library** libs, int size)
{
  int count = 0;
  while(count < size)
  {
    printf("\nLibrary #%d Data...\n", count);
    printf("Number of books: %d\n", libs[count]->numBooks);
    printf("Maximum number of pages: %lld\n", libs[count]->maxNumPages);
    printf("Book Data...\n");
    for(int i=0; i<libs[count]->numBooks; i++)
    {
      printf("Book ID: %d ", libs[count]->b[i].bookID);
      printf("Number of pages in book: %ld\n", libs[count]->b[i].numPages);
    }
    count++;
  }
}

void freeLibraries(library** libs, int numLibraries)
{
  for (int i = 0; i < numLibraries; i++)
  {
    free(libs[i]->b); //free each book...
    free(libs[i]); //free each library...
  }
  free(libs); //free all libraries...
}