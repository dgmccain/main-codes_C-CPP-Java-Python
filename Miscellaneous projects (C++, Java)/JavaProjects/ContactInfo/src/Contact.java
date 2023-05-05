import java.util.ArrayList;
import java.util.Scanner;

public class Contact {
    //variables have to be protected for use in print method within main...
    protected String name;
    protected String emailAddress;
    protected String phoneNumber; //can also be changed to int of 10 digits instead...

    //constructor...
    public Contact() {
        this.name = getName();
        this.emailAddress = getEmailAddress();
        this.phoneNumber = getPhoneNumber();
    }

    public String getName() {
        Scanner nameScan = new Scanner(System.in);
        String nameInput;

        System.out.print("Enter your name: ");
        nameInput = nameScan.next();

        return nameInput;
    }

    public String getEmailAddress() {
        Scanner emailScan = new Scanner(System.in);
        String emailInput;

        System.out.print("Enter your email address: ");
        emailInput = emailScan.next();

        return emailInput;
    }

    //as previously mentioned, phone number can be changed to double type instead...
    //consider adding a parsing process to check for if int values entered...
    public String getPhoneNumber() {
        Scanner numberScan = new Scanner(System.in);
        String numberInput;

        System.out.print("Enter your phone number: ");
        numberInput = numberScan.next();

        return numberInput;
    }

    //print arraylist containing contacts' info, created in main method...
    //NOTE: must be declared static because of use within main...
    public static void printContacts(ArrayList<Contact> contacts) {
        System.out.println("\n*** Data entered ***");
        for (int i = 0; i < contacts.size(); i++) {
            System.out.println("===============================================");
            System.out.println("[Contact #" + (i+1) + "] info...");
            System.out.println("Name: " + contacts.get(i).name);
            System.out.println("Email Address: " + contacts.get(i).emailAddress);
            System.out.println("Phone Number: " + contacts.get(i).phoneNumber);
            System.out.println("===============================================");
        }
    }
}
