/* COP 3502C Assignment 2
This program is written by: David McCain */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//structures
typedef struct tree
{
  int x;
  int y;
} tree;

//functions
float calculate(tree* treesList, int index, int numTrees, float sum, int flag);
void swap(tree* a, tree* b);
float getDistance(tree treesList[], int numTrees);

//main
int main(void)
{
  FILE* infile;
  FILE* outfile;
  int numTestCases;
  int numRopes;
  int numTrees;
  tree* treesList;
  float answer;
  int start = 1; //skip redundant non-zero index permutations...
  int flag = 1; //skip first return step for recursion...

  //open files
  infile = fopen("in.txt", "r");
  outfile = fopen("out.txt", "w");

  //read from file
  fscanf(infile, "%d", &numTestCases);

  //read rest of file and calculate
  for(int i=0; i<numTestCases; i++)
  {
    //read each test case
    fscanf(infile, "%d", &numRopes);
    numTrees = 2 * numRopes;

    //allocate memory
    treesList = (tree*)malloc(numTrees * sizeof(tree));

    //read each tree x and y coordinate
    for(int j=0; j<numTrees; j++)
    {
      fscanf(infile, "%d", &treesList[j].x);
      fscanf(infile, "%d", &treesList[j].y);
    }
    
    //calculate
    answer = 0;
    answer = calculate(treesList, start, numTrees, answer, flag);
    
    //output - to 3 decimal places
    fprintf(outfile, "%0.3lf\n", answer);
    printf("%0.3lf\n", answer);

    //free memory
    free(treesList);
  }

  //close files
  fclose(infile);
  fclose(outfile);

  return 0;
}

float calculate(tree* treesList, int index, int numTrees, float sum, int flag)
{
  double tempSum = 0; //used to compare later with sum parameter...

  //base case (each recursive permutation)
  //calculate each permutation's distance
  tempSum = getDistance(treesList, numTrees);

  //set sum if tempSum distance is smaller, or if there is no sum yet
  if(sum > tempSum || sum == 0)
  {
    sum = tempSum;
      //only return if not first recursion
      if(!flag)
      {
        return sum;
      }
  }

  //recursion process
  for (int i=index; i<numTrees; i++)
  {
    if(index != i)
    {
      //swap values for permutation
      swap(&treesList[index], &treesList[i]);
      //recursion
      sum = calculate(treesList, index+1, numTrees, sum, 0);
      //swap back
      swap(&treesList[index], &treesList[i]);
    }
  }

  return sum;
}

void swap(tree* a, tree* b)
{
  tree tempVar;

  tempVar = *a;
  *a = *b;
  *b = tempVar;
}

float getDistance(tree treesList[], int numTrees)
{
  double tempA = 0; //x1 - x2...
  double tempB = 0; //y1 - y2...
  double tempAnswer = 0; //square root of tempA + tempB...

  //calculate answer by adding together distances of all trees
  for(int i=0; i<numTrees; i++)
  {
    //square the difference of tree 1 and tree 2 x coordinates
    tempA = (treesList[i].x - treesList[i+1].x);
    tempA *= tempA;
    //square the difference of tree 1 and tree 2 y coordinates
    tempB = (treesList[i].y - treesList[i+1].y);
    tempB *= tempB;
    //find the square root of the 2 differences added together
    tempAnswer += sqrt(tempA + tempB);
    //increase i to move on to the next pair of trees
    i++;
  }

  //return the total distance of ropes added together
  return tempAnswer;
}