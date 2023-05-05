public class Application {

    public static void main(String[] args) {
        // Display Testing Message - Start
        System.out.println("Beginning tests.");

        // Create Account Using Constructor With Parameters
        Account account1 = new Account("12345", 125.50);

        // Check Account Creation
        if (account1.equals(account1) == false) {
            System.out.println("FAILED account creation");
        }

        // Set Annual Interest Rate
        account1.setAnnualInterestRate(7.2);
        if (account1.getAnnualInterestRate() != 7.2) {
            System.out.println("FAILED get/set annualInterestRate");
        }

        // Withdraw
        account1.withdraw(100.0);
        if (account1.getBalance() != 25.50) {
            System.out.println("FAILED get/set withdraw");
        }

        // ERROR Test
        // Withdraw Too Much
        account1.withdraw(9999);
        if (account1.getBalance() != 25.50) {
            System.out.println("FAILED get/set withdraw");
        }

        // Deposit
        account1.deposit(200.0);
        if (account1.getBalance() != 225.50) {
            System.out.println("FAILED get/set deposit");
        }

        // Set ID
        account1.setId("first account id");
        if (account1.getId() != "first account id") {
            System.out.println("FAILED get/set id");
        }

        // Set Balance
        account1.setBalance(12345.0);
        if (account1.getBalance() != 12345.0) {
            System.out.println("FAILED get/set balance");
        }

        // Get Monthly Interest
        if (account1.getMonthlyInterestRate() != (account1.getAnnualInterestRate() / 12)) {
            System.out.println("FAILED get monthly interest rate");
        }

        // Test the Equals Method
        if (account1.equals(account1) == false) {
            System.out.println("FAILED account equals check");
        }

        // Test the toString Method
        if (!account1.toString().equals("ID: " + account1.getId()
                + "\nBalance: " + account1.getBalance()
                + "\nAnnual Interest Rate: " + account1.getAnnualInterestRate()
                + "\nDate Created: " + account1.getDateCreated())) {
            System.out.println("FAILED account toString check");
        }

        // Create Account Using Default Constructor With No Parameters
        Account account2 = new Account();

        // Check Account Creation
        if (account2.equals(account2) == false) {
            System.out.println("FAILED default account creation");
        }

        // Set Annual Interest Rate
        account2.setAnnualInterestRate(8.4);
        if (account2.getAnnualInterestRate() != 8.4) {
            System.out.println("FAILED get/set annualInterestRate");
        }

        // Deposit
        account2.deposit(200.0);
        if (account2.getBalance() != 200.0) {
            System.out.println("FAILED get/set deposit");
        }

        // Withdraw
        account2.withdraw(50.0);
        if (account2.getBalance() != 150.0) {
            System.out.println("FAILED get/set withdraw");
        }

        // ERROR Test
        // Withdraw Too Much
        account2.withdraw(9999);
        if (account2.getBalance() != 150.0) {
            System.out.println("FAILED get/set withdraw");
        }

        // Set ID
        account2.setId("new id");
        if (account2.getId() != "new id") {
            System.out.println("FAILED get/set id");
        }

        // Set Balance
        account2.setBalance(12345.0);
        if (account2.getBalance() != 12345.0) {
            System.out.println("FAILED get/set balance");
        }

        // Get Monthly Interest
        if (account2.getMonthlyInterestRate() != (account2.getAnnualInterestRate() / 12)) {
            System.out.println("FAILED get monthly interest rate");
        }

        // Test the Equals Method
        if (account2.equals(account2) == false) {
            System.out.println("FAILED account equals check");
        }

        // Test the toString Method
        if (!account2.toString().equals("ID: " + account2.getId()
                + "\nBalance: " + account2.getBalance()
                + "\nAnnual Interest Rate: " + account2.getAnnualInterestRate()
                + "\nDate Created: " + account2.getDateCreated())) {
            System.out.println("FAILED account toString check");
        }

        // Display Testing Message - Finish
        System.out.println("Finished tests.");
    }
}
