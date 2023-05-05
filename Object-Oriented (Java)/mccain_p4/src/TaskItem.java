public class TaskItem {
    private String title;
    private String description;
    private String dueDate;
    private boolean status;

    //CONSTRUCTORS
    //set default status to false if not given...
    public TaskItem(String title, String description, String dueDate) {
        new TaskItem(false, title, description, dueDate);
    }

    //main constructor...
    public TaskItem(boolean status, String title, String description, String dueDate) {
        //if status == true, then marked...
        this.status = status;

        //exception handling...
        try {
            if (isTitleValid(title)) {
                this.title = title;
            }
            else {
                throw new IllegalArgumentException();
            }
        }
        catch (IllegalArgumentException e) {
            System.out.println("You must enter a title...");
        }

        //description does not need exception handling...
        this.description = description;

        //exception handling...
        try {
            if (isDueDateValid(dueDate)) {
                this.dueDate = dueDate;
            } else {
                throw new IllegalArgumentException();
            }
        } catch (IllegalArgumentException e) {
            System.out.println("You must enter a valid date...");
        }
    }

    //TITLE
    public boolean isTitleValid(String title) {
        //check if title is empty...
        return !title.matches("");
    }
    public void setTitle(String title){
        if(isTitleValid(title))
            this.title = title;
        else
            throw new IllegalArgumentException("You must enter a title...");
    }
    public String getTitle() {
        return title;
    }

    //DESCRIPTION
    public void setDescription(String description) {
        this.description = description;
    }
    public String getDescription() {
        return description;
    }

    //DUE DATE
    public boolean isDueDateValid(String dd) {
        //check if due date match yyyy-MM-dd format...
        //if statements ensure that months are 01-12 and days are 01-32...
        if (dd.matches("[0-9]{4}[-][0-1][0-9][-][0-3][0-9]")) {
            //if month == 0...
            if (dd.matches("[0-9]{4}[-][0][0][-][0-3][0-9]")) {
                return false;
            }
            //if month >= 13...
            else if (dd.matches("[0-9]{4}[-][1][3-9][-][0-3][0-9]")) {
                return false;
            }
            //if days == 0...
            else if (dd.matches("[0-9]{4}[-][0-1][0-9][-][0][0]")) {
                return false;
            }
            //if days >= 32...
            else if (dd.matches("[0-9]{4}[-][0-1][0-9][-][3][2-9]")) {
                return false;
            }
            //else should return all other valid dates (months 01-12 and days 01-31)...
            else{
                return true;
            }
        } else {
            //input did not match yyyy-MM-dd format...
            return false;
        }
    }
    public void setDueDate(String dueDate){
        if(isDueDateValid(dueDate))
            this.dueDate = dueDate;
        else
            throw new IllegalArgumentException("You must enter a valid due date...");
    }
    public String getDueDate() {
        return dueDate;
    }

    //STATUS
    public void setStatusAsComplete() {
        this.status = true;
    }
    public void setStatusAsIncomplete() {
        this.status = false;
    }
    public boolean getStatus() {
        return this.status;
    }
}