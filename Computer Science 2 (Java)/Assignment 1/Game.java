/* David McCain
   Dr. Steinberg
   COP3503 Spring 2023
   Programming Assignment 1
*/

import java.io.File;
import java.util.Scanner;
import java.io.FileNotFoundException;

public class Game {
  int[][] board;
  char[] moves;

  public Game(int boardSize, String fileName) {
    board = new int[boardSize][boardSize];
    board[0][0] = 1; //start in top left square...
    int numLines = countFileLines(fileName);
    moves = new char[numLines];

    readMoves(fileName);
  }

  public static int countFileLines(String fileName) {
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

  public void readMoves(String fileName) {
    if (doesFileExist(fileName)) {
      int i = 0; //iterate through moves[]...

      try {
        Scanner fileScanner = new Scanner(new File(fileName));
        while (fileScanner.hasNextLine()) {
          moves[i] = fileScanner.next().charAt(0);
          i++;
        }
      } catch (FileNotFoundException e) {
        System.out.println("error reading file...");
      }
    } else {
      System.out.println("file does not exist...");
    }
  }

  public static boolean doesFileExist(String fileName) {
    File inputFile = new File(fileName);

    return inputFile.exists();
  }

  public int play(int playerNum) {
    int playerTurn = 1;

    resetBoard();
    
    //player 1 win strategy...
    if(playerNum == 1) {
      //player 1 moves first, setting up winning scenario...
      executeMove('d');
      for(int i=0; i<moves.length; i++) {
        if(board[board.length-1][board.length-1] == 1) break;
        //player 2 moves...
        if(executeMove(moves[i])) {
          playerTurn++;
        }
        //player 1 moves...
        if(executeMove(moves[i])) {
          playerTurn++;
        }
      }
    }
    //player 2 win strategy...
    if(playerNum == 2) {
      //player 1 moves first, setting up losing scenario...
      executeMove('r');
      for(int i=0; i<moves.length; i++) {
        //player 2 moves...
        if(executeMove(moves[i])) {
          playerTurn++;
        }
        //player 1 moves...
        if(executeMove(moves[i])) {
          playerTurn++;
        }
        //account for scenario preventing lose condition...
        if(board[board.length-2][board.length-3] == 1) {
          undoMove(moves[i]);
          executeMove('b');
        }
      }
    }

    //keep track of current/winning player...
    playerTurn = playerTurn % 2;
    if(playerTurn == 0) playerTurn = 2;
    
    return playerTurn;
  }

  public boolean isMoveValid(char c) {
    int size = board.length;

    //game over condition - piece moved to last square...
    if(board[size-1][size-1] == 1) return false;

    //move right...
    if(c == 'r') {
      for(int i=0; i<size; i++) {
        if(board[i][size-1] == 1) return false;
      }
    }
    //move down...
    if(c == 'b') {
      for(int i=0; i<size; i++) {
        if(board[size-1][i] == 1) return false;
      }
    }
    //move diagonal (down and right)...
    if(c == 'd') {
      boolean moveDiag = isMoveValid('r');
      if(moveDiag) moveDiag = isMoveValid('b');
      return moveDiag;
    }
    
    return true;
  }

  public boolean executeMove(char c) {
    if(isMoveValid(c)) {
      for(int i=0; i<board.length; i++) {
        for(int j=0; j<board.length; j++) {
          //find piece on board...
          if(board[i][j] == 1) {
            //move right...
            if(c == 'r') {
              board[i][j] = 0;
              board[i][j+1] = 1;
              return true; //exit loop after moving...
            }
            //move down...
            if(c == 'b') {
              board[i][j] = 0;
              board[i+1][j] = 1;
              return true;
            }
            //move diagonal...
            if(c == 'd') {
              board[i][j] = 0;
              board[i+1][j+1] = 1;
              return true;
            }
          }
        }
      }
    }
    return false; //move was invalid, thus did not execute...
  }

  public boolean undoMove(char c) {
    for(int i=0; i<board.length; i++) {
      for(int j=0; j<board.length; j++) {
        //find piece on board...
        if(board[i][j] == 1) {
          //undo move right...
          if(c == 'r') {
            board[i][j] = 0;
            board[i][j-1] = 1;
            return true; //exit loop after moving...
          }
          //undo move down...
          if(c == 'b') {
            board[i][j] = 0;
            board[i-1][j] = 1;
            return true;
          }
          //undo move diagonal...
          if(c == 'd') {
            board[i][j] = 0;
            board[i-1][j-1] = 1;
            return true;
          }
        }
      }
    }
    
    return false;
  }

  public void resetBoard() {
    for(int i=0; i<board.length; i++) {
      for(int j=0; j<board.length; j++) {
        board[i][j] = 0;
      }
    }
    board[0][0] = 1;
  }

  public void displayBoard() {
    for(int i=0; i<board.length; i++) {
      for(int j=0; j<board.length; j++) {
        System.out.print(board[i][j]);
      }
      System.out.println();
    }
    System.out.println();
  }
  
}