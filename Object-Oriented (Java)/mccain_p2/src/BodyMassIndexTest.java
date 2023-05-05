import org.testng.annotations.Test;
import static org.junit.jupiter.api.Assertions.*;

public class BodyMassIndexTest {

    @Test
    void TestBodyMassIndex() {
        //test the entire bmi object...
        BodyMassIndex bmiTest = new BodyMassIndex(70.5678, 140.000);
        assertEquals(70.5678, bmiTest.BMIHeight); //rounding takes place only in BMIScore...
        assertEquals(140.0, bmiTest.BMIWeight);
        assertEquals(19.7, bmiTest.BMIScore);
        assertEquals("Normal weight", bmiTest.BMICategory);
    }

    @Test
    void TestScore() {
        //bmi score will round because bmi object is set to round all values to 1 decimal place...
        BodyMassIndex bmiTest = new BodyMassIndex(70.5678, 140.000);
        assertEquals(19.7, bmiTest.BMIScore);
    }

    @Test
    void TestCategory1() {
        BodyMassIndex bmiTest = new BodyMassIndex(74.12, 140.03953);
        assertEquals("Underweight", bmiTest.BMICategory);
    }

    @Test
    void TestCategory2() {
        BodyMassIndex bmiTest = new BodyMassIndex(70.3, 130);
        assertEquals("Normal weight", bmiTest.BMICategory);
    }

    @Test
    void TestCategory3() {
        BodyMassIndex bmiTest = new BodyMassIndex(68, 170);
        assertEquals("Overweight", bmiTest.BMICategory);
    }

    @Test
    void TestCategory4() {
        BodyMassIndex bmiTest = new BodyMassIndex(71.01, 251.301);
        assertEquals("Obese", bmiTest.BMICategory);
    }
}