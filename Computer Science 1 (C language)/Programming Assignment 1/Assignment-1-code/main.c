#include <stdio.h>
#include <stdlib.h>
#include "leak_detector_c.h"

//global variables
FILE* infile;
FILE* outfile;

//structs
typedef struct item
{
    int itemID;
    int numParts;
} item;

typedef struct recipe
{
    int numItems;
    item* itemList;
    int totalParts;
} recipe;

//functions
char** readIngredients(int* numIngredients);
recipe* readRecipe();
recipe** readAllRecipes(int* numRecipes);
double* calculateOrder(int ingredientCount, int numSmoothies, recipe** recipeList);
void printOrder(char** ingredientNames, double* orderList, int numIngredients);
void freeIngredients(char** ingredientList, int numIngredients);
void freeRecipes(recipe** allRecipes, int numRecipes);

int main()
{
    atexit(report_mem_leak);
    
    //variables
    int numIngredients;
    int numRecipes;
    int numStores;
    char** ingredientNames;
    recipe** smoothieList;
    double* amtOfEachItem;
    int numRecipesPerStore;

    //open input file
    infile = fopen("in.txt", "r");
    if (infile == NULL) //check if input file did not open correctly...
    {
        printf("\nFile not found...\n");
        fclose(infile);
        return 0;
    }
    else
    {
        //open output file
        outfile = fopen("out.txt", "w");

        //get number of ingredients
        fscanf(infile, "%d", &numIngredients); //reads first line of input file...

        //store a list of ingredient names to double pointer
        ingredientNames = readIngredients(&numIngredients);

        //get number of recipes
        fscanf(infile, "%d", &numRecipes);

        //store a list of recipes to double pointer
        smoothieList = readAllRecipes(&numRecipes);

        //get number of stores
        fscanf(infile, "%d", &numStores);

        //read each store's sales data, calculate order, and output to file
        for(int i = 0; i < numStores; i++)
        {
          //get number of recipes per store
          numRecipesPerStore = 0; //initialize before reading from input file...
          fscanf(infile, "%d", &numRecipesPerStore);

          //get amount
          amtOfEachItem = calculateOrder(numIngredients, numRecipesPerStore, smoothieList);

          //output store number
          fprintf(outfile, "Store #%d:\n", i+1); //output to file...
          printf("Store #%d:\n", i+1); //output to console...
          //output ingredients and their amounts per store
          printOrder(ingredientNames, amtOfEachItem, numIngredients);
          fprintf(outfile, "\n"); //output to file...
          printf("\n"); //output to console...

          //free amount
          free(amtOfEachItem);
        }

        //free pointers
        freeIngredients(ingredientNames, numIngredients);
        freeRecipes(smoothieList, numRecipes);

        //close output file
        fclose(outfile);
    }

    //close input file
    fclose(infile);

    return 0;
}

char** readIngredients(int* numIngredients)
{
    //create a double pointer array of strings to store ingredient names
    char** ingredientNames = (char**)malloc(*numIngredients * sizeof(char*));

    //allocate strings to have a max length of 20 chars + endline
    for (int i = 0; i < *numIngredients; i++)
    {
        ingredientNames[i] = (char*)malloc((20 + 1) * sizeof(char));
    }

    //store ingredient names to the array of strings
    for (int i = 0; i < *numIngredients; i++)
    {
        fscanf(infile, "%s", ingredientNames[i]);
    }

    return ingredientNames;
}

recipe* readRecipe()
{
    recipe* singleRecipe;
    int numItems;

    //read number of items in recipe
    fscanf(infile, "%d", &numItems);

    //allocate memory space for recipe data
    singleRecipe = (recipe*)malloc(sizeof(recipe));
    singleRecipe->itemList = (item*)malloc(numItems * sizeof(item));

    //store number of items to recipe
    singleRecipe->numItems = numItems;

    //read and store item ID
    for (int i = 0; i < singleRecipe->numItems; i++)
    {
        fscanf(infile, "%d", &singleRecipe->itemList[i].itemID);
        fscanf(infile, "%d", &singleRecipe->itemList[i].numParts);
    }

    //read and store total amount of items
    singleRecipe->totalParts = 0;
    for (int i = 0; i < singleRecipe->numItems; i++)
    {
        singleRecipe->totalParts = singleRecipe->totalParts + singleRecipe->itemList[i].numParts;
    }

    return singleRecipe;
}

recipe** readAllRecipes(int* numRecipes)
{
    recipe** recipeList;

    //allocate memory for number of recipes
    recipeList = (recipe**)malloc(*numRecipes * sizeof(recipe*));

    //read recipes
    for (int i = 0; i < *numRecipes; i++)
    {
        recipeList[i] = readRecipe();
    }

    return recipeList;
}

double* calculateOrder(int ingredientCount, int numSmoothies, recipe** recipeList)
{
  //allocate memory for each store's ingredient quantity
  double* amountOfEachItem = (double*)calloc(ingredientCount, sizeof(double));
  //variables for containing recipeID and quantity of each recipeID per store
  int* recipeIDPerStore = (int*)malloc(numSmoothies * sizeof(int));
  int* quantityOfRecipesPerStore = (int*)malloc(numSmoothies * sizeof(int));
  //variables for calculations
  double numerator;
  double denominator;

  //read store data
  for(int i=0; i<numSmoothies; i++)
  {
    //get [recipe id] - for the store
    fscanf(infile, "%d", &recipeIDPerStore[i]);
    //get [quantity] (of recipe) - for the store
    fscanf(infile, "%d", &quantityOfRecipesPerStore[i]);

    //store amounts of ingredients
    for(int j=0; j<recipeList[recipeIDPerStore[i]]->numItems; j++)
    {
      //calculate numerators and denominators for amounts of ingredients
      numerator = 0; //initialize...
      numerator = recipeList[recipeIDPerStore[i]]->itemList[j].numParts * quantityOfRecipesPerStore[i];
      //^^^numerator = ratio of single ingredient * quantity of recipe...
      denominator = 0; //initialize...
      denominator += recipeList[recipeIDPerStore[i]]->totalParts;
      //^^^denominator = total number of all recipe ingredient ratios...

      //store amount as float value (6 decimal places)
      amountOfEachItem[recipeList[recipeIDPerStore[i]]->itemList[j].itemID] += numerator/denominator;
    }
  }

  free(recipeIDPerStore);
  free(quantityOfRecipesPerStore);

  return amountOfEachItem;
}

void printOrder(char** ingredientNames, double* orderList, int numIngredients)
{
  for(int i=0; i<numIngredients; i++)
  {
    if(orderList[i] > 0)
    {
      fprintf(outfile, "%s %0.6lf\n", ingredientNames[i], orderList[i]); //output to file...
      printf("%s %0.6lf\n", ingredientNames[i], orderList[i]); //output to console...
    }
  }
}

void freeIngredients(char** ingredientList, int numIngredients)
{
    for (int i = 0; i < numIngredients; i++)
    {
        free(ingredientList[i]);
    }
    free(ingredientList);
}

void freeRecipes(recipe** recipes, int numRecipes)
{
    for (int i = 0; i < numRecipes; i++)
    {
        free(recipes[i]->itemList); //free each item...
        free(recipes[i]); //free each recipe (contains 2 ints and an item*)...
    }
    free(recipes); //free all recipes (contains 1 recipe**)...
}