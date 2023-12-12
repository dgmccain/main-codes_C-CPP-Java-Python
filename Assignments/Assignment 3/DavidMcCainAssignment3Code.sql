/* David McCain - CGS2545 Assignment 3 */

USE airline

/* create 1 new table */

CREATE TABLE cityState (
city varChar(90) NOT NULL,
state char(2) NOT NULL,
zipCode char(5) NOT NULL UNIQUE PRIMARY KEY
);

/* insert data into new table from 2 existing tables */

INSERT INTO cityState (city, state, zipCode)
SELECT DISTINCT city, state, zipCode
FROM employee
WHERE zipCode NOT IN (SELECT zipCode FROM cityState);

INSERT INTO cityState (city, state, zipCode)
SELECT DISTINCT city, state, zipCode
FROM passenger
WHERE zipCode NOT IN (SELECT zipCode FROM cityState);

/* add foreign key to 1 existing table, then drop 2 columns */

ALTER TABLE employee
ADD FOREIGN KEY (zipCode) REFERENCES cityState (zipCode);

ALTER TABLE employee
DROP COLUMN city,
DROP COLUMN state;

/* add foreign key to 1 existing table, then drop 2 columns */

ALTER TABLE passenger
ADD FOREIGN KEY (zipCode) REFERENCES cityState (zipCode);

ALTER TABLE passenger
DROP COLUMN city,
DROP COLUMN state;
  
/* create 1 new table */

CREATE TABLE employeePosition (
employeeID int NOT NULL UNIQUE,
positionID int NOT NULL,
PRIMARY KEY (employeeID, positionID),
FOREIGN KEY (employeeID) REFERENCES employee (ID),
FOREIGN KEY (positionID) REFERENCES position (ID)
);

/* insert data into new table using info from existing tables */

INSERT INTO employeePosition (employeeID, positionID) VALUES (1, 1);
INSERT INTO employeePosition (employeeID, positionID) VALUES (2, 2);
INSERT INTO employeePosition (employeeID, positionID) VALUES (3, 3);
INSERT INTO employeePosition (employeeID, positionID) VALUES (4, 6);
INSERT INTO employeePosition (employeeID, positionID) VALUES (5, 7);
INSERT INTO employeePosition (employeeID, positionID) VALUES (6, 11);
INSERT INTO employeePosition (employeeID, positionID) VALUES (7, 14);
INSERT INTO employeePosition (employeeID, positionID) VALUES (8, 15);
INSERT INTO employeePosition (employeeID, positionID) VALUES (9, 15);
INSERT INTO employeePosition (employeeID, positionID) VALUES (10, 16);

/* test cases 1-7 */

SELECT * FROM employee;

SELECT * FROM passenger;

SELECT * FROM cityState;

DESCRIBE employee;

DESCRIBE passenger;

SELECT * FROM employeePosition;

SELECT e.firstName AS "Employee First Name" , e.lastName AS "Employee Last Name", e.phone AS "Employee Phone", p.description AS "Employee Position"
FROM employee e, position p, employeePosition ep
WHERE ep.employeeID = e.ID AND ep.positionID = p.ID; 
