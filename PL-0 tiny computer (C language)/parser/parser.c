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

// Global Variables - for max sizes
#define MAX_NUMBER_DIGITS 5
#define MAX_IDENTIFIER_LENGTH 11
#define INPUT_SIZE 5000
#define MAX_SYMBOL_TABLE_SIZE 500
#define MAX_ASSEMBLY_CODE_TABLE_SIZE 500

// Structures
typedef enum {
  skipsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5, multsym = 6, slashsym = 7, oddsym = 8, eqlsym = 9, neqsym = 10, lessym = 11, leqsym = 12, gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17, semicolonsym = 18, periodsym = 19, becomessym = 20, beginsym = 21, endsym = 22, ifsym = 23, thensym = 24, whilesym = 25, dosym = 26, callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31, readsym = 32, elsesym = 33, colonsym = 34
} token_type;

typedef struct {
  char identifiers[MAX_IDENTIFIER_LENGTH];
} lexme;

typedef struct symbol { 
  int kind; // const = 1, var = 2, proc = 3
  char name[MAX_IDENTIFIER_LENGTH];
  int val;
  int level;
  int addr; // M address
  int mark; // to indicate unavailable or deleted
} symbol;
//^^^For constants, you must store kind, name and value.
//^^^For variables, you must store kind, name, L and M.

typedef struct assembly_code {
  int line;
  char opcode[3];
  int l;
  int m;
} assembly_code;

// More Global Variables
int curr_symbol_table_size = 0; //num symbols
symbol symbol_table[MAX_SYMBOL_TABLE_SIZE];
int curr_assembly_code_table_size = 0; //num opcode instructions
assembly_code assembly_code_table[MAX_ASSEMBLY_CODE_TABLE_SIZE];
// Input tokenized
int tokenizedInput[INPUT_SIZE];
int tokenizedInputLength = 0;
int curr_token_idx = 0;
// Symbols and variables stored for lexme table
lexme lexmeIdentifiers[INPUT_SIZE];
int lexmeLength = 0;
// File input and output variables
char c;
FILE *infile;
FILE *outfile;
char *outfilename = "output.txt";

// Functions
int symbolTableCheck(char* str);
void outputAssemblyCode();
void outputSymbolTable();
// Program Functions
void emit(char* opcode, int l, int m);
void program();
void block();
void const_declaration();
int var_declaration();
void statement();
void condition();
void expression();
void term();
void factor();
void error(char* str, int newln);

int main(int argc, char* argv[]) {
  // Input file depends on main args
  char *infilename = argv[argc-1]; //last command line argument is stored as filename
  // Input verbatim
  char input[INPUT_SIZE];
  int inputLength = 0;
  // Input formatted
  char formattedInput[INPUT_SIZE];
  int formattedInputLength = 0;
  // String variable
  char tempStr[MAX_IDENTIFIER_LENGTH]; //used for identifiers strcpy
  int tempStrLength = 0;
  // Miscellaneous - error handling and formatting
  int shouldCheckForCommentStart = 0;
  int shouldCheckForCommentEnd = 0;
  int commentBlockStarted = 0;
  int commentBlockEnded = 1;
  int shouldSkipInputIncrement = 0;

  // Open output file
  outfile = fopen(outfilename, "w");

  // Initial file checking for file exception handling
  if(argc < 2) {
    printf("Enter the filename for input: ");
    if(scanf("%s", infilename) != 1) {
      error("could not open input file", 0);
    }
  }

  // Open input file
  infile = fopen(infilename, "r");
  if(!infile)
    error("file is empty or does not exist", 0);

  // Read input
  while(fscanf(infile, "%c", &c) != EOF) {
    // Store current input being read
    input[inputLength] = c;
    inputLength++;
  }
  input[inputLength] = '\0';

  // Output file contents verbatim
  printf("Source Program:\n");
  fprintf(outfile, "Source Program:\n");
  for(int i=0; i<inputLength; i++) {
    printf("%c", input[i]);
    fprintf(outfile, "%c", input[i]);
  }

  // Format input
  for(int i=0; i<inputLength; i++) {
    // Read chars, digits, and symbols
    if(isspace(input[i])) {
      // Skip through ' ', '\n', and '\t'
      while (isspace(input[i]))
        i++;
      // Add space delimitter between inputs
      formattedInput[formattedInputLength] = ' ';
      formattedInputLength++;
      i--;
      continue;
    }

    // Skip the comment block
    if (input[i] == '/' && input[i+1] == '*') {
      i += 2;
      while (!(input[i] == '*' && input[i+1] == '/')) i++;
      i++;
      continue;
    }
    
    // Store current input being read
    formattedInput[formattedInputLength] = input[i];
    formattedInputLength++;
  }

  // Tokenize input
  for(int i=0; i<formattedInputLength; i++) {
    tempStrLength = 0; //reset tempStrLength for default case...
    if (isspace(formattedInput[i])) continue;
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
        tokenizedInput[tokenizedInputLength] = eqlsym;
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
        if((formattedInput[i+1] == 'e') && (formattedInput[i+2] == 'g') && (formattedInput[i+3] == 'i') && (formattedInput[i+4] == 'n') && (isspace(formattedInput[i+5]) || !isalnum(formattedInput[i+5]))) {
          tokenizedInput[tokenizedInputLength] = beginsym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "begin");
          lexmeLength++;
          i += 4;
          continue;
        }
      case 'e':
        // Check for end
        if((formattedInput[i+1] == 'n') && (formattedInput[i+2] == 'd') && (isspace(formattedInput[i+3]) || !isalnum(formattedInput[i+3]))) {
          tokenizedInput[tokenizedInputLength] = endsym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "end");
          lexmeLength++;
          i += 2;
          continue;
        }
        // Check for else
        else if((formattedInput[i+1] == 'l') && (formattedInput[i+2] == 's') && (formattedInput[i+3] == 'e') && (isspace(formattedInput[i+4]) || !isalnum(formattedInput[i+4]))) {
          tokenizedInput[tokenizedInputLength] = elsesym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "else");
          lexmeLength++;
          i += 3;
          continue;
        }
      case 'i':
        // Check for if
        if((formattedInput[i+1] == 'f') && (isspace(formattedInput[i+2]) || !isalnum(formattedInput[i+2]))) {
          tokenizedInput[tokenizedInputLength] = ifsym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "if");
          lexmeLength++;
          i++;
          continue;
        }
      case 't':
        // Check for then
        if((formattedInput[i+1] == 'h') && (formattedInput[i+2] == 'e') && (formattedInput[i+3] == 'n') && (isspace(formattedInput[i+4]) || !isalnum(formattedInput[i+4]))) {
          tokenizedInput[tokenizedInputLength] = thensym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "then");
          lexmeLength++;
          i += 3;
          continue;
        }
      case 'd':
        // Check for do
        if(formattedInput[i+1] == 'o' && (isspace(formattedInput[i+2]) || !isalnum(formattedInput[i+2]))) {
          tokenizedInput[tokenizedInputLength] = dosym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "do");
          lexmeLength++;
          i++;
          continue;
        }
      case 'r':
        // Check for read
        if ((formattedInput[i+1] == 'e') && (formattedInput[i+2] == 'a') && (formattedInput[i+3] == 'd') && (isspace(formattedInput[i+4]) || !isalnum(formattedInput[i+4]))) {
          tokenizedInput[tokenizedInputLength] = readsym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "read");
          lexmeLength++;
          i += 3;
          continue;
        }
      case 'w':
        // Check for while
        if((formattedInput[i+1] == 'h') && (formattedInput[i+2] == 'i') && (formattedInput[i+3] == 'l') && (formattedInput[i+4] == 'e') && (isspace(formattedInput[i+5]) || !isalnum(formattedInput[i+5]))) {
          tokenizedInput[tokenizedInputLength] = whilesym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "while");
          lexmeLength++;
          i += 4;
          continue;
        }
        // Check for write
        else if((formattedInput[i+1] == 'r') && (formattedInput[i+2] == 'i') && (formattedInput[i+3] == 't') && (formattedInput[i+4] == 'e') && (isspace(formattedInput[i+5]) || !isalnum(formattedInput[i+5]))) {
          tokenizedInput[tokenizedInputLength] = writesym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "write");
          lexmeLength++;
          i += 4;
          continue;
        }
      case 'c':
        // Check for call
        if((formattedInput[i+1] == 'a') && (formattedInput[i+2] == 'l') && (formattedInput[i+3] == 'l') && (isspace(formattedInput[i+4]) || !isalnum(formattedInput[i+4]))) {
          tokenizedInput[tokenizedInputLength] = callsym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "call");
          lexmeLength++;
          i += 3;
          continue;
        }
        // Check for const
        else if((formattedInput[i+1] == 'o') && (formattedInput[i+2] == 'n') && (formattedInput[i+3] == 's') && (formattedInput[i+4] == 't') && (isspace(formattedInput[i+5]) || !isalnum(formattedInput[i+5]))) {
          tokenizedInput[tokenizedInputLength] = constsym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "const");
          lexmeLength++;
          i += 4;
          continue;
        }
      case 'v':
        // Check for var
        if((formattedInput[i+1] == 'a') && (formattedInput[i+2] == 'r') && (isspace(formattedInput[i+3]) || !isalnum(formattedInput[i+3]))) {
          tokenizedInput[tokenizedInputLength] = varsym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "var");
          lexmeLength++;
          i += 2;
          continue;
        }
      case 'p':
        // Check for procedure
        if((formattedInput[i+1] == 'r') && (formattedInput[i+2] == 'o') && (formattedInput[i+3] == 'c') && (formattedInput[i+4] == 'e') && (formattedInput[i+5] == 'd') && (formattedInput[i+6] == 'u') && (formattedInput[i+7] == 'r') && (formattedInput[i+8] == 'e') && (isspace(formattedInput[i+9]) || !isalnum(formattedInput[i+9]))) {
          tokenizedInput[tokenizedInputLength] = procsym;
          tokenizedInputLength++;
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, "procedure");
          lexmeLength++;
          i += 8;
          continue;
        }
      case 'o':
        // Check for odd
        if((formattedInput[i+1] == 'd') && (formattedInput[i+2] == 'd') && (isspace(formattedInput[i+3]) || !isalnum(formattedInput[i+3]))) {
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
              error("identifier too long", 1);
            }
            i++;
          }
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, tempStr);
          lexmeLength++;
          tokenizedInput[tokenizedInputLength] = identsym;
          tokenizedInputLength++; 
          i--;
          continue;
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
              error("too many digits", 1);
            }
            i++;
          }
          
          if (isalpha(formattedInput[i])) {
            // Identifier starts with digit
            error("identifier starts with digit", 1);
          }
          
          strcpy(lexmeIdentifiers[lexmeLength].identifiers, tempStr);
          lexmeLength++;
          tokenizedInput[tokenizedInputLength] = numbersym;
          tokenizedInputLength++; 
          i--;
          continue;
        }
        // Invalid Symbol - default case
        else {
        // Output exit message
          error("invalid symbol", 1);
        }
    }
  }

  // Add JMP and main as first entries to assembly_code and symbol tables
  emit("JMP", 0, 3);
  symbol_table[curr_symbol_table_size].kind = 3;
  strcpy(symbol_table[curr_symbol_table_size].name, "main");
  symbol_table[curr_symbol_table_size].val = 0;
  symbol_table[curr_symbol_table_size].level = 0;
  symbol_table[curr_symbol_table_size].addr = 3;
  symbol_table[curr_symbol_table_size].mark = 0;
  curr_symbol_table_size++;
  // Parsing - main program
  program();
  symbol_table[curr_symbol_table_size].mark = 1;
  // Update all identifier marks to be 1 before exiting main()
  for(int i=0; i<curr_symbol_table_size; i++) {
    symbol_table[i].mark = 1;
  }

  // Output Assembly Code
  outputAssemblyCode();
  // Output Symbol Table
  outputSymbolTable();

  fclose(infile);
  fclose(outfile);

	return 0;
}

int symbolTableCheck(char* str) {
  // Return index of symbol if found
  for(int i=0; i<curr_symbol_table_size; i++) {
    if(strcmp(str, symbol_table[i].name) == 0)
      return i;
  }
  return -1; //symbol not found
}

void outputAssemblyCode() {
  printf("\n\nAssembly Code:\n");
  fprintf(outfile, "\n\nAssembly Code:\n");
  printf("Line   OP    L    M\n");
  fprintf(outfile, "Line   OP    L    M\n");
  for(int i=0; i<curr_assembly_code_table_size; i++) {
    printf("%-6d %-5s %-4d %d\n", assembly_code_table[i].line, assembly_code_table[i].opcode, assembly_code_table[i].l, assembly_code_table[i].m);
    fprintf(outfile, "%-6d %-5s %-4d %d\n", assembly_code_table[i].line, assembly_code_table[i].opcode, assembly_code_table[i].l, assembly_code_table[i].m);
  }
}

void outputSymbolTable() {
  printf("\nSymbol Table:\n");
  fprintf(outfile, "\nSymbol Table:\n");
  printf("Kind  Name  Value  Level  Address  Mark\n");
  fprintf(outfile, "Kind  Name  Value  Level  Address  Mark\n");
  for(int i=0; i<curr_symbol_table_size; i++) {
    printf("%-5d %-5s %-6d %-6d %-8d %d\n", symbol_table[i].kind, symbol_table[i].name, symbol_table[i].val, symbol_table[i].level, symbol_table[i].addr, symbol_table[i].mark);
    fprintf(outfile, "%-5d %-5s %-6d %-6d %-8d %d\n", symbol_table[i].kind, symbol_table[i].name, symbol_table[i].val, symbol_table[i].level, symbol_table[i].addr, symbol_table[i].mark);
  }
}

// Add line of assembly code instruction to table
void emit(char* opcode, int l, int m) {
  assembly_code_table[curr_assembly_code_table_size].line = curr_assembly_code_table_size;
  strcpy(assembly_code_table[curr_assembly_code_table_size].opcode, opcode);
  assembly_code_table[curr_assembly_code_table_size].l = l;
  assembly_code_table[curr_assembly_code_table_size].m = m;
  curr_assembly_code_table_size++;
}

void program() {
  block();
  if(tokenizedInput[curr_token_idx] != periodsym) {
    error("missing period", 1);
  }
  emit("SYS", 0, 3);
}

void block() {
  const_declaration();
  int numVars = var_declaration();
  emit("INC", 0, 3+numVars);
  statement();
}

void const_declaration() {
  if(tokenizedInput[curr_token_idx] == constsym) {
    do {
      curr_token_idx++;
      if(tokenizedInput[curr_token_idx] != identsym) {
        error("missing const identifier", 1);
      }
      if(symbolTableCheck(lexmeIdentifiers[curr_token_idx].identifiers) != -1) {
        error("const identifier already declared", 1);
      }
      symbol_table[curr_symbol_table_size].kind = 1;
      strcpy(symbol_table[curr_symbol_table_size].name, lexmeIdentifiers[curr_token_idx].identifiers);
      curr_token_idx++;
      if(tokenizedInput[curr_token_idx] != eqlsym) {
        error("missing const initial value", 1);
      }
      curr_token_idx++;
      if(tokenizedInput[curr_token_idx] != numbersym) {
        error("const value must be a number", 1);
      }
      symbol_table[curr_symbol_table_size].val = atoi(lexmeIdentifiers[curr_token_idx].identifiers);
      symbol_table[curr_symbol_table_size].level = 0;
      symbol_table[curr_symbol_table_size].addr = 0;
      symbol_table[curr_symbol_table_size].mark = 0;
      curr_symbol_table_size++;
      curr_token_idx++;
    } while(tokenizedInput[curr_token_idx] == commasym);
    if(tokenizedInput[curr_token_idx] != semicolonsym) {
      error("missing semicolon after const declaration", 1);
    }
    curr_token_idx++;
  }
}

int var_declaration() {
  int numVars = 0;
  if(tokenizedInput[curr_token_idx] == varsym) {
    do {
      numVars++;
      curr_token_idx++;
      if (tokenizedInput[curr_token_idx] != identsym) {
        error("missing var identifier", 1);
      }
      if (symbolTableCheck(lexmeIdentifiers[curr_token_idx].identifiers) != -1) {
        error("var identifier already declared", 1);
      }
      // Add var ident to symbol table
      symbol_table[curr_symbol_table_size].kind = 2;
      strcpy(symbol_table[curr_symbol_table_size].name, lexmeIdentifiers[curr_token_idx].identifiers);
      symbol_table[curr_symbol_table_size].val = 0; //intitialize vars to 0...
      symbol_table[curr_symbol_table_size].level = 0;
      symbol_table[curr_symbol_table_size].addr = numVars+2;
      curr_symbol_table_size++;
      curr_token_idx++;
    } while (tokenizedInput[curr_token_idx] == commasym);
    if (tokenizedInput[curr_token_idx] != semicolonsym) {
      error("missing semicolon after var declaration", 1);
    }
    curr_token_idx++;
  }
  return numVars;
}

void statement() {
  if(tokenizedInput[curr_token_idx] == identsym) {
    int symIdx = symbolTableCheck(lexmeIdentifiers[curr_token_idx].identifiers);
    if(symIdx == -1) {
      error("identifier not found in symbol table", 1);
    }
    if(symbol_table[symIdx].kind != 2) {
      error("you can only change value of vars", 1);
    }
    curr_token_idx++;
    if(tokenizedInput[curr_token_idx] != becomessym) {
      error("missing becomes symbol", 1);
    }
    curr_token_idx++;
    //current token should now be the token after becomes
    //update var's symbol_table.val before checking expression()...
    expression();
    emit("STO", symbol_table[symIdx].level, symbol_table[symIdx].addr);
    return;
  }
  if(tokenizedInput[curr_token_idx] == beginsym) {
    do {
      curr_token_idx++;
      statement();
    } while (tokenizedInput[curr_token_idx] == semicolonsym);
    if (tokenizedInput[curr_token_idx] != endsym) {
      error("missing end symbol", 1);
    }
    curr_token_idx++;
    return;
  }
  if(tokenizedInput[curr_token_idx] == ifsym) {
    curr_token_idx++;
    condition();
    int jpcIdx = curr_token_idx;
    emit("JPC", 0, 0);
    if(tokenizedInput[curr_token_idx] != thensym) {
      error("missing then symbol", 1);
    }
    curr_token_idx++;
    statement();
    assembly_code_table[jpcIdx].m = curr_token_idx;
    return;
  }
  if(tokenizedInput[curr_token_idx] == whilesym) {
    curr_token_idx++;
    int loopIdx = curr_token_idx;
    condition();
    if (tokenizedInput[curr_token_idx] != dosym) {
      error("missing do symbol", 1);
    }
    curr_token_idx++;
    int jpcIdx = curr_token_idx;
    emit("JPC", 0, 0);
    statement();
    emit("JMP", 0, loopIdx);
    assembly_code_table[jpcIdx].m = curr_token_idx;
    return;
  }
  if(tokenizedInput[curr_token_idx] == readsym) {
    curr_token_idx++;
    if(tokenizedInput[curr_token_idx] != identsym) {
      error("missing ident symbol", 1);
    }
    int symIdx = symbolTableCheck(lexmeIdentifiers[curr_token_idx].identifiers);
    if(symIdx == -1) {
      error("identifier not found in symbol table", 1);
    }
    if(symbol_table[symIdx].kind != 2) {
      error("you can only change vars", 1);
    }
    curr_token_idx++;
    emit("SYS", 0, 2);
    emit("STO", 0, symbol_table[symIdx].addr);
    return;
  }
  if(tokenizedInput[curr_token_idx] == writesym) {
    curr_token_idx++;
    expression();
    emit("SYS", 0, 1);
    return;
  }
}

void condition() {
  if(tokenizedInput[curr_token_idx] == oddsym) {
    curr_token_idx++;
    expression();
    emit("ODD", 0, 0);
  }
  else {
    expression();
    if(tokenizedInput[curr_token_idx] == eqlsym) {
      curr_token_idx++;
      expression();
      emit("EQL", 0, 5);
    }
    else if(tokenizedInput[curr_token_idx] == neqsym) {
      curr_token_idx++;
      expression();
      emit("NEQ", 0, 6);
    }
    else if(tokenizedInput[curr_token_idx] == lessym) {
      curr_token_idx++;
      expression();
      emit("LSS", 0, 7);
    }
    else if(tokenizedInput[curr_token_idx] == leqsym) {
      curr_token_idx++;
      expression();
      emit("LEQ", 0, 8);
    }
    else if(tokenizedInput[curr_token_idx] == gtrsym) {
      curr_token_idx++;
      expression();
      emit("GTR", 0, 9);
    }
    else if(tokenizedInput[curr_token_idx] == geqsym) {
      curr_token_idx++;
      expression();
      emit("GEQ", 0, 10);
    }
    else {
      error("invalid operation", 1);
    }
  }
}

void expression() {
  if(tokenizedInput[curr_token_idx] == minussym) {
    curr_token_idx++;
    term();
    emit("NEQ", 0, 6); //was written as NEG...
    while(tokenizedInput[curr_token_idx] == plussym || tokenizedInput[curr_token_idx] == minussym) {
      if(tokenizedInput[curr_token_idx] == plussym) {
        curr_token_idx++;
        term();
        emit("ADD", 0, 1);
      }
      else {
        curr_token_idx++;
        term();
        emit("SUB", 0, 2);
      }
    }
  }
  else {
    if(tokenizedInput[curr_token_idx] == plussym)
      curr_token_idx++;
    term();
    while(tokenizedInput[curr_token_idx] == plussym || tokenizedInput[curr_token_idx] == minussym) {
      if(tokenizedInput[curr_token_idx] == plussym) {
        curr_token_idx++;
        term();
        emit("ADD", 0, 1);
      }
      else {
        curr_token_idx++;
        term();
        emit("SUB", 0, 2);
      }
    }
  }
}

void term() {
  factor();
  while(tokenizedInput[curr_token_idx] == multsym || tokenizedInput[curr_token_idx] == slashsym) { //removed || modsymb
    if(tokenizedInput[curr_token_idx] == multsym) {
      curr_token_idx++;
      factor();
      emit("MUL", 0, 3);
    }
    else if(tokenizedInput[curr_token_idx] == slashsym) {
      curr_token_idx++;
      factor();
      emit("DIV", 0, 4);
    }
  }
}

void factor() {
  if(tokenizedInput[curr_token_idx] == identsym) {
    int symIdx = symbolTableCheck(lexmeIdentifiers[curr_token_idx].identifiers);
    if(symIdx == -1) {
      error("identifier not found in symbol table", 1);
    }
    if(symbol_table[symIdx].kind == 1)
      emit("LIT", 0, symbol_table[symIdx].val);
    else //var
      emit("LOD", 0, symbol_table[symIdx].addr);
    curr_token_idx++;
  }
  else if(tokenizedInput[curr_token_idx] == numbersym) {
    emit("LIT", 0, atoi(lexmeIdentifiers[curr_token_idx].identifiers));
    curr_token_idx++;
  }
  else if(tokenizedInput[curr_token_idx] == lparentsym) {
    curr_token_idx++;
    expression();
    if(tokenizedInput[curr_token_idx] != rparentsym) {
      error("missing right parenthesis", 1);
    }
    curr_token_idx++;
  }
  else {
    error("input needs to be ident, num, or appropriate parenthesis", 1);
  }
}

void error(char* str, int newln) {
  if(newln == 1) {
    printf("\n");
    fprintf(outfile, "\n");
  }
  printf("Error: %s", str);
      fprintf(outfile, "Error: %s", str);
      exit(0); // immediately exit if error occurs
}