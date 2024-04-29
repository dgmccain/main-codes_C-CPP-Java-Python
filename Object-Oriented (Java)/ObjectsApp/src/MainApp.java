import java.util.Scanner;

public class MainApp {
    private final Scanner userInput = new Scanner(System.in);

    //program entry point...
    public static void main(String[] args) {
        MainApp MApp = new MainApp();
        MApp.runMApp();
    }

    //RUN PROGRAM
    public void runMApp() {
        boolean isMainMenuOpen = true;
        String mainMenuChoice;

        while(isMainMenuOpen) {
            displayMainMenu();
            mainMenuChoice = retrieveMainMenuInput();

            switch(mainMenuChoice) {
                case "1":
                    //if task list is chosen...
                    TaskApp TApp = new TaskApp();
                    TApp.runTApp();
                    break;
                case "2":
                    //if contacts list is chosen...
                    ContactApp CApp = new ContactApp();
                    CApp.runCApp();
                    break;
                case "3":
                    System.out.println("program closing...");
                    isMainMenuOpen = false;
                    break;
                default:
                    System.out.println("ERROR - issue occurred with main menu choice");
            }
        }
    }

    //MAIN MENU FUNCTIONS
    public void displayMainMenu() {
        System.out.print(System.lineSeparator());
        System.out.println("           - Main Menu -           ");
        System.out.println("===================================");
        System.out.println("| 1. open the task list menu      |");
        System.out.println("| 2. open the contact list menu   |");
        System.out.println("| 3. quit the program             |");
        System.out.println("===================================");
        System.out.print(System.lineSeparator());
    }
    public String retrieveMainMenuInput() {
        String choice = "";
        boolean flag = true;

        //loop until a valid choice is made...
        while (flag) {
            System.out.print(System.lineSeparator());
            System.out.print("Enter your choice: ");
            choice = userInput.nextLine();

            //check if choice is within bounds (1-3 in menu)...
            if (choice.matches("[1-3]")) { //check if input is 1-3...
                flag = false;
            } else {
                System.out.println(("You must choose from the 3 main menu options..."));
            }
        }

        return choice;
    }
}
