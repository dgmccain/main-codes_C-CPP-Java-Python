import java.io.File;
import java.util.InputMismatchException;
import java.util.Scanner;

public class ContactApp {

    private final Scanner userInput = new Scanner(System.in);
    private final ContactList currentContactList = new ContactList();
    //initialize a temporary contact item for later use throughout the ContactApp class...
    private ContactItem currentContactItem = new ContactItem(
            "tempFirstName", "tempLastName", "tempPhoneNumber", "tempEmailAddress");
    private boolean contactsOpen = true;

    //run ContactApp class...
    public void runCApp() {
        String mainMenuChoice;

        //TasksOpen is initially true...
        while (contactsOpen) {
            //main menu...
            displayContactsMainMenu();
            mainMenuChoice = retrieveContactsMainMenuInput();
            switch (mainMenuChoice) {
                case "1" -> loadContactsMenu();
                case "2" -> branchMenu();
                case "3" -> contactsOpen = false;
                default -> System.out.println("ERROR - issue occurred with contacts main menu choice...");
            }
        }

        System.out.println("Returning to Program Main Menu...");
    }

    //menu option 1...
    public void loadContactsMenu() {
        //get filename...
        String fileName = retrieveFileNameFromUserInput();
        //load if file exists...
        if(doesFileExist(fileName)) {
            currentContactList.loadContactListFromFile(fileName);
        }
        else {
            System.out.println(fileName + " does not exist...");
        }
    }

    //menu option 2...
    public void branchMenu() {
        boolean branchMenuOpen = true;
        String branchMenuChoice;
        int index;
        String fileName;
        boolean fileExistence;
        boolean overWriteFile;

        while (branchMenuOpen) {
            displayContactListOperationsMenu();
            branchMenuChoice = retrieveContactListOperationsMenuInput();

            switch (branchMenuChoice) {
                case "1":
                    //view contacts...
                    if(!isContactListEmpty()) {
                        currentContactList.displayContactItemsInList();
                    }
                    break;
                case "2":
                    //add contact...
                    setContactItemFromUserInput();
                    currentContactList.addContactItemToList(currentContactItem);
                    break;
                case "3":
                    //edit contact...
                    if(!isContactListEmpty()) {
                        currentContactList.displayContactItemsInList();
                        //get the contact index to edit...
                        index = retrieveContactIndexFromUserInput("edit");
                        if (isContactIndexWithinBounds(index)) {
                            //set the current contact item to newly entered user input...
                            setContactItemFromUserInput();
                            //replace contact item in current contact list with the new item data...
                            currentContactList.editContactItemInList(currentContactItem, index);
                            System.out.println("contact #" + index + 1 + " was edited");
                        }
                    }
                    break;
                case "4":
                    //remove contact...
                    if(!isContactListEmpty()) {
                        currentContactList.displayContactItemsInList();
                        index = retrieveContactIndexFromUserInput("delete");
                        if (isContactIndexWithinBounds(index)) {
                            currentContactList.deleteContactItemFromList(index);
                        }
                    }
                    break;
                case "5":
                    //save contacts...
                    fileName = retrieveFileNameFromUserInput();
                    fileExistence = doesFileExist(fileName);
                    if (fileExistence) {
                        overWriteFile = shouldFileBeOverWritten(fileName);
                        if (overWriteFile) {
                            currentContactList.saveContactListToFile(fileName);
                        } else {
                            System.out.println("You chose not to overwrite " + fileName);
                        }
                    }
                    else {
                        currentContactList.saveContactListToFile(fileName);
                    }
                    break;
                case "6":
                    //return to contact main menu...
                    System.out.println("returning to contact options menu");
                    branchMenuOpen = false;
                    break;
                default:
                    System.out.println("ERROR - issue occurred with contact operation menu choice");
            }
        }
    }

    //USER FUNCTIONS
    //retrieve user input data...
    public String retrieveUserInputFirstName() {
        String userFirstName;

        System.out.print("Enter first name: ");
        userFirstName = userInput.nextLine();

        return userFirstName;
    }
    public String retrieveUserInputLastName() {
        String userLastName;

        System.out.print("Enter last name: ");
        userLastName = userInput.nextLine();

        return userLastName;
    }
    public String retrieveUserInputPhoneNumber() {
        String userPhoneNumber;

        System.out.print("Enter phone number: ");
        userPhoneNumber = userInput.nextLine();

        return userPhoneNumber;
    }
    public String retrieveUserInputEmailAddress() {
        String userEmailAddress;

        System.out.print("Enter email address: ");
        userEmailAddress = userInput.nextLine();

        return userEmailAddress;
    }
    //retrieve contact item from user input...
    public void setContactItemFromUserInput() {
        String firstname;
        String lastName;
        String phoneNumber;
        String emailAddress;
        boolean flag = true;

        while(flag) {
            firstname = retrieveUserInputFirstName();
            lastName = retrieveUserInputLastName();
            phoneNumber = retrieveUserInputPhoneNumber();
            emailAddress = retrieveUserInputEmailAddress();

            try {
                currentContactItem = new ContactItem(firstname, lastName, phoneNumber, emailAddress);
                flag = false;
            } catch (IllegalArgumentException e) {
                System.out.println(e.getMessage());
            }
        }
    }
    //retrieve contact index from user input...
    public int retrieveContactIndexFromUserInput(String msg) {
        int contactIndex = 0;
        boolean flag = true;

        while (flag) {
            System.out.print(System.lineSeparator());
            System.out.println("If you would like to cancel, please enter a negative number. Otherwise...");
            System.out.print("Enter which contact you would like to " + msg + ": ");
            try {
                contactIndex = userInput.nextInt();
                flag = false;
            } catch (InputMismatchException e) {
                System.out.println(("you did not enter a number..."));
            }
            userInput.nextLine(); //input buffer
        }

        //subtract 1 because first index is actually at 0, not 1...
        return contactIndex - 1;
    }
    public boolean isContactIndexWithinBounds(int index) {
        if (index >= 0 && index < currentContactList.getEntireContactListSize()) {
            return true;
        } else if (index == -1) {
            System.out.println("0 is not a valid contact number");
            return false;
        } else if(index < 0) {
            System.out.println("You entered a negative number");
            return false;
        } else {
            System.out.println("There are only " + currentContactList.getEntireContactListSize() + " contacts");
            return false;
        }
    }
    //retrieve file name from user input...
    public String retrieveFileNameFromUserInput() {
        String fileName;

        System.out.print("Enter a file name: ");
        fileName = userInput.nextLine();

        return fileName;
    }
    public boolean shouldFileBeOverWritten(String fileName) {
        String response;

        System.out.println("The file <" + fileName + "> already exists. Would you like to permanently overwrite it?");
        System.out.print("Enter 'yes' to continue. Enter anything else to cancel: ");
        response = userInput.nextLine();

        return response.equalsIgnoreCase("yes");
    }

    //CHECKER FUNCTIONS
    public boolean isContactListEmpty() {
        if(currentContactList.getEntireContactListSize() == 0) {
            System.out.println("Currently, there are no contacts in your list...");
            return true;
        }
        else {
            return false;
        }
    }
    //MUST be static for thorough test case checking in <TaskListTest> and
    //<ContactListTest> classes. The test cases are for saving and loading...
    public static boolean doesFileExist(String fileName) {
        File inputFile = new File(fileName);

        return inputFile.exists();
    }

    //MENU FUNCTIONS
    //main menu functions...
    public void displayContactsMainMenu() {
        System.out.print(System.lineSeparator());
        System.out.println("          - Contact Options Menu -          ");
        System.out.println("********************************************");
        System.out.println("* 1. load an existing contact list         *");
        System.out.println("* 2. view current contact list options     *");
        System.out.println("* 3. return to main menu                   *");
        System.out.println("********************************************");
    }
    public String retrieveContactsMainMenuInput() {
        String choice = "";
        Scanner choiceInput = new Scanner(System.in);
        boolean flag = true;

        //loop until a valid choice is made...
        while (flag) {
            System.out.print(System.lineSeparator());
            System.out.print("Enter your choice: ");
            choice = choiceInput.nextLine();

            //check if input is 1-3...
            if (choice.matches("[1-3]")) {
                flag = false;
            }
            else {
                System.out.println(("You must choose between the 3 menu options..."));
            }
        }

        return choice;
    }
    //branch menu functions...
    public void displayContactListOperationsMenu() {
        System.out.print(System.lineSeparator());
        System.out.println("      - Contact List Operations Menu -      ");
        System.out.println("********************************************");
        System.out.println("* 1. view current contact list             *");
        System.out.println("* 2. add a contact                         *");
        System.out.println("* 3. edit a contact                        *");
        System.out.println("* 4. delete a contact                      *");
        System.out.println("* 5. save current contact list             *");
        System.out.println("* 6. return to contact list options menu   *");
        System.out.println("********************************************");
    }
    public String retrieveContactListOperationsMenuInput() {
        String choice = "";
        boolean flag = true;

        //loop until a valid choice is made...
        while (flag) {
            System.out.print(System.lineSeparator());
            System.out.print("Enter your choice: ");
            choice = userInput.nextLine();

            //check if choice is within bounds (1-6 in menu)...
            if (choice.matches("[1-6]")) { //check if input is 1-6...
                flag = false;
            } else {
                System.out.println(("You must choose between the 6 menu options..."));
            }
        }

        return choice;
    }

    //return to MainApp.runMApp()...
}
