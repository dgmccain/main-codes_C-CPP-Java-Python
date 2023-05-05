/*
  Dareen Bashir, David McCain
  Professor Montagne
  COP 3402
  Spring 2023
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Global variables for array
#define MAX_PAS_SIZE 500
int pas[MAX_PAS_SIZE] = {0};

// Struct
typedef struct instructionRegister {
  int OP;
  int L;
  int M;
} instructionRegister;

int base(int BP, int L);

// VM (main)
int main(int argc, char *argv[]) {
  // Local variables
  int bp = 499; // current AR in stack
  int sp = bp + 1;
  int pc = 0; // increments by 3
  instructionRegister ir; // stores current instruction
  // File variables
  FILE *infile;
  char *filename = argv[argc-1]; // last command line argument is stored as filename
  // Additional variables
  int eopFlag = 1; // end of program flag
  char opCode[] = "SYS";
  int shouldPrintARSeparator = 0;

  // Initial file checking for file exception handling
  if(argc < 2) {
    printf("Enter the filename for input: ");
    if(scanf("%s", filename) != 1)
      exit(0); // immediately exit if no file detected
  }
  infile = fopen(filename, "r");

  // Output initial values
  printf("\t\t\tPC \tBP \tSP \tstack\n");
  printf("Initial Values: \t%d \t%d \t%d\n\n", pc, bp, sp);

  int currNumLines = 0; // store for printing output later
  while (!feof(infile)) {
    // Update number of lines
    currNumLines++;

    // Read input
    if(fscanf(infile, "%d %d %d", &ir.OP, &ir.L, &ir.M)!=3) {
      printf("Error occurred during fscanf...\n");
    }

    // Store current input to array
    pas[pc] = ir.OP;
    pas[pc + 1] = ir.L;
    pas[pc + 2] = ir.M;
    // Update pc
    pc += 3;
  }

  // Reset register variables after reading input to pas[]
  sp = 500;
  bp = sp - 1;
  pc = 0;
  ir.OP = 0;
  ir.L = 0;
  ir.M = 0;
  int count = 0;

  // fetch and execute cycles
  while (eopFlag != 0) {
    // fetch()
    ir.OP = pas[count];
    ir.L = pas[count + 1];
    ir.M = pas[count + 2];
    pc += 3;

    // execute()
    switch (ir.OP) {
    // NOP
    case 0:
      strcpy(opCode, "NOP");
      break;
    // LIT
    case 1:
      strcpy(opCode, "LIT");
      sp = sp - 1;
      pas[sp] = ir.M;
      break;
    // OPR
    case 2:
      strcpy(opCode, "OPR");
      switch(ir.M) {
        // RTN
        case 0:
          strcpy(opCode, "RTN");
          sp = bp + 1;
          bp = pas[sp - 2];
          pc = pas[sp - 3];
          // Next line tracks that AR has ended
          shouldPrintARSeparator = 0;
          break;
        // ADD
        case 1:
          strcpy(opCode, "ADD");
          pas[sp + 1] = pas[sp + 1] + pas[sp];
          sp = sp + 1;
          break;
        // SUB
        case 2:
          strcpy(opCode, "SUB");
          pas[sp + 1] = pas[sp + 1] - pas[sp];
          sp = sp + 1;
          break;
        // MUL
        case 3:
          strcpy(opCode, "MUL");
          pas[sp + 1] = pas[sp + 1] * pas[sp];
          sp = sp + 1;
          break;
        // DIV
        case 4:
          strcpy(opCode, "DIV");
          pas[sp + 1] = pas[sp + 1] / pas[sp];
          sp = sp + 1;
          break;
        // EQL
        case 5:
          strcpy(opCode, "EQL");
          pas[sp + 1] = pas[sp + 1] == pas[sp];
          sp = sp + 1;
          break;
        // NEQ
        case 6:
          strcpy(opCode, "NEQ");
          pas[sp + 1] = pas[sp + 1] != pas[sp];
          sp = sp + 1;
          break;
        // LSS
        case 7:
          strcpy(opCode, "LSS");
          pas[sp + 1] = pas[sp + 1] < pas[sp];
          sp = sp + 1;
          break;
        // LEQ
        case 8:
          strcpy(opCode, "LEQ");
          pas[sp + 1] = pas[sp + 1] <= pas[sp];
          sp = sp + 1;
          break;
        // GTR
        case 9:
          strcpy(opCode, "GTR");
          pas[sp + 1] = pas[sp + 1] > pas[sp];
          sp = sp + 1;
          break;
        // GEQ
        case 10:
          strcpy(opCode, "GEQ");
          pas[sp + 1] = pas[sp + 1] >= pas[sp];
          sp = sp + 1;
          break;
        default:
          printf("Error occured during %s...\n", opCode);
      }
      break;
    // LOD
    case 3:
      strcpy(opCode, "LOD");
      sp = sp - 1;
      pas[sp] = pas[base(bp, ir.L) - ir.M];
      break;
    // STO
    case 4:
      strcpy(opCode, "STO");
      pas[base(bp, ir.L) - ir.M] = pas[sp];
      sp = sp + 1;
      break;
    // CAL
    case 5:
      strcpy(opCode, "CAL");
      // Next 3 lines create AR
      pas[sp - 1] = base(bp, ir.L); // static link (SL)
      pas[sp - 2] = bp; // dynamic link (DL)
      pas[sp - 3] = pc;  // return address (RA)
      // Next line tracks that AR has been created
      shouldPrintARSeparator = 1;
      bp = sp - 1;
      pc = ir.M;
      break;
    // INC
    case 6:
      strcpy(opCode, "INC");
      sp = sp - ir.M;
      break;
    // JMP
    case 7:
      strcpy(opCode, "JMP");
      pc = ir.M;
      break;
    // JSC
    case 8:
      strcpy(opCode, "JPC");
      if(pas[sp] == 0)
        pc = ir.M;
      sp = sp + 1;
      //^^^note: files example has +1 after popping the stack,
      //but sample output has -1, which would push the stack
      break;
    // SYS
    case 9:
      strcpy(opCode, "SYS");
      switch (ir.M) {
      // SOU
      case 1:
        strcpy(opCode, "SOU");
        printf("Output result is: ");
        printf("%d", pas[sp]);
        printf("\n");
        sp = sp + 1;
        break;
      // SIN
      case 2:
        strcpy(opCode, "SIN");
        printf("Please Enter an Integer: ");
        sp = sp - 1;
        if(scanf("%d", &pas[sp]) != 1)
          printf("Error occurred during stdin...\n");
        break;
      // EOP
      case 3:
        strcpy(opCode, "EOP");
        eopFlag = 0;
        break;
      default:
        printf("Error occurred when exiting the program...\n");
      }
      break;
    default:
      printf("\nError occured during execution...\n");
    }

    // Output operation info
    printf("\t%s %d %d \t%d \t%d \t%d \t", opCode, pas[count + 1], pas[count + 2], pc, bp, sp);
    // Output stack
    for(int i=MAX_PAS_SIZE; i>sp; i--) {
      // Output separation of AR
      if(i == bp+1 && shouldPrintARSeparator == 1)
        printf("| ");
      printf("%d ", pas[i-1]);
    }
    printf("\n");

    // Update instruction count
    count+=3;
  }

  fclose(infile);

  return 0;
}

int base(int BP, int L) {
  int arb = BP; // arb = activation record base
  // Find base L levels down
  while (L > 0) {
    arb = pas[arb];
    L--;
  }
  return arb;
}