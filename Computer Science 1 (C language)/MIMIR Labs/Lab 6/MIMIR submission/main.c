#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 50
#define EMPTY 'I'

//structures
struct stack {
  char items[SIZE];
  int top;
};

//functions
//old functions
void initialize(struct stack* stackPtr);
int full(struct stack* stackPtr);
int push(struct stack* stackPtr, char value);
int empty(struct stack* stackPtr);
char pop(struct stack* stackPtr);
char peek(struct stack* stackPtr);
void print_stack(struct stack* stackPtr);
//new functions
int checkBalance(char exp[]); //check whether the parenthesis are valid
int priority(char ch); //returns the priority of a given operator
int isOperator(char ch); //check whether it is an operator
char* infixToPostfix(char infix[]); //convert a given infix into postfix
int isParentheses(char ch1); //check is it a parenthesis or not

//main
int main() {
  int ch;
  int valid;
  char exp[SIZE];
  char c;

  //get expression
  printf("Enter Expression: ");
  scanf("%[^\n]s", exp);

  //show expression
  printf("Your input expression: %s\n\n", exp);

  //determine if expression is valid
  printf("Checking balance...\n");
  valid = checkBalance(exp);

  //if expression is valid
  if(valid)
  {
    char* postfix = infixToPostfix(exp);
    printf("The postfix is: %s", postfix);
    free(postfix);
  }

  return 0;
}

//initialize top of stack
void initialize(struct stack* stackPtr) {
  stackPtr->top = -1;
}

//return true/1 if push is successfull
int push(struct stack* stackPtr, char value) {
  //check if stack is full
  if (full(stackPtr)) return 0;

  //add value to the top of the stack
  stackPtr->items[stackPtr->top+1] = value;

  //increment top of stack
  (stackPtr->top)++;

  return 1;
}

//return true/1 if stack is full
int full(struct stack* stackPtr) {
  return (stackPtr->top == SIZE - 1);
}

//return true/1 if stack is empty
int empty(struct stack* stackPtr) {
  return (stackPtr->top == -1);
}

//remove the top of stack and return the value removed
char pop(struct stack* stackPtr) {
  char retval;

  //check if stack is empty
  if (empty(stackPtr)) return EMPTY;

  //get pop value to return
  retval = stackPtr->items[stackPtr->top];

  //decrement top of stack
  (stackPtr->top)--;

  return retval;
}

//return top of stack
char peek(struct stack* stackPtr) {
  //check if stack is empty
  if (empty(stackPtr)) return EMPTY;
  return stackPtr->items[stackPtr->top];
}

//output stack contents to console
void display(struct stack* stackPtr) {
  printf("\nPrinting the Current stack...");

  for(int i=0; i<=stackPtr->top; i++)
    printf("%d ", stackPtr->items[i]);
}

int checkBalance(char exp[]) {
  int valid = 1;
  struct stack validator;

  //initialize top of stack
  initialize(&validator);

  //iterate through stack to check parenthesis
  for(int i=0; exp[i] != '\0'; i++)
  {
    //check if exp[i] == (, [, {
    if(exp[i] == '(' || exp[i] == '[' || exp[i] == '{')
    {
      //copy parenthesis value to validator stack
      push(&validator, exp[i]);
    }
    else if(exp[i] == ')')
    {
      //get last stored parenthesis in validator stack
      char a = pop(&validator);
      //check if last stored parenthesis in validator stack is incorrect
      if(a != '(' || a == EMPTY)
      {
        valid = 0;
        printf("INVALID for )!!!\n");
        return valid;
      }
    }
    else if(exp[i] == ']')
    {
      char a = pop(&validator);
      if(a != '[' || a == EMPTY)
      {
        valid = 0;
        printf("INVALID for ]!!!\n");
        return valid;
      }
    }
    else if(exp[i] == '}')
    {
      char a = pop(&validator);
      if(a != '{' || a == EMPTY)
      {
        valid = 0;
        printf("INVALID for }!!!\n");
        return valid;
      }
    }
  }

  //check if number of chars is incorrect
  if(pop(&validator) != EMPTY)
  {
    valid = 0;
    printf("invalid - extra chars\n");
  }

  //output message if case is valid
  if(valid)
  {
    printf("VALID\n");
  }

  return valid;
}

//return priority based upon order of operations
int priority(char ch) {
  int prio;

  if(ch == '(' || ch == '[' || ch == '{')
  {
    prio = 0;
  }
  if(ch == '+' || ch == '-')
  {
    prio = 1;
  }
  if(ch == '*' || ch == '/' || ch == '%')
  {
    prio = 2;
  }
  if(ch == '^')
  {
    prio = 3;
  }

  return prio;
}

//return true/1 if input is operator
int isOperator(char ch) {
  if(ch == '+' || ch == '-' || ch == '*' ||
  ch == '/' || ch == '%' || ch == '^') return 1;
  return 0;
}

char* infixToPostfix(char infix[]) {
  struct stack operators;
  char* postfix;
  int count = 0;
  int tempIter = 0;

  //initialize operators stack
  initialize(&operators);

  //allocate memory for postfix stack
  postfix = (char*)malloc((strlen(infix)+1) * sizeof(char));
  
  for(int i=0; i<strlen(infix); i++)
  {
    if(isdigit(infix[i]))
    {
      while(isdigit(infix[i]))
      {
        postfix[count] = infix[i];
        i++;
        count++;
      }
      i--;
      postfix[count] = ' ';
      count++;
    }
    else if(isOperator(infix[i]))
    {
      if(empty(&operators))
      {
        push(&operators, infix[i]);
      }
      else if(priority(infix[i]) > priority(peek(&operators)))
      {
        push(&operators, infix[i]);
      }
      else
      {
        while(!empty(&operators) && priority(infix[i]) <= priority(peek(&operators)) && !isParentheses(peek(&operators)))
        {
          postfix[count] = pop(&operators);
          count++;
          postfix[count] = ' ';
          count++;
        }
        push(&operators, infix[i]);
      }
    }
    else if(infix[i] == '(' || infix[i] == ')')
    {
      if(infix[i] == '(')
      {
        push(&operators, infix[i]);
      }
      else
      {
        while(peek(&operators) != '(')
        {
          postfix[count] = pop(&operators);
          count++;
          postfix[count] = ' ';
          count++;
        }
        pop(&operators);
      }
    }
  }

  //move remaining operators to postfix (except parenthesis)
  for(int i=operators.top; i>=0; i--)
  {
    if(isOperator(peek(&operators)))
    {
      postfix[count] = pop(&operators);
      count++;
      postfix[count] = ' ';
      count++;
    }
    else
    {
      tempIter++;
      operators.top--;
    }
  }
  operators.top += tempIter;

  return postfix;
}

//return true/1 if input is parenthesis/bracket/brace
int isParentheses(char ch1) {
  if(ch1 == '{' || ch1 == '}' || ch1 == '[' ||
  ch1 == ']' || ch1 == '(' || ch1 == ')') return 1;
  return 0;
}