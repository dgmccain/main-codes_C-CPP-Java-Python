/* David McCain - CGS2545 Assignment 8 */

USE airline;

/* create new view using union */

CREATE VIEW airlineManifestView AS
SELECT
    CONCAT(e.firstName, ' ', e.lastName) AS Name,
    e.phone AS "Phone Number",
    p.description AS "Role",
    f.origin AS "Origin",
    f.departure AS "Departure",
    f.destination AS "Destination",
    f.arrival AS "Arrival"
FROM
    employee e
    JOIN employeeFlight AS ef ON e.ID = ef.employeeID
    JOIN employeePosition AS ep ON e.ID = ep.employeeID
    JOIN position AS p ON ep.positionID = p.ID
    JOIN flight AS f ON ef.flightID = f.ID
UNION
SELECT
    CONCAT(p.firstName, ' ', p.lastName) AS Name,
    p.phone AS "Phone Number",
    'Passenger' AS "Role",
    f.origin AS "Origin",
    f.departure AS "Departure",
    f.destination AS "Destination",
    f.arrival AS "Arrival"
FROM
    passenger p
    JOIN passengerFlight AS pf ON p.ID = pf.passengerID
    JOIN flight AS f ON pf.flightID = f.ID;

/* test case */

SELECT * FROM airlineManifestView;
