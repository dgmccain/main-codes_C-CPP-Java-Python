import java.time.LocalDate;

public class TaskItem {
    private String title;
    private String description;
    private String dueDate;
    private boolean status; //status is complete/incomplete task status...

    //DEFAULT CONSTRUCTOR (for user input)...
    public TaskItem(String title, String description, String dueDate) {
        if (isTitleValid(title)) {
            this.title = title;
        } else {
            throw new IllegalArgumentException("INVALID - you did not enter a title");
        }

        this.description = description;

        if (isDueDateValid(dueDate)) {
            this.dueDate = dueDate;
        } else {
            throw new IllegalArgumentException("INVALID - you did not enter a correct due date");
        }

        //TaskApp should not retrieve status from user input when a new task
        //item is created (because new tasks should not be set as complete),
        //so the default status should be set to false (incomplete)...
        this.status = false;
    }

    //CONSTRUCTOR (with status included as a parameter)...
    public TaskItem(String title, String description, String dueDate, boolean status) {
        this.title = title;
        this.description = description;
        this.dueDate = dueDate;
        this.status = status;
    }

    //INPUT VALIDATION
    public boolean isTitleValid(String title) {
        //check if title is empty...
        return !title.matches("");
    }
    public boolean isDueDateValid(String dueDate) {
        //variables used in the event when user enters '/' instead of '-' for date...
        char[] correctDueDate = dueDate.toCharArray();
        StringBuilder dueDateBuilder = new StringBuilder("");

        //TEMPORARILY adjust user input from '/' to be changed to '-' instead, so
        //that LocalDate can be correctly parsed with the entered dueDate...
        if (dueDate.matches("[0-9]{4}[/][0-1][0-9][/][0-3][0-9]")) {
            correctDueDate[4] = '-';
            correctDueDate[7] = '-';

            //stopping point is before 10, because there are 10 chars in yyyy-MM-dd format and
            //the index at 0 should be included as the 1st char entry point within the loop...
            for (int i = 0; i < 10; i++) {
                dueDateBuilder.append(correctDueDate[i]);
            }
            dueDate = dueDateBuilder.toString();
        }

        //after '-' format is verified, check if date is legitimate...
        LocalDate dateChecker;
        try {
            dateChecker = LocalDate.parse(dueDate);
            return true;
        } catch (java.time.format.DateTimeParseException e) {
            return false;
        }
        //NOTE: the user's preferred choice of yyyy/MM/dd is stored in the TaskItem
        //object, because this function's dueDate is only temporarily used to return
        //a boolean type value. To store the dueDate with format yyyy-MM-dd instead
        //of yyyy/MM/dd, insert <this.dueDate = dueDate;> after the following line:
        //<dateChecker = LocalDate.parse(dueDate);> and before: <return true;>. Then
        //remove the line: <this.dueDate = dueDate;> from the TaskItem constructor.
        //Otherwise, the constructor will continue to set the TaskItem object's dueDate
        //back to the user's yyyy/MM/dd format...
    }

    //SETTERS
    //setTitle() and setDueDate() catch exceptions in the TaskApp class...
    public void setTitle(String title) {
        if (isTitleValid(title)) {
            this.title = title;
        } else {
            throw new IllegalArgumentException("You did not enter a title - Task was not created...");
        }
    }
    public void setDescription(String description) {
        this.description = description;
    }
    public void setDueDate(String dueDate){
        if(isDueDateValid(dueDate)) {
            this.dueDate = dueDate;
        } else {
            throw new IllegalArgumentException("You must enter a valid due date...");
        }
    }
    public void setStatusAsComplete() {
        this.status = true;
    }
    public void setStatusAsIncomplete() {
        this.status = false;
    }

    //GETTERS
    public String getTitle() {
        return this.title;
    }
    public String getDescription() {
        return this.description;
    }
    public String getDueDate() {
        return this.dueDate;
    }
    public boolean getStatus() {
        return this.status;
    }
}