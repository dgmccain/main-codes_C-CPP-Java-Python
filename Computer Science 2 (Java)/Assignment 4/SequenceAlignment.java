/* Name: David McCain
 * Dr. Andrew Steinberg
 * COP3503 Spring 2023
 * Programming Assignment 4
 */

public class SequenceAlignment {
  // class variables
  private String s1;
  private String s2;
  private String strAlignment;

  // constructor
  public SequenceAlignment(String str1, String str2) {
    s1 = str1;
    s2 = str2;
    strAlignment = "";
  }

  // get computed alignment
  public String getAlignment() {
    return (strAlignment);
  }

  // dynamic programming solution
  public void computeAlignment(int delta) {
    // Initialize a 2D array to store the alignment costs
    int[][] dp = new int[s1.length() + 1][s2.length() + 1];

    // Initialize the first row and column of the array
    for (int i = 0; i <= s1.length(); i++) {
        dp[i][0] = i * delta;
    }
    for (int j = 0; j <= s2.length(); j++) {
        dp[0][j] = j * delta;
    }

    // Fill in the rest of the array using dynamic programming
    for (int i = 1; i <= s1.length(); i++) {
        for (int j = 1; j <= s2.length(); j++) {
            int matchCost = s1.charAt(i-1) == s2.charAt(j-1) ? 0 : 
                (isVowel(s1.charAt(i-1)) && isVowel(s2.charAt(j-1)) ? 1 :
                (!isVowel(s1.charAt(i-1)) && !isVowel(s2.charAt(j-1)) ? 1 :
                (isVowel(s1.charAt(i-1)) && !isVowel(s2.charAt(j-1)) ? 3 : 3)));
            dp[i][j] = Math.min(Math.min(dp[i-1][j-1] + matchCost, dp[i-1][j] + delta), dp[i][j-1] + delta);
        }
    }

    // Trace back the optimal alignment and return it as an array of strings
    StringBuilder alignedS1 = new StringBuilder();
    StringBuilder alignedS2 = new StringBuilder();
    int i = s1.length();
    int j = s2.length();
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && dp[i][j] == dp[i-1][j-1] + (s1.charAt(i-1) == s2.charAt(j-1) ? 0 : 
                (isVowel(s1.charAt(i-1)) && isVowel(s2.charAt(j-1)) ? 1 :
                (!isVowel(s1.charAt(i-1)) && !isVowel(s2.charAt(j-1)) ? 1 :
                (isVowel(s1.charAt(i-1)) && !isVowel(s2.charAt(j-1)) ? 3 : 3))))) {
            alignedS1.append(s1.charAt(i-1));
            alignedS2.append(s2.charAt(j-1));
            i--;
            j--;
        } else if (i > 0 && dp[i][j] == dp[i-1][j] + delta) {
            alignedS1.append(s1.charAt(i-1));
            alignedS2.append("-");
            i--;
        } else if (j > 0 && dp[i][j] == dp[i][j-1] + delta) {
            alignedS1.append("-");
            alignedS2.append(s2.charAt(j-1));
            j--;
        }
    }
    String[] alignment = new String[2];
    alignment[0] = alignedS1.reverse().toString();
    alignment[1] = alignedS2.reverse().toString();
    strAlignment = alignment[0] + " " + alignment[1];
  }

  public boolean isVowel(char a)
  {
    char c = Character.toLowerCase(a);
    if(c=='a' || c=='e' || c=='i' || c=='o' ||  c=='u') 
      return true;
    else
      return false;
  }
}