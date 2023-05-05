import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class TaskListTest {
    //NEW TASK LIST IS EMPTY
    @Test
    public void newTaskListIsEmpty() {
        TaskList testList = new TaskList();

        assertEquals(0, testList.getEntireTaskListSize());
    }

    //ADDING TASK ITEM
    @Test
    public void addingTaskItemIncreasesSize() {
        TaskItem testItem = new TaskItem("title", "desc", "2020-01-01");
        TaskList testList = new TaskList();

        testList.addTaskItemToList(testItem);

        assertEquals(1, testList.getEntireTaskListSize());
    }
    @Test
    public void addingTaskItemIsCorrectlyStoredInList() {
        TaskItem testItem = new TaskItem("title", "desc", "2020-01-01");
        TaskList testList = new TaskList();

        testList.addTaskItemToList(testItem);

        assertEquals("title", testList.getTaskItemTitleFromList(0));
        assertEquals("desc", testList.getTaskItemDescriptionFromList(0));
        assertEquals("2020-01-01", testList.getTaskItemDueDateFromList(0));
        assertFalse(testList.getTaskItemStatusFromList(0));
    }

    //REMOVING TASK ITEM
    @Test
    public void removingTaskItemFailsWithInvalidIndex() {
        TaskList testList = new TaskList();

        assertThrows(IndexOutOfBoundsException.class, () -> testList.deleteTaskItemFromList(0));
    }
    @Test
    public void removingTaskItemDecreasesSize() {
        TaskItem testItem = new TaskItem("title", "desc", "2020-01-01");
        TaskList testList = new TaskList();

        testList.addTaskItemToList(testItem);
        testList.deleteTaskItemFromList(0);

        assertEquals(0, testList.getEntireTaskListSize());
    }

    //GETTING TASK ITEM DATA
    @Test
    public void gettingTaskItemTitleFailsWithInvalidIndex() {
        TaskList testList = new TaskList();

        assertThrows(IndexOutOfBoundsException.class, () -> testList.getTaskItemTitleFromList(0));
    }
    @Test
    public void gettingTaskItemTitleSucceedsWithValidIndex() {
        TaskItem testItem = new TaskItem("title", "desc", "2020-01-01");
        TaskList testList = new TaskList();

        testList.addTaskItemToList(testItem);

        assertEquals("title", testList.getTaskItemTitleFromList(0));
    }
    @Test
    public void gettingTaskItemDescriptionFailsWithInvalidIndex() {
        TaskList testList = new TaskList();

        assertThrows(IndexOutOfBoundsException.class, () -> testList.getTaskItemDescriptionFromList(0));
    }
    @Test
    public void gettingTaskItemDescriptionSucceedsWithValidIndex() {
        TaskItem testItem = new TaskItem("title", "desc", "2020-01-01");
        TaskList testList = new TaskList();

        testList.addTaskItemToList(testItem);

        assertEquals("desc", testList.getTaskItemDescriptionFromList(0));
    }
    @Test
    public void gettingTaskItemDueDateFailsWithInvalidIndex() {
        TaskList testList = new TaskList();

        assertThrows(IndexOutOfBoundsException.class, () -> testList.getTaskItemDueDateFromList(0));
    }
    @Test
    public void gettingTaskItemDueDateSucceedsWithValidIndex() {
        TaskItem testItem = new TaskItem("title", "desc", "2020-01-01");
        TaskList testList = new TaskList();

        testList.addTaskItemToList(testItem);

        assertEquals("2020-01-01", testList.getTaskItemDueDateFromList(0));
    }
    @Test
    public void gettingTaskItemStatusFailsWithInvalidIndex() {
        TaskList testList = new TaskList();

        assertThrows(IndexOutOfBoundsException.class, () -> testList.getTaskItemStatusFromList(0));
    }
    @Test
    public void gettingTaskItemStatusSucceedsWithValidIndex() {
        TaskItem testItem = new TaskItem("title", "desc", "2020-01-01");
        TaskList testList = new TaskList();

        testList.addTaskItemToList(testItem);

        assertEquals(false, testList.getTaskItemStatusFromList(0));
    }

    //EDITING TASK ITEM
    //title...
    @Test
    public void editingTaskItemTitleFailsWithInvalidIndex() {
        //applies to title, description, and due date because the function takes
        //an entire task item as a parameter along with an index (item location)...
        TaskItem testItem = new TaskItem("title", "desc", "2020-01-01");
        TaskList testList = new TaskList();

        //testItem was never added to the list, so there is no item to edit...
        assertThrows(IndexOutOfBoundsException.class, () ->
                testList.editTaskItemInList(testItem, 0));
    }
    @Test
    public void editingTaskItemTitleFailsIfEmptyString() {
        TaskItem testOriginalItem = new TaskItem("original title", "desc", "2020-01-01");
        TaskList testList = new TaskList();

        testList.addTaskItemToList(testOriginalItem);
        assertEquals("original title", testList.getTaskItemTitleFromList(0));

        try {
            TaskItem testUpdatedItem = new TaskItem("", "desc", "2020-01-01");
            //the following edit function will not actually be called because the TaskItem
            //constructor should first throw an exception (because the title is empty). If
            //the TaskItem was ACTUALLY valid, then it would be passed to the edit function...
            testList.editTaskItemInList(testUpdatedItem, 0);
        } catch (IllegalArgumentException e){
            System.out.println(e.getMessage());
        }
    }
    @Test
    public void editingTaskItemTitleSucceedsWithExpectedValue() {
        TaskItem testOriginalItem = new TaskItem("original title", "desc", "2020-01-01");
        TaskList testList = new TaskList();

        //add an item to list and check to see if it was stored correctly...
        testList.addTaskItemToList(testOriginalItem);
        assertEquals("original title", testList.getTaskItemTitleFromList(0));

        //edit the item and verify the updated contents...
        TaskItem testUpdatedItem = new TaskItem("updated title", "desc", "2020-01-01");
        testList.editTaskItemInList(testUpdatedItem, 0);

        assertEquals("updated title", testList.getTaskItemTitleFromList(0));
    }

    //description...
    @Test
    public void editingTaskItemDescriptionFailsWithInvalidIndex() {
        TaskItem testItem = new TaskItem("title", "desc", "2020-01-01");
        TaskList testList = new TaskList();

        assertThrows(IndexOutOfBoundsException.class, () ->
                testList.editTaskItemInList(testItem, 0));
    }
    @Test
    public void editingTaskItemDescriptionSucceedsWithExpectedValue() {
        TaskItem testOriginalItem = new TaskItem("title", "original desc", "2020-01-01");
        TaskList testList = new TaskList();

        testList.addTaskItemToList(testOriginalItem);
        assertEquals("original desc", testList.getTaskItemDescriptionFromList(0));

        TaskItem testUpdatedItem = new TaskItem("title", "updated desc", "2020-01-01");
        testList.editTaskItemInList(testUpdatedItem, 0);

        assertEquals("updated desc", testList.getTaskItemDescriptionFromList(0));
    }

    //due date...
    @Test
    public void editingTaskItemDueDateFailsWithInvalidIndex() {
        TaskItem testItem = new TaskItem("title", "desc", "2020-01-01");
        TaskList testList = new TaskList();

        assertThrows(IndexOutOfBoundsException.class, () ->
                testList.editTaskItemInList(testItem, 0));
    }
    @Test
    public void editingTaskItemDueDateFailsWithInvalidDateFormat() {
        TaskItem testOriginalItem = new TaskItem("title", "desc", "2020-01-01");
        TaskList testList = new TaskList();

        testList.addTaskItemToList(testOriginalItem);
        assertEquals("2020-01-01", testList.getTaskItemDueDateFromList(0));

        try {
            TaskItem testUpdatedItem = new TaskItem("title", "updated desc", "date");
            testList.editTaskItemInList(testUpdatedItem, 0);
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }
    }
    @Test
    public void editingTaskItemDueDateFailsWithInvalidMonth() {
        TaskItem testOriginalItem = new TaskItem("title", "desc", "2020-01-01");
        TaskList testList = new TaskList();

        testList.addTaskItemToList(testOriginalItem);
        assertEquals("2020-01-01", testList.getTaskItemDueDateFromList(0));

        try {
            TaskItem testUpdatedItem = new TaskItem("title", "updated desc", "2020-13-01");
            testList.editTaskItemInList(testUpdatedItem, 0);
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }
    }
    @Test
    public void editingTaskItemDueDateFailsWithInvalidDay() {
        TaskItem testOriginalItem = new TaskItem("title", "desc", "2020-01-01");
        TaskList testList = new TaskList();

        testList.addTaskItemToList(testOriginalItem);
        assertEquals("2020-01-01", testList.getTaskItemDueDateFromList(0));

        try {
            TaskItem testUpdatedItem = new TaskItem("title", "updated desc", "2020-01-32");
            testList.editTaskItemInList(testUpdatedItem, 0);
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }
    }
    @Test
    public void editingTaskItemDueDateSucceedsWithExpectedValue() {
        TaskItem testOriginalItem = new TaskItem("title", "desc", "2020-01-01");
        TaskList testList = new TaskList();

        testList.addTaskItemToList(testOriginalItem);
        assertEquals("2020-01-01", testList.getTaskItemDueDateFromList(0));

        TaskItem testUpdatedItem = new TaskItem("title", "updated desc", "2020-02-02");
        testList.editTaskItemInList(testUpdatedItem, 0);

        assertEquals("2020-02-02", testList.getTaskItemDueDateFromList(0));
    }

    //MARKING TASK ITEM
    @Test
    public void markingTaskItemFailsWithInvalidIndex() {
        TaskItem testOriginalItem = new TaskItem("title", "desc", "2020-01-01");
        TaskList testList = new TaskList();

        testList.addTaskItemToList(testOriginalItem);
        assertFalse(testList.getTaskItemStatusFromList(0));

        try {
            //original task item is stored in index 0, so there will be no index 1...
            testList.markTaskItemInList(1);
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }
    }
    @Test
    public void markingTaskItemChangesStatus() {
        TaskItem testOriginalItem = new TaskItem("title", "desc", "2020-01-01");
        TaskList testList = new TaskList();

        testList.addTaskItemToList(testOriginalItem);
        assertFalse(testList.getTaskItemStatusFromList(0));

        testList.markTaskItemInList(0);
        assertTrue(testList.getTaskItemStatusFromList(0));
    }

    //UNMARKING TASK ITEM
    @Test
    public void unmarkingTaskItemFailsWithInvalidIndex() {
        TaskItem testOriginalItem = new TaskItem("title", "desc", "2020-01-01", true);
        TaskList testList = new TaskList();

        testList.addTaskItemToList(testOriginalItem);
        assertTrue(testList.getTaskItemStatusFromList(0));

        try {
            //original task item is stored in index 0, so there will be no index 1...
            testList.unmarkTaskItemInList(1);
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }
    }
    @Test
    public void unmarkingTaskItemChangesStatus() {
        TaskItem testOriginalItem = new TaskItem("title", "desc", "2020-01-01", true);
        TaskList testList = new TaskList();

        testList.addTaskItemToList(testOriginalItem);
        assertTrue(testList.getTaskItemStatusFromList(0));

        testList.unmarkTaskItemInList(0);
        assertFalse(testList.getTaskItemStatusFromList(0));
    }

    //SAVING TASK LIST
    @Test
    public void savingTaskListFails() {
        TaskList testList = new TaskList();

        //create file - WILL OVERWRITE FILE WITH IDENTICAL NAME (only if a file with
        //an identical name exists and is stored in the same path)...
        testList.saveTaskListToFile("saveTaskList_ExampleFile2.txt");
        //check if the newly saved file exists...
        assertFalse(TaskApp.doesFileExist("saveTaskList_ExampleFile2.txt"));
    }
    @Test
    public void savingTaskListSucceeds() {
        TaskItem testOriginalItem = new TaskItem("title", "desc", "2020-01-01");
        TaskList testList = new TaskList();

        testList.addTaskItemToList(testOriginalItem);

        //create file - WILL OVERWRITE FILE WITH IDENTICAL NAME (only if a file with
        //an identical name exists and is stored in the same path)...
        testList.saveTaskListToFile("saveTaskList_ExampleFile1.txt");
        //check if the newly saved file exists...
        assertTrue(TaskApp.doesFileExist("saveTaskList_ExampleFile1.txt"));
    }

    //LOADING TASK LIST
    @Test
    public void loadingTaskListFails() {
        TaskList testList = new TaskList();

        //try to load a task that does not exist. The exception is caught in the
        //<TaskList.loadTasks()> function, sending an error message to the console...
        testList.loadTaskListFromFile("aFileThatDoesNotExist");

        //check if the file exists...
        assertFalse(TaskApp.doesFileExist("aFileThatDoesNotExist"));
    }
    @AfterAll
    public static void loadingTaskListSucceeds() {
        //can ONLY TEST AFTER <savingTaskListSucceeds()> test has passed. File
        //names in both test cases can be changed; the load file just needs to
        //be identical in name to the save file...
        TaskList testList = new TaskList();

        //load list...
        testList.loadTaskListFromFile("saveTaskList_ExampleFile1.txt");

        //verify loaded list contents...
        assertEquals("title", testList.getTaskItemTitleFromList(0));
        assertEquals("desc", testList.getTaskItemDescriptionFromList(0));
        assertEquals("2020-01-01", testList.getTaskItemDueDateFromList(0));
        assertFalse(testList.getTaskItemStatusFromList(0));
    }
}