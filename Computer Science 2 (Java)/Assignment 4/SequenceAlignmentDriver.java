/* Name:
 * Dr. Andrew Steinberg
 * COP3503 Spring 2023
 * Programming Assignment 4
 */


public class SequenceAlignmentDriver {
    
    
    public static void main(String args[])
    {
        int pass = 0;
        
        System.out.println("Beginning Test Cases...");
        System.out.println("****************************************");
        System.out.println("Starting with a test case 1...");
        
        SequenceAlignment test = new SequenceAlignment("mean", "name");
        test.computeAlignment(2);
        
        if(test.getAlignment().compareTo("mean- n-ame") == 0)
        {
            System.out.println("Test 1 Passed!"); 
            ++pass;
        }
        
        System.out.println("Ending test case 1...");
        System.out.println("****************************************");
        System.out.println("Starting with a test case 2...");
        
        SequenceAlignment test2 = new SequenceAlignment("across", "accross");     
        test2.computeAlignment(2);

        if(test2.getAlignment().compareTo("a-cross accross") == 0)
        {
            System.out.println("Test 2 Passed!");
            ++pass;
        }
        
        System.out.println("Ending test case 2...");
        System.out.println("****************************************");
        System.out.println("Starting with a test case 3...");
        
        SequenceAlignment test3 = new SequenceAlignment("four", "for");
        test3.computeAlignment(2);
        
        if(test3.getAlignment().compareTo("four fo-r") == 0)
        {
            System.out.println("Test 3 Passed!");
            ++pass;
        }
        
        System.out.println("Ending test case 3...");
        System.out.println("****************************************");
        System.out.println("Starting with a test case 4...");
        
        SequenceAlignment test4 = new SequenceAlignment("runnnning", "running");
        test4.computeAlignment(2);
       
        
        if(test4.getAlignment().compareTo("runnnning ru--nning") == 0)
        {
            System.out.println("Test 4 Passed!");
            ++pass;
        }
        
        System.out.println("Ending test case 4...");
        System.out.println("****************************************");
        System.out.println("Starting with a test case 5...");
        
        
        SequenceAlignment test5 = new SequenceAlignment("programming", "programmmming");       
        test5.computeAlignment(2);
        
        if(test5.getAlignment().compareTo("progra--mming programmmming") == 0)
        {
            System.out.println("Test 5 Passed!");
            ++pass;
        }
        
        
        System.out.println("Ending test case 5...");
        System.out.println("****************************************");
        System.out.println("Now checking test case results...");
        
        if(pass == 5)
            System.out.println("WOOHOO ALL THE TEST CASES PASSED! :)");
        else
            System.out.println("Oh no! Not all the test cases passed. :(");
    }
    
}
