<?php

///////////////////////////////////////////////////
// Create new indexed table of just the political
// divisions of comprehensive checklists only.
// This speeds up joins in susubsequent queries
///////////////////////////////////////////////////

echo "Creating table of comprehensive checklists...";
$sql="
DROP TABLE IF EXISTS cclist;

CREATE TABLE cclist
SELECT DISTINCT country, state_province, county_parish
FROM distribution d JOIN source s 
ON d.source_id=s.source_id
WHERE is_comprehensive=1;

ALTER TABLE cclist
ADD INDEX(country),
ADD INDEX(state_province),
ADD INDEX(county_parish);
";
sql_execute_multiple($dbh, $sql);	

// Add US and Canada as country-level checklists
// Necessary because database only includes state- 
// and province-level lists, but these also function 
// collectively as comprehensive country-lists.
// DISTINCT values selected in case country-level 
// entries were already present
$sql="
INSERT INTO cclist 
	(country)
VALUES 
	('United States'),
	('Canada');
DROP TABLE IF EXISTS cclist2;
CREATE TABLE cclist2 LIKE cclist;
INSERT INTO cclist2 SELECT DISTINCT * FROM cclist;
DROP TABLE cclist;
RENAME TABLE cclist2 TO cclist;
";
sql_execute_multiple($dbh, $sql);	
echo $done;


?>