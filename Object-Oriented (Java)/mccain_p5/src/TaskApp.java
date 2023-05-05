import java.io.File;
import java.util.InputMismatchException;
import java.util.Scanner;

public class TaskApp {

    private final Scanner userInput = new Scanner(System.in);
    private final TaskList currentTaskList = new TaskList();
    //initialize a temporary task item for later use throughout the TaskApp class...
    private TaskItem currentTaskItem = new TaskItem("tempTitle", "tempDesc", "2020-01-01");
    private boolean TasksOpen = true;

    //run TaskApp class...
    public void runTApp() {
        String mainMenuChoice;

        //TasksOpen is initially true...
        while (TasksOpen) {
            //main menu...
            displayTasksMainMenu();
            mainMenuChoice = retrieveTasksMainMenuInput();
            switch (mainMenuChoice) {
                case "1" -> loadTaskMenu();
                case "2" -> branchMenu();
                case "3" -> TasksOpen = false;
                default -> System.out.println("ERROR - issue occurred with task options menu choice...");
            }
        }

        System.out.println("Returning to program main menu...");
    }

    //menu option 1...
    public void loadTaskMenu() {
        //get filename...
        String fileName = retrieveFileNameFromUserInput();
        //load if file exists...
        if(doesFileExist(fileName)) {
            currentTaskList.loadTaskListFromFile(fileName);
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
            displayTaskListOperationsMenu();
            branchMenuChoice = retrieveTaskListOperationsMenuInput();

            switch (branchMenuChoice) {
                case "1":
                    //view tasks...
                    if(!isTaskListEmpty()) {
                        currentTaskList.displayTaskItemsInList();
                    }
                    break;
                case "2":
                    //add task...
                    setTaskItemFromUserInput();
                    currentTaskList.addTaskItemToList(currentTaskItem);
                    break;
                case "3":
                    //edit task...
                    if(!isTaskListEmpty()) {
                        currentTaskList.displayTaskItemsInList();
                        //get the task number to edit...
                        index = retrieveTaskNumberFromUserInput("edit");
                        if (isTaskNumberWithinBounds(index)) {
                            //set the current task item to newly entered user input...
                            setTaskItemFromUserInput();
                            //replace task item in current task list with the new item data...
                            currentTaskList.editTaskItemInList(currentTaskItem, index);
                            System.out.println("task #" + index + 1 + " was edited");
                        }
                    }
                    break;
                case "4":
                    //remove task...
                    if(!isTaskListEmpty()) {
                        currentTaskList.displayTaskItemsInList();
                        index = retrieveTaskNumberFromUserInput("delete");
                        if (isTaskNumberWithinBounds(index)) {
                            currentTaskList.deleteTaskItemFromList(index);
                        }
                    }
                    break;
                case "5":
                    //mark tasks...
                    if(!isUnmarkedListEmpty()) {
                        currentTaskList.displayUnmarkedTaskItemsInList();
                        index = retrieveTaskNumberFromUserInput("mark");
                        if (isTaskNumberWithinBounds(index)) {
                            currentTaskList.markTaskItemInList(index);
                        }
                    }
                    break;
                case "6":
                    //unmark tasks...
                    if(!isMarkedListEmpty()) {
                        currentTaskList.displayMarkedTaskItemsInList();
                        index = retrieveTaskNumberFromUserInput("unmark");
                        if (isTaskNumberWithinBounds(index)) {
                            currentTaskList.unmarkTaskItemInList(index);
                        }
                    }
                    break;
                case "7":
                    //save tasks...
                    fileName = retrieveFileNameFromUserInput();
                    fileExistence = doesFileExist(fileName);
                    if (fileExistence) {
                        overWriteFile = shouldFileBeOverWritten(fileName);
                        if (overWriteFile) {
                            currentTaskList.saveTaskListToFile(fileName);
                        } else {
                            System.out.println("You chose not to overwrite " + fileName);
                        }
                    }
                    else {
                        currentTaskList.saveTaskListToFile(fileName);
                    }
                    break;
                case "8":
                    //return to task main menu...
                    System.out.println("returning to task main menu");
                    branchMenuOpen = false;
                    break;
                default:
                    System.out.println("ERROR - issue occurred with task operation menu choice");
            }
        }
    }

    //USER FUNCTIONS
    //retrieve user input data...
    public String retrieveUserInputTitle() {
        String userTitle;

        System.out.print("Enter a Title: ");
        userTitle = userInput.nextLine();

        return userTitle;
    }
    public String retrieveUserInputDescription() {
        String userDescription;

        System.out.print("Enter a Description: ");
        userDescription = userInput.nextLine();

        return userDescription;
    }
    public String retrieveUserInputDueDate() {
        String userDueDate;

        System.out.print("Enter a Due Date: ");
        userDueDate = userInput.nextLine();

        return userDueDate;
    }
    //retrieve task item from user input...
    public void setTaskItemFromUserInput() {
        String title;
        String description;
        String dueDate;
        boolean flag = true;

        while(flag) {
            title = retrieveUserInputTitle();
            description = retrieveUserInputDescription();
            dueDate = retrieveUserInputDueDate();

            try {
                currentTaskItem = new TaskItem(title, description, dueDate);
                flag = false;
            } catch (IllegalArgumentException e) {
                System.out.println(e.getMessage());
            }
        }
    }
    //retrieve task number from user input...
    public int retrieveTaskNumberFromUserInput(String msg) {
        int taskNum = 0;
        boolean flag = true;

        while (flag) {
            System.out.print(System.lineSeparator());
            System.out.println("If you would like to cancel, please enter a negative number. Otherwise...");
            System.out.print("Enter the task number you would like to " + msg + ": ");
            try {
                taskNum = userInput.nextInt();
                flag = false;
            } catch (InputMismatchException e) {
                System.out.println(("you did not enter a valid task number..."));
            }
            userInput.nextLine(); //input buffer
        }

        //subtract 1 because first index is actually at 0, not 1...
        return taskNum - 1;
    }
    public boolean isTaskNumberWithinBounds(int index) {
        if (index >= 0 && index < currentTaskList.getEntireTaskListSize()){
            return true;
        } else if (index == -1) {
            System.out.println("0 is not a valid task number");
            return false;
        } else if(index < 0) {
            System.out.println("You entered a negative number");
            return false;
        } else {
            System.out.println("There are only " + currentTaskList.getEntireTaskListSize() + " tasks");
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
    public boolean isTaskListEmpty() {
        if(currentTaskList.getEntireTaskListSize() == 0) {
            System.out.println("Currently, there are no tasks in your list...");
            return true;
        }
        else {
            return false;
        }
    }
    public boolean isMarkedListEmpty() {
        if(currentTaskList.getMarkedTaskListSize() == 0) {
            System.out.println("Currently, there are no complete tasks...");
            return true;
        }
        else {
            return false;
        }
    }
    public boolean isUnmarkedListEmpty() {
        if(currentTaskList.getUnmarkedTaskListSize() == 0) {
            System.out.println("Currently, there are no incomplete tasks...");
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
    public void displayTasksMainMenu() {
        System.out.print(System.lineSeparator());
        System.out.println("          - Task Options Menu -          ");
        System.out.println("*****************************************");
        System.out.println("* 1. load an existing task list         *");
        System.out.println("* 2. view current task list options     *");
        System.out.println("* 3. return to main menu                *");
        System.out.println("*****************************************");
    }
    public String retrieveTasksMainMenuInput() {
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
    public void displayTaskListOperationsMenu() {
        System.out.print(System.lineSeparator());
        System.out.println("      - Task List Operations Menu -      ");
        System.out.println("*****************************************");
        System.out.println("* 1. view current task list             *");
        System.out.println("* 2. add a task                         *");
        System.out.println("* 3. edit a task                        *");
        System.out.println("* 4. delete a task                      *");
        System.out.println("* 5. set a task as complete             *");
        System.out.println("* 6. set a task as incomplete           *");
        System.out.println("* 7. save current task list             *");
        System.out.println("* 8. return to task list options menu   *");
        System.out.println("*****************************************");
    }
    public String retrieveTaskListOperationsMenuInput() {
        String choice = "";
        boolean flag = true;

        //loop until a valid choice is made...
        while (flag) {
            System.out.print(System.lineSeparator());
            System.out.print("Enter your choice: ");
            choice = userInput.nextLine();

            //check if choice is within bounds (1-8 in menu)...
            if (choice.matches("[1-8]")) { //check if input is 1-8...
                flag = false;
            } else {
                System.out.println(("You must choose between the 8 menu options..."));
            }
        }

        return choice;
    }

    //return to MainApp.runMApp()...
}