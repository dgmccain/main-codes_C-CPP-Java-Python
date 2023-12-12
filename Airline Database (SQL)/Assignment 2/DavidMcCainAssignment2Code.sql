/* David McCain - CGS2545 Assignment 2 */

/* create and use 1 new database */

CREATE DATABASE airline;
USE airline

/* create 3 new tables */

CREATE TABLE employee (
ID int NOT NULL PRIMARY KEY AUTO_INCREMENT,
firstName varChar(50) NOT NULL,
lastName varChar(50) NOT NULL,
address varChar(90) NOT NULL,
city varChar(50) NOT NULL,
state char(2) NOT NULL,
zipCode char(5) NOT NULL,
phone char(10) NOT NULL UNIQUE,
email varChar(90) NOT NULL UNIQUE
);

CREATE TABLE passenger (
ID int NOT NULL PRIMARY KEY AUTO_INCREMENT,
firstName varChar(50) NOT NULL,
lastName varChar(50) NOT NULL,
address varChar(90) NOT NULL,
city varChar(50) NOT NULL,
state char(2) NOT NULL,
zipCode char(5) NOT NULL,
phone char(10) NOT NULL UNIQUE,
email varChar(90) NOT NULL UNIQUE
);

CREATE TABLE position (
ID int NOT NULL PRIMARY KEY AUTO_INCREMENT,
description varChar(50) NOT NULL UNIQUE,
hourly dec(5, 2) NOT NULL DEFAULT 11.00
);

/* insert data into the 3 new tables */
INSERT INTO employee (firstName, lastName, address, city, state, zipCode, phone, email) VALUES
('Paris','Lindsey','763 West Mulberry St','Clover','SC',29710,2025550132,'plindsey@isp.com'),
('Umaiza','Melia','545 Ohio Ave','Clover','SC',29710,2025550135,'umelia@isp.com'),
('Nico','Prince','20 Middle River Street','Willoughby','OH',44094,2025550137,'nprince@isp.com'),
('Javan','Rennie','8112 North Country St','Willoughby','OH',44094,2025550139,'jrennie@isp.com'),
('Ali','Waters','83 Rockland Lane','Willoughby','OH',44094,2025550144,'awaters@isp.com'),
('JohnPaul','Clarke','1 Riverside Lane','Willoughby','OH',44094,2025550153,'jpcClarke@isp.com'),
('Dane','Kaiser','694 Wall Road','Willoughby','OH',44094,2025550155,'kdaiser@isp.com'),
('Hammad','Newman','9970 State Court','Duluth','GA',30096,2025550157,'hnewman@isp.com'),
('Maha','Guthrie','54 Woodsman Drive','Duluth','GA',30096,2025550161,'mguthrie@isp.com'),
('Tulisa','Roberts','7174 Studebaker Street','Duluth','GA',30096,2025550163,'troberts@isp.com');

INSERT INTO passenger (firstName, lastName, address, city, state, zipCode, phone, email) VALUES
('Igor','Prince','12 Creekside St','Huntington Beach','CA',92647,2025550199,'iprince@isp.com'),
('Dante','Rennie','137 Wall St','Memphis','TN',38117,2225550112,'drennie@isp.com'),
('Thomas','Waters','411 Shirley St','Abingdon','VA',24210,2225550115,'twaters@isp.com'),
('Avaya','Clarke','7771 Border Court','San Marcos','CA',92078,2225550119,'aclarke@isp.com'),
('Haniya','Kaiser','6 South Sulphur Springs Street','Jefferson','LA',70121,2225550121,'hkaiser@isp.com'),
('Victor','Newman','942 New Saddle Drive','Covington','LA',70433,2225550122,'vnewman@isp.com'),
('Douglas','Guthrie','9 Wrangler Ave','Ontario','CA',91764,2225550124,'dguthrie@isp.com'),
('Brian','Roberts','7319 S. Greenview Drive','Cuyahoga Falls','OH',44223,2225550125,'broberts@isp.com'),
('Paris','Solis','763 West Mulberry St','Battle Creek','MI',49016,2025550132,'psolis@isp.com'),
('Umaiza','Heath','545 Ohio Ave','Scottsdale','AZ',85260,2025550135,'uheath@isp.com'),
('Yvonne','Goodman','12 Creekside St','Nashville','TN',37205,2025550109,'ygoodman@isp.com'),
('Dante','Mackenzie','137 Wall St','Nashville','TN',37205,2025550112,'dmackenzie@isp.com'),
('Alysha','Rollins','411 Shirley St','Nashville','TN',37205,2025550115,'arollins@isp.com'),
('Avaya','Gonzalez','7771 Border Court','Nashville','TN',37205,2025550119,'agonzalez@isp.com'),
('Haniya','Kelly','6 South Sulphur Springs Street','Nashville','TN',37205,2025550121,'hkelly@isp.com'),
('Nathalie','Chambers','942 New Saddle Drive','Clover','SC',29710,2025550122,'nchambers@isp.com'),
('Dante','Rollins','9 Wrangler Ave','Clover','SC',29710,2025550124,'drollins@isp.com'),
('Beverley','Mckee','7319 S. Greenview Drive','Clover','SC',29710,2025550125,'bmckee@isp.com'),
('Robin','Solis','8474 Wentworth Street','Duluth','GA',30096,2025550164,'rsolis@isp.com'),
('Kavita','Heath','796 Hartford St','Duluth','GA',30096,2025550165,'kheath@isp.com'),
('Meera','White','484 Bridge St','Piscataway','NJ',08854,2025550166,'mwhite@isp.com'),
('Bradlee','Esparza','7031 Gainsway St','Piscataway','NJ',08854,2025550173,'besparza@isp.com'),
('Leilani','Leonard','37 Monroe Street','Piscataway','NJ',08854,2025550175,'lleonard@isp.com'),
('Stefanie','Brook','7990 West Surrey St','Piscataway','NJ',08854,2025550179,'sbrook@isp.com'),
('Grover','Squires','7618 Madison Court','Piscataway','NJ',08854,2025550180,'gsquires@isp.com'),
('Jonathan','Kumar','25 Annadale Court','Jupiter','FL',33458,2025550182,'jkumar@isp.com'),
('Angus','Neville','9841 Smith Drive','Jupiter','FL',33458,2025550187,'aneville@isp.com'),
('Uzair','Sparrow','7999 Hall Street','Jupiter','FL',33458,2025550188,'usparrow@isp.com'),
('Amari','Currie','8411 Pleasant St','Jupiter','FL',33458,2025550194,'acurrie@isp.com'),
('Imaani','Wallace','33 Pierce Rd','Jupiter','FL',33458,2025550195,'iwallace@isp.com'),
('Efe','House','97 High Point Street','Glenarden','MD',20706,2025550196,'ehouse@isp.com'),
('Atticus','Atkinson','66 Harrison Dr','Glenarden','MD',20706,2025550197,'aatkinson@isp.com'),
('Michelle','Ramirez','370 Hill Field Ave','Glenarden','MD',20706,2025550198,'mramirez@isp.com'),
('Remy','Hassan','249 Devon Lane','Glenarden','MD',20706,2225550199,'rhassan@isp.com'),
('Jordana','Beck','7911 Carson Lane','Glenarden','MD',20706,2025550200,'jbeck@isp.com');

INSERT INTO position (description, hourly) VALUES
('Pilot', 58.00),
('Co-pilot', 40.00),
('Flight Attendant', 48.00),
('Cabin Attendant', 38.00),
('Aeronautical Engineer', 42.00),
('Aircraft Mechanic', 33.00),
('Airport Police', 20.00),
('Security', 14.00),
('Airport Planner', 46.00),
('Airfield Operations Specialists', 22.00),
('Airline Ticket Agent', 13.00),
('Reservation Service Agent', 15.00),
('Passenger Service Agent', 11.00),
('Meteorologist', 37.00),
('Baggage Handler', 13.00),
('Administrative Jobs', 17.00),
('Cleaning Jobs', 13.00);

/* view all contents of the 3 tables */

SELECT * FROM employee;
SELECT * FROM passenger;
SELECT * FROM position;
