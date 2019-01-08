<?php

/////////////////////////////////////////////////////////////
// Extract unique records
/////////////////////////////////////////////////////////////

$tbl_raw_2 = $tbl_raw . "_regions";

echo "  Removing non-unique records:\r\n";

echo "    Creating table $tbl_raw_2...";
$sql="
DROP TABLE IF EXISTS $tbl_raw_2;
CREATE TABLE $tbl_raw_temp (
family VARCHAR(255) DEFAULT NULL,
genus VARCHAR(255) DEFAULT NULL,
epithet VARCHAR(255) DEFAULT NULL,
author VARCHAR(255) DEFAULT NULL,
westIndies VARCHAR(255) DEFAULT NULL,
greaterAntilles VARCHAR(255) DEFAULT NULL,
jamaica VARCHAR(255) DEFAULT NULL,
cuba VARCHAR(255) DEFAULT NULL,
caymanIsland VARCHAR(255) DEFAULT NULL,
hispaniola VARCHAR(255) DEFAULT NULL,
puertoRico VARCHAR(255) DEFAULT NULL,
virginIslands VARCHAR(255) DEFAULT NULL,
bahamas VARCHAR(255) DEFAULT NULL,
lesserAntillles VARCHAR(255) DEFAULT NULL
)  ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Insert distinct records into $tbl_raw_2...";
$sql="

INSERT INTO $tbl_raw_2 (
family,
genus,
epithet,
author,
westIndies,
greaterAntilles,
jamaica,
cuba,
caymanIsland,
hispaniola,
puertoRico,
virginIslands,
bahamas,
lesserAntillles
)
SELECT DISTINCT
family,
genus,
epithet,
author,
westIndies,
greaterAntilles,
jamaica,
cuba,
caymanIsland,
hispaniola,
puertoRico,
virginIslands,
bahamas,
lesserAntillles
FROM $tbl_raw
;
DROP TABLE $tbl_raw;
RENAME TABLE $tbl_raw_2 TO $tbl_raw;
";
sql_execute_multiple($dbh, $sql);
echo $done;


/*
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
*/

?>