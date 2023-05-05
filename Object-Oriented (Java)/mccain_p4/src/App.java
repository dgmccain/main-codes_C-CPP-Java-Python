import java.io.File;
import java.util.Scanner;

public class App {

    //main menu functions...
    public static void displayMainMenu() {
        System.out.print(System.lineSeparator());
        System.out.println("              - Main Menu -              ");
        System.out.println("*****************************************");
        System.out.println("* 1. load an existing task list         *");
        System.out.println("* 2. view current task list options     *");
        System.out.println("* 3. quit the program                   *");
        System.out.println("*****************************************");
    }
    public static String mainMenuInput() {
        String choice = "";
        Scanner choiceInput = new Scanner(System.in);
        boolean flag = true;

        //loop until a valid choice is made...
        while (flag) {
            System.out.print("\nEnter your choice: ");
            choice = choiceInput.nextLine();

            //exception handling...
            try {
                //check if input is 1-3...
                if (choice.matches("[1-3]")) {
                    flag = false;
                }
                else {
                    throw new InvalidChoiceException();
                }
            } catch (InvalidChoiceException e) {
                System.out.println("You must choose between the 3 menu options...");
            }
        }

        return choice;
    }

    //branch menu functions...
    public static boolean branchFromMainMenu(String mainMenuChoice, TaskList currentTaskList) {
        String createListChoice;
        boolean shouldGoToMainMenu = false;

        //NOTE: Unconventional switch case was used to
        //streamline handling file loading sequence...
        switch(mainMenuChoice) {
            case "1":
                //load existing task list...
                String tempFileName = getFileName();
                //check if the file entered exists...
                boolean doesExist = doesFileExist(tempFileName);

                if (doesExist) {
                    //load file contents into list...
                    currentTaskList.loadTasks(tempFileName);
                }
                else {
                    System.out.println("The file name you entered does not exist...");
                }
                //regardless of whether or not the file was found, the
                //main menu should be called after the loading process...
                shouldGoToMainMenu = true;
                break;
            //case 1 should only break if there is an error reading the file name. The code
            //should then bring up the main menu again. Otherwise, new menu functions from
            //case 2 should be invoked using the data that was loaded from the txt file...
            case "2":
                //open create list menu...
                displayCreateListMenu();
                createListChoice = createListMenuInput();
                shouldGoToMainMenu = determineListMenuOption(createListChoice, currentTaskList);
                break;
            case "3":
                //quitting the program is handled in the App's main function
                //before this function is ever called...
                break;
            default:
                System.out.println("Error occurred when determining choice...");
        }

        return shouldGoToMainMenu;
    }
    public static void displayCreateListMenu() {
        System.out.print(System.lineSeparator());
        System.out.println("        - Task List Menu -        ");
        System.out.println("**********************************");
        System.out.println("* 1. view current task list      *");
        System.out.println("* 2. add a task                  *");
        System.out.println("* 3. edit a task                 *");
        System.out.println("* 4. delete a task               *");
        System.out.println("* 5. set a task as complete      *");
        System.out.println("* 6. set a task as incomplete    *");
        System.out.println("* 7. save current task list      *");
        System.out.println("* 8. quit to main menu           *");
        System.out.println("**********************************");
    }
    public static String createListMenuInput() {
        String choice = "";
        Scanner choiceInput = new Scanner(System.in);
        boolean flag = true;

        //loop until a valid choice is made...
        while (flag) {
            System.out.print("\nEnter your choice: ");
            choice = choiceInput.nextLine();

            //exception handling...
            try {
                //check if input is 1-8...
                if (choice.matches("[1-8]")) {
                    flag = false;
                } else {
                    throw new InvalidChoiceException();
                }
            } catch (InvalidChoiceException e) {
                System.out.println("You must choose between the 8 menu options...");
            }
        }

        return choice;
    }
    public static boolean determineListMenuOption(String choice, TaskList currentTaskList) {
        boolean shouldGoToMainMenu = false;
        switch (choice) {
            case "1" -> currentTaskList.printTasks(currentTaskList); //view current task list...
            case "2" -> { //add task item to task list...
                //create a temporary task item populated from a function...
                TaskItem tempTaskItem = setTaskItemFromUser();
                //store task item in task array list...
                currentTaskList.addTasks(tempTaskItem);
            }
            case "3" -> currentTaskList.editTasks(currentTaskList); //edit a task item...
            case "4" -> currentTaskList.deleteTask(); //delete a task item...
            case "5" -> currentTaskList.setStatus("mark", "true", currentTaskList); //mark a task item...
            case "6" -> currentTaskList.setStatus("unmark", "false", currentTaskList);//unmark a task item...
            case "7" -> currentTaskList.storeTasks(); //save current task list to txt file...
            case "8" -> shouldGoToMainMenu = true; //return to main menu...
            default -> System.out.println("Error occurred when trying to determine your choice...");
        }
        //TaskList functions are non-accessible at the moment...

        return shouldGoToMainMenu;
    }

    //App class getters for task item data...
    public static String getTitle() {
        Scanner titleInput = new Scanner(System.in);
        String title;

        System.out.print("Enter a title: ");
        title = titleInput.nextLine();

        return title;
    }
    public static String getDescription() {
        Scanner descriptionInput = new Scanner(System.in);
        String description;

        System.out.print("Enter a description: ");
        description = descriptionInput.nextLine();

        return description;
    }
    public static String getDueDate() {
        Scanner dueDateInput = new Scanner(System.in);
        String dueDate;

        System.out.print("Enter a due date [yyyy-MM-dd] format: ");
        dueDate = dueDateInput.nextLine();

        return dueDate;
    }

    //App class setter for task item data...
    public static TaskItem setTaskItemFromUser() {
        //get user input...
        boolean tempStatus = false; //new task items shouls not be marked...
        String tempTitle = getTitle();
        String tempDescription = getDescription();
        String tempDueDate = getDueDate();
        boolean flag = true;

        //create task item from the above variables, then return the object...
        TaskItem tempTask = new TaskItem(tempStatus, tempTitle, tempDescription, tempDueDate);

        //do not loop if valid input is entered...
        if (tempTask.isTitleValid(tempTitle) && tempTask.isDueDateValid(tempDueDate)) {
            flag = false;
        }
        else {
            //loop until a valid task item is entered...
            while (flag) {
                //get user data again...
                tempTitle = getTitle();
                tempDescription = getDescription();
                tempDueDate = getDueDate();

                //make a new task item object with updated input...
                tempTask = new TaskItem(tempStatus, tempTitle, tempDescription, tempDueDate);

                //stop looping once valid input is entered...
                if (tempTask.isTitleValid(tempTitle) && tempTask.isDueDateValid(tempDueDate)) {
                    flag = false;
                }
            }
        }

        return tempTask;
    }

    //file handling
    public static String getFileName() {
        String fileName;
        Scanner fileNameInput = new Scanner(System.in);

        System.out.print("Enter the name of the file you want to load: ");
        fileName = fileNameInput.nextLine();

        return fileName;
    }
    public static boolean doesFileExist(String fileName) {
        File inputFile = new File(fileName);

        return inputFile.exists();
    }

    //the following class is used for exception handling...
    static class InvalidChoiceException extends IllegalArgumentException {
        public InvalidChoiceException() {
            super();
        }
    }

    //main method...
    public static void main(String[] args) {
        boolean quitKey = false;
        String menuChoice = null;
        boolean mainMenuOpen = true;

        TaskList currentTaskList = new TaskList();

        while (!quitKey) {
            //start with main menu...
            while(mainMenuOpen) {
                displayMainMenu();
                menuChoice = mainMenuInput();
                mainMenuOpen = false; //close after user choice is made...
            }

            //determine what choice was made in the main menu...
            if (menuChoice.matches("3")) {
                quitKey = true;
            }
            else {
                mainMenuOpen = branchFromMainMenu(menuChoice, currentTaskList);
            }

        }

        System.out.println("Program closing...");
    }
}