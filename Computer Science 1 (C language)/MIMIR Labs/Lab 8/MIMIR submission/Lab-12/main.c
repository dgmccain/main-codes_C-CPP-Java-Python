#include <stdio.h>
#include <stdlib.h>

//functions
int isHeap_recursive(int* arr, int i, int n);
int isHeap_iter(int* arr, int n);

//main
int main()
{
  int* arr;
  int arrSize;

  //Get array size
  printf("How many entries? ");
  scanf("%d", &arrSize);
  //Allocate memory for array
  arr = (int*)malloc(arrSize * sizeof(int));
  //Get array elements
  printf("Enter %d entries: ", arrSize);
  for(int i=0; i<arrSize; i++)
  {
    scanf("%d", &arr[i]);
  }

  //Recursive check
  if(isHeap_recursive(arr, 0, arrSize))
    printf("Recursive says Yes!\n");
  else
    printf("Recursive says No!\n");

  //Iterative check
  if(isHeap_iter(arr, arrSize))
    printf("Iterative says Yes!\n");
  else
    printf("Iterative says No!\n");

  //Free memory
  free(arr);
  
  return 0;
}

int isHeap_recursive(int* arr, int i, int n)
{
  //Base case
  if(n <= 0 || n <= i)
    return 1;

  //Left case
  if(2*i+1 < n)
    if(arr[2*i+1] < arr[i])
      return 0;

  //Right case
  if(2*i+2 < n)
    if(arr[2*i+2] < arr[i])
      return 0;

  //Recursion
  return isHeap_recursive(arr, 2*i+1, n) * isHeap_recursive(arr, 2*i+2, n);
}

int isHeap_iter(int* arr, int n)
{
  for(int i=0; i<=(n-2)/2; i++)
  {
    //Left check
    if(2*i+1 < n) //do not check unassigned (NULL) nodes...
      if(arr[2*i+1] < arr[i])
        return 0;

    //Right check
    if(2*i+2 < n) //do not check unassigned (NULL) nodes...
      if(arr[2*i+2] < arr[i])
        return 0;
  }
  return 1;
}