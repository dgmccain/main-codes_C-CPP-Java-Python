import java.time.LocalDate;

public class Account {
    // Fields
    private String id;
    private double balance;
    private double annualInterestRate;
    private LocalDate dateCreated;

    // Constructors
    public Account() {
        // Default Constructor Populates Account Without Parameters
        setId("NEW ID");
        setBalance(0.0);
        this.dateCreated = getDateCreated();
        setAnnualInterestRate(0.0);
    }
    public Account(String id, double balance) {
        // Constructor Populates Account Using Parameter Data
        setId(id);
        setBalance(balance);
        this.dateCreated = getDateCreated();
        setAnnualInterestRate(0.0);
    }

    // Getters and Setters
    // ID
    String getId() {
        return this.id;
    }
    void setId(String id) {
        this.id = id;
    }

    // Balance
    double getBalance() {
        return this.balance;
    }
    void setBalance(double balance) {
        this.balance = balance;
    }

    // Annual Interest Rate
    double getAnnualInterestRate() {
        return this.annualInterestRate;
    }
    void setAnnualInterestRate(double annualInterestRate) {
        this.annualInterestRate = annualInterestRate;
    }

    // Date Created
    LocalDate getDateCreated() {
        LocalDate currentDate = LocalDate.now();
        return currentDate;
    }

    // Monthly Interest Rate
    double getMonthlyInterestRate() {
        // Calculation
        double result = this.annualInterestRate / 12.0;
        return result;
    }

    // Withdraw
    void withdraw(double withdrawAmount) {
        // Calculation
        if (this.balance - withdrawAmount >= 0.0) {
            this.balance -= withdrawAmount;
        }
        // Error Message
        else {
            System.out.println("ERROR - You do not a high enough balance");
        }
    }

    // Deposit
    void deposit(double depositAmount) {
        // Calculation
        this.balance += depositAmount;
    }

    // Check If Equals
    @Override
    public boolean equals(Object object) {
        boolean status = false;

        //Check if ID Of The Object Parameter Equals getId() Method Return Value
        if (object instanceof Account){
            if (getId().equals(((Account) object).getId())) {
                status = true;
            }
        }
        return status;
    }

    // Convert Account Data To String
    @Override
    public String toString() {
        String str;
        str = "ID: " + this.id
                + "\nBalance: " + this.balance
                + "\nAnnual Interest Rate: " + this.annualInterestRate
                + "\nDate Created: " + this.dateCreated;
        return str;
    }
}
