/* David McCain
 * Dr. Steinberg
 * COP3503 Spring 2023
 * Programming Assignment 2
 */

import java.io.File;
import java.util.Scanner;
import java.io.FileNotFoundException;

public class MagicMaze {
  char[][] mazeInput;
  char[][]spacesTravelled;
  String mazeName;
  int rows, cols;
  char gamePiece = 'O';
  int xPos, yPos;
  char winPiece = 'X';
  int winPosX, winPosY;
  char emptySpace = '*';
  char blockPiece = '@';
  char travelledPiece = '.';
  int isTeleportDigitStored;
  char teleportDigit;
  int currMove; // directions are 0-3...
  int moves[];
  int numMoves;

  // constructor with parameters
  public MagicMaze(String fileName, int x, int y) {
    this.mazeName = fileName;
    this.rows = x;
    this.cols = y;
    this.currMove = 0;
    setMoves();
  }

  // check if file exists
  public static boolean doesFileExist(String fileName) {
    File inputFile = new File(fileName);
    return inputFile.exists();
  }

  // get number of lines in file
  public int getNumRows(String fileName) {
    int count = 0;

    try {
      Scanner fileScanner = new Scanner(new File(fileName));
      while (fileScanner.hasNextLine()) {
        fileScanner.next();
        count++;
      }
    } catch (FileNotFoundException e) {
      System.out.println("error with file...\n");
    }
    return count;
  }

  // get maximum number of chars per line in file
  public int getNumCols(String fileName) {
    int count = 0;
    int tempCount = 0;

    try {
      Scanner fileScanner = new Scanner(new File(fileName));
      while (fileScanner.hasNextLine()) {
        String line = fileScanner.nextLine();
        tempCount = line.length();
        if (tempCount > count)
          count = tempCount;
      }
    } catch (FileNotFoundException e) {
      System.out.println("error with file...\n");
    }
    // fileScanner.close();
    return count;
  }

  // set 2D char array to copy file contents
  public void setMaze() {
    mazeInput = new char[rows][cols];
    int i = 0;
    int j = 0;

    try {
      Scanner fileScanner = new Scanner(new File(mazeName));
      while (fileScanner.hasNextLine()) {
        String line = fileScanner.nextLine();
        for (j = 0; j < line.length(); j++) {
          mazeInput[i][j] = line.charAt(j);
        }
        i++;
      }
    } catch (FileNotFoundException e) {
      System.out.println("error with file...\n");
    }

    // set initial game piece coordinates to bottom left...
    xPos = 0;
    yPos = rows - 1;
    mazeInput[yPos][xPos] = gamePiece;
  }

  public void setSpacesTravelled() {
    spacesTravelled = new char[rows][cols];
    
    for(int i=0; i<rows; i++) {
      for(int j=0; j<cols; j++) {
        spacesTravelled[i][j] = emptySpace;
        if(mazeInput[i][j] == blockPiece)
          spacesTravelled[i][j] = blockPiece;
        }
    }

    spacesTravelled[yPos][xPos] = gamePiece;
    spacesTravelled[winPosY][winPosX] = winPiece;
  }

  // determine coordinates for win condition position
  public void setWinPos() {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (mazeInput[i][j] == winPiece) {
          winPosY = i;
          winPosX = j;
        }
      }
    }
  }

  public void setMoves() {
    moves = new int[rows*cols];
    
    for(int i=0; i<rows; i++) {
      for( int j=0; j<cols; j++) {
        moves[i+j] = -1;
      }
    }

    numMoves = 0;
  }

  // clear console screen
  public void clearScreen() {
    System.out.print("\033[H\033[2J");  
    System.out.flush();
  }

  // display maze
  public void printMaze() {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        System.out.print(mazeInput[i][j]);
      }
      System.out.println();
    }
    System.out.println();
    System.out.println("xPos:" + xPos + " yPos:" + yPos);
    System.out.println("rows:" + rows + " cols:" + cols);
    printMoves();
  }

  public void printSpacesTravelled() {
    for(int i=0; i<rows; i++) {
      for(int j=0; j<cols; j++) {
        System.out.print(spacesTravelled[i][j]);
      }
      System.out.println();
    }
    System.out.println();
  }

  public void printMoves() {
    System.out.print("moves:");
    for(int i=0; i<numMoves; i++) {
      System.out.print(moves[i]);
    }
    System.out.println();
  }

  // determine if goal has been reached...
  public boolean winCondition() {
    if (xPos == winPosX && yPos == winPosY)
      return true;
    return false;
  }

  // process for moving game piece
  public void executeMove(int move) {
      spacesTravelled[yPos][xPos] = travelledPiece;
      // move right...
      if (move == 0) {
        if (!shouldTeleport(yPos, xPos + 1)) {
          mazeInput[yPos][xPos + 1] = gamePiece;
          spacesTravelled[yPos][xPos+1] = gamePiece;
          if (isTeleportDigitStored == 1) {
            mazeInput[yPos][xPos] = teleportDigit;
            isTeleportDigitStored = 0;
          } else
            mazeInput[yPos][xPos] = travelledPiece;
            xPos++;
        } else {
          spacesTravelled[yPos][xPos+1] = travelledPiece;
          fixTeleport(xPos, yPos);
          processTeleport(yPos, xPos + 1);
        }
      }
      // move up...
      if (move == 1) {
        if (!shouldTeleport(yPos - 1, xPos)) {
          mazeInput[yPos - 1][xPos] = gamePiece;
          spacesTravelled[yPos-1][xPos] = gamePiece;
          if (isTeleportDigitStored == 1) {
            mazeInput[yPos][xPos] = teleportDigit;
            isTeleportDigitStored = 0;
          } else
            mazeInput[yPos][xPos] = travelledPiece;
            yPos--;
        } else {
          spacesTravelled[yPos-1][xPos] = travelledPiece;
          fixTeleport(xPos, yPos);
          processTeleport(yPos - 1, xPos);
        }
      }
      // move left...
      if (move == 2) {
        if (!shouldTeleport(yPos, xPos - 1)) {
          mazeInput[yPos][xPos - 1] = gamePiece;
          spacesTravelled[yPos][xPos-1] = gamePiece;
          if (isTeleportDigitStored == 1) {
            mazeInput[yPos][xPos] = teleportDigit;
            isTeleportDigitStored = 0;
          } else
            mazeInput[yPos][xPos] = travelledPiece;
            xPos--;
        } else {
          spacesTravelled[yPos][xPos-1] = travelledPiece;
          fixTeleport(xPos, yPos);
          processTeleport(yPos, xPos - 1);
        }
      }
      // move down...
      if (move == 3) {
        if (!shouldTeleport(yPos + 1, xPos)) {
          mazeInput[yPos + 1][xPos] = gamePiece;
          spacesTravelled[yPos+1][xPos] = gamePiece;
          if (isTeleportDigitStored == 1) {
            mazeInput[yPos][xPos] = teleportDigit;
            isTeleportDigitStored = 0;
          } else
            mazeInput[yPos][xPos] = travelledPiece;
            yPos++;
        } else {
          spacesTravelled[yPos+1][xPos] = travelledPiece;
          fixTeleport(xPos, yPos);
          processTeleport(yPos + 1, xPos);
        }
      }
      moves[numMoves] = move;
      numMoves++;
  }

  public void fixTeleport(int x, int y) {
    if (isTeleportDigitStored == 1) {
      mazeInput[y][x] = teleportDigit;
      isTeleportDigitStored = 0;
    }
    else mazeInput[y][x] = travelledPiece;
  }

  // check if move is valid
  public boolean isMoveValid(int move) {
    if (move < 0 || move > 3)
      return false;

    // move right...
    if (move == 0) {
      if (xPos >= cols - 1)
        return false;
      if (mazeInput[yPos][xPos+1] == blockPiece)
        return false;
      if (spacesTravelled[yPos][xPos+1] == travelledPiece)
        return false;
    }
    // move up...
    if (move == 1) {
      if (yPos <= 0)
        return false;
      if (mazeInput[yPos-1][xPos] == blockPiece)
        return false;
      if (spacesTravelled[yPos-1][xPos] == travelledPiece)
        return false;
    }
    // move left...
    if (move == 2) {
      if (xPos <= 0)
        return false;
      if (mazeInput[yPos][xPos-1] == blockPiece)
        return false;
      if (spacesTravelled[yPos][xPos-1] == travelledPiece)
        return false;
    }
    // move down...
    if (move == 3) {
      if (yPos >= rows - 1)
        return false;
      if (mazeInput[yPos+1][xPos] == blockPiece)
        return false;
      if (spacesTravelled[yPos+1][xPos] == travelledPiece)
        return false;
    }
    return true;
  }

  // returns i (y position)
  public int findI() {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (mazeInput[i][j] == gamePiece)
          return i;
      }
    }
    return -1;
  }

  // returns j (x position)
  public int findJ() {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (mazeInput[i][j] == gamePiece)
          return j;
      }
    }
    return -1;
  }

  // process teleport for move execution
  public boolean processTeleport(int a, int b) {
    // update game vars to store teleport info...
    teleportDigit = mazeInput[a][b];
    isTeleportDigitStored = 1;

    // teleport piece across the board...
    for (int i=0; i<rows; i++) {
      for (int j=0; j<cols; j++) {
        // move to other teleport digit location on board...
        if (mazeInput[i][j] == teleportDigit && (i!=a || j!=b)) {
          mazeInput[i][j] = gamePiece;
          spacesTravelled[i][j] = gamePiece;
          xPos = j;
          yPos = i;
          return true;
        }
      }
    }
    return false;
  }

  // determine if teleport should occur
  public boolean shouldTeleport(int a, int b) {
    // check if char is digit...
    if (Character.isDigit(mazeInput[a][b])) {
      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          // check if digit has match for teleport location...
          if (mazeInput[i][j] == mazeInput[a][b] && (i != a || j != b))
            return true;
        }
      }
    }
    return false;
  }

  public boolean executeTeleport() {
    // teleport piece across the board...
    for (int i=0; i<rows; i++) {
      for (int j=0; j<cols; j++) {
        // move to other teleport digit location on board...
        if (mazeInput[i][j] == teleportDigit) {
          mazeInput[i][j] = gamePiece;
          spacesTravelled[i][j] = gamePiece;
          fixTeleport(xPos, yPos);
          xPos = j;
          yPos = i;
          return true;
        }
      }
    }
    return false;
  }

  // main menu function of program
  public boolean solveMagicMaze() {
    // set up game vars...
    setMaze();
    setWinPos();
    setSpacesTravelled();

    // main game process...
    if(solveMagicMazeUtil())
      return true;
    return false;
  }

  // helper function for solving maze
  public boolean solveMagicMazeUtil() {
    // base case - return true if maze solved...
    if (winCondition()) {
      return true;
    }

    //unsolvable if backtracked to start and reached dead end...
    if(numMoves == 0 && shouldBacktrack())
      return false;

    // move if valid...
    if(isMoveValid(currMove)) {
      executeMove(currMove);
      // backtrack if necessary...
      if(shouldBacktrack() && !winCondition())
        if(!backtracking()) //return false after backtracking...
          return false;
      if(solveMagicMazeUtil())
        return true;
    }
    // change move if invalid...
    else {
      if(numMoves == 0)
        return false;
      currMove = (currMove+1)%4;
      if(solveMagicMazeUtil()) {
        return true;
      }
    }
    return false; //return false if unsolved...
  }

  // recursively backtrack until space is available
  public boolean backtracking() {
    if(shouldBacktrack()) {
        undoMove();
        backtracking();
      }
    else return false;
    return true;
  }

  // determines if backtracking should occur
  public boolean shouldBacktrack() {
    int count = 0;

    //evaluate surrounding 4 spaces...
    for(int i=0; i<4; i++)
      if(isMoveValid(i))
        count++;

    if(count < 1 && numMoves > 0)
      return true;
    return false;
  }

  // undo previous move
  public void undoMove() {
    int tempMove = (moves[numMoves-1]+2)%4;
    //check if multiple teleports were used for moves...
    if(!isMoveValid(tempMove)) {
      if(isTeleportDigitStored == 1) {
        executeTeleport();
      }
    }
    //reverse move (ex. up=down, right=left)...
    executeMove(tempMove);
    //update moves array
    moves[numMoves-1] = -1;
    numMoves = numMoves-2; //already incremented in executeMove()...
  }

}