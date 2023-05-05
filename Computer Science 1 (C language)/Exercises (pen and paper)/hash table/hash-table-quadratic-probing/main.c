/*  Program: Hash Table implementation using Quadratic Probing
    Written By: David McCain
    Date: 19 November 2021
    
    NOTE: need to finish the printTableToFile() function. This
    will print the hash table data (created from the input file)
    to an output file determined by the user.
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

//global variables
#define MAX_SIZE 29
#define TABLE_SIZE 59999
FILE *ifp;
FILE *ofp;

//structures
typedef struct htable
{
  char entries[TABLE_SIZE][MAX_SIZE+1];
} htable;

//functions
void initTable(htable* h);
int hashvalue(char word[]);
void insertTable(htable* h, char word[]);
int searchTable(htable* h, char word[]);
void deleteTable(htable* h, char word[]);
int isCharInStrValid(char* temp);
void printTableToFile(FILE* ofp, htable* mytable, int numwords);

//main
int main(void)
{
  char filename[MAX_SIZE+1];
  char temp[MAX_SIZE+1];
  int numwords;
  htable mytable;
  int ans;

  //get input file name
  printf("What is the name of the dictionary file?\n");
  scanf("%s", filename);
  //open input file
  ifp = fopen(filename, "r+");

  //get number of words
  fscanf(ifp, "%d", &numwords);

  //initialize table
  initTable(&mytable);
  //read words from file and store in table
  for (int i=0; i<numwords; i++)
  {
    fscanf(ifp, "%s", temp);
    insertTable(&mytable, temp);
  }

  //menu
  do
  {
    printf("\nMENU:\n1) search word\n2) add word\n3) delete a word\n4) save/quit\n");
    scanf("%d", &ans);
    printf("\n");

    switch(ans)
    {
      case 1: //search for a word...
        printf("What word are you looking for?\n");
        scanf("%s", temp);
        if (searchTable(&mytable, temp))
          printf("%s was found.\n", temp);
        else
          printf("%s was NOT found.\n", temp);
        break;
      case 2: //add a word
        printf("What word do you want to add?\n");
        scanf("%s", temp);
        if (searchTable(&mytable, temp))
          printf("%s was ALREADY in the table\n", temp);
        else
          insertTable(&mytable, temp);
          numwords++;
        break;
      case 3: //delete a word
        printf("What word do you want to delete?\n");
        scanf("%s", temp);
        deleteTable(&mytable, temp);
        numwords--;
        break;
      case 4: //quit program - choose to save
        do
        {
          //determine if user wants to save
          printf("would you like to save? Y/N\n");
          scanf("%s", temp);
          //check if valid input
          if(!isCharInStrValid(temp))
            printf("\nInvalid choice\n\n");
        } while(!isCharInStrValid(temp));
        if(temp[0] == 'y' || temp[0] == 'Y')
        {
          //get output file
          printf("\nEnter the name of the file you would like to save to: ");
          scanf("%s", filename);
          //open output file
          ofp = fopen(filename, "w+");
          //output table to output file
          printTableToFile(ofp, &mytable, numwords);
          //close output file
          fclose(ofp);
        }
        else
        {
          printf("\nAre you sure that you want to quit without saving?\n");
          printf("Y = quit | N = return to menu\nY/N: ");
          scanf("%s", temp);
          if(temp[0] == 'y' || temp[0] == 'Y')
            continue;
          else
            ans = 1;
        }
        break;
      default:
        printf("Invalid choice...\n\n");
    }
  } while (ans != 4);

  //close input file
  fclose(ifp);

  return 0;
}

void initTable(htable* h)
{
  for (int i=0; i<TABLE_SIZE; i++)
    strcpy(h->entries[i], "");
}

int hashvalue(char word[])
{
  int sum=0;

  for (int i=0; i<strlen(word); i++)
    sum = (128*sum + (int)(word[i]))%TABLE_SIZE;
  
  return sum;
}

void insertTable(htable* h, char word[])
{
  int hashval = hashvalue(word);
  int i = 1; //start with 1^2...

  while (strcmp(h->entries[hashval], "") != 0)
  {
    hashval = (hashval+i)%TABLE_SIZE; //hashval+i instead of hashval+1...
    i *= 2; //i^2 becomes (i+1)^2...
  }

  strcpy(h->entries[hashval], word);
}

int searchTable(htable* h, char word[])
{
  int hashval = hashvalue(word);
  int i = 1; //start with 1^2...

  while (strcmp(h->entries[hashval], "") != 0 &&
  strcmp(h->entries[hashval], word) != 0)
  {
    hashval = (hashval+i)%TABLE_SIZE; //hashval+i instead of hashval+1...
    i *= 2; //i^2 becomes (i+1)^2...
  }

  if (strcmp(h->entries[hashval], word) == 0)
    return 1;

  return 0;
}

void deleteTable(htable* h, char word[])
{
  int hashval = hashvalue(word);
  int i = 1; //start with 1^2...

  while (strcmp(h->entries[hashval], "") != 0 &&
  strcmp(h->entries[hashval], word) != 0)
  {
    hashval = (hashval+i)%TABLE_SIZE; //hashval+i instead of hashval+1...
    i*= 2; //i^2 becomes (i+1)^2...
  }
  if (strcmp(h->entries[hashval], word) == 0)
    strcpy(h->entries[hashval],"");
}

int isCharInStrValid(char* temp)
{
  if(temp[0] != 'y' || temp[0] != 'Y' || temp[0] != 'n' || temp[0] != 'N')
    return 1;
  else
    return 0;
}

void printTableToFile(FILE* ofp, htable* mytable, int numwords)
{
  char temp[MAX_SIZE+1];

  fprintf(ofp, "%d", numwords);
  for(int i=0; i<numwords; i++)
  {
    //print word in hash table to output file
    //strcpy(temp, mytable->entries[i]);
    //fprintf(ofp, "%s", temp);
  }
}