#include <stdio.h>
#include <stdlib.h>
#include "leak_detector_c.h"

//structures
struct node
{
  int data;
  struct node* next;
};

//functions
struct node* insert(struct node* list,int d);
struct node* del(struct node* list,int d);
void print(struct node* list);
void freeList(struct node* list);
void copy(struct node* q, struct node** s);

//main
int main(void)
{
  atexit(report_mem_leak);

  int number = 0;
  int choice = 0;
  struct node* pList = NULL;
  struct node* nList = NULL;

  //menu
  while(choice!= 4)
  {
    //get menu choice
    printf("\nDo you want to (1)insert, (2)delete, (3)copy, (4)quit.\n");
    scanf("%d", &choice);
    printf("Your choice is %d\n", choice);

    //process menu choice
    if (choice == 1)
    {
      //insert data
      printf("Enter the value to insert\n");
      scanf("%d", &number);
      pList = insert(pList, number);
      printf("Items in linked list: ");
      print(pList);
    }
    else if (choice == 2)
    {
      //delete data
      printf("Enter the value to delete.\n");
      scanf("%d", &number);
      pList = del(pList, number);
      printf("Items in linked list: ");
      print(pList);
    }
    else if (choice == 3)
    {
      //copy linked list
      if (nList)
      {
        freeList(nList);
      }
      copy(pList, &nList); //pass by reference of nList...
      printf("Items in NEW linked list: ");
      print(nList);
    }
    else
    {
      break;
    }
  }

  //free memory
  freeList(nList);
  freeList(pList);

  //output end message
  printf("\nBye..\n");
  return 0;
}


// Copies a linked list into another
void copy(struct node* source, struct node** dest)
{
  if (source != NULL)
  {
    *dest =  (struct node*)malloc(sizeof(struct node));

    (*dest)->data = source -> data; //need double dereference to access nList's pointed data
    (*dest)->next = NULL ;

    copy(source->next, &((*dest)->next)); //call recursively with source next and reference of nList-> next
  }
}

// Recursively inserts item into the LL pointed to by list in order.
struct node* insert(struct node* list, int item)
{
  // Node is at front, insert and return.
  if (list == NULL || item <= list->data)
  {
    //create new node to store item/data
    struct node* pNew = (struct node*)malloc(sizeof(struct node));
    pNew->data = item;
    pNew->next = list;
    return pNew;
  }

  // Recursively insert and return the front of the list.
  list->next = insert(list->next, item);
  return list;
}

// Recursively deletes the first node storing item in the list pointed to
// by list. If no such node exists, no changes are made. a pointer to the front
// of the resulting list is returned.
struct node* del(struct node* list, int item)
{
  // Simple case.
  if (list == NULL)
  {
    return NULL;
  }

  // Free this node and return a pointer to the rest of the list.
  if (item == list->data)
  {
    struct node* rest = list->next;
    free(list);
    return rest;
  }

  // Recursively delete and return the front of the list.
  list->next = del(list->next, item);
  return list;
}

void print(struct node* list)
{
  while(list != NULL)
  {
    printf("->%d", list->data);
    list = list->next;
  }
}

// Frees each node in the LL pointed to by list.
void freeList(struct node* list)
{
  struct node* temp = list;
  while(list != NULL)
  {
    temp = list;
    list = list->next;
    free(temp);
  }
}