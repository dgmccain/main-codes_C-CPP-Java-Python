/*
  Dareen Bashir, David McCain
  Professor Montagne
  COP 3402
  Spring 2023
*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Global vars
#define MAX_NUMBER_DIGITS 5
#define MAX_IDENTIFIER_LENGTH 11
#define INPUT_SIZE 5000

// Structs
typedef enum {
  skipsym = 1,
  identsym = 2,
  numbersym = 3,
  plussym = 4,
  minussym = 5,
  multsym = 6,
  slashsym = 7,
  oddsym = 8,
  eqsym = 9,
  neqsym = 10,
  lessym = 11,
  leqsym = 12,
  gtrsym = 13,
  geqsym = 14,
  lparentsym = 15,
  rparentsym = 16,
  commasym = 17,
  semicolonsym = 18,
  periodsym = 19,
  becomessym = 20,
  beginsym = 21,
  endsym = 22,
  ifsym = 23,
  thensym = 24,
  whilesym = 25,
  dosym = 26,
  callsym = 27,
  constsym = 28,
  varsym = 29,
  procsym = 30,
  writesym = 31,
  readsym = 32,
  elsesym = 33,
  colonsym = 34
} token_type;
typedef struct {
  char identifiers[MAX_IDENTIFIER_LENGTH];
} lexme;

// Main function
int main(int argc, char* argv[]) {
	// File input and output variables
  char c;
  FILE *infile;
  FILE *outfile;
  char *filename = argv[argc-1]; //last command line argument is stored as filename
  // Input verbatim
  char input[INPUT_SIZE];
  int inputLength = 0;
  // Input formatted
  char formattedInput[INPUT_SIZE];
  int formattedInputLength = 0;
  // Input tokenized
  int tokenizedInput[INPUT_SIZE];
  int tokenizedInputLength = 0;
  // Symbols and variables stored for lexme table
  lexme lexmeIdentifiers[INPUT_SIZE];
  int lexmeLength = 0;
  char tempStr[MAX_IDENTIFIER_LENGTH]; //used for strcpy
  int tempStrLength = 0;
  // Miscellaneous - error handling and formatting
  int shouldCheckForCommentStart = 0;
  int shouldCheckForCommentEnd = 0;
  int commentBlockStarted = 0;
  int commentBlockEnded = 1;
  int shouldSkipInputIncrement = 0;

  // Initial file checking for file exception handling
  if(argc < 2) {
    printf("Enter the filename for input: ");
    if(scanf("%s", filename) != 1)
      exit(0); // immediately exit if no file detected
  }

  // Open files
  infile = fopen(filename, "r");
  outfile = fopen("output.txt", "w");

  // Read input
  while((c = getc(infile)) != EOF) {
    // store current input being read
    input[inputLength] = c;
    inputLength++;
  }

  // Output file contents verbatim
  printf("Source Program:\n");
  fprintf(outfile, "Source Program:\n");
  for(int i=0; i<inputLength; i++) {
    printf("%c", input[i]);
    fprintf(outfile, "%c", input[i]);
  }

  // Format input
  for(int i=0; i<inputLength; i++) {
    // Only read chars, digits, and symbols
    if(input[i] == '\n' || input[i] == ' ' || input[i] == '\t') {
      continue;
    }
    // Check if input is a symbol
    if(!isdigit(input[i]) && !isalpha(input[i])) {
      switch(input[i]) {
        case '/':
          // Check if input could start a comment block
          if(!commentBlockStarted)
            shouldCheckForCommentStart = 1;
          // Check if input is ending a comment block
          if(commentBlockStarted && shouldCheckForCommentEnd) {
            commentBlockEnded = 1;
            shouldCheckForCommentEnd = 0;
            commentBlockStarted = 0;
            shouldSkipInputIncrement = 1; // do not read comments
          }
          break;
        case '*':
          // Check if input could end a comment block
          if(commentBlockStarted)
            shouldCheckForCommentEnd = 1;
          // Check if input is starting a comment block
          if(shouldCheckForCommentStart) {
            commentBlockStarted = 1;
            shouldCheckForCommentStart = 0;
            commentBlockEnded = 0;
            formattedInputLength--; // do not read comments
          }
          break;
        case '+':
          break;
        case '-':
          break;
        case '<':
          break;
        case '>':
          break;
        case '=':
          break;
        case '(':
          break;
        case ')':
          break;
        case ':':
          break;
        case ';':
          break;
        case ',':
          break;
        case '.':
          break;
        default:
          // character is invalid symbol - handle later
          break;
      }

      // Reset condition if input is not part of a comment block
      if(input[i] != '/')
        shouldCheckForCommentStart = 0;
      if(input[i] != '*')
        shouldCheckForCommentEnd = 0;
    }
    
    // store current input being read
    if(!commentBlockStarted && commentBlockEnded) {
      formattedInput[formattedInputLength] = input[i];
      if(!shouldSkipInputIncrement) {
        formattedInputLength++;
      }
    }
    shouldSkipInputIncrement = 0; // do not read comments
  }

  // Tokenize input
  for(int i=0; i<formattedInputLength; i++) {
    tempStrLength = 0; //reset tempStrLength for default case...
    switch(formattedInput[i]) {
      case '*':
        // Check for multiplication
        tokenizedInput[tokenizedInputLength] = multsym;
        tokenizedInputLength++;
        strcpy(lexmeIdentifiers[lexmeLength].identifiers, "*");
        lexmeLength++;
        continue;
      case '/':
        tokenizedInput[tokenizedInputLength] = slashsym;
        tokenizedInputLength++;
        strcpy(lexmeIdentifiers[lexmeLength].identifiers, "/");
        lexmeLength++;
        continue;
      case '+':
        //Check for addition
        tokenizedInput[tokenizedInputLength] = plussym;
        tokenizedInputLength++;
        strcpy(lexmeIdentifiers[lexmeLength].identifiers, "+");
        lexmeLength++;
        continue;
      case '-':
        tokenizedInput[tokenizedInputLength] = minussym;
        tokenizedInputLength++;
        strcpy(lexmeIdentifiers[lexmeLength].identifiers, "-");
        lexmeLength++;
        continue;
      case '<':
        // Check for not equals
        if(formattedInput[i+1] == '>') {
          tokenizedInput[tokenizedInputLength] = neqsym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "<>");
          lexmeLength++;
          i++;
        }
        // Check for less than or equal to
        else if(formattedInput[i+1] == '=') {
          tokenizedInput[tokenizedInputLength] = leqsym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "<=");
          lexmeLength++;
          i++;
        }
        // Check for less than
        else {
          tokenizedInput[tokenizedInputLength] = lessym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "<");
          lexmeLength++;
        }
        continue;
      case '>':
        // Check for greater than or equal to
        if(formattedInput[i+1] == '=') {
          tokenizedInput[tokenizedInputLength] = geqsym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, ">=");
          lexmeLength++;
          i++;
        }
        // Check for greater than
        else {
          tokenizedInput[tokenizedInputLength] = gtrsym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, ">");
          lexmeLength++;
        }
        continue;
      case ':':
        // Check for becomes
        if(formattedInput[i+1] == '=') {
          tokenizedInput[tokenizedInputLength] = becomessym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, ":=");
          lexmeLength++;
          i++;
        }
        //note: no else case needed because a colon without
        //the equals sign after it will just not be added to
        //the lexme table
        continue;
      case '=':
        tokenizedInput[tokenizedInputLength] = eqsym;
        tokenizedInputLength++;
        strcpy(lexmeIdentifiers[lexmeLength].identifiers, "=");
        lexmeLength++;
        continue;
      case ',':
        tokenizedInput[tokenizedInputLength] = commasym;
        tokenizedInputLength++;
        strcpy(lexmeIdentifiers[lexmeLength].identifiers, ",");
        lexmeLength++;
        continue;
      case '(':
        tokenizedInput[tokenizedInputLength] = lparentsym;
        tokenizedInputLength++;
        strcpy(lexmeIdentifiers[lexmeLength].identifiers, "(");
        lexmeLength++;
        continue;
      case ')':
        tokenizedInput[tokenizedInputLength] = rparentsym;
        tokenizedInputLength++;
        strcpy(lexmeIdentifiers[lexmeLength].identifiers, ")");
        lexmeLength++;
        continue;
      case ';':
        tokenizedInput[tokenizedInputLength] = semicolonsym;
        tokenizedInputLength++;
        strcpy(lexmeIdentifiers[lexmeLength].identifiers, ";");
        lexmeLength++;
        continue;
      case '.':
        tokenizedInput[tokenizedInputLength] = periodsym;
        tokenizedInputLength++;
        strcpy(lexmeIdentifiers[lexmeLength].identifiers, ".");
        lexmeLength++;
        continue;
      case 'b':
        // Check for begin
        if((formattedInput[i+1] == 'e') && (formattedInput[i+2] == 'g') && (formattedInput[i+3] == 'i') && (formattedInput[i+4] == 'n')) {
          tokenizedInput[tokenizedInputLength] = beginsym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "begin");
          lexmeLength++;
          i += 4;
          continue;
        }
      case 'e':
        // Check for end
        if((formattedInput[i+1] == 'n') && (formattedInput[i+2] == 'd')) {
          tokenizedInput[tokenizedInputLength] = endsym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "end");
          lexmeLength++;
          i += 2;
          continue;
        }
        // Check for else
        else if((formattedInput[i+1] == 'l') && (formattedInput[i+2] == 's') && (formattedInput[i+3] == 'e')) {
          tokenizedInput[tokenizedInputLength] = elsesym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "else");
          lexmeLength++;
          i += 3;
          continue;
        }
      case 'i':
        // Check for if
        if(formattedInput[i+1] == 'f') {
          tokenizedInput[tokenizedInputLength] = ifsym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "if");
          lexmeLength++;
          i++;
          continue;
        }
      case 't':
        // Check for then
        if((formattedInput[i+1] == 'h') && (formattedInput[i+2] == 'e') && (formattedInput[i+3] == 'n')) {
          tokenizedInput[tokenizedInputLength] = thensym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "then");
          lexmeLength++;
          i += 3;
          continue;
        }
      case 'd':
        // Check for do
        if(formattedInput[i+1] == 'o') {
          tokenizedInput[tokenizedInputLength] = dosym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "do");
          lexmeLength++;
          i++;
          continue;
        }
      case 'r':
        // Check for read
        if ((formattedInput[i+1] == 'e') && (formattedInput[i+2] == 'a') && (formattedInput[i+3] == 'd')) {
          tokenizedInput[tokenizedInputLength] = readsym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "read");
          lexmeLength++;
          i += 3;
          continue;
        }
      case 'w':
        // Check for while
        if((formattedInput[i+1] == 'h') && (formattedInput[i+2] == 'i') && (formattedInput[i+3] == 'l') && (formattedInput[i+4] == 'e')) {
          tokenizedInput[tokenizedInputLength] = whilesym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "while");
          lexmeLength++;
          i += 4;
          continue;
        }
        // Check for write
        else if((formattedInput[i+1] == 'r') && (formattedInput[i+2] == 'i') && (formattedInput[i+3] == 't') && (formattedInput[i+4] == 'e')) {
          tokenizedInput[tokenizedInputLength] = writesym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "write");
          lexmeLength++;
          i += 4;
          continue;
        }
      case 'c':
        // Check for call
        if((formattedInput[i+1] == 'a') && (formattedInput[i+2] == 'l') && (formattedInput[i+3] == 'l')) {
          tokenizedInput[tokenizedInputLength] = callsym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "call");
          lexmeLength++;
          i += 3;
          continue;
        }
        // Check for const
        else if((formattedInput[i+1] == 'o') && (formattedInput[i+2] == 'n') && (formattedInput[i+3] == 's') && (formattedInput[i+4] == 't')) {
          tokenizedInput[tokenizedInputLength] = constsym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "const");
          lexmeLength++;
          i += 4;
          continue;
        }
      case 'v':
        // Check for var
        if((formattedInput[i+1] == 'a') && (formattedInput[i+2] == 'r')) {
          tokenizedInput[tokenizedInputLength] = varsym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "var");
          lexmeLength++;
          i += 2;
          continue;
        }
      case 'p':
        // Check for procedure
        if((formattedInput[i+1] == 'r') && (formattedInput[i+2] == 'o') && (formattedInput[i+3] == 'c') && (formattedInput[i+4] == 'e') && (formattedInput[i+5] == 'd') && (formattedInput[i+6] == 'u') && (formattedInput[i+7] == 'r') && (formattedInput[i+8] == 'e')) {
          tokenizedInput[tokenizedInputLength] = procsym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "procedure");
          lexmeLength++;
          i += 8;
          continue;
        }
      case 'o':
        // Check for odd
        if((formattedInput[i+1] == 'd') && (formattedInput[i+2] == 'd')) {
          tokenizedInput[tokenizedInputLength] = oddsym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "odd");
          lexmeLength++;
          i += 2;
          continue;
        }
      default:
        // Reset tempStr
        memset(tempStr,0,sizeof(tempStr));
        // Identifier case
        if(isalpha(formattedInput[i])) {
          while(isalpha(formattedInput[i]) || isdigit(formattedInput[i])) {
            strncpy(&tempStr[tempStrLength], &formattedInput[i], 1);
            tempStrLength++;
            // Check if identifier length is within bounds
            if(tempStrLength > MAX_IDENTIFIER_LENGTH) {
              // Output exit message
              printf("ERROR - IDENTIFIER TOO LONG...\n");
              fprintf(outfile, "ERROR - IDENTIFIER TOO LONG...\n");
              exit(0);
            }
            i++;
          }
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, tempStr);
          lexmeLength++;
          tokenizedInput[tokenizedInputLength] = identsym;
          tokenizedInputLength++; 
          i--;
        }
        // Integer case
        else if(isdigit(formattedInput[i])) {
          // Check if const or var are still running - that semicolon
          // has not yet been entered after dealing with identifiers
          while(isdigit(formattedInput[i])) {
            strncpy(&tempStr[tempStrLength], &formattedInput[i], 1);
            tempStrLength++;
            // Check if number of digits are within bounds
            if(tempStrLength > MAX_NUMBER_DIGITS) {
              // Output exit message
              printf("ERROR - TOO MANY DIGITS...\n");
              fprintf(outfile, "ERROR - TOO MANY DIGITS...\n");
              exit(0);
            }
            i++;
          }
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, tempStr);
          lexmeLength++;
          tokenizedInput[tokenizedInputLength] = numbersym;
          tokenizedInputLength++; 
          i--;
        }
        // Invalid Symbol - default case
        else if(!isalpha(formattedInput[i]) && !isdigit(formattedInput[i])) {
        // Output exit message
          printf("ERROR - INVALID SYMBOL %c...\n", formattedInput[i]);
          fprintf(outfile, "ERROR - INVALID SYMBOL %c...\n", formattedInput[i]);
          exit(0);
        }
    }
  }

  // Output Lexeme Table
  printf("\n\nLexeme Table:\n");
  fprintf(outfile, "\n\nLexeme Table:\n");
  printf("Lexeme      Token_type\n");
  fprintf(outfile, "Lexeme      Token_type\n");
  for(int i=0; i<lexmeLength; i++) {
    printf("%-11s %d\n", lexmeIdentifiers[i].identifiers, tokenizedInput[i]);
    fprintf(outfile, "%-11s %d\n", lexmeIdentifiers[i].identifiers, tokenizedInput[i]);
  }

  // Output Lexeme List
  printf("\nLexeme List:\n");
  fprintf(outfile, "\nLexeme List:\n");
  for(int i=0; i<tokenizedInputLength; i++) {
    printf("%d", tokenizedInput[i]);
    fprintf(outfile, "%d", tokenizedInput[i]);
    if(tokenizedInput[i] == identsym || tokenizedInput[i] == numbersym) {
      printf(" %s", lexmeIdentifiers[i].identifiers);
      fprintf(outfile, " %s", lexmeIdentifiers[i].identifiers);
    }
    printf("|");
    fprintf(outfile, "|");
  }

  fclose(infile);
  fclose(outfile);

	return 0;
}