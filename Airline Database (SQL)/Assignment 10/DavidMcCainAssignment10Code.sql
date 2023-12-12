/* David McCain - CGS2545 Assignment 10 */

/* Change to use the database airline */
USE airline;

/* Set delimiter to $$ */
DELIMITER $$

/* Create stored procedure payDeposit */
DELIMITER $$
CREATE PROCEDURE payDeposit (
    IN employeeNum INT,
    INOUT deposit VARCHAR(4000)
)
BEGIN
    /* Declare variables */
    DECLARE v_finished INT DEFAULT 0;
    DECLARE v_lines VARCHAR(100) DEFAULT "--------------------------------------------------------------------------------";
    DECLARE v_empFirst VARCHAR(100) DEFAULT "";
    DECLARE v_empLast VARCHAR(100) DEFAULT "";
    DECLARE v_empAddress VARCHAR(100) DEFAULT "";
    DECLARE v_empCity VARCHAR(100) DEFAULT "";
    DECLARE v_empState VARCHAR(100) DEFAULT "";
    DECLARE v_empZip VARCHAR(100) DEFAULT "";
    DECLARE v_tHours INT DEFAULT 0;
    DECLARE v_pHourly DECIMAL(5,2) DEFAULT 0.0;
    DECLARE v_overtime INT DEFAULT 0;
    DECLARE v_count INT DEFAULT 0;
    DECLARE v_deposit DECIMAL(8,2) DEFAULT 0.0;

    /* Declare cursor */
    DECLARE employee_cursor CURSOR FOR
        SELECT
            e.firstName,
            e.lastName,
            e.address,
            cs.city,
            cs.state,
            cs.zipCode,
            SUM(t.sun+t.mon+t.tues+t.wed+t.thurs+t.fri+t.sat) AS "hours",
            p.hourly
        FROM
            employee e
            JOIN cityState AS cs ON e.zipCode = cs.zipCode
            JOIN timesheet AS t ON e.ID = t.employeeID
	    JOIN employeePosition AS ep ON e.ID = ep.employeeID
            JOIN position AS p ON ep.positionID = p.ID
        WHERE
            e.ID = employeeNum
        GROUP BY
            e.firstName, e.lastName, e.address, cs.city, cs.state, cs.zipCode, p.hourly;

    /* Declare continue handler */
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET v_finished = 1;

    /* Open cursor */
    OPEN employee_cursor;

    /* Loop through cursor */
    get_employee: LOOP
        FETCH employee_cursor INTO v_empFirst, v_empLast, v_empAddress, v_empCity, v_empState, v_empZip, v_tHours, v_pHourly;

        IF v_finished = 1 THEN
            LEAVE get_employee;
        END IF;

        SET v_count = v_count + 1;

        IF v_count = 1 THEN
            IF v_tHours <= 40 THEN
                SET v_deposit = v_tHours * v_pHourly;
            ELSE
                SET v_overtime = (v_tHours - 40) * (v_pHourly * 1.5);
                SET v_deposit = 40 * v_pHourly + v_overtime;
            END IF;

            /* Update deposit */
            SET deposit = CONCAT(
                deposit, 
                '\nFrom:\n\nCGS 2545 Regional Airlines \nUCF\nMSB 260\n\n',
                'Pay to the order of:\n\n',
                v_empFirst, ' ', v_empLast, '\n',
                v_empAddress, '\n',
                v_empCity, ', ', v_empState, ' ', v_empZip, '\n',
                '\nIn the amount of:\n\n$',
                v_deposit,
                '\n\n*** Pay will be deposited into account number provided ***\n',
                '\n', v_lines, '\n'
            );
        END IF;
    END LOOP;

    /* Close cursor */
    CLOSE employee_cursor;
END $$

/* Set delimiter back to ; */
DELIMITER ;

/*
Source code to test the stored procedure - Note: Make sure to replace employeeId in the test code with the actual employee ID you want to test...

-- Set session variable
SET @deposit = "";
-- Call stored procedure
CALL payDeposit(employeeId, @deposit);
-- Select @deposit
SELECT @deposit;
*/

SET @deposit = "";
CALL payDeposit(39, @deposit);
SELECT @deposit;
SET @deposit = "";
CALL payDeposit(29, @deposit);
SELECT @deposit;
SET @deposit = "";
CALL payDeposit(19, @deposit);
SELECT @deposit;
SET @deposit = "";
CALL payDeposit(24, @deposit);
SELECT @deposit;
SET @deposit = "";
CALL payDeposit(14, @deposit);
SELECT @deposit;
SET @deposit = "";
CALL payDeposit(13, @deposit);
SELECT @deposit;
SET @deposit = "";
CALL payDeposit(3, @deposit);
SELECT @deposit;
SET @deposit = "";
CALL payDeposit(30, @deposit);
SELECT @deposit;
SET @deposit = "";
CALL payDeposit(34, @deposit);
SELECT @deposit;
SET @deposit = "";
CALL payDeposit(38, @deposit);
SELECT @deposit;
