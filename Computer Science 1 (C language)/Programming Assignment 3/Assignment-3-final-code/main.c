/* COP 3502C Assignment 3
This program is written by: David McCain */

#include <stdio.h>
#include <stdlib.h>
#include "leak_detector_c.h"

//global variables
#define EMPTY -1
FILE* infile;
FILE* outfile;

//structures
typedef struct monster
{
  int sequenceNum;
  struct monster* next;
} monster;

typedef struct queue
{
  monster* monsters;
  int front;
  int back;
  int mCount; //number of monsters...
  int skipVal; //number to skip over for deletion...
  int mLeft; //number of monsters to be left...
  int lineNum; //line id/number...
  int queueSize; //maximum number of monsters
} queue;

//functions
monster* createMonster(int sequence);
void initQueue(queue* q, int queueSize);
void createReverseCircle(queue *q);
void enqueue(queue* qPtr, int val);
void dequeue(queue* q);
int peek(queue* q);
int isEmpty(queue* q);
void display(queue* q);
void orderByLine(queue** qPtr, int numQueues, int iter);
void swapQueues(queue* q1, queue* q2);
void rearrangeCircle(queue* q);
void swapElements(int* e1, int* e2);
void phase1(queue** qPtr, int numQueues);
void phase1Execution(queue* qPtr);
void phase2(queue** qPtr, int numQueues);
void phase2Execution(queue* qPtr);
void freeQueue(queue* q);
void freeAllQueues(queue** q, int numQueues);

//main
int main(void)
{
  //memory leak detection
  atexit(report_mem_leak);

  //variables
  int numQueues;
  queue** queuesList;
  int lineNum;
  int numElements;
  int skipVal;
  int numEleLeft;

  //open input file
  infile = fopen("in.txt", "r");
  if (infile == NULL)
  {
      printf("\nFile not found...\n");
      fclose(infile);
      return 0;
  }
  else
  {
      //open output file
      outfile = fopen("out.txt", "w");

      //get number of Lines
      fscanf(infile, "%d", &numQueues);

      //allocate memory for list of queues
      queuesList = (queue**)malloc(numQueues * sizeof(queue*));

      /* READ AND PROCESS QUEUE DATA FROM INPUT FILE */
      for(int i=0; i<numQueues; i++)
      {
        //allocate memory for each queue
        queuesList[i] = (queue*)malloc(sizeof(queue));

        //get line number
        fscanf(infile, "%d", &lineNum);

        //get number of elements
        fscanf(infile, "%d", &numElements);
        //initialize queue elements
        initQueue(queuesList[i], numElements);
        //populate queue elements (in descending order)
        createReverseCircle(queuesList[i]);

        //get number for traversing/skipping through queue
        fscanf(infile, "%d", &skipVal);

        //get number of elements to be left
        fscanf(infile, "%d", &numEleLeft);

        //store (temporary) line data to (permanent) queue
        queuesList[i]->lineNum = lineNum;
        queuesList[i]->mCount = numElements;
        queuesList[i]->skipVal = skipVal;
        queuesList[i]->mLeft = numEleLeft;
      }

      //order queues list by line number (in ascending order)
      orderByLine(queuesList, numQueues, 0); //iteration 0 first...

      //display queues
      printf("Initial nonempty lists status\n");
      fprintf(outfile, "Initial nonempty lists status\n");
      for(int i=0; i<numQueues; i++)
      {
        display(queuesList[i]);
      }

      //reverse elements in queue
      for(int i=0; i<numQueues; i++)
      {
        rearrangeCircle(queuesList[i]);
      }

      //display ordered queues
      printf("\nAfter ordering nonempty lists status\n");
      fprintf(outfile, "\nAfter ordering nonempty lists status\n");
      for(int i=0; i<numQueues; i++)
      {
        display(queuesList[i]);
      }

      /* PHASE 1 */
      phase1(queuesList, numQueues);

      /* PHASE 2 */
      phase2(queuesList, numQueues);

      //free pointers
      freeAllQueues(queuesList, numQueues);

      //close output file
      fclose(outfile);
  }

    //close input file
    fclose(infile);

    return 0;
}

monster* createMonster(int sequence)
{
  //create monster and store data
  monster* temp = (monster*)malloc(sizeof(monster));
  temp->sequenceNum = sequence;

  //set pointers
  temp->next = temp;

  //return created monster
  return temp;
}

void initQueue(queue* q, int queueSize)
{
  //allocate memory
  q->monsters = (monster*)malloc(sizeof(monster)*queueSize);

  //initialize front index, back index, and number of elements to zero
  q->front = 0;
  q->back = 0;
  q->mCount = 0;

  //set initial queueSize (passed in as parameter to avoid global var)
  q->queueSize = queueSize;
}

void createReverseCircle(queue *q)
{
  //create and store new monsters
  for(int i=0; i<q->queueSize; i++)
  {
    //create new monster
    monster* tempMonster = createMonster(q->queueSize-i);

    //enqueue new monster
    enqueue(q, tempMonster->sequenceNum);
    q->monsters[i] = *tempMonster;

    //free new monster
    free(tempMonster);
  }
  //set new monster next pointers
  for(int i=0; i<q->mCount; i++)
  {
    q->monsters[i].next = &q->monsters[(i+1)%q->mCount];
  }
}

void enqueue(queue* qPtr, int val)
{
  int i;

  //if queue is not full
  if (qPtr->mCount != qPtr->queueSize)
  {
    //enqueue the new element, using mod in case of wraparound
    qPtr->monsters[(qPtr->front+qPtr->mCount)%qPtr->queueSize].sequenceNum = val;
    (qPtr->mCount)++;
  }
  //if queue is full
  else
  {
    //allocate (more) memory, to double the size of queue
    qPtr->monsters = realloc(qPtr->monsters, (qPtr->queueSize)*2*sizeof(int));

    //move elements from before the front of queue to new correct locations
    for (i=0; i<=qPtr->front-1; i++)
    {
      qPtr->monsters[i+qPtr->queueSize] = qPtr->monsters[i];
      /*  ^^^opposite of wraparound example: in a queue of size 10
          (before being doubled), element 0 will be copied to element
          11. continue process until front is reached...
      */
    }
    //enqueue the new element
    qPtr->monsters[i+qPtr->queueSize].sequenceNum = val;

    //size of queue is doubled
    (qPtr->queueSize) *= 2;

    //increase number of elements by 1
    (qPtr->mCount)++;
  }
}

void dequeue(queue* q)
{
  //if queue is empty
  if (q->mCount == 0)
  {
    return;
  }
  //if queue is not empty
  else
  {
    //set the front element to empty
    q->monsters[q->front].sequenceNum = EMPTY;

    //increase front of queue, using mod in case of wraparound
    do
    {
      q->front = (q->front + 1) % q->queueSize;
      q->back = (q->front - 1) % q->queueSize;
    } while(q->front == EMPTY);

    //update number of elements in queue
    (q->mCount)--;
  }
}

int peek(queue* q)
{
  //return front monster
  int retval = q->monsters[q->front].sequenceNum;
  return retval;
}

int isEmpty(queue* q)
{
  //return boolean value 1 if queue is empty
  return (q->mCount == 0);
}

void display(queue* qPtr)
{
  //if queue is empty
  if(isEmpty(qPtr))
  {
    printf("\nQueue is empty...\n");
    fprintf(outfile, "\nQueue is empty...\n");
  }
  //if queue is not empty
  else
  {
    //output line number
    printf("%d ", qPtr->lineNum);
    fprintf(outfile, "%d ", qPtr->lineNum);

    //output all monsters in each line (except last monster)
    for(int i=0; i<qPtr->mCount-1; i++)
    {
      //display front data
      printf("%d ", peek(qPtr));
      fprintf(outfile, "%d ", peek(qPtr));
      //increment front
      qPtr->front++;
    }
    //output last monster
    printf("%d", peek(qPtr));
    fprintf(outfile, "%d", peek(qPtr));
    //increment front
    qPtr->front++;
    qPtr->front %= qPtr->queueSize;

    printf("\n");
    fprintf(outfile, "\n");
  }
}

void orderByLine(queue** qPtr, int numQueues, int iter)
{
  //order queues list by line number (in ascending order)
  for(int i=0; i<numQueues-1; i++)
  {
    //compare line numbers before changing order
    if(qPtr[i]->lineNum > qPtr[i+1]->lineNum)
    {
      //swap and recursion
      swapQueues(qPtr[i], qPtr[i+1]);
      orderByLine(qPtr, numQueues, iter++);
    }
  }
  //NOTE: uses recursion instead of a double loop in the code above
}

void swapQueues(queue* q1, queue* q2)
{
  queue tempQ = *q1;

  *q1 = *q2;
  *q2 = tempQ;
}

void rearrangeCircle(queue* q)
{
  //order queue elements (in ascending order)
  for(int i=0; i<q->mCount-1; i++)
  {
    for(int j=0; j<q->mCount-1; j++)
    {
      //compare elements before changing order
      if(q->monsters[j].sequenceNum > q->monsters[j+1].sequenceNum)
      {
        //swap and recursion
        swapElements(&q->monsters[j].sequenceNum, &q->monsters[j+1].sequenceNum);
        rearrangeCircle(q);
      }
    }
  }
  //NOTE: using recursion within double loop in code above
}

void swapElements(int* e1, int* e2)
{
  int tempE = *e1;

  *e1 = *e2;
  *e2 = tempE;
}

void phase1(queue** qPtr, int numQueues)
{
  //output phase 1 message
  printf("\nPhase1 execution\n");
  fprintf(outfile, "\nPhase1 execution\n");

  //execute phase 1
  for(int i=0; i<numQueues; i++)
  {
    printf("\nLine# %d\n", qPtr[i]->lineNum);
    fprintf(outfile, "\nLine# %d\n", qPtr[i]->lineNum);
    phase1Execution(qPtr[i]);

    //reset front of each queue to first nonempty value
    qPtr[i]->front = 0;
    qPtr[i]->back = (qPtr[i]->front - 1) + qPtr[i]->queueSize;
  }
}

void phase1Execution(queue* qPtr)
{
  //find element to delete
  for(int i=0; qPtr->mCount > qPtr->mLeft; i++)
  {
    //set front to increase by skip value
    for(int j=0; j<qPtr->skipVal-1; j++)
    {
      //increase front value if element has already been deleted
      while(qPtr->monsters[qPtr->front].sequenceNum == EMPTY)
      {
        qPtr->front++;
        //new front element needs to be within bounds
        qPtr->front %= qPtr->queueSize;
      }

      //iterate
      qPtr->front++;
      //new front element needs to be within bounds
      qPtr->front %= qPtr->queueSize;

      //check again to make sure that new front element is valid
      while(qPtr->monsters[qPtr->front].sequenceNum == EMPTY)
      {
        qPtr->front++;
        //new front element needs to be within bounds
        qPtr->front %= qPtr->queueSize;
      }
    }

    //output execution message
    printf("Monster# %d executed\n", peek(qPtr));
    fprintf(outfile, "Monster# %d executed\n", peek(qPtr));

    //dequeue(remove) element
    dequeue(qPtr);
  }
}

void phase2(queue** qPtr, int numQueues)
{
  int totalEle = 0;
  int tempHighest = 0;

  //get total number of elements
  for(int i=0; i<numQueues; i++)
  {
    totalEle += qPtr[i]->mCount;
  }

  //output phase 2 message
  printf("\nPhase2 execution\n");
  fprintf(outfile, "\nPhase2 execution\n");

  //make sure front of all queues are not empty
  for(int i=0; i<numQueues; i++)
  {
    while(qPtr[i]->monsters[qPtr[i]->front].sequenceNum == EMPTY)
    {
      qPtr[i]->front++;
      qPtr[i]->back = (qPtr[i]->front-1 + qPtr[i]->queueSize) % qPtr[i]->queueSize;
    }
  }

  //execute phase 2
  do
  {
    //reset tempHighest
    tempHighest = EMPTY;
    //find highest value in front of all queues
    for(int i=0; i<numQueues; i++)
    {
      //make sure that queue is not empty
      if(qPtr[i]->mCount != 0 && qPtr[i]->front != qPtr[i]->back)
      {
        //check if tempHighest has been set yet
        if(tempHighest == EMPTY)
        {
          tempHighest = i;
        }
        //check if current front of queue is higher
        else if(qPtr[i]->front > qPtr[tempHighest]->front)
        {
          tempHighest = i;
        }
      }
    }    phase2Execution(qPtr[tempHighest]);
    totalEle--;
  } while(totalEle > 1);

  for(int i=0; i<numQueues; i++)
  {
    if(!isEmpty(qPtr[i]))
    {
      printf("\nMonster %d from line %d will survive", qPtr[i]->monsters[qPtr[i]->front].sequenceNum, qPtr[i]->lineNum);
      fprintf(outfile, "\nMonster %d from line %d will survive", qPtr[i]->monsters[qPtr[i]->front].sequenceNum, qPtr[i]->lineNum);
    }
  }
}

void phase2Execution(queue* qPtr)
{
  //output phase 2 message
  printf("Executed Monster %d from line %d\n", qPtr->monsters[qPtr->front].sequenceNum, qPtr->lineNum);
  fprintf(outfile, "Executed Monster %d from line %d\n", qPtr->monsters[qPtr->front].sequenceNum, qPtr->lineNum);
  
  //delete monster
  dequeue(qPtr);

  //move queue front pointer
  while(qPtr->monsters[qPtr->front].sequenceNum == EMPTY)
  {
    if(qPtr->front == qPtr->back)
    {
      qPtr->front = 0;
      qPtr->back = 0;
    }
    qPtr->front++;
  }
}

void freeQueue(queue* q)
{
  //free single queue
  free(q->monsters); //free each monster...
  free(q); //free each queue...
}

void freeAllQueues(queue** q, int numQueues)
{
  //free all queues
  for (int i = 0; i < numQueues; i++)
  {
      freeQueue(q[i]); //free single queue...
  }
  free(q); //free all queues...
}