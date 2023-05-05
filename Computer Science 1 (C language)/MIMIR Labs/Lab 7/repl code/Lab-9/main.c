#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "leak_detector_c.h"

//global variables
#define NUMARRAYS 6
#define SIZE 10000
#define MAXSIZE 1000000

//functions
void randNumGen(int* arr, int size);
void copyArrs(int* arr1, int* arr2, int size);
void swap(int* a, int* b);
void bubbleSort(int* arr, int n);
void selectionSort(int* arr, int n);
void mergeSort(int* arr, int low, int high);
void merge(int* arr, int low, int mid, int high);
void quickSort(int* numbers, int low, int high);
int partition(int* vals, int low, int high);
void insertionSort(int* arr, int size);
long timeDiff(clock_t t1, clock_t t2);
void freeMem(int** arrs, int numArrs);

int main(void)
{
  atexit(report_mem_leak);
  srand(time(NULL)); //used to seed the random numbers...
  clock_t start;
  clock_t end;
  int sizes[NUMARRAYS] = { 1*SIZE, 2*SIZE, 3*SIZE, 4*SIZE, 5*SIZE, 6*SIZE};
  int* originalArrs;
  int* sortedArrs;
  int currSize;
  long elapsed;

  //iterate through each array
  for(int i=0; i<NUMARRAYS; i++)
  {
    currSize = sizes[i];

    //allocate memory for arrays
    originalArrs = (int*)malloc(currSize * sizeof(int));
    sortedArrs = (int*)malloc(currSize * sizeof(int));

    //populate arrays
    randNumGen(originalArrs, currSize);

    //copy arrays
    copyArrs(originalArrs, sortedArrs, currSize);

    //sort arrays
    start = clock();
    bubbleSort(sortedArrs, currSize);
    end = clock();
    elapsed = timeDiff(start, end);
    printf("\nsorting %d values takes %ld milli seconds for Bubble sort\n", currSize, elapsed);
    
    start = clock();
    selectionSort(sortedArrs, currSize);
    end = clock();
    elapsed = timeDiff(start, end);
    printf("\nsorting %d values takes %ld milli seconds for Selection sort\n", currSize, elapsed);

    start = clock();
    mergeSort(sortedArrs, 0, currSize);
    end = clock();
    elapsed = timeDiff(start, end);
    printf("\nsorting %d values takes %ld milli seconds for Merge sort\n", currSize, elapsed);

    start = clock();
    quickSort(sortedArrs, 0, currSize);
    end = clock();
    elapsed = timeDiff(start, end);
    printf("\nsorting %d values takes %ld milli seconds for Quick sort\n", currSize, elapsed);

    start = clock();
    insertionSort(sortedArrs, currSize);
    end = clock();
    elapsed = timeDiff(start, end);
    printf("\nsorting %d values takes %ld milli seconds for Insertion sort\n", currSize, end-start);

    //free arrays
    free(originalArrs);
    free(sortedArrs);
  }

  return 0;
}

void randNumGen(int* arr, int size)
{
  for(int i=0; i<size; i++)
  {
    arr[i] = rand() % size + 1;
  }
}

void copyArrs(int* arr1, int* arr2, int size)
{
  for(int i=0; i<size; i++)
  {
    arr2[i] = arr1[i];
  }
}

void swap(int* a, int* b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void bubbleSort(int* arr, int n)
{
  for (int i=0; i<n-1; i++)
  {
    for (int j=0; j<n-i-1; j++)
    {
      if (arr[j] > arr[j+1])
      {
        swap(&arr[j], &arr[j+1]);
      }
    }
  }
}

void selectionSort(int* arr, int n)
{
  int min_idx;

  for (int i=0; i<n-1; i++)
  {
    //find the minimum element in unsorted array
    min_idx = i;
    for (int j=i+1; j<n; j++)
    {
      if (arr[j] < arr[min_idx])
      {
        min_idx = j;
      }
    }
    //swap the found minimum element with the first element
    swap(&arr[i], &arr[min_idx]);
  }
}

void mergeSort(int* arr, int low, int high) {
   int mid;
   
   if(low < high) {
      mid = (low + high) / 2;
      mergeSort(arr, low, mid);
      mergeSort(arr, mid+1, high);
      merge(arr, low, mid, high);
   } else { 
      return;
   }   
}

void merge(int* arr, int low, int mid, int high) {
  int i = low;
  int j = mid+1;
  int k = 0; //number of elements in temp...

  //create temp array
  int temp[high-low+1];

  //traverse original and temp arrays
  //in each iteration, add smaller of both elements in temp 
  while(i <= mid && j <= high) {
		if(arr[i] <= arr[j]) {
			temp[k] = arr[i];
			k += 1;
      i += 1;
		}
		else {
			temp[k] = arr[j];
			k += 1;
      j += 1;
		}
	}

  //add elements left in the first interval 
  while(i <= mid) {
		temp[k] = arr[i];
		k += 1;
    i += 1;
	}

  //add elements left in the second interval 
  while(j <= high) {
		temp[k] = arr[j];
		k += 1; j += 1;
  }

  //copy temp to original interval
  for(i = low; i <= high; i += 1) {
		arr[i] = temp[i - low];
	}
}

void quickSort(int* numbers, int low, int high)
{
  if(low < high)
  {
    int split = partition(numbers, low, high);
    quickSort(numbers, low, split-1);
    quickSort(numbers, split+1, high);
  }
}

int partition(int* vals, int low, int high)
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

void insertionSort(int* arr, int size)
{
  int item;

  for(int i=1; i<size; i++)
  {
    item = arr[i];
    for(int j=i-1; j>=0; j--)
    {
      if(arr[j] > item)
      {
        arr[j+1] = arr[j];
      }
      else
      {
        break;
      }
      arr[j+1] = item;
    }
  }
}

long timeDiff(clock_t t1, clock_t t2)
{
  long elapsed;
  elapsed = ((double)t2-t1) / CLOCKS_PER_SEC * 1000;
  return elapsed;
}

void freeMem(int** arrs, int numArrs)
{
  for(int i=0; i<numArrs; i++)
  {
    free(arrs[i]);
  }
  free(arrs);
}