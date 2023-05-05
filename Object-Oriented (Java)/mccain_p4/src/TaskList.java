import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Formatter;
import java.util.Scanner;

public class TaskList {
    private final ArrayList<TaskItem> taskList = new ArrayList<>();

    //default constructor...
    public TaskList() {
        //variable is declared above and the constructor will serve no other purpose...
    }

    //ensure that user enters an int value to use as task number...
    public int getIntFromUser(String msg) {
        Scanner taskNumInput = new Scanner(System.in);
        boolean flag = true;

        //loop until valid input is entered...
        while (flag) {
            //re-print message if invalid input is entered...
            System.out.print("Enter which task number you want to " + msg + ": ");

            //make user input an int value...
            if (!taskNumInput.hasNextInt()) {
                System.out.println("invalid input...");
                taskNumInput.next();
            } else {
                //if input is valid then a false flag will stop the loop...
                flag = false;
            }
        }

        //return the user's valid input...
        return taskNumInput.nextInt();
    }

    //print array list elements...
    public void printTasks(TaskList tempList) {
        //tempList included for test cases...
        String mark = "***";

        //taskList is only accessible from within class TaskList...
        for (int i = 0; i < this.taskList.size(); i++) {
            //use (i+1) so that task #0 becomes task #1...
            System.out.print((i+1 + ")"));
            //only output "***" if the task item status is true...
            if (this.taskList.get(i).getStatus()) {
                System.out.print(" " + mark);
            }
            //output remaining task item object variables...
            System.out.println(" " + this.taskList.get(i).getTitle() +": " +
                    this.taskList.get(i).getDescription() + " [" + this.taskList.get(i).getDueDate() + "]");
        }
    }

    //add task item to task list...
    public void addTasks(TaskItem tempTask) {
        taskList.add(tempTask);
    }

    //nested function that contains <getIntFromUser>...
    public int getTaskItemNumFromUser(String msg) {
        int taskNum;

        //get input from user...
        taskNum = getIntFromUser(msg);
        //subtract 1 because displayed task #1 corresponds to list element #0...
        taskNum = taskNum - 1;

        return taskNum;
    }

    //edit task item in task list...
    public void editTasks(TaskList currentTaskList) {
        int taskNum;

        //get input from user...
        taskNum = getTaskItemNumFromUser("edit");

        //edit task after ensuring the value is within bounds...
        if (taskNum >= 0 && taskNum < taskList.size()) {
            System.out.println("Enter new info...");

            //get new input...
            TaskItem tempItem = App.setTaskItemFromUser();

            //store the new input...
            taskList.set(taskNum, tempItem);
        } else {
            System.out.println("The task number you entered does not exist...");
        }
    }

    //remove task item from task list...
    public void deleteTask() {
        int taskNum;

        //get input from user...
        taskNum = getTaskItemNumFromUser("delete");

        //delete task after ensuring the value is within bounds...
        try {
            if (taskNum >= 0 && taskNum < taskList.size()) {
                taskList.remove(taskNum);
            } else {
                throw new IllegalArgumentException();
            }
        } catch (IllegalArgumentException e) {
            System.out.println("The task number you entered does not exist...");
        }

    }

    //store list to txt file...
    public void storeTasks() {
        Scanner fileNameInput = new Scanner(System.in);
        String fileName;
        boolean shouldContinue = true;

        System.out.print("Enter a file name to save your list to: ");
        fileName = fileNameInput.nextLine();

        //check if file name already exists...
        if (App.doesFileExist(fileName)) {
            Scanner overwriteInput = new Scanner(System.in);
            String response;

            System.out.println("That file already exists. Would you like to permanently overwrite it?");
            System.out.print("Enter Y or y to continue: ");
            response = overwriteInput.nextLine();

            //confirm that the user wants to overwrite the file...
            if (response.equalsIgnoreCase("y")) {

                //create file object for deletion...
                File oldFile = new File(fileName);

                //check if file is not empty...
                if (oldFile.length() != 0) {
                    //delete the file object to clear all of its contents before overwriting...
                    if (oldFile.delete()) {
                        System.out.println("The file was successfully overwritten");
                    } else {
                        System.out.println("There was an issue overwriting the file...");
                    }
                }
                //empty file does not need to be deleted...
                else {
                    System.out.println("The file was successfully overwritten");
                }

                //continue to get new file contents...
                shouldContinue = true;
            }
            //do not continue if the user does not want to overwrite the file...
            else {
                System.out.println(fileName + " was not overwritten...");
                shouldContinue = false;
            }
        }

        if (shouldContinue) {
            //create a new txt file from above user input. The
            //txt file should contain data from the list elements...
            try (Formatter output = new Formatter(fileName)) {
                for (TaskItem taskItem : taskList) {
                    output.format("%s;%s;%s;%s;%n", taskItem.getStatus(), taskItem.getTitle(),
                            taskItem.getDescription(), taskItem.getDueDate());
                }
                //let user know that the file was saved successfully...
                System.out.println("You saved " + fileName + " successfully!");

                //these catches should not typically be triggered since exception handling is
                //already dealt with in functions <App.getFileName> and <App.doesFileExist>...
            } catch (FileNotFoundException ex) {
                System.out.println("ERROR - file was likely deleted or does not exist...");
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
        //returns to menu if the user user does not want to overwrite the file...
    }

    //load txt file contents to list...
    public void loadTasks(String fileName) {
        String lineStatus;
        String lineTitle;
        String lineDescription;
        String lineDueDate;
        boolean actualStatus;

        //start by deleting the current taskList before storing the txt data...
        for (int i = taskList.size(); i > 0; i--) {
            //remove the last element in the array list...
            taskList.remove((i-1));
        }

        //exception handling for loading file...
        try {
            Scanner fileScanner = new Scanner(new File(fileName));

            while (fileScanner.hasNextLine()) {
                //delimiter is what separates the object variables on the same line...
                fileScanner.useDelimiter(";");

                //read status...
                lineStatus = fileScanner.next();
                //read title...
                lineTitle = fileScanner.next();
                //read description...
                lineDescription = fileScanner.next();
                //read due date...
                lineDueDate = fileScanner.next();

                //buffer the next line input...
                fileScanner.nextLine();


                //returns bool value of whether lineStatus == true...
                actualStatus = lineStatus.matches("true");

                //store as new task item...
                TaskItem tempItem = new TaskItem(actualStatus, lineTitle, lineDescription, lineDueDate);
                //store task item in list...
                taskList.add(tempItem);
            }

            //this function is only called if load is successful...
            System.out.println(fileName + " loaded successfully!");

        } catch (FileNotFoundException e) {
            System.out.println("An error occurred when trying to load your file...");
        }
    }

    //set mark/unmark status...
    public void setStatus(String msg, String status, TaskList currentTaskList) {
        int taskNum;
        String tempTitle;
        String tempDescription;
        String tempDueDate;
        boolean actualStatus = (status.matches("true"));

        taskNum = getTaskItemNumFromUser(msg);

        if (taskNum >= 0 && taskNum < taskList.size()) {
            tempTitle = this.taskList.get(taskNum).getTitle();
            tempDescription = this.taskList.get(taskNum).getDescription();
            tempDueDate = this.taskList.get(taskNum).getDueDate();

            //create a new task item with updated status...
            TaskItem tempTaskItem = new TaskItem(actualStatus, tempTitle, tempDescription, tempDueDate);

            //store the new task item in the list at element of old item...
            this.taskList.set(taskNum, tempTaskItem);
        } else {
            System.out.println("The task number you entered does not exist...");
        }
    }

    //return size of the array list...
    public int getListSize(TaskList tempList) {
        //used exclusively for test case to serve as temList.size() function. This is
        //because size() is not equally easy to call from within test case classes...
        return this.taskList.size();
    }
}
