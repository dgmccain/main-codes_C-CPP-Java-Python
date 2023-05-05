import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Formatter;
import java.util.List;
import java.util.Scanner;

public class ContactList {
    private final List<ContactItem> contactList = new ArrayList<>();

    public ContactList() {
        //default constructor...
    }

    //ADD
    //add item to list...
    public void addContactItemToList(ContactItem contactItem) {
        contactList.add(contactItem);
    }

    //UPDATE
    //edit items in list...
    public void editContactItemInList(ContactItem updatedContactItem, int location) {
        String tempFirstName;
        String tempLastName;
        String tempPhoneNumber;
        String tempEmailAddress;

        try {
            tempFirstName = updatedContactItem.getFirstName();
            tempLastName = updatedContactItem.getLastName();
            tempPhoneNumber = updatedContactItem.getPhoneNumber();
            tempEmailAddress = updatedContactItem.getEmailAddress();

            this.contactList.get(location).setContactItem(tempFirstName, tempLastName, tempPhoneNumber, tempEmailAddress);
        } catch (IllegalArgumentException e) {
            System.out.println(e.getMessage());
        }
    }

    //REMOVE
    //delete item from list...
    public void deleteContactItemFromList(int index) {
        contactList.remove(index);
        System.out.println("contact #" + (index + 1) + " was deleted");
    }

    //VIEW
    //display entire list contents...
    public void displayContactItemsInList() {
        int contactNum;
        for (int i = 0; i < this.contactList.size(); i++) {
            contactNum = i+1;
            System.out.println("----------------------------------------");
            //use (i+1) so that task #0 becomes task #1...
            System.out.println(("Contact #" + contactNum + ":"));
            //output contact list item contents...
            System.out.println("First name: " + this.contactList.get(i).getFirstName());
            System.out.println("Last name: " + this.contactList.get(i).getLastName());
            System.out.println("Phone number: " + this.contactList.get(i).getPhoneNumber());
            System.out.println("Email address: " + this.contactList.get(i).getEmailAddress());
        }
        System.out.println("----------------------------------------");
    }

    //GET
    //this.size() function...
    public int getEntireContactListSize() {
        return this.contactList.size();
    }
    //functions for getting item data from list...
    public String getContactItemFirstNameFromList(int index) {
        return this.contactList.get(index).getFirstName();
    }
    public String getContactItemLastNameFromList(int index) {
        return this.contactList.get(index).getLastName();
    }
    public String getContactItemPhoneNumberFromList(int index) {
        return this.contactList.get(index).getPhoneNumber();
    }
    public String getContactItemEmailAddressFromList(int index) {
        return this.contactList.get(index).getEmailAddress();
    }

    //STORE
    //store list to file...
    public void saveContactListToFile(String fileName) {
        //only proceed if contactList contains data...
        if(contactList.size() > 0) {
            if (clearExistingContactFileContentsBeforeSaving(fileName)) {
                //only continue if the file is blank to ensure that contents are not compromised...
                try (Formatter output = new Formatter(fileName)) {
                    //store contact items in file...
                    for (ContactItem contactItem : contactList) {
                        output.format("%s;%s;%s;%s;%n", contactItem.getFirstName(), contactItem.getLastName(),
                                contactItem.getPhoneNumber(), contactItem.getEmailAddress());
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
            System.out.println("You do not have a contact list of items to save...");
        }
    }
    public boolean clearExistingContactFileContentsBeforeSaving(String fileName) {
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
    public void loadContactListFromFile(String fileName) {
        String lineFirstName;
        String lineLastName;
        String linePhoneNumber;
        String lineEmailAddress;

        //start by deleting the current contactList before loading from file contents...
        for (int i = contactList.size(); i > 0; i--) {
            //remove the last element in the array list...
            contactList.remove((i-1));
        }

        //exception handling for loading file...
        try {
            Scanner fileScanner = new Scanner(new File(fileName));

            while (fileScanner.hasNextLine()) {
                //delimiter is what separates the object variables on the same line...
                fileScanner.useDelimiter(";");

                //read first name...
                lineFirstName = fileScanner.next();
                //read last name...
                lineLastName = fileScanner.next();
                //read phone number...
                linePhoneNumber = fileScanner.next();
                //read email address...
                lineEmailAddress = fileScanner.next();

                //buffer the next line input...
                fileScanner.nextLine();

                //store as new contact item...
                ContactItem tempItem = new ContactItem(lineFirstName, lineLastName, linePhoneNumber, lineEmailAddress);
                //store contact item in list...
                contactList.add(tempItem);
            }

            //this function is only called if load is successful...
            System.out.println(fileName + " loaded successfully!");

        } catch (FileNotFoundException e) {
            System.out.println("An error occurred when trying to load your file...");
        }
    }
}
