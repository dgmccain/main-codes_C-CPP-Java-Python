#define _CRT_SECURE_NO_WARNINGS

#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main() {
  char delimitter = ',';
  char c;
  char filename[30];
  int searchForComment = 1;
  int startSlashEntered = 0;
  int startCommentEntered = 0;
  int endCommentEntered = 0;
  int endSlashEntered = 0;

  // Get name of input file
  printf("Enter name of file for input: ");
  fgets(filename, 30, stdin);
  filename[strcspn(filename, "\n")] = 0; // remove \n from filename

  // Open input file
  FILE *infile = fopen(filename, "r");
  if (infile == NULL) {
    printf("this file is empty or does not exist in this folder");
    return 0;
  }

  // Ignore file extension for input file name
  for (int i = 0; i < strlen(filename); i++) {
    if (filename[i] == '.')
      filename[i] = '\0';
  }
  // Create output file name
  strncat(filename, "Formatted.txt", 13);
  // Open output file
  FILE *outfile = fopen(filename, "w");
  printf("Output file < %s > was created\n", filename);

  // Ignore first comment section
  c = fgetc(infile);
  // Check for start comment
  if (c == '/') {
    startSlashEntered = 1;
    c = fgetc(infile);
    if (c == '*') {
      startCommentEntered = 1;

      do {
        c = fgetc(infile);

        // Check for end comment
        if (c == '*') {
          endCommentEntered = 1;
          c = fgetc(infile);
          if (c == '/')
            endSlashEntered = 1;
          else
            endCommentEntered = 0;
          continue;
        }

        // Process end of comment
        if (endCommentEntered == 1 && endSlashEntered == 1)
          searchForComment = 0;
      } while (searchForComment);
    } else
      startSlashEntered = 0;
  } else
    ungetc(c, infile);

  // Format the start of new file
  do {
    c = fgetc(infile);
  } while (isspace(c));
  ungetc(c, infile);
  fprintf(outfile, "%s", "(\'");

  // Format rest of input from existing file
  do {
    c = fgetc(infile);

    // Checking for end of file
    if (feof(infile)) {
      fprintf(outfile, "%s", "\');");
      break;
    }

    // Checking for formats to ignore
    if (isspace(c) && c != ' ' && c != '\n')
      continue;

    // Format start of delimitter
    if (c == delimitter)
      fprintf(outfile, "%s", "\'");

    // Format newline
    if (c == '\n') {
      fprintf(outfile, "%s", "\'),\n(\'");
      continue;
    }

    // Output char to output file
    fprintf(outfile, "%c", c);

    // Format end of delimitter
    if (c == delimitter) {
      fprintf(outfile, "%s", "\'");
      do {
        c = fgetc(infile);
      } while (c == ' ');
      ungetc(c, infile);
    }
  } while (1);

  printf("File < %s > was formatted\n", filename);

  fclose(infile);
  fclose(outfile);

  return 0;
}