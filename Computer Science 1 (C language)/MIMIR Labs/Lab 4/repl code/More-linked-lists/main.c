#include <stdio.h>
#include <stdlib.h>

//structures
typedef struct node
{
  int data;
  struct node* next;
} node;

//functions
node* insert_front(node* root, int item);
void display(node* t);
node* reverse(node* head);
node* insertToPlace(node* list, int val, int place);
int getListSize(node* list);

//main
int main(void)
{
  node* main_list = NULL;
  int choice = 1; //initialize to non-zero for do-while loop...
  int place;
  int val;

  do
  {
    printf("Menu: 1. insert at front, 2. reverse list, 3. insert to place, 0. exit: ");
    scanf("%d", &choice);
    switch(choice)
    {
      case 0:
        printf("\nGOOD BYE>>>>\n");
        break;
      case 1:
        printf("Enter value: ");
        scanf("%d", &val);
        main_list = insert_front(main_list, val);
        display(main_list);
        break;
      case 2:
        printf("\nReversing list...");
        main_list = reverse(main_list);
        display(main_list);
        break;
      case 3:
        printf("Enter value: ");
        scanf("%d", &val);
        printf("Enter place: ");
        scanf("%d", &place);
        main_list = insertToPlace(main_list, val, place);
        display(main_list);
        break;
      default:
        printf("\nERROR - invalid choice\n\n");
    }
  } while(choice != 0);

  return 0;
}

node* insert_front(node* root, int item)
{
  //create new node forlinked list
  node* temp;

  //allocate memory for node
  temp = (node*)malloc(sizeof(node));

  //fill node with data
  temp->data = item;
  temp->next = NULL;

  //check if linked list is empty or not
  if(root == NULL)
  {
    root = temp;
  }
  else
  {
    temp->next = root; //set newly created node to point to existing list...
    root = temp; //set existing list to temp, where new node is at front...
  }

  return root; //return updated linked list (containing new node)...
}

void display(node* t)
{
  //output message
  printf("\nPrinting linked list...");

  //traverse through list, outputting data
  while(t != NULL)
  {
    printf("%d ", t->data);
    t = t->next;
  }
  printf("\n");
}

node* reverse(node* head)
{
  //check if list is empty or only contains 1 element
  if(head == NULL || head->next == NULL)
  {
    return head;
  }

  //create a pointer to traverse list
  node* main_list = head->next;

  //create a pointer to reverse list
  node* reversed_list = head;
  reversed_list->next = NULL;

  //iterate through list
  while(main_list != NULL)
  {
    node* temp = main_list;
    main_list = main_list->next;
    temp->next = reversed_list;
    reversed_list = temp;
  }

  return reversed_list;
}

node* insertToPlace(node* list, int val, int place)
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