/* David McCain - CGS2545 Assignment 5 */

USE airline

/* create 2 new tables */

CREATE TABLE airport (
faa char(3) NOT NULL,
icao char(4) NOT NULL UNIQUE,
cityServed char(5) NOT NULL,
PRIMARY KEY (faa),
FOREIGN KEY (cityServed) REFERENCES cityState (zipCode)
);

CREATE TABLE aircraft (
ID int NOT NULL PRIMARY KEY AUTO_INCREMENT,
manufacturer varChar(50) NOT NULL,
icaoCode varChar(5) NOT NULL,
model varChar(50) NOT NULL,
engineClass enum('Piston','Jet','Turboprop') NOT NULL DEFAULT 'Turboprop',
numEngine int NOT NULL DEFAULT 1,
numSeat int NOT NULL DEFAULT 10
);

/* insert data into 3 tables */

INSERT INTO cityState (city, state, zipCode) VALUES
('Daytona Beach','FL',32114),
('Fort Lauderdale','FL',33301),
('Fort Myers','FL',33900),
('Fort Walton Beach','FL',32547),
('Gainesville','FL',32601),
('Jacksonville','FL',32099),
('Key West','FL',33041),
('Melbourne','FL',32904),
('Miami','FL',33109),
('Orlando','FL',32801),
('Panama City','FL',32401),
('Pensacola','FL',32501),
('Punta Gorda','FL',33950),
('Sanford','FL',32771),
('Sarasota','FL',34231),
('St. Petersburg','FL',33701),
('Tallahassee','FL',32301),
('Tampa','FL',33602),
('West Palm Beach','FL',33401);

INSERT INTO airport (cityServed, faa, icao) VALUES
(32114,'DAB','KDAB'),
(33301,'FLL','KFLL'),
(33900,'RSW','KRSW'),
(32547,'VPS','KVPS'),
(32601,'GNV','KGNV'),
(32099,'JAX','KJAX'),
(33041,'EYW','KEYW'),
(32904,'MLB','KMLB'),
(33109,'MIA','KMIA'),
(32801,'MCO','KMCO'),
(32401,'ECP','KECP'),
(32501,'PNS','KPNS'),
(33950,'PGD','KPGD'),
(32771,'SFB','KSFB'),
(34231,'SRQ','KSRQ'),
(33701,'PIE','KPIE'),
(32301,'TLH','KTLH'),
(33602,'TPA','KTPA'),
(33401,'PBI','KPBI');

INSERT INTO aircraft (manufacturer, icaoCode, model, engineClass, numEngine, numSeat) VALUES
('Acro Sport','ACRO','Acro Sport','Piston',1,10),
('Adam Aircraft Industries','A500','A-500','Piston',2,20),
('Beechcraft','B18T','Model 18 Turboliner','Turboprop',2,40),
('Boeing','B743','747-300SR','Jet',4,75),
('Cessna','C526','CitationJet','Jet',2,50),
('Embraer','E170','EMB 175-E2','Jet',2,30),
('Globe Aircraft/TEMCO','GC1','GC-1B Globe','Piston',1,40),
('Israel Aircraft Industries','WW23','1123 Westwind','Jet',4,60),
('North American Rockwell','SBR1','Sabre 40/60','Jet',2,50),
('Piper','PA18','PA-18-150 Super Cub','Piston',1,30);

/* test cases 1-3 */

SELECT * FROM cityState;
SELECT * FROM airport;
SELECT * FROM aircraft;

/* join query - test case 4 */

SELECT a.faa, a.icao, c.city, c.state, c.zipCode
FROM airport AS a
INNER JOIN cityState AS c ON a.cityServed = c.zipCode
ORDER BY c.city;
