/* David McCain - CGS2545 Assignment 6 */

USE airline

/* create 1 new table */

CREATE TABLE flight (
ID int NOT NULL PRIMARY KEY AUTO_INCREMENT,
origin char(3) NOT NULL,
destination char(3) NOT NULL,
aircraft int NOT NULL,
departure timestamp NOT NULL,
arrival timestamp NOT NULL,
FOREIGN KEY (origin) REFERENCES airport (faa),
FOREIGN KEY (destination) REFERENCES airport (faa),
FOREIGN KEY (aircraft) REFERENCES aircraft (ID)
);

/* alter table data */

ALTER TABLE flight AUTO_INCREMENT = 100;

/* insert data into table */

INSERT INTO flight (origin, destination, aircraft, departure, arrival) VALUES
('DAB','FLL','1','2023-11-01 07:00:00','2023-11-01 08:00:00'),
('FLL','RSW','9','2023-11-01 08:00:00','2023-11-01 09:00:00'),
('RSW','VPS','2','2023-11-01 09:00:00','2023-11-01 10:00:00'),
('VPS','GNV','8','2023-11-01 10:00:00','2023-11-01 11:00:00'),
('GNV','JAX','3','2023-11-11 11:00:00','2023-11-11 12:00:00'),
('JAX','EYW','7','2023-11-11 12:00:00','2023-11-11 13:00:00'),
('EYW','MLB','4','2023-11-04 13:00:00','2023-11-04 14:00:00'),
('MLB','MIA','6','2023-11-04 14:00:00','2023-11-04 15:00:00'),
('MIA','MCO','5','2023-11-05 15:00:00','2023-11-05 16:00:00'),
('MCO','ECP','5','2023-11-05 16:00:00','2023-11-05 17:00:00'),
('ECP','PNS','6','2023-11-06 17:00:00','2023-11-06 18:00:00'),
('PNS','PGD','4','2023-11-06 19:00:00','2023-11-06 20:00:00'),
('PGD','SFB','7','2023-11-07 07:00:00','2023-11-07 08:00:00'),
('SFB','SRQ','3','2023-11-07 09:00:00','2023-11-07 10:00:00'),
('SRQ','PIE','8','2023-11-08 07:00:00','2023-11-08 08:00:00'),
('PIE','TLH','2','2023-11-08 09:00:00','2023-11-08 10:00:00'),
('TLH','TPA','9','2023-11-09 07:00:00','2023-11-09 08:00:00'),
('TPA','PBI','1','2023-11-09 10:00:00','2023-11-09 11:00:00'),
('PBI','DAB','10','2023-11-10 11:00:00','2023-11-10 12:00:00');

/* test case 1 */

SELECT * FROM flight;

/* join query - test case 2 */

SELECT f.ID AS "Flight Number", a.model AS "Aircraft", f.origin AS "Origin", f.departure AS "Departure", f.destination AS "Destination", f.arrival AS "Arrival"
FROM flight AS f
INNER JOIN aircraft AS a ON f.aircraft = a.ID
ORDER BY f.departure;
