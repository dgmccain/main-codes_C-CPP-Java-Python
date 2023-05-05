import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Formatter;
import java.util.List;
import java.util.Scanner;

public class TaskList {
    private final List<TaskItem> taskList = new ArrayList<>();

    public TaskList() {
        //default constructor...
    }

    //ADD
    //add item to list...
    public void addTaskItemToList(TaskItem taskItem) {
        taskList.add(taskItem);
    }

    //UPDATE
    //edit items in list...
    public void editTaskItemInList(TaskItem updatedTaskItem, int location) {
        try {
            this.taskList.get(location).setTitle(updatedTaskItem.getTitle());
            this.taskList.get(location).setDescription(updatedTaskItem.getDescription());
            this.taskList.get(location).setDueDate(updatedTaskItem.getDueDate());
            this.taskList.get(location).setStatusAsIncomplete();
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }
    }

    //REMOVE
    //delete item from list...
    public void deleteTaskItemFromList(int index) {
        taskList.remove(index);
        System.out.println("task #" + (index + 1) + " was deleted");
    }

    //VIEW
    //display entire list contents...
    public void displayTaskItemsInList() {
        String mark = "***";

        for (int i = 0; i < this.taskList.size(); i++) {
            //use (i+1) so that task #0 becomes task #1...
            System.out.print((i + 1 + ")"));
            //only output "***" if the task item status is true...
            if (this.taskList.get(i).getStatus()) {
                System.out.print(" " + mark);
            }
            //output remaining task item object variables...
            System.out.println(" " + this.taskList.get(i).getTitle() + ": " +
                    this.taskList.get(i).getDescription() + " [" + this.taskList.get(i).getDueDate() + "]");
        }
    }
    //display marked/unmarked task items in task list...
    public void displayMarkedTaskItemsInList() {
        String mark = "***";

        for (int i = 0; i < this.taskList.size(); i++) {
            //only output "***" if the task item status is true...
            if (this.taskList.get(i).getStatus()) {
                //use (i+1) so that task #0 becomes task #1...
                System.out.print((i + 1 + ")"));
                System.out.print(" " + mark);

                //only output completed task items...
                System.out.println(" " + this.taskList.get(i).getTitle() + ": " +
                        this.taskList.get(i).getDescription() + " [" + this.taskList.get(i).getDueDate() + "]");
            }
        }
    }
    public void displayUnmarkedTaskItemsInList() {
        for (int i = 0; i < this.taskList.size(); i++) {
            //only output task item if the status is false...
            if (!this.taskList.get(i).getStatus()) {
                //use (i+1) so that task #0 becomes task #1...
                System.out.print((i + 1 + ")"));

                //only output incomplete task items...
                System.out.println(" " + this.taskList.get(i).getTitle() + ": " +
                        this.taskList.get(i).getDescription() + " [" + this.taskList.get(i).getDueDate() + "]");
            }
        }
    }

    //SET
    //set task item in task list to marked/unmarked...
    public void markTaskItemInList(int index) {
        int taskNum = index + 1;

        if (index >= 0 && index < getEntireTaskListSize()) {
            //if status is unmarked...
            if (!this.taskList.get(index).getStatus()) {
                this.taskList.get(index).setStatusAsComplete();
                System.out.println("task #" + taskNum + " was marked...");
            } else {
                System.out.println("task #" + taskNum + " was already marked...");
            }
        } else {
            throw new IllegalArgumentException("ERROR - index out of bounds. Did not mark task");
        }
    }
    public void unmarkTaskItemInList(int index) {
        int taskNum = index + 1;

        if (index >= 0 && index < getEntireTaskListSize()) {
            //if status is marked...
            if (this.taskList.get(index).getStatus()) {
                this.taskList.get(index).setStatusAsIncomplete();
                System.out.println("task #" + taskNum + " was unmarked...");
            } else {
                System.out.println("task #" + taskNum + " was already unmarked...");
            }
        } else {
            throw new IllegalArgumentException("ERROR - index out of bounds. Did not unmark task");
        }
    }

    //GET
    //function for getting sizes of list...
    public int getEntireTaskListSize() {
        return taskList.size();
    }
    public int getMarkedTaskListSize() {
        int count = 0;

        for (int i = 0; i < taskList.size(); i++) {
            //if status is marked, then add to count...
            if(taskList.get(i).getStatus()) {
                count++;
            }
        }

        return count;
    }
    public int getUnmarkedTaskListSize() {
        int count = 0;

        for (int i = 0; i < taskList.size(); i++) {
            //if status is unmarked, then add to count...
            if(!taskList.get(i).getStatus()) {
                count++;
            }
        }

        return count;
    }
    //functions for getting item data from list...
    public String getTaskItemTitleFromList(int index) {
        return this.taskList.get(index).getTitle();
    }
    public String getTaskItemDescriptionFromList(int index) {
        return this.taskList.get(index).getDescription();
    }
    public String getTaskItemDueDateFromList(int index) {
        return this.taskList.get(index).getDueDate();
    }
    public boolean getTaskItemStatusFromList(int index) {
        return this.taskList.get(index).getStatus();
    }

    //STORE
    //store list to file...
    public void saveTaskListToFile(String fileName) {
        //only proceed if taskList contains data...
        if(taskList.size() > 0) {
            if (clearExistingTaskFileContentsBeforeSaving(fileName)) {
                //only continue if the file is blank to ensure that contents are not compromised...
                try (Formatter output = new Formatter(fileName)) {
                    //store task items in file...
                    for (TaskItem taskItem : taskList) {
                        output.format("%s;%s;%s;%s;%n", taskItem.getStatus(), taskItem.getTitle(),
                                taskItem.getDescription(), taskItem.getDueDate());
                    }
                    //let user know that the file was saved successfully...
                    System.out.println("You saved " + fileName + " successfully!");
                } catch (FileNotFoundException ex) {
                    System.out.println("ERROR - file was likely deleted or does not exist...");
                } catch (Exception ex) {
                    System.out.println("ERROR - file handling exception has occurred");
                    ex.printStackTrace();
                }
            }
        } else {
            System.out.println("You do not have a task list of items to save...");
        }
    }
    public boolean clearExistingTaskFileContentsBeforeSaving(String fileName) {
        boolean fileWasCleared = true;

        //create file object for deletion...
        File oldFile = new File(fileName);

        //check if file is not empty...
        if (oldFile.length() != 0) {
            //delete the file object to clear all of its contents before overwriting...
            if (oldFile.delete()) {
                System.out.println("The file was successfully overwritten");
            } else {
                fileWasCleared = false;
                System.out.println("There was an issue overwriting the file...");
            }
        }
        //empty file does not need to be deleted...
        else {
            System.out.println("The file was successfully overwritten");
        }

        return fileWasCleared;
    }

    //LOAD
    //load list from file...
    public void loadTaskListFromFile(String fileName) {
        String lineStatus;
        String lineTitle;
        String lineDescription;
        String lineDueDate;
        boolean actualStatus;

        //start by deleting the current taskList before loading from file contents...
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

                //store as new task item (using non-default constructor)...
                TaskItem tempItem = new TaskItem(lineTitle, lineDescription, lineDueDate, actualStatus);
                //store task item in list...
                taskList.add(tempItem);
            }

            //this function is only called if load is successful...
            System.out.println(fileName + " loaded successfully!");

        } catch (FileNotFoundException e) {
            System.out.println("An error occurred when trying to load your file...");
        }
    }
}