/* David McCain
   Dr. Steinberg
   COP3503 Spring 2023
   Programming Assignment 3
*/

import java.io.File;
import java.util.Arrays;
import java.util.Scanner;

public class Cookies {
  int[] greedyFactor;
  int[] sizeFactor;
  int happyCampers;
  int angryCampers;

  public Cookies(int numCookies, int numCampers, String fileName_greedyFactor, String fileName_sizeFactor) {
    this.greedyFactor = read(fileName_greedyFactor);
    this.sizeFactor = read(fileName_sizeFactor);
    this.happyCampers = 0;
    this.angryCampers = 0;
  }

  public int[] read(String fileName) {
    Scanner scanLines = null;
    Scanner scanInts = null;
    int numLines = 0;
    
    try {
      File infile = new File(fileName);
      scanLines = new Scanner(infile);

      //find number of lines in file
      while(scanLines.hasNextInt()) {
        numLines++;
        scanLines.nextInt();
      }

      //create int array based upon number of lines in file
      int[] newArray = new int[numLines];
      scanInts = new Scanner(infile);

      //store file data in int array
      for(int i=0; i<numLines; i++)
        newArray[i] = scanInts.nextInt();

      return newArray;
    }
    catch(Exception e) {
      System.out.println("Error occurred when reading file...");
      return null;
    }
    finally {
      scanLines.close();
      scanInts.close();
    }
  }

  public void passCookies() {
    //greedy algorithm solution
    Arrays.sort(greedyFactor);
    Arrays.sort(sizeFactor);

    for(int i=0; i<greedyFactor.length; i++) {
      for(int j=0; j<sizeFactor.length; j++) {
        if(greedyFactor[i] <= sizeFactor[j]) {
          happyCampers++;
          sizeFactor[j] = -1;
          break;
        }
      }
    }

    angryCampers = greedyFactor.length - happyCampers;
  }

  public void display() {
    System.out.println("There are " + this.happyCampers + " happy campers.");
    System.out.println("There are " + this.angryCampers + " angry campers.");
  }
}