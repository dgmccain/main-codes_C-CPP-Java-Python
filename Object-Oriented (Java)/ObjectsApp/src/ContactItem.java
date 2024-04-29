public class ContactItem {
    private String firstName;
    private String lastName;
    private String phoneNumber;
    private String emailAddress;

    public ContactItem(String firstName, String lastName, String phoneNumber, String emailAddress) {
        if (isContactItemValid(firstName, lastName, phoneNumber, emailAddress)) {
            this.firstName = firstName;
            this.lastName = lastName;
            this.phoneNumber = phoneNumber;
            this.emailAddress = emailAddress;
        } else {
            throw new IllegalArgumentException("Contact must have at least 1 valid entry type. Contact was not created...");
        }
    }

    //VALIDATION
    public boolean isContactItemValid(String firstName, String lastName, String phoneNumber, String emailAddress) {
        //check to make sure that at least 1 valid entry was entered...
        if (!firstName.matches("")) {
            return true;
        } else if (!lastName.matches("")) {
            return true;
        } else if (!phoneNumber.matches("")) {
            return true;
        } else if (!emailAddress.matches("")) {
            return true;
        } else {
            return false;
        }
    }

    //GETTERS
    public String getFirstName() {
        return this.firstName;
    }
    public String getLastName() {
        return this.lastName;
    }
    public String getPhoneNumber() {
        return this.phoneNumber;
    }
    public String getEmailAddress() {
        return this.emailAddress;
    }

    //SETTER
    public void setContactItem(String firstName, String lastName, String phoneNumber, String emailAddress) {
        if (isContactItemValid(firstName, lastName, phoneNumber, emailAddress)) {
            this.firstName = firstName;
            this.lastName = lastName;
            this.phoneNumber = phoneNumber;
            this.emailAddress = emailAddress;
        } else {
            throw new IllegalArgumentException("Contact must have at least 1 valid entry type. Contact was not updated...");
        }
    }
}
