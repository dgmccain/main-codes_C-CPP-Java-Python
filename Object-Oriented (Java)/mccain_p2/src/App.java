import java.util.ArrayList;
import java.util.Scanner;

public class App {
    public static void main(String[] args) {
        ArrayList<BodyMassIndex> bmiData = new ArrayList<BodyMassIndex>();

        while (moreInput()) {
            double height = getUserHeight();
            double weight = getUserWeight();

            BodyMassIndex bmi = new BodyMassIndex(height, weight);
            bmiData.add(bmi);

            displayBmiInfo(bmi);
        }

       displayBmiStatistics(bmiData);
    }

    //determine if there is more input...
    private static boolean moreInput() {
            System.out.println("Would you like to enter data?");
            System.out.print("Enter Y to continue or N to quit: ");
            Scanner quitScan = new Scanner(System.in);
            String answer = quitScan.nextLine();
            switch (answer) {
                case "Y": //case-sensitive...
                    return true;
                case "N": //case-sensitive...
                    return false;
                default:
                    System.out.println("ERROR - you need to enter Y or N...");
                    moreInput();
                    return true; //should not get called, but including a return avoids error message...
            }
    }

    //print out average bmi score info in bmi array...
    private static void displayBmiStatistics(ArrayList<BodyMassIndex> bmiData) {
        double sum = 0;
        double average;
        for (int i = 0; i < bmiData.size(); i++) {
            sum += bmiData.get(i).BMIScore;
        }
        average = sum / bmiData.size();
        average = Math.round(average * 10); //round average to 1 decimal place...
        average = average / 10;
        System.out.println("Average BMI of all users: " + average);
    }

    //print out current individual's info here...
    private static void displayBmiInfo(BodyMassIndex bmi) {
        System.out.println("BMI: " + bmi.BMIScore);
        System.out.println("Condition: " + bmi.BMICategory);
    }

    private static double getUserWeight() {
        Scanner weightScan = new Scanner(System.in);
        double resultW;
        do {
            System.out.print("Enter your weight in pounds: ");
            resultW = weightScan.nextDouble();
            weightScan.nextLine();
            if (resultW < 0) {
                System.out.println("You have to enter a positive number...");
            }
        } while (resultW < 0);
        return resultW;
    }

    private static double getUserHeight() {
        Scanner responseScan = new Scanner(System.in);
        Scanner heightScan = new Scanner(System.in);
        double resultH;
        do {
            System.out.println("Would you like to enter your height in feet?");
            System.out.print("If yes enter 'yes', if no, enter 'no': ");
            String response;
            response = responseScan.next();
            switch (response) {
                case "yes":
                    System.out.print("Enter your height in feet: ");
                    resultH = heightScan.nextDouble();
                    heightScan.nextLine();
                    if (resultH < 0) {
                        System.out.println("You have to enter a positive number...");
                    }
                    resultH = resultH * 12; //convert feet to inches...
                    System.out.print("Enter remaining inches: ");
                    resultH += heightScan.nextDouble();
                    heightScan.nextLine();
                    if (resultH < 0) {
                        System.out.println("You have to enter a positive number...");
                    }
                    break;
                case "no":
                    System.out.print("Enter your height in inches: ");
                    resultH = heightScan.nextDouble();
                    heightScan.nextLine();
                    if (resultH < 0) {
                        System.out.println("You have to enter a positive number...");
                    }
                    break;
                default:
                    System.out.println("ERROR - data entered incorrectly...");
                    resultH = 0;
                    break;
            }
        } while (resultH <= 0);
        return resultH;
    }
}
