#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structures
typedef struct node
{
  int data;
  struct node* next;
} node;

//functions
void question1();
void rec2(int x);

void question2();
int crazySum(int n);
int power(int a, int b);

void question3();
int question3Function(int a, int b);

void question4();
int convertDecimalToOctal(int n);

void question5();
int zeros(int n);

void question6();
int productDigits(int n);

void question7();
int weightedSum(int numbers[], int n);

void question8();
int sqrfunc(int n);
int fcomp(int n, int k);

void question9();
int fun(int x);

void question10();
int f(int n);

void question11();
int isSorted(int *array, int n);

void question12();
void permute(char* s, int l, int r);
void swap(char* a, char* b);

void question13();
int search(int numbers[], int low, int high, int value);

void question14();
void addNodeToFront(node** dataNode, int data);
void addNodeToEnd(node** dataNode, int data);
node* addNodeToPlace(node* list, int val, int place);
node* deleteNodeFromFront(node* dataNode);
node* deleteNodeFromEnd(node* dataNode);
void deleteSpecificNodeFromList(node** dataNode, int n);
void displayNode(node* dataNode);
int getListSize(node* list);

//main
int main(void)
{
  printf("question #1:\n");
  question1();
  printf("\n\n");

  printf("question #2:\n");
  question2();
  printf("\n\n");

  printf("question #3:\n");
  question3();
  printf("\n\n");

  printf("question #4:\n");
  question4();
  printf("\n\n");

  printf("question #5:\n");
  question5();
  printf("\n\n");

  printf("question #6:\n");
  question6();
  printf("\n\n");

  printf("question #7:\n");
  question7();
  printf("\n\n");

  printf("question #8:\n");
  question8();
  printf("\n\n");

  printf("question #9:\n");
  question9();
  printf("\n\n");

  printf("question #10:\n");
  question10();
  printf("\n\n");

  printf("question #11:\n");
  question11();
  printf("\n\n");

  printf("question #12:\n");
  question12();
  printf("\n");

  printf("question #13:\n");
  question13();
  printf("\n\n");

  printf("question #14:\n");
  question14();
  printf("\n");

  return 0;
}

void question1()
{
  rec2(5);
}
void rec2(int x)
{
  if (x==0)
  {
    return;
  }
  else
  {
    rec2(x-1);
  }
  printf("%d  ", x);
}

void question2() {
  int answer = crazySum(3);

  printf("%d", answer);
}
int crazySum(int n)
{
  if(n == 0)
  {
    return 0; //add 0 to end...
  }
  else
  {
    return power(n, n) + crazySum(n-1);
  }
}
int power(int a, int b)
{
  if(b == 0)
  {
    return 1; //multiply by 1 at end...
  }
  else
  {
    return a * power(a, b-1);
  }
}

void question3()
{
  int answer = question3Function(10, 101);

  printf("%d", answer);
}
int question3Function(int a, int b)
{
  if (a == 0) return b;
  if (b == 0) return a;
  return question3Function((10*a+b%10), b/10);
  //order of operations: (10*a) + (b%10)...
  //first, returns (101, 10)...
  //then, returns (1010, 1)...
  //finally, returns (10101) - because b==0, and a==10101...
}

void question4()
{
  int answer = convertDecimalToOctal(210);

  printf("%d", answer);
}
int convertDecimalToOctal(int n)
{
  int remainder = 0;
  int nextN = 0;
  if(n == 0)
  {
    return n; //returns 0...
  }
  else
  {
    remainder = n%8;
    nextN = n/8;
    return remainder + 10*convertDecimalToOctal(nextN);
    //*using three integer (210) decimal as example*
    //convertDecimalToOctal(210) will return 2 + 10*convert(26)...
    //convertDecimalToOctal(26) will return 2 + 10*convert(3)...
    //convertDecimalToOctal(3) will return 3 +10*convert(0)...
    //convertDecimalToOctal(0) will return 0...
    //*plug in the return values*
    //convertDecimalToOctal(3) will return 3 + 0...
    //convertDecimalToOctal(26) will return 2 + 30...
    //convertDecimalToOctal(210) will return 2 + 320...
    //final return will be (2+320) = 322...
    //*note*
    //remainder and nextN variables can be removed...
    //then the else statement will be return n%8+10*convertDecimalToOctal(n/8)...
    //the variables within the function just help to understand the process...
  }

  //done with static variables:
  /*
  static int octal = 0;
  static int place = 1;
  if( n != 0)
  {
    octal+=(n%8)*place;
    place*=10;
    convertDecimalToOctal(n/8);
  }
  return octal;
  */
}

void question5()
{
  int answer = zeros(25);

  printf("%d", answer);
}
int zeros(int n)
{
  if(n == 0)
  {
    return 0;
  }
  else
  {
    return (n/5) + zeros(n/5);
    //returns the result of diving current value n by 5 after each run...
    //then adds the result to the previous run...
    //this continues until n == 0, then 0 is added to final run...
  }
}

void question6()
{
  int answer = productDigits(243);

  printf("%d", answer);
}
int productDigits(int n)
{
  int lastDigit = 0;
  int nextN = 0;
  if(n == 0)
  {
    return 1; //return 1 for multiplication...
  }
  else
  {
    lastDigit = n%10;
    nextN = n-lastDigit;
    return (lastDigit) * productDigits(nextN/10);
    //n%10 will get last digit...
    //need to subtract last digit from n...
    //need to divide n by 10 to remove last digit from n...
  }
}

void question7() {
  int n = 3;
  int array[3] = {5, 2, 6};
  int answer = weightedSum(array, n);

  printf("%d", answer);
}
int weightedSum(int numbers[], int n)
{
  if(n == 0)
  {
    return 0; //add 0...
  }
  else
  {
    return (numbers[n-1] * n) + weightedSum(numbers, n-1);
    //arrays start at index 0, so use numbers[n-1] to equal n...
    //multiply current array index with n, then add previous index...
    //previous index will use the same array, with index n-1...
    //function will continue adding previous array elements until 0...
  }
}

void question8()
{
  int answer = fcomp(5, 3);

  printf("%d", answer);
}
int sqrfunc(int n) //f is used in question 10, so using square function instead...
{
  return n*n;
}
int fcomp(int n, int k)
{
  if(k == 1)
  {
    return sqrfunc(n); //runs function once...
  }
  else if(k > 1)
  {
    return fcomp(n, k-1) * sqrfunc(n); //runs recursion until k==1...
  }
  else
  {
    printf("ERROR - must be positive number\n");
    return 0;
  }
}

void question9()
{
  int answer = fun(7);

  printf("%d", answer);
}
int fun(int x)
{
  if(x==0)
  {
    return 0; //will return 0 to be added...
  }
  if(x%3==0)
  {
    return fun(x/3);
  }
  return fun(x-1) + x;
  //using 7 for example...
  //determine functions during process...
  //fun(7) = return fun(6) + 7...
  //fun(6) = return fun(2)...
  //fun(2) = return fun(1) + 2...
  //fun(1) = return fun(0) + 1...
  //fun(0) = return 0...
  //determine results from processing...
  //0 + 1 = 1...
  //1 + 2 = 3...
  //3 + 7 = 10...
  //10 is the final answer...
}

void question10()
{
  int answer = f(5);

  printf("%d", answer);
}
int f(int n)
{
  int ans;
  int i;
  if(n<3)
  {
    return n;
  }
  ans = f(n/2);
  for(i=0; i<n; i++)
  {
    ans += f(i);
  }
  return ans;

  /*
  NOTES for this function:
  f(5)
	ans = f(5/2) - "5/2 == 2"
		f(2) = 2
	ans = 2
	for (int i=0; i<n; i++)
	{
		ans += f(i);
		//while i<3, will be added to ans...
		//this means that when i==2, ans==5...
		//when i==3, then ans==9...
		//when i==4, then ans==18...
	}
  */
}

void question11()
{
  int array1[] = {2, 4, 6, 8, 10};
  int answer1 = isSorted(array1, sizeof(array1)/4);
  int array2[] = {24, 75, 97, 2, 75, 99};
  int answer2 = isSorted(array2, sizeof(array2)/4);

  printf("sorted:%d unsorted:%d", answer1, answer2);
}
int isSorted(int *tempArray, int n)
{
  if(n>1)
  {
    if(tempArray[n-1] >= tempArray[n-2])
    {
      return 1 * isSorted(tempArray, n-1); //if in ascending order...
    }
    else
    {
      //return 0 * isSorted(tempArray, n-1);
      return 0; //if not in ascending order...
    }
  }
  else
  {
    return 1; //will start by multiplying by 1...
  }
}

void question12()
{
  char string[] = "CAT";
  int l = 0; //start at 0...
  int r = strlen(string)-1; //end at string length-1...
  permute(string, l, r); //permutations == n!...
}
void permute(char* s, int l, int r)
{
  if(l == r)
  {
    printf("%s\n", s); //output each permutation...
  }
  else
  {
    for(int i=l; i<=r; i++)
    {
      swap(&s[l], &s[i]); //swap...
      permute(s, l+1, r); //recursion...
      swap(&s[l], &s[i]); //swap back...
      //when i == 0, output permutations CAT and CTA...
      //when i == 1, output permutations ACT and ATC...
      //when i == 2, output permutations TAC and TCA...
    }
  }
}
void swap(char* a, char* b)
{
  char tempChar;

  tempChar = *a;
  *a = *b;
  *b = tempChar;
}

void question13()
{
  int numbers[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
  int low = 0; //start at index 0...
  int high = (sizeof(numbers)/sizeof(int))-1; //end at index 4...
  int value = 3; //search for number 3...
  int location = search(numbers, low, high, value);

  printf("%d", location);
}
int search(int numbers[], int low, int high, int value)
{
  int mid = 0;
  if(low <= high)
  {
    mid = (low+high)/2;
    if (value < numbers[mid]) //if location is lower...
      return search(numbers, low, mid-1, value);
    else if (value > numbers[mid]) //if location is higher...
      return search(numbers, mid+1, high, value);
    else //if numbers[mid] == value...
      return mid; //returns location (index of found value)...
  }
  else
    return -1; //return value of -1 if value was not found...
}

void question14()
{
  int num = 5;
  node* dataNode = NULL;
  int val = 10;
  int place = 3;

  //fill linked list with ascending numbers up to size of num
  for(int i=0; i<num; i++)
  {
    addNodeToEnd(&dataNode, i+1);
  }
  printf("Original linked list: ");
  displayNode(dataNode);
  printf("\n");

  //add node to front of list
  printf("Adding node to front: ");
  addNodeToFront(&dataNode, dataNode->data-1);
  displayNode(dataNode);
  printf("\n");

  //add node to end of list
  printf("Adding node to end: ");
  addNodeToEnd(&dataNode, num+1);
  displayNode(dataNode);
  printf("\n");

  //add node to specific place in list
  printf("Adding node %d to place %d: ", val, place);
  dataNode = addNodeToPlace(dataNode, val, place);
  displayNode(dataNode);
  printf("\n");

  //delete node from front of list
  printf("removing node from front: ");
  dataNode = deleteNodeFromFront(dataNode);
  displayNode(dataNode);
  printf("\n");

  //delete node from end of list
  printf("removing node from end: ");
  dataNode = deleteNodeFromEnd(dataNode);
  displayNode(dataNode);
  printf("\n");

  //delete specific node from list
}
void addNodeToFront(node** dataNode, int n)
{
  //allocate memory for node
  node* new_node = (node*)malloc(sizeof(node));

  //fill node with data
  new_node->data = n;

  //set node->next to original linked list pointer
  new_node->next = (*dataNode);

  //set original linked list pointer to newly created node
  (*dataNode) = new_node;
}
void addNodeToEnd(node** dataNode, int n)
{
  //allocate memory for node
  node* newNode = (node*)malloc(sizeof(node));
  //allocate memory for end of list, which copies original list
  node* lastNode = *dataNode;

  //fill in node data
  newNode->data = n;
  //set next node pointer
  newNode->next = NULL;

  //if list is empty
  if(*dataNode == NULL)
  {
    *dataNode = newNode;
  }
  //if list is not empty
  else
  {
    //find last node location
    while (lastNode->next != NULL)
    {
      lastNode = lastNode->next;
    }
  
    //add new node to end of last node location
    lastNode->next = newNode;
  }
}
node* addNodeToPlace(node* list, int val, int place)
{
  //get number of nodes in list
  int listSize = getListSize(list);

  //check if list is empty
  if(list == NULL)
  {
    printf("\n*ERROR* - list is empty\n");
    return list;
  }
  //check if place is not valid
  else if(place < 1 || place > listSize)
  {
    printf("\n*ERROR* - place is invalid\n");
    return list;
  }
  //valid case
  else
  {
    //create (empty) list that will later contain nodes before place
    node *previous_list = NULL;
    //create list (copy of list) which will contain nodes after place
    node *current_list = list;
    //create new node and MUST allocate memory for node because it is new
    node* temp_node = (node*)malloc(sizeof(node));
    //store data (val) to new node
    temp_node->data = val;

    //locate place within linked list
    for(int i=0; i<place; i++)
    {
      if(i >= place-1) //if place is higher than number of elements...
      {
        break; //if i reaches place location break loop...
      }
      //set previous list to current list to save nodes before place
      previous_list = current_list;
      //traverse through current list to keep track of nodes after place
      current_list = current_list->next;
    }

    //set temp node's next pointer to current list
    temp_node->next = current_list;

    //check if previous list contained data
    if (previous_list != NULL)
    {
      //set previous list's next pointer to temp node
      previous_list->next = temp_node;
    }
    //if previous list was empty
    else
    {
      //set linked list to start at temp node
      list = temp_node;
    }

    //return updated list
    return list;
  }
}
node* deleteNodeFromFront(node* dataNode)
{
  //check if linked list is empty
  if(dataNode == NULL)
  {
    printf("list is already empty");
    return NULL;
  }
  //check if linked list only contains 1 node
  else if(dataNode->next == NULL) {
    free(dataNode);
    return NULL;
  }
  else
  {
    //allocate memory for temp list, which copies original list
    node* deleteNode = dataNode;

    //move list down by one place
    dataNode = dataNode->next;

    //delete node
    free(deleteNode);

    //return updated list
    return dataNode;
  }
}
node* deleteNodeFromEnd(node* dataNode)
{
  //check if linked list is empty
  if(dataNode == NULL)
  {
    return NULL;
  }
  //check if linked list only contains 1 node
  else if(dataNode->next == NULL) {
    free(dataNode);
    return NULL;
  }
  else
  {
    //allocate memory for temp list, which copies original list
    node* second_last = dataNode;

    //find node before end of linked list
    while (second_last->next->next != NULL)
    {
      second_last = second_last->next;
    }
 
    //free last node
    free(second_last->next);

    //set (the last) next pointer to null
    second_last->next = NULL;

    //return the original (modified) linked list
    return dataNode;
  }
}
void deleteSpecificNodeFromList(node** dataNode, int n)
{
  //create before and after node pointers that will traverse through
  //the list, stop when the location's data equals n, free the node at
  //the location, and then connect the before and after node pointers...
}
void displayNode(node* dataNode)
{
  //loop until list is empty
	while (dataNode != NULL)
	{
    //output data
		printf("%d", dataNode->data);
    //traverse through list
		dataNode = dataNode->next;
    //output symbol between data points
		if (dataNode != NULL)
		{
			printf("->");
		}
	}
}
int getListSize(node* list)
{
  int count = 0;
  node* current_list = list; //for traversing through list...

  //loop until end of list
  while (current_list != NULL)
  {
    count++; //keep track of number of nodes...
    current_list = current_list->next; //traverse through list...
  }

  return count;
}