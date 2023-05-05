import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class TaskItemTest {

    //TITLE
    //fails to create...
    @Test
    public void TestCreateTaskItemFailsWithInvalidTitle() {
        //NOTE: The task item actually IS created. The exception handling should print
        //out an error message to the user, and then the task item is re-called to create
        //a task item within the App class function <setTaskItemFromUser()>. This test is
        //actually checking for if title is return as a null value...
        TaskItem testItem = new TaskItem(false,"", "blank title test", "2020-01-01");
        assertEquals(null, testItem.getTitle());
    }

    //successfully creates...
    @Test
    public void TestCreateTaskItemSucceedsWithValidTitle() {
        TaskItem testItem = new TaskItem(false,"title", "description", "2020-01-01");
        assertEquals(testItem.getTitle(), "title");
        //verify contents by checking description and due date too...
        assertEquals(testItem.getDescription(), "description");
        assertEquals(testItem.getDueDate(), "2020-01-01");
    }

    //fails to set...
    @Test
    public void TestSetTaskItemFailsWithInvalidTitle() {
        TaskItem testItem = new TaskItem(false,"Existing title", "will be re-assigned", "2020-01-01");
        //exception handling should catch the newly set invalid title argument...
        assertThrows(IllegalArgumentException.class, () -> {
            //set title to empty for invalid input exception to be thrown...
            testItem.setTitle("");
        });
    }

    //successfully sets...
    @Test
    public void TestSetTaskItemSucceedsWithValidTitle() {
        TaskItem testItem = new TaskItem(false,"Original title", "will be re-assigned", "2020-01-01");
        testItem.setTitle("New title");
        assertEquals(testItem.getTitle(), "New title");
        //fully verify contents by testing description and due date too...
        assertEquals(testItem.getDescription(), "will be re-assigned");
        assertEquals(testItem.getDueDate(), "2020-01-01");
    }

    //DUE DATE
    //fails to create due date of non-int values...
    @Test
    public void TestCreateTaskItemFailsWithInvalidDueDate1() {
        //NOTE: functions in the same way as the failed title test. ALL of the
        //following dueDate tests in the TaskItemTest class operate in the same manner...
        TaskItem testItem = new TaskItem(false,"title", "description", "date goes here");
        assertEquals(null, testItem.getDueDate());
    }

    //fails to create due date of incorrectly formatted due date...
    @Test
    public void TestCreateTaskItemFailsWithInvalidDueDate2() {
        TaskItem testItem = new TaskItem(false,"title", "description", "2020/01/01");
        assertEquals(null, testItem.getDueDate());
    }

    //fails to create due date of invalid month...
    @Test
    public void TestCreateTaskItemFailsWithInvalidDueDate3() {
        TaskItem testItem = new TaskItem(false,"title", "description", "2020-13-01");
        assertEquals(null, testItem.getDueDate());
    }

    //fails to create due date of invalid day...
    @Test
    public void TestCreateTaskItemFailsWithInvalidDueDate4() {
        TaskItem testItem = new TaskItem(false,"title", "description", "2020-10-33");
        assertEquals(null, testItem.getDueDate());
    }

    //successfully creates...
    @Test
    public void TestCreateTaskItemSucceedsWithValidDueDate() {
        TaskItem testItem = new TaskItem(false,"title", "description", "2020-01-01");
        assertEquals(testItem.getDueDate(), "2020-01-01");
        //verify contents by checking title and description too...
        assertEquals(testItem.getTitle(), "title");
        assertEquals(testItem.getDescription(), "description");
    }

    //fails to set due date to non-int values...
    @Test
    public void TestSetTaskItemFailsWithInvalidDueDate1() {
        TaskItem testItem = new TaskItem(false,"title", "description", "2020-01-01");
        assertThrows(IllegalArgumentException.class, () -> {
            testItem.setDueDate("date");
        } );
    }

    //fails to set due date to incorrectly formatted due date...
    @Test
    public void TestSetTaskItemFailsWithInvalidDueDate2() {
        TaskItem testItem = new TaskItem(false,"title", "description", "2020-01-01");
        assertThrows(IllegalArgumentException.class, () -> {
            testItem.setDueDate("2020/02/02");
        } );
    }

    //fails to set due date to invalid month...
    @Test
    public void TestSetTaskItemFailsWithInvalidDueDate3() {
        TaskItem testItem = new TaskItem(false,"title", "description", "2020-01-01");
        assertThrows(IllegalArgumentException.class, () -> {
            testItem.setDueDate("2020-13-01");
        } );
    }

    //fails to set due date to invalid day...
    @Test
    public void TestSetTaskItemFailsWithInvalidDueDate4() {
        TaskItem testItem = new TaskItem(false,"title", "description", "2020-01-01");
        assertThrows(IllegalArgumentException.class, () -> {
            testItem.setDueDate("2020-01-33");
        } );
    }

    //successfully sets...
    @Test
    public void TestSetTaskItemSucceedsWithValidDueDate() {
        TaskItem testItem = new TaskItem(false,"title", "description", "2020-01-01");
        testItem.setDueDate("2020-02-02");
        assertEquals(testItem.getDueDate(), "2020-02-02");
        //fully verify contents by testing title and description too...
        assertEquals(testItem.getTitle(), "title");
        assertEquals(testItem.getDescription(), "description");
    }
}