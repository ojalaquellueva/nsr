<?php

/////////////////////////////////////////////////////////////
// Fixes specific to this source, if any
//
// Leave content between this comment and closing line blank 
// if no source-specific fixes required
/////////////////////////////////////////////////////////////

echo "  Removing records not identified to species...";
$sql="
DELETE FROM `$tbl_raw`
WHERE `$fld_scientific_name` LIKE '%Not Listed%'
OR `$fld_scientific_name` LIKE '% sp.%'
OR `$fld_scientific_name`='Other other'
OR `$fld_scientific_name` NOT LIKE '% %';
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Populating column `country`...";
$sql="
UPDATE `$tbl_raw`
SET country='United States'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Translating state abbreviations...";
// change columns
$sql="
ALTER TABLE `$tbl_raw`
CHANGE State stateCode VARCHAR(5) DEFAULT NULL,
ADD COLUMN state VARCHAR(50) DEFAULT NULL,
ADD INDEX (stateCode),
ADD INDEX (state)
;
";
sql_execute_multiple($dbh, $sql);

// look up state names
$results = mysqli_query($dbh, "
SELECT DISTINCT stateCode FROM `$tbl_raw`;
");

while ($row = mysqli_fetch_assoc($results)) {
	$stateCode = $row["stateCode"];
	
	$state = state_name_US($stateCode);
	$sql="
	UPDATE `$tbl_raw`
	SET state='$state'
	WHERE stateCode='$stateCode'
	;		
	";
	sql_execute_multiple($dbh, $sql);
}

echo $done;



?>