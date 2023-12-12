ALTER TABLE tablename
RENAME COLUMN oldColumnName TO newColumnName;

ALTER TABLE tablename
  ADD FOREIGN KEY (columnName) REFERENCES referredTable (referredColumn);
  
/* this is called a subquery, a query within a query */
INSERT INTO tablename
SELECT DISTINCT column, column, column
  FROM tablename
 WHERE column NOT IN 
      (SELECT DISTINCT column 
         FROM tablename);