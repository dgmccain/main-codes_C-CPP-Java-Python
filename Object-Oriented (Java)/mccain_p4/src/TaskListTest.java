import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class TaskListTest {

    @Test
    public void TestGetIntFromUser() {
        //requires user input...
    }

    @Test
    public void TestPrintTasks() {
        TaskList testList = new TaskList();
        TaskItem testItem = new TaskItem(false,"title", "description", "2020-01-01");

        testList.addTasks(testItem);
        testList.printTasks(testList);
        //NOTE: testList should output to console without problems...
    }

    @Test
    public void TestAddToList() {
        TaskList testList = new TaskList();
        TaskItem testItem = new TaskItem(false,"title", "description", "2020-01-01");

        testList.addTasks(testItem);
        assertEquals(1, testList.getListSize(testList));

    }

    @Test
    public void TestGetItemNumFromUser() {
        //requires user input...
    }

    @Test
    public void TestEditTasks() {
        //the test breaks because user input is required...
        TaskList testList = new TaskList();

        TaskItem testItem1 = new TaskItem(false,"title1", "description1", "2020-01-01");
        testList.addTasks(testItem1);
        TaskItem testItem2 = new TaskItem(false,"title2", "description2", "2020-02-02");
        testList.addTasks(testItem2);

        //testList.editTasks(testList);

        //CANNOT call testList.editTasks(testList) above because the user needs to
        //enter scanner input data within <TaskList.editTasks> function due to a
        //nested function <getIntFromUser>, which will ask the user for the task
        //number to edit and wait for a response...
    }

    @Test
    public void TestDeleteTasks() {
        //same issue as editTasks...
    }

    @Test
    public void TestStoreTasks() {
        //same issue as editTasks...
    }

    @Test
    public void TestLoadTasks() {
        //same issue as editTasks...
    }

    /*
        USE CODE FROM ABOVE!!!!!
    */

    //TEST GETTERS
    //fails to get title...
    @Test
    public void TestGettingTaskItemTitleFailsWithInvalidIndex() {
        TaskList testList = new TaskList();
        TaskItem testItem = new TaskItem(false,"title", "description", "2020-01-01");

        testList.addTasks(testItem);

    }

    //successfully gets title...
    @Test
    public void TestGettingTaskItemTitleSucceedsWithValidIndex() {
        //test goes here...
    }

    //fails to get description...
    @Test
    public void TestGettingTaskItemDescriptionFailsWithInvalidIndex() {
        //test goes here...
    }

    //successfully gets description...
    @Test
    public void TestGettingTaskItemDescriptionSucceedsWithValidIndex() {
        //test goes here...
    }

    //fails to get due date...
    @Test
    public void TestGettingTaskItemDueDateFailsWithInvalidIndex() {
        //test goes here...
    }

    //successfully gets due date...
    @Test
    public void TestGettingTaskItemDueDateSucceedsWithValidIndex() {
        //test goes here...
    }

    //TEST ADDING TASK ITEMS
    @Test
    public void TestAddingTaskItemsIncreasesSize() {
        //test goes here...
    }

    //TEST EDITING TASK ITEMS
    //fails to edit title...
    @Test
    public void TestEditingTaskItemTitleFailsWithInvalidIndex() {
        //test goes here...
    }

    //successfully edits title...
    @Test
    public void TestEditingTaskItemTitleChangesValue() {
        //test goes here...
    }

    //fails to edit description...
    @Test
    public void TestEditingTaskItemDescriptionFailsWithInvalidIndex() {
        //test goes here...
    }

    //successfully edits description...
    @Test
    public void TestEditingTaskItemDescriptionChangesValue() {
        //test goes here...
    }

    //fails to edit due date...
    @Test
    public void TestEditingTaskItemDueDateFailsWithInvalidIndex() {
        //test goes here...
    }

    //successfully edits due date...
    @Test
    public void TestEditingTaskItemDueDateChangesValue() {
        //test goes here...
    }

    //successfully edits task item...
    @Test
    public void TestEditingTaskItemChangesValues() {
        //test goes here...
    }

    //TEST REMOVING TASK ITEMS
    //fails to remove task item...
    @Test
    public void TestRemovingTaskItemsFailsWithInvalidIndex() {
        //test goes here...
    }

    //successfully removes task item...
    @Test
    public void TestRemovingTaskItemsDecreasesSize() {
        //test goes here...
    }

    //TEST CHANGING TASK ITEM STATUS
    //fails to mark task item...
    @Test
    public void TestCompletingTaskItemFailsWithInvalidIndex() {
        //test goes here...
    }

    //successfully marks task item...
    @Test
    public void TestCompletingTaskItemChangesStatus() {
        //test goes here...
    }

    //fails to unmark task item...
    @Test
    public void TestUncompletingTaskItemFailsWithInvalidIndex() {
        //test goes here...
    }

    //successfully unmarks task item...
    @Test
    public void TestUncompletingTaskItemChangesStatus() {
        //test goes here...
    }

    //TEST LOAD TASK LIST
    //successfully loads task item...
    @Test
    public void TestSavedTaskListCanBeLoaded() {
        //test goes here...
    }
}