import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class TaskItemTest {

    //TITLE
    //fails to create...
    @Test
    public void TestCreateTaskItemFailsWithInvalidTitle() {
        assertThrows(IllegalArgumentException.class, () ->
                new TaskItem("", "desc", "2020-01-01"));
    }

    //successfully creates...
    @Test
    public void TestCreateTaskItemSucceedsWithValidTitle() {
        TaskItem testItem = new TaskItem("title", "desc", "2020-01-01");

        assertEquals("title", testItem.getTitle());
    }

    //fails to set...
    @Test
    public void TestSetTaskItemFailsWithInvalidTitle() {
        TaskItem testItem = new TaskItem("title", "desc", "2020-01-01");

        assertThrows(IllegalArgumentException.class, () -> {
            testItem.setTitle("");
        });
    }

    //successfully sets...
    @Test
    public void TestSetTaskItemSucceedsWithValidTitle() {
        TaskItem testItem = new TaskItem("Original Title", "desc", "2020-01-01");
        testItem.setTitle("Updated Title");

        assertEquals("Updated Title", testItem.getTitle());
    }

    //DESCRIPTION
    //successfully sets...
    @Test
    public void TestSetTaskItemDescriptionSucceeds() {
        TaskItem testItem = new TaskItem("title", "Original Description", "2020-01-01");

        testItem.setDescription("Updated Description");

        assertEquals("Updated Description", testItem.getDescription());
    }

    //DUE DATE
    //fails to create due date of non-int values...
    @Test
    public void TestCreateTaskItemFailsWithInvalidDueDate1() {
        assertThrows(IllegalArgumentException.class, () ->
                new TaskItem("title", "desc", "date"));
    }

    //fails to create due date of incorrectly formatted due date, (because
    //the user did not enter a hyphen between year, month, and date)...
    @Test
    public void TestCreateTaskItemFailsWithInvalidDueDate2() {
        assertThrows(IllegalArgumentException.class, () ->
                new TaskItem("title", "desc", "2020 01 01"));
    }

    //fails to create due date of invalid month...
    @Test
    public void TestCreateTaskItemFailsWithInvalidDueDate3() {
        assertThrows(IllegalArgumentException.class, () ->
                new TaskItem("title", "desc", "2020-13-01"));
    }

    //fails to create due date of invalid day...
    @Test
    public void TestCreateTaskItemFailsWithInvalidDueDate4() {
        assertThrows(IllegalArgumentException.class, () ->
                new TaskItem("title", "desc", "2020-01-32"));
    }

    //successfully creates...
    @Test
    public void TestCreateTaskItemSucceedsWithValidDueDate() {
        TaskItem testItem = new TaskItem("title", "desc", "2020-01-01");

        assertEquals("2020-01-01", testItem.getDueDate());
    }

    //fails to set due date to non-int values...
    @Test
    public void TestSetTaskItemFailsWithInvalidDueDate1() {
        TaskItem testItem = new TaskItem("title", "desc", "2020-01-01");

        assertThrows(IllegalArgumentException.class, () -> {
            testItem.setDueDate("non-int value");
        });
    }

    //fails to create due date of incorrectly formatted due date, (because
    //the user did not enter a hyphen between year, month, and date)...
    @Test
    public void TestSetTaskItemFailsWithInvalidDueDate2() {
        TaskItem testItem = new TaskItem("title", "desc", "2020-01-01");

        assertThrows(IllegalArgumentException.class, () -> {
            testItem.setDueDate("2020 01 01");
        });
    }

    //fails to set due date to invalid month...
    @Test
    public void TestSetTaskItemFailsWithInvalidDueDate3() {
        TaskItem testItem = new TaskItem("title", "desc", "2020-01-01");

        assertThrows(IllegalArgumentException.class, () -> {
            testItem.setDueDate("2020-13-01");
        });
    }

    //fails to set due date to invalid day...
    @Test
    public void TestSetTaskItemFailsWithInvalidDueDate4() {
        TaskItem testItem = new TaskItem("title", "desc", "2020-01-01");

        assertThrows(IllegalArgumentException.class, () -> {
            testItem.setDueDate("2020-01-32");
        });
    }

    //successfully sets...
    @Test
    public void TestSetTaskItemSucceedsWithValidDueDate() {
        TaskItem testItem = new TaskItem("title", "desc", "2020-01-01");

        assertEquals("2020-01-01", testItem.getDueDate());
    }
}