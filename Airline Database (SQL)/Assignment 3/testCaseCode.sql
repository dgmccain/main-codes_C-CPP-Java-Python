SELECT e.firstName AS "Employee First Name" , e.lastName AS "Employee Last Name", e.phone AS "Employee Phone", p.description AS "Employee Position"
  FROM employee e, position p, employeePosition ep
 WHERE ep.employeeId = e.id
   AND ep.positionId = p.id; 
   