/* David McCain - CGS2545 Assignment 11 */

/* Change to use the database airline */
USE airline;

/* Set delimiter to $$ */
DELIMITER $$

/* Create new trigger */
CREATE TRIGGER after_employee_insert
AFTER INSERT ON employee
FOR EACH ROW
BEGIN
    INSERT INTO timesheet (employeeId, sun, mon, tues, wed, thurs, fri, sat)
    VALUES (NEW.id, 0, 0, 0, 0, 0, 0, 0);
END $$

/* Set delimiter back to ; */
DELIMITER ;

/* Insert data into existing employee table */
INSERT INTO employee (firstName, lastName, address, zipCode, phone, email) VALUES
('Fatima','Robles','2519 Bottom Lane','33900','5126024452','frobles@airline.com'),
('Angelita','Turner','3447 Valley Lane','33109','8574960348','aturner@airline.com'),
('Robert','Johnson','526 Metz Lane','32401','5306942786','rjohnson@airline.com'),
('Francisca','Spence','1253 Coulter Lane','32547','8043389754','fspence@airline.com'),
('Matthew','Lee','756 Long Street','32601','3522635642','mlee@airline.com');

/* Create new table */
CREATE TABLE employeeAudit (
    ID INT AUTO_INCREMENT NOT NULL,
    employeeNumber INT NOT NULL,
    firstName VARCHAR(50) NOT NULL,
    lastName VARCHAR(50) NOT NULL,
    email VARCHAR(90) NOT NULL UNIQUE,
    changeDate DATETIME DEFAULT NULL,
    action VARCHAR(50) DEFAULT NULL,
    PRIMARY KEY (ID)
);

/* Set delimiter to $$ */
DELIMITER $$

/* Create new trigger */
CREATE TRIGGER before_employee_update
BEFORE UPDATE ON employee
FOR EACH ROW
BEGIN
    INSERT INTO employeeAudit (action, employeeNumber, firstName, lastName, email, changeDate)
    VALUES ('UPDATE', OLD.id, OLD.firstName, OLD.lastName, OLD.email, NOW());
END $$

/* Set delimiter back to ; */
DELIMITER ;

/* Update email addresses for employees with '@isp.com' or '@cruise.com' */
/* NOTE: default case will result in UPDATE to old email, thus inserted into employeeAudit */
UPDATE employee
SET email = 
    CASE 
        WHEN email LIKE '%@isp.com' THEN REPLACE(email, '@isp.com', '@airline.com')
        WHEN email LIKE '%@cruise.com' THEN REPLACE(email, '@cruise.com', '@airline.com')
        ELSE email
    END;

/* test cases 1-3 */
SELECT * FROM employee;
SELECT * FROM timesheet;
SELECT * FROM employeeAudit;
