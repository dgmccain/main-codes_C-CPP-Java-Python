#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "leak_detector_c.h"

//global variables
FILE* infile;
FILE* outfile;
int wordLength = 20;
int numWords = 0;

//structures
typedef struct sortedWords
{
  char* word;
  int freq;
} sortedWords;
typedef struct tree_node
{
  sortedWords* wordData;
  int depth;
  struct tree_node* left;
  struct tree_node* right;
} tree_node;

//functions
tree_node* readFile(tree_node* my_root);
tree_node* create_node(char* str);
tree_node* insert(tree_node* root, tree_node* element);
tree_node* search(tree_node* current_ptr, char* str);
sortedWords* createWords();
void copyFromTree(tree_node* current_ptr, sortedWords* wordsInOrder);
void quickSort(sortedWords* arr, int low, int high);
int partition (sortedWords* arr, int low, int high);
void swap(sortedWords* a, sortedWords* b);
int compareTo(sortedWords* a, sortedWords* b);
void printSortedWords(sortedWords* wordsInOrder);
void freeTree(tree_node* myTree);
void freeSortedWords(sortedWords* myWords);

//main
int main(void)
{
  atexit(report_mem_leak);
  
  tree_node* my_root = NULL;
  sortedWords* wordsInOrder;

  infile = fopen("in.txt", "r");
  outfile = fopen("out.txt", "w");

  my_root = readFile(my_root);

  if(my_root != NULL)
  {
    //copy words from tree
    wordsInOrder = createWords();
    copyFromTree(my_root, wordsInOrder);

    //sort words then output sorted words
    quickSort(wordsInOrder, 0, numWords-1);
    printSortedWords(wordsInOrder);

    freeSortedWords(wordsInOrder);
    freeTree(my_root);
  }

  fclose(infile);
  fclose(outfile);

  return 0;
}

tree_node* readFile(tree_node* my_root)
{
  tree_node* temp_node;
  int numLines;
  int option;
  char str[wordLength];

  //get number of lines
  fscanf(infile, "%d", &numLines);

  //read in words and their instructions from file
  for(int i=0; i<numLines; i++)
  {
    fscanf(infile, "%d %s", &(option), str);
    switch(option)
    {
      case 1:
        temp_node = search(my_root, str);
        if(temp_node == NULL)
        {
          temp_node = create_node(str);
          my_root = insert(my_root, temp_node);
        }
        else
          temp_node->wordData->freq++;
        break;
      case 2:
        temp_node = search(my_root, str);
        if(temp_node == NULL)
        {
          printf("-1 -1\n");
          fprintf(outfile, "-1 -1\n");
        }
        else
        {
          printf("%d %d\n", temp_node->wordData->freq, temp_node->depth);
          fprintf(outfile, "%d %d\n", temp_node->wordData->freq, temp_node->depth);
        }
        break;
      default:
        printf("ERROR\n");
    }
  }

  return my_root;
}

tree_node* create_node(char* str)
{
  //create new node
  tree_node* new_node;
  new_node = (tree_node*)malloc(sizeof(tree_node));
  new_node->wordData = (sortedWords*)malloc(sizeof(sortedWords));
  new_node->wordData->word = (char*)malloc(wordLength * sizeof(char));
  
  //set new node
  strcpy(new_node->wordData->word, str);
  new_node->wordData->freq = 1;
  new_node->depth = 0;
  new_node->left = NULL;
  new_node->right = NULL;

  return new_node;
}

tree_node* insert(tree_node* root, tree_node* element)
{
  if(root==NULL)
  {
    numWords++;
    return element;
  }
  else
  {
    //if element word is greater than root word
    if(strcmp(element->wordData->word, root->wordData->word) > 0)
    {
      element->depth++; //increase depth tracked...
      if(root->right != NULL)
        root->right = insert(root->right, element);
      else
      {
        root->right = element;
        numWords++; //increase number of words tracked...
      }    
    }
    //if element word is less than root word
    else if(strcmp(element->wordData->word, root->wordData->word) < 0)
    {
      element->depth++; //increase depth tracked...
      if(root->left != NULL)
        root->left  = insert(root->left, element);
      else
      {
        root->left = element;
        numWords++; //increase number of words tracked...
      }
    }
    return root;
  }
}

tree_node* search(tree_node* current_ptr, char* str)
{
  if(current_ptr != NULL)
  {
    if(strcmp(str, current_ptr->wordData->word) < 0)
      return search(current_ptr->left, str);
    else if(strcmp(str, current_ptr->wordData->word) > 0)
      return search(current_ptr->right, str);
    else
      return current_ptr;
  }
  else
  {
    return NULL;
  }
}

sortedWords* createWords()
{
  sortedWords* wordsInOrder = (sortedWords*)malloc(numWords* sizeof(sortedWords));

  for(int i=0; i<numWords; i++)
  {
    wordsInOrder[i].word = (char*)malloc(wordLength * sizeof(char));
  }

  return wordsInOrder;
}

void copyFromTree(tree_node* current_ptr, sortedWords* wordsInOrder)
{
  static int place = 0;
  if(current_ptr != NULL)
  {
    strcpy(wordsInOrder[place].word, current_ptr->wordData->word);
    wordsInOrder[place].freq = current_ptr->wordData->freq;

    place++;
    copyFromTree(current_ptr->left, wordsInOrder);
    copyFromTree(current_ptr->right, wordsInOrder);
  }
}

void quickSort(sortedWords* arr, int low, int high)
{
  int j;
  if(low < high)
  {
    j = partition(arr, low, high);
    quickSort(arr, low, j-1);
    quickSort(arr, low+1, high);
  }
}

int partition (sortedWords* arr, int low, int high)
{
  int pivot = low;
  low++;

  while (low <= high)
  {
    while (low <= high && arr[low].freq >= arr[pivot].freq)
    {
      //if frequency is the same then sort alphabetically
      if(arr[low].freq == arr[pivot].freq)
      {
        //if compareTo() returns 1 then swap
        if(compareTo(&arr[low], &arr[pivot]) == 1)
        {
          swap(&arr[low], &arr[pivot]);
        }
      }
      low++;
    }

    while (high >= low && arr[high].freq < arr[pivot].freq)
    {
      high--;
    }

    if (low < high)
    {
      swap(&arr[low], &arr[high]);
    }
  }
  swap(&arr[pivot], &arr[high]);

  return high;
}

void swap(sortedWords* a, sortedWords* b)
{
  sortedWords temp = *a;
  *a = *b;
  *b = temp;
}

int compareTo(sortedWords* a, sortedWords* b)
{
  //if words are not in alphabetical order then swap
  if(strcmp(a->word, b->word) > 0)
    return 1;
  else
    return -1;
}

void printSortedWords(sortedWords* wordsInOrder)
{
  for(int i=0; i<numWords; i++)
  {
    printf("%s %d\n", wordsInOrder[i].word, wordsInOrder[i].freq);
    fprintf(outfile, "%s %d\n", wordsInOrder[i].word, wordsInOrder[i].freq);
  }
}

void freeTree(tree_node* myTree)
{
  if(myTree == NULL)
  {
    return;
  }
  
  freeTree(myTree->left);
  freeTree(myTree->right);

  free(myTree->wordData->word);
  free(myTree->wordData);
  free(myTree);
}
void freeSortedWords(sortedWords* myWords)
{
  for(int i=0; i<numWords; i++)
  {
    free(myWords[i].word);
  }
  free(myWords);
}