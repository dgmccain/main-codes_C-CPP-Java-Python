/* Name: David McCain
 * Dr. Andrew Steinberg
 * COP3503 Fall 2022
 * Programming Assignment 4
 */

public class LCS {
  //class variables
  private String str1;
  private String str2;
  private int[][] arrC;
  private char[][] arrB;
  private String longestStr;

  //constructor
  public LCS(String s1, String s2) {
    str1 = s1;
    str2 = s2;
    arrC = new int[str1.length()+1][str2.length()+1];
    arrB = new char[str1.length()+1][str2.length()+1];
    longestStr = "";
  }

  //accessors and mutators
  public String getStr1() { return str1; }
  public String getStr2() { return str2; }
  public String getLCS() { return longestStr; }
  //note: this setter function can be improved by changing
  //string concatenation to char array with initial size of
  //the smallest string length (i.e. str1)
  public void setLongestStr(char c) { longestStr += c; }

  //functions
  public void lcsDynamicSol() {
    int m = getStr1().length();
    int n = getStr2().length();

    //initialize arrC first row and column to zero
    for(int i=0; i<=m; i++) {
      arrC[i][0] = 0;
    }
    for(int j=1; j<=n; j++) {
      arrC[0][j] = 0;
    }
    //initialize arrB first row and column to zero
    for(int i=0; i<=m; i++) {
      arrB[i][0] = '0';
    }
    for(int j=1; j<=n; j++) {
      arrB[0][j] = '0';
    }

    //traversal
    for(int i=1; i<=m; i++) {
      //arrows correspond to char values explained below
      for(int j=1; j<=n; j++) {
        if(getStr1().charAt(i-1) == getStr2().charAt(j-1)) {
          arrC[i][j] = arrC[i-1][j-1]+1;
          arrB[i][j] = 'a'; //a for across
        }
        else if(arrC[i-1][j] >= arrC[i][j-1]) {
          arrC[i][j] = arrC[i-1][j];
          arrB[i][j] = 'u'; //u for up
        }
        else {
          arrC[i][j] = arrC[i][j-1];
          arrB[i][j] = 'l'; //l for left
        }
      }
    }

    //track longest string from arrB data
    helperFunctionLCS(m, n);
  }

  public void helperFunctionLCS(int i, int j) {
    if(i == 0 || j == 0)
      return;

    if(arrB[i][j] == 'a') {
      helperFunctionLCS(i-1, j-1);
      setLongestStr(getStr1().charAt(i-1));
    }
    else if(arrB[i][j] == 'u') {
      helperFunctionLCS(i-1, j);
    }
    else { //case for 'l' (left)
      helperFunctionLCS(i, j-1);
    }
  }

  public void displayArrays() {
    int m = getStr1().length();
    int n = getStr2().length();
    
    //display arrC (int array)
    for(int i=0; i<=m; i++) {
      for(int j=0; j<=n; j++) {
        System.out.print(arrC[i][j]);
      }
      System.out.println();
    }
    System.out.println();
    //display arrB (char array)
    for(int i=0; i<=m; i++) {
      for(int j=0; j<=n; j++) {
        System.out.print(arrB[i][j]);
      }
      System.out.println();
    }
    System.out.println();
  }
}