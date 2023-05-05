import java.util.Scanner;
import java.util.ArrayList;

public class Main {
    public static void main(String[] args) {
        //variables to be passed to other methods...
        Scanner quitScan = new Scanner(System.in);
        ArrayList<Contact> contacts = new ArrayList<>();

        mainMenu(quitScan, contacts); //menu method with a self-contained loop for recursion...

       Contact.printContacts(contacts); //output entered contact information...
    }

    //NOTE: must be declared static because of use within main...
    public static void mainMenu(Scanner quitScan, ArrayList<Contact> contacts) {
        int quitKey;
        do {
            //obtain data...
            System.out.print("Would you like to enter info? Enter 1 to continue or 2 to quit: ");
            quitKey = quitScan.nextInt();

            //enhanced switch case...
            switch (quitKey) {
                case 1 -> {
                    Contact c = new Contact(); //create new Contact object...
                    contacts.add(c); //add to array list...
                }
                case 2 -> System.out.println("You chose to stop entering data...");
                case 3 -> System.out.println("ERROR - You did not enter 1 or 2...");
            }
        } while (quitKey != 2); //stop entering data if 2 is entered...
    }
}