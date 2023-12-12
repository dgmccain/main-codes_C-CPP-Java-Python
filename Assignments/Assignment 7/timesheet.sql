/* order of data

    employee.firstName, employee.lastName, timsheet.sun, timsheet.mon, timsheet.tues, timsheet.wed, timsheet.thurs, timsheet.fri, timsheet.sat
    
    employeeId should be looked up in table employee based on employee.firstName, employee.lastName
    
    Example insert statement:
    
    INSERT INTO timesheet(employeeId, sun, mon, tues, wed, thurs, fri, sat) VALUES
    (29, 0, 8, 8, 8, 8, 8, 0);

    alternative to only entering hours that are greater than 0
    
    INSERT INTO timesheet(employeeId, mon, tues, wed, thurs, fri) VALUES
    (29, 8, 8, 8, 8, 8);
*/

Ethan, Ali, 7, 4, 9, 0, 0, 10, 3
Oliwier, Barnett, 0, 12, 6, 10, 6, 8, 0
Sara, Barron, 10, 8, 0, 0, 8, 10, 10
Ty, Bell, 12, 0, 12, 0, 4, 12, 0
Leo, Bird, 6, 6, 6, 6, 6, 5, 0
Awais, Carrillo, 12, 0, 12, 0, 4, 12, 0
Laila, Christensen, 12, 0, 12, 0, 4, 12, 0
JohnPaul, Clarke, 12, 0, 12, 0, 4, 12, 0
Aamina, Dillon, 7, 4, 9, 0, 0, 10, 3
Fern, Garner, 0, 12, 6, 10, 6, 8, 0
Louis, Giles, 6, 6, 6, 6, 6, 5, 0
Raja, Glass, 0, 8, 8, 8, 8, 8, 0
Brodie, Gordon, 6, 6, 6, 6, 6, 5, 0
Maha, Guthrie, 10, 8, 0, 0, 8, 10, 10
Ernest, Higgins, 0, 8, 8, 8, 8, 8, 0
Kaya, Hodge, 0, 12, 6, 10, 6, 8, 0
Mathew, Horton, 6, 6, 6, 6, 6, 5, 0
Floyd, Johns, 0, 8, 8, 8, 8, 8, 0
Dane, Kaiser, 8, 8, 0, 0, 8, 10, 6
Paris, Lindsey, 10, 8, 0, 0, 8, 10, 10
Kamil, Lozano, 10, 8, 0, 0, 8, 10, 10
Dawson, Marquez, 12, 0, 12, 0, 4, 12, 0
Umaiza, Melia, 8, 8, 0, 0, 8, 10, 6
Jemima, Miller, 10, 8, 0, 0, 8, 10, 10
Raheem, Montgomery, 0, 8, 8, 8, 8, 8, 0
Rebekah, Morgan, 6, 6, 6, 6, 6, 5, 0
Lauren, Morton, 7, 4, 9, 0, 0, 10, 3
Lyra, Murphy, 0, 12, 6, 10, 6, 8, 0
Hammad, Newman, 0, 8, 8, 8, 8, 8, 0
Alissa, Ortiz, 0, 8, 8, 8, 8, 8, 0
Nicholas, Pena, 8, 8, 0, 0, 8, 10, 6
Alexa, Preston, 0, 12, 6, 10, 6, 8, 0
Nico, Prince, 6, 6, 6, 6, 6, 5, 0
Javan, Rennie, 7, 4, 9, 0, 0, 10, 3
Tulisa, Roberts, 10, 8, 0, 0, 8, 10, 10
Malik, Vincent, 0, 12, 6, 10, 6, 8, 0
Krystal, Walters, 8, 8, 0, 0, 8, 10, 6
Honey, Warren, 8, 8, 0, 0, 8, 10, 6
Ali, Waters, 0, 8, 8, 8, 8, 8, 0
Harvey, West, 12, 0, 12, 0, 4, 12, 0