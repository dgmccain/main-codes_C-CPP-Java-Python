import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class ContactListTest {

    //NEW CONTACT LIST IS EMPTY
    @Test
    public void newContactListIsEmpty() {
        ContactList testList = new ContactList();

        assertEquals(0, testList.getEntireContactListSize());
    }

    //ADDING CONTACT ITEM
    @Test
    public void addingContactItemIncreasesSize() {
        ContactItem testItem = new ContactItem("first", "last", "phone", "email");
        ContactList testList = new ContactList();

        testList.addContactItemToList(testItem);

        assertEquals(1, testList.getEntireContactListSize());
    }
    @Test
    public void addingContactItemIsCorrectlyStoredInList() {
        ContactItem testItem = new ContactItem("first", "last", "phone", "email");
        ContactList testList = new ContactList();

        testList.addContactItemToList(testItem);

        assertEquals("first", testList.getContactItemFirstNameFromList(0));
        assertEquals("last", testList.getContactItemLastNameFromList(0));
        assertEquals("phone", testList.getContactItemPhoneNumberFromList(0));
        assertEquals("email", testList.getContactItemEmailAddressFromList(0));
    }

    //REMOVING CONTACT ITEM
    @Test
    public void removingContactItemFailsWithInvalidIndex() {
        ContactList testList = new ContactList();

        assertThrows(IndexOutOfBoundsException.class, () -> testList.deleteContactItemFromList(0));
    }
    @Test
    public void removingContactItemDecreasesSize() {
        ContactItem testItem = new ContactItem("first", "last", "phone", "email");
        ContactList testList = new ContactList();

        testList.addContactItemToList(testItem);
        testList.deleteContactItemFromList(0);

        assertEquals(0, testList.getEntireContactListSize());
    }

    //GETTING CONTACT ITEM
    @Test
    public void gettingContactItemFirstNameFailsWithInvalidIndex() {
        ContactList testList = new ContactList();

        assertThrows(IndexOutOfBoundsException.class, () -> testList.getContactItemFirstNameFromList(0));
    }
    @Test
    public void gettingContactItemFirstNameSucceedsWithValidIndex() {
        ContactItem testItem = new ContactItem("first", "last", "phone", "email");
        ContactList testList = new ContactList();

        testList.addContactItemToList(testItem);

        assertEquals("first", testList.getContactItemFirstNameFromList(0));
    }
    @Test
    public void gettingContactItemLastNameFailsWithInvalidIndex() {
        ContactList testList = new ContactList();

        assertThrows(IndexOutOfBoundsException.class, () -> testList.getContactItemLastNameFromList(0));
    }
    @Test
    public void gettingContactItemLastNameSucceedsWithValidIndex() {
        ContactItem testItem = new ContactItem("first", "last", "phone", "email");
        ContactList testList = new ContactList();

        testList.addContactItemToList(testItem);

        assertEquals("last", testList.getContactItemLastNameFromList(0));
    }
    @Test
    public void gettingContactItemPhoneNumberFailsWithInvalidIndex() {
        ContactList testList = new ContactList();

        assertThrows(IndexOutOfBoundsException.class, () -> testList.getContactItemPhoneNumberFromList(0));
    }
    @Test
    public void gettingContactItemPhoneNumberSucceedsWithValidIndex() {
        ContactItem testItem = new ContactItem("first", "last", "phone", "email");
        ContactList testList = new ContactList();

        testList.addContactItemToList(testItem);

        assertEquals("phone", testList.getContactItemPhoneNumberFromList(0));
    }
    @Test
    public void gettingContactItemEmailAddressFailsWithInvalidIndex() {
        ContactList testList = new ContactList();

        assertThrows(IndexOutOfBoundsException.class, () -> testList.getContactItemEmailAddressFromList(0));
    }
    @Test
    public void gettingContactItemEmailAddressSucceedsWithValidIndex() {
        ContactItem testItem = new ContactItem("first", "last", "phone", "email");
        ContactList testList = new ContactList();

        testList.addContactItemToList(testItem);

        assertEquals("email", testList.getContactItemEmailAddressFromList(0));
    }

    //EDITING CONTACT ITEM
    //all variables...
    @Test
    public void editingContactItemFailsWithInvalidIndex() {
        ContactItem testItem = new ContactItem("first", "last", "phone", "email");
        ContactList testList = new ContactList();

        //testItem was never added to the list, so there is no item to edit...
        assertThrows(IndexOutOfBoundsException.class, () ->
                testList.editContactItemInList(testItem, 0));
    }
    @Test
    public void editingContactItemFailsWithAllBlankValues() {
        ContactItem testItem = new ContactItem("first", "last", "phone", "email");
        ContactList testList = new ContactList();

        testList.addContactItemToList(testItem);

        try {
            testItem.setContactItem("", "", "", "");
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }
    }
    @Test
    public void editingContactItemSucceedsWithNonBlankValues() {
        ContactItem testItem = new ContactItem("first1", "last1", "phone1", "email1");
        ContactList testList = new ContactList();

        //add original item to list...
        testList.addContactItemToList(testItem);
        //set original item to updated item data...
        testItem.setContactItem("first2", "last2", "phone2", "email2");
        //update the contact list with the new item data...
        testList.editContactItemInList(testItem, 0);

        //check to see if the list updated to now contain the edited item data...
        assertEquals("first2", testList.getContactItemFirstNameFromList(0));
        assertEquals("last2", testList.getContactItemLastNameFromList(0));
        assertEquals("phone2", testList.getContactItemPhoneNumberFromList(0));
        assertEquals("email2", testList.getContactItemEmailAddressFromList(0));
    }
    //first name...
    @Test
    public void editingContactItemSucceedsWithOnlyFirstName() {
        ContactItem testItem = new ContactItem("first1", "last1", "phone1", "email1");
        ContactList testList = new ContactList();

        testList.addContactItemToList(testItem);

        testItem.setContactItem("first2", "", "", "");
        testList.editContactItemInList(testItem, 0);

        //check to see if the list updated to now contain the edited item data...
        assertEquals("first2", testList.getContactItemFirstNameFromList(0));
        assertEquals("", testList.getContactItemLastNameFromList(0));
        assertEquals("", testList.getContactItemPhoneNumberFromList(0));
        assertEquals("", testList.getContactItemEmailAddressFromList(0));
    }
    @Test
    public void editingContactItemSucceedsWithBlankFirstName() {
        ContactItem testItem = new ContactItem("first1", "last1", "phone1", "email1");
        ContactList testList = new ContactList();

        testList.addContactItemToList(testItem);

        testItem.setContactItem("", "last2", "phone2", "email2");
        testList.editContactItemInList(testItem, 0);

        //check to see if the list updated to now contain the edited item data...
        assertEquals("", testList.getContactItemFirstNameFromList(0));
        assertEquals("last2", testList.getContactItemLastNameFromList(0));
        assertEquals("phone2", testList.getContactItemPhoneNumberFromList(0));
        assertEquals("email2", testList.getContactItemEmailAddressFromList(0));
    }
    //last name...
    @Test
    public void editingContactItemSucceedsWithOnlyLastName() {
        ContactItem testItem = new ContactItem("first1", "last1", "phone1", "email1");
        ContactList testList = new ContactList();

        testList.addContactItemToList(testItem);

        testItem.setContactItem("", "last2", "", "");
        testList.editContactItemInList(testItem, 0);

        //check to see if the list updated to now contain the edited item data...
        assertEquals("", testList.getContactItemFirstNameFromList(0));
        assertEquals("last2", testList.getContactItemLastNameFromList(0));
        assertEquals("", testList.getContactItemPhoneNumberFromList(0));
        assertEquals("", testList.getContactItemEmailAddressFromList(0));
    }
    @Test
    public void editingContactItemSucceedsWithBlankLastName() {
        ContactItem testItem = new ContactItem("first1", "last1", "phone1", "email1");
        ContactList testList = new ContactList();

        testList.addContactItemToList(testItem);

        testItem.setContactItem("first2", "", "phone2", "email2");
        testList.editContactItemInList(testItem, 0);

        //check to see if the list updated to now contain the edited item data...
        assertEquals("first2", testList.getContactItemFirstNameFromList(0));
        assertEquals("", testList.getContactItemLastNameFromList(0));
        assertEquals("phone2", testList.getContactItemPhoneNumberFromList(0));
        assertEquals("email2", testList.getContactItemEmailAddressFromList(0));
    }
    //phone number...
    @Test
    public void editingContactItemSucceedsWithOnlyPhoneNumber() {
        ContactItem testItem = new ContactItem("first1", "last1", "phone1", "email1");
        ContactList testList = new ContactList();

        testList.addContactItemToList(testItem);

        testItem.setContactItem("", "", "phone2", "");
        testList.editContactItemInList(testItem, 0);

        //check to see if the list updated to now contain the edited item data...
        assertEquals("", testList.getContactItemFirstNameFromList(0));
        assertEquals("", testList.getContactItemLastNameFromList(0));
        assertEquals("phone2", testList.getContactItemPhoneNumberFromList(0));
        assertEquals("", testList.getContactItemEmailAddressFromList(0));
    }
    @Test
    public void editingContactItemSucceedsWithBlankPhoneNumber() {
        ContactItem testItem = new ContactItem("first1", "last1", "phone1", "email1");
        ContactList testList = new ContactList();

        testList.addContactItemToList(testItem);

        testItem.setContactItem("first2", "last2", "", "email2");
        testList.editContactItemInList(testItem, 0);

        //check to see if the list updated to now contain the edited item data...
        assertEquals("first2", testList.getContactItemFirstNameFromList(0));
        assertEquals("last2", testList.getContactItemLastNameFromList(0));
        assertEquals("", testList.getContactItemPhoneNumberFromList(0));
        assertEquals("email2", testList.getContactItemEmailAddressFromList(0));
    }
    //email address...
    @Test
    public void editingContactItemSucceedsWithOnlyEmailAddress() {
        ContactItem testItem = new ContactItem("first1", "last1", "phone1", "email1");
        ContactList testList = new ContactList();

        testList.addContactItemToList(testItem);

        testItem.setContactItem("", "", "", "email2");
        testList.editContactItemInList(testItem, 0);

        //check to see if the list updated to now contain the edited item data...
        assertEquals("", testList.getContactItemFirstNameFromList(0));
        assertEquals("", testList.getContactItemLastNameFromList(0));
        assertEquals("", testList.getContactItemPhoneNumberFromList(0));
        assertEquals("email2", testList.getContactItemEmailAddressFromList(0));
    }
    @Test
    public void editingContactItemSucceedsWithBlankPhoneEmailAddress() {
        ContactItem testItem = new ContactItem("first1", "last1", "phone1", "email1");
        ContactList testList = new ContactList();

        testList.addContactItemToList(testItem);

        testItem.setContactItem("first2", "last2", "phone2", "");
        testList.editContactItemInList(testItem, 0);

        //check to see if the list updated to now contain the edited item data...
        assertEquals("first2", testList.getContactItemFirstNameFromList(0));
        assertEquals("last2", testList.getContactItemLastNameFromList(0));
        assertEquals("phone2", testList.getContactItemPhoneNumberFromList(0));
        assertEquals("", testList.getContactItemEmailAddressFromList(0));
    }

    //SAVING CONTACT LIST
    @Test
    public void savingContactListFails() {
        ContactList testList = new ContactList();

        //create file - WILL OVERWRITE FILE WITH IDENTICAL NAME (only if a file with
        //an identical name exists and is stored in the same path)...
        testList.saveContactListToFile("saveContactList_ExampleFile2.txt");
        //check if the newly saved file exists...
        assertFalse(TaskApp.doesFileExist("saveTaskList_ExampleFile2.txt"));
    }
    @Test
    public void savingContactListSucceeds() {
        ContactItem testOriginalItem = new ContactItem("first", "last", "phone", "email");
        ContactList testList = new ContactList();

        testList.addContactItemToList(testOriginalItem);

        //create file - WILL OVERWRITE FILE WITH IDENTICAL NAME (only if a file with
        //an identical name exists and is stored in the same path)...
        testList.saveContactListToFile("saveContactList_ExampleFile1.txt");
        //check if the newly saved file exists...
        assertTrue(TaskApp.doesFileExist("saveContactList_ExampleFile1.txt"));
    }

    //LOADING CONTACT LIST
    @Test
    public void loadingContactListFails() {
        ContactList testList = new ContactList();

        //try to load a task that does not exist. The exception is caught in the
        //<TaskList.loadTasks()> function, sending an error message to the console...
        testList.loadContactListFromFile("aFileThatDoesNotExist");

        //check if the file exists...
        assertFalse(TaskApp.doesFileExist("aFileThatDoesNotExist"));
    }
    @AfterAll
    public static void loadingContactListSucceeds() {
        //can ONLY TEST AFTER <savingTaskListSucceeds()> test has passed. File
        //names in both test cases can be changed; the load file just needs to
        //be identical in name to the save file...
        ContactList testList = new ContactList();

        //load list...
        testList.loadContactListFromFile("saveContactList_ExampleFile1.txt");

        //verify loaded list contents...
        assertEquals("first", testList.getContactItemFirstNameFromList(0));
        assertEquals("last", testList.getContactItemLastNameFromList(0));
        assertEquals("phone", testList.getContactItemPhoneNumberFromList(0));
        assertEquals("email", testList.getContactItemEmailAddressFromList(0));
    }
}