/* David McCain - CGS2545 Assignment 7 */

USE airline;

/* create 3 new tables */

CREATE TABLE timesheet (
ID int NOT NULL PRIMARY KEY AUTO_INCREMENT,
employeeID int NOT NULL,
sun int NOT NULL DEFAULT 0,
mon int NOT NULL DEFAULT 0,
tues int NOT NULL DEFAULT 0,
wed int NOT NULL DEFAULT 0,
thurs int NOT NULL DEFAULT 0,
fri int NOT NULL DEFAULT 0,
sat int NOT NULL DEFAULT 0,
FOREIGN KEY (employeeID) REFERENCES employee (ID)
);

CREATE TABLE employeeFlight (
employeeID int NOT NULL,
flightID int NOT NULL,
PRIMARY KEY (employeeID, flightID),
FOREIGN KEY (employeeID) REFERENCES employee (ID),
FOREIGN KEY (flightID) REFERENCES flight (ID)
);

CREATE TABLE passengerFlight (
passengerID int NOT NULL,
flightID int NOT NULL,
PRIMARY KEY (passengerID, flightID),
FOREIGN KEY (passengerID) REFERENCES passenger (ID),
FOREIGN KEY (flightID) REFERENCES flight (ID)
);

/* insert data into 3 tables */

INSERT INTO timesheet (employeeId, sun, mon, tues, wed, thurs, fri, sat) VALUES
('25','7','4','9','0','0','10','3'),
('13','0','12','6','10','6','8','0'),
('27','10','8','0','0','8','10','10'),
('36','12','0','12','0','4','12','0'),
('12','6','6','6','6','6','5','0'),
('29','12','0','12','0','4','12','0'),
('32','12','0','12','0','4','12','0'),
('6','12','0','12','0','4','12','0'),
('20','7','4','9','0','0','10','3'),
('14','0','12','6','10','6','8','0'),
('21','6','6','6','6','6','5','0'),
('16','0','8','8','8','8','8','0'),
('34','6','6','6','6','6','5','0'),
('9','10','8','0','0','8','10','10'),
('39','0','8','8','8','8','8','0'),
('30','0','12','6','10','6','8','0'),
('38','6','6','6','6','6','5','0'),
('37','0','8','8','8','8','8','0'),
('7','8','8','0','0','8','10','6'),
('1','10','8','0','0','8','10','10'),
('40','10','8','0','0','8','10','10'),
('15','12','0','12','0','4','12','0'),
('2','8','8','0','0','8','10','6'),
('31','10','8','0','0','8','10','10'),
('11','0','8','8','8','8','8','0'),
('24','6','6','6','6','6','5','0'),
('35','7','4','9','0','0','10','3'),
('28','0','12','6','10','6','8','0'),
('8','0','8','8','8','8','8','0'),
('17','0','8','8','8','8','8','0'),
('18','8','8','0','0','8','10','6'),
('23','0','12','6','10','6','8','0'),
('3','6','6','6','6','6','5','0'),
('4','7','4','9','0','0','10','3'),
('10','10','8','0','0','8','10','10'),
('26','0','12','6','10','6','8','0'),
('22','8','8','0','0','8','10','6'),
('33','8','8','0','0','8','10','6'),
('5','0','8','8','8','8','8','0'),
('19','12','0','12','0','4','12','0');

INSERT INTO employeeFlight (employeeID, flightID) VALUES
('2','100'),
('3','100'),
('34','100'),
('24','100'),
('36','100'),
('38','106'),
('12','106'),
('26','106'),
('28','106'),
('32','106'),
('1','113'),
('3','113'),
('14','113'),
('26','113'),
('36','113'),
('34','116'),
('12','116'),
('24','116'),
('28','116'),
('32','116');

INSERT INTO passengerFlight (passengerID, flightID) VALUES
('2','100'),
('3','100'),
('13','100'),
('19','100'),
('35','100'),
('4','106'),
('30','106'),
('5','106'),
('25','106'),
('33','106'),
('6','113'),
('10','113'),
('20','113'),
('11','113'),
('31','113'),
('8','116'),
('14','116'),
('18','116'),
('1','116'),
('29','116');

/* create 3 new views */

CREATE VIEW timesheetView AS
SELECT
	CONCAT(e.firstName, " ", e.lastName) AS "Employee",
	p.description AS "Position",
	(t.sun + t.mon + t.tues + t.wed + t.thurs + t.fri + t.sat) AS "Hours"
FROM employee AS e
JOIN employeePosition AS ep ON e.ID = ep.employeeID
JOIN position AS p ON ep.positionID = p.ID
LEFT JOIN timesheet AS t ON e.ID = t.employeeID
ORDER BY e.lastName;

CREATE VIEW employeeFlightView AS
SELECT
	CONCAT(e.firstName, " ", e.lastName) AS "Employee",
	f.origin AS "Origin",
	f.departure AS "Departure",
	f.destination AS "Destination",
	f.arrival AS "Arrival"
FROM employee AS e
JOIN employeeFlight AS ef ON e.ID = ef.employeeID
JOIN flight AS f ON ef.flightID = f.ID
ORDER BY f.departure, e.lastName;

CREATE VIEW passengerFlightView AS
SELECT
    CONCAT(p.firstName, ' ', p.lastName) AS "Passenger",
    f.origin AS "Origin",
    f.departure AS "Departure",
    f.destination AS "Destination",
    f.arrival AS "Arrival"
FROM passenger AS p
JOIN passengerFlight AS pf ON p.ID = pf.passengerID
JOIN flight AS f ON pf.flightID = f.ID
ORDER BY f.departure, p.lastName;

/* test cases 1-6 */

SELECT * FROM timesheet;
SELECT * FROM timesheetView;
SELECT * FROM employeeFlight;
SELECT * FROM employeeFlightView;
SELECT * FROM passengerFlight;
SELECT * FROM passengerFlightView;
