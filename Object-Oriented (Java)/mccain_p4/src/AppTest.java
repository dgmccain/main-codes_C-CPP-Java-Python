import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import java.util.Scanner;

class AppTest {
    //===================================================================
    //The following should be tests for functions within the App class...
    //===================================================================

    @Test
    public void TestUnsuccessfulMainMenuChoice() {
        //enter a char or out-of-bounds int...
    }

    @Test
    public void TestMainMenuChoice1() {
        //test for if int 1 is entered...
    }

    @Test
    public void TestForIfFileDoesNotLoad() {
        //enter the file name of a txt file that does not exist...
        //expect print to console confirming the file does not exist...
    }

    @Test
    public void TestForIfFileLoads() {
        //enter the file name of a txt file that already exists...
        //expect print to console confirming the file exists/loaded...
    }

    @Test
    public void TestMainMenuChoice2() {
        //test for if int 2 is entered...
    }

    @Test
    public void TestMainMenuChoice3() {
        //test for if int 3 is entered...
        //program should close...
    }
}