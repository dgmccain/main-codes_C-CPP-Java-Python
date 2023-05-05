import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class ContactItemTest {

    //ALL VARIABLES
    //fails to create...
    @Test
    public void TestCreateContactItemFailsWithAllBlankValues() {
        //fails with all empty string values...
        assertThrows(IllegalArgumentException.class, () ->
                new ContactItem("", "", "", ""));
    }

    //successfully creates...
    @Test
    public void TestCreateContactItemSucceedsWithAllNonBlankValues() {
        ContactItem testItem = new ContactItem("first", "last", "phone", "email");

        assertEquals("first", testItem.getFirstName());
        assertEquals("last", testItem.getLastName());
        assertEquals("phone", testItem.getPhoneNumber());
        assertEquals("email", testItem.getEmailAddress());
    }

    //fails to set...
    @Test
    public void TestSetContactItemFailsWithAllBlankValues() {
        ContactItem testItem = new ContactItem("first", "last", "phone", "email");

        assertThrows(IllegalArgumentException.class, () -> {
            testItem.setContactItem("", "", "", "");
        });
    }

    //successfully sets...
    @Test
    public void TestSetContactItemSucceedsWithAllValidValues() {
        ContactItem testItem = new ContactItem("first1", "last1", "phone1", "email1");

        testItem.setContactItem("first2", "last2", "phone2", "email2");

        assertEquals("first2", testItem.getFirstName());
        assertEquals("last2", testItem.getLastName());
        assertEquals("phone2", testItem.getPhoneNumber());
        assertEquals("email2", testItem.getEmailAddress());
    }


    //FIRST NAME
    //successfully creates...
    @Test
    public void TestCreateContactItemSucceedsWithOnlyFirstName() {
        ContactItem testItem = new ContactItem("first", "", "", "");

        assertEquals("first", testItem.getFirstName());
    }
    @Test
    public void TestCreateContactItemSucceedsWithBlankFirstName() {
        ContactItem testItem = new ContactItem("", "last", "phone", "email");

        assertEquals("", testItem.getFirstName());
    }

    //successfully sets...
    @Test
    public void TestSetContactItemSucceedsWithOnlyFirstName() {
        ContactItem testItem = new ContactItem("first1", "last1", "phone1", "email1");

        testItem.setContactItem("first2", "", "", "");

        assertEquals("first2", testItem.getFirstName());
    }
    @Test
    public void TestSetContactItemSucceedsWithBlankFirstName() {
        ContactItem testItem = new ContactItem("", "last1", "phone1", "email1");

        testItem.setContactItem("", "last2", "phone2", "email2");

        assertEquals("", testItem.getFirstName());
    }

    //LAST NAME
    //successfully creates...
    @Test
    public void TestCreateContactItemSucceedsWithOnlyLastName() {
        ContactItem testItem = new ContactItem("", "last", "", "");

        assertEquals("last", testItem.getLastName());
    }
    @Test
    public void TestCreateContactItemSucceedsWithBlankLastName() {
        ContactItem testItem = new ContactItem("first", "", "phone", "email");

        assertEquals("", testItem.getLastName());
    }

    //successfully sets...
    @Test
    public void TestSetContactItemSucceedsWithOnlyLastName() {
        ContactItem testItem = new ContactItem("first1", "last1", "phone1", "email1");

        testItem.setContactItem("", "last2", "", "");

        assertEquals("last2", testItem.getLastName());
    }
    @Test
    public void TestSetContactItemSucceedsWithBlankLastName() {
        ContactItem testItem = new ContactItem("first1", "last1", "phone1", "email1");

        testItem.setContactItem("first2", "", "phone2", "email2");

        assertEquals("", testItem.getLastName());
    }

    //PHONE NUMBER
    //successfully creates...
    @Test
    public void TestCreateContactItemSucceedsWithOnlyPhoneNumber() {
        ContactItem testItem = new ContactItem("", "", "phone", "");

        assertEquals("phone", testItem.getPhoneNumber());
    }
    @Test
    public void TestCreateContactItemSucceedsWithBlankPhoneNumber() {
        ContactItem testItem = new ContactItem("first", "last", "", "email");

        assertEquals("", testItem.getPhoneNumber());
    }

    //successfully sets...
    @Test
    public void TestSetContactItemSucceedsWithOnlyPhoneNumber() {
        ContactItem testItem = new ContactItem("first1", "last1", "phone1", "email1");

        testItem.setContactItem("", "", "phone2", "");

        assertEquals("phone2", testItem.getPhoneNumber());
    }
    @Test
    public void TestSetContactItemSucceedsWithBlankPhoneNumber() {
        ContactItem testItem = new ContactItem("first1", "last1", "phone1", "email1");

        testItem.setContactItem("first2", "last2", "", "email2");

        assertEquals("", testItem.getPhoneNumber());
    }

    //EMAIL ADDRESS
    //successfully creates...
    @Test
    public void TestCreateContactItemSucceedsWithOnlyEmailAddress() {
        ContactItem testItem = new ContactItem("", "", "", "email");

        assertEquals("email", testItem.getEmailAddress());
    }
    @Test
    public void TestCreateContactItemSucceedsWithBlankEmailAddress() {
        ContactItem testItem = new ContactItem("first", "last", "phone", "");

        assertEquals("", testItem.getEmailAddress());
    }

    //successfully sets...
    @Test
    public void TestSetContactItemSucceedsWithOnlyEmailAddress() {
        ContactItem testItem = new ContactItem("first1", "last1", "phone1", "email1");

        testItem.setContactItem("", "", "", "email2");

        assertEquals("email2", testItem.getEmailAddress());
    }
    @Test
    public void TestSetContactItemSucceedsWithBlankEmailAddress() {
        ContactItem testItem = new ContactItem("first1", "last1", "phone1", "email1");

        testItem.setContactItem("first2", "last2", "phone2", "");

        assertEquals("", testItem.getEmailAddress());
    }
}