/* 
  David McCain
  Dr. Steinberg
  COP3503 Spring 2023
  Programming Assignment 5
*/

import java.io.*;
import java.util.*;

public class Railroad {
  private int numRails; //number of tracks in the text file
  private String[] src;
  private String[] dst;
  private int[] cost; // weight

  public Railroad(int numLines, String filename) throws FileNotFoundException {
    numRails = numLines;
    src = new String[numLines];
    dst = new String[numLines];
    cost = new int[numLines];
    readFile(filename);
  }
  
  public void readFile(String filename) {
    Scanner fileScanner = null;

    try {
      File infile = new File(filename);
      fileScanner = new Scanner(infile);
      int currLine = 0;

      while (fileScanner.hasNext() && currLine < numRails) {
        String[] Line = fileScanner.nextLine().split(" ");
        src[currLine] = Line[0];
        dst[currLine] = Line[1];
        cost[currLine] = Integer.parseInt(Line[2]);
        // alphabetize
        if(src[currLine].compareTo(dst[currLine]) > 0)
          swapSrcDst(currLine);
        currLine++;
      }
    } catch (Exception e) {
      System.out.println("Error occurred when opening file...");
      return;
    } finally {
      fileScanner.close();
    }
    
    quickSort(cost, 0, numRails - 1);
  }

  // returns graph & cost message.
  public String buildRailroad() {
    String[] solution = new String[numRails * 3];
    String message = "";
    int total = 0;
    int tempSize = 0;

    for (int i = 0; i < numRails * 3; i += 3) {
      // check if src and dst are not in solution
      if (!Arrays.asList(solution).contains(src[i / 3]) || !Arrays.asList(solution).contains(dst[i / 3])) {
        solution[tempSize] = src[i / 3];
        solution[tempSize + 1] = dst[i / 3];
        solution[tempSize + 2] = String.valueOf(cost[i / 3]);
        total += cost[i / 3];
        tempSize += 3;
      }
      // check if both vertices already exist, but are not connected
        /*
      else if(doVerticesConnect(solution, src[i/3], dst[i/3], tempSize-1, (i/3)-1)) {
        solution[tempSize] = src[i / 3];
        solution[tempSize + 1] = dst[i / 3];
        solution[tempSize + 2] = String.valueOf(cost[i / 3]);
        total += cost[i / 3];
        tempSize += 3;
      }
      */
    }
    for (int i = 0; i < tempSize; i += 3) {
      message += solution[i] + "---" + solution[i + 1] + '\t' + "$" + solution[i + 2] + '\n';
    }
    message += "The cost of the railroad is $" + total;
    return message;
  }

  public int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1); // index of smaller element
    for (int j = low; j < high; j++) {
      // if current element is smaller than pivot
      if (arr[j] < pivot) {
        i++;
        /*
         * swap arr[i] and arr[j]. After swapping arr (cost[]),
         * then swap src[] and dst[] too
         */
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        String tempSrc = src[i];
        src[i] = src[j];
        src[j] = tempSrc;
        String tempDst = dst[i];
        dst[i] = dst[j];
        dst[j] = tempDst;
      }
      // if current element is equal to pivot
      if (arr[j] == pivot && (src[i].compareTo(src[j]) < 0)) {
        i++;
        // perform swap if alphabetically out of order
        String tempSrc = src[i];
        src[i] = src[j];
        src[j] = tempSrc;
        String tempDst = dst[i];
        dst[i] = dst[j];
        dst[j] = tempDst;
      }
    }

    /*
     * swap arr[i+1] and arr[high] (or pivot). After swapping
     * arr (which is cost[]), then swap src[] and dst[] too
     */
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    String tempSrc = src[i + 1];
    src[i + 1] = src[high];
    src[high] = tempSrc;
    String tempDst = dst[i + 1];
    dst[i + 1] = dst[high];
    dst[high] = tempDst;

    return i + 1;
  }

  public void quickSort(int arr[], int low, int high) {
    if (low < high) {
      int pi = partition(arr, low, high);
      quickSort(arr, low, pi - 1);
      quickSort(arr, pi + 1, high);
    }
  }

  public void swapSrcDst(int i) {
    String temp = src[i];
    src[i] = dst[i];
    dst[i] = temp;
  }

  /*
  public boolean doVerticesConnect(String[] solution, String str1, String str2, int solutionLength, int indexLength) {
    // base case
    if(indexLength < 0 || solutionLength < 0)
      return false;

    for(int i=0; i<solutionLength; i+=3) {
      if(solution[i].equals(str1)) {
        if(solution[i+1].equals(str2))
          return true;
        return doVerticesConnect(solution, solution[i+1], str2, solutionLength-3, indexLength-1);
      }
      else if(solution[i].equals(str2)) {
        if(solution[i+1].equals(str1))
          return true;
        return doVerticesConnect(solution, solution[i+1], str1, solutionLength-3, indexLength-1);
      }
    }
    
    return false;
  }
  */
}