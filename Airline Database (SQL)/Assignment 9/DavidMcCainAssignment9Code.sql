/* David McCain - CGS2545 Assignment 9 */

/* change to database 'airline' */
USE airline;

/* verify current user */
SELECT CURRENT_USER;

/* create new user */
CREATE USER 'david'@'localhost' IDENTIFIED BY 'cgs2545$%';

/* verify new user */
SELECT host, user, select_priv, insert_priv, update_priv, delete_priv, create_priv, drop_priv
FROM mysql.user;

/* grant new user permissions */
GRANT SELECT, INSERT, UPDATE ON airline.* TO 'david'@'localhost';

/* verify new user permissions */
SHOW GRANTS FOR 'david'@'localhost';

/* change user from root to new user */
/* FOR MACOS... */
quit;
cd /usr/local/mysql/bin
./mysql -u david -p
/* enter password: cgs2545$% when prompted */

/* change to database 'airline' */
USE airline;

/* try delete query - expect user denied permission */
DELETE FROM timesheetview WHERE Hours < 40;

/* change user from new user to root */
/* FOR MACOS... */
quit;
cd /usr/local/mysql/bin
./mysql -u root -p
/* enter root password: cgs2545$% (from first day of using mySQL Workbench) */

/* change to database 'airline' */
USE airline;

/* create new user 'agent' */
CREATE USER 'agent'@'localhost' IDENTIFIED BY 'cgs2545$%';

/* verify user 'agent' */
SELECT host, user, select_priv, insert_priv, update_priv, delete_priv, create_priv, drop_priv
FROM mysql.user;

/* grant 'agent' permissions */
GRANT SELECT, SHOW VIEW ON airline.airlinemanifestview TO 'agent'@'localhost';
GRANT SELECT, SHOW VIEW ON airline.employeeflightview TO 'agent'@'localhost';
GRANT SELECT, SHOW VIEW ON airline.passengerflightview TO 'agent'@'localhost';
GRANT SELECT, SHOW VIEW ON airline.timesheetview TO 'agent'@'localhost';

/* verify 'agent' permissions */
SHOW GRANTS FOR 'agent'@'localhost';

/* change user from root to 'agent' */
/* FOR MACOS... */
quit;
cd /usr/local/mysql/bin
./mysql -u agent -p
/* enter password: cgs2545$% when prompted */

/* change to database 'airline' */
USE airline;

/* execute query to show tables */
SHOW tables;

/* enter select query from any table - expect user denied permission */
SELECT * from timesheet;
