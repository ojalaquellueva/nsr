<?php

/////////////////////////////////////////////////////
// Optimizations:
// 1. Creates columns state_province_full and 
//    county_parish_full. Allow joings on single column
// 	  instead of 2-3  columns.
/////////////////////////////////////////////////////

echo "Performing optimizations:\r\n";

echo "  Standardizing case..";
$sql="
UPDATE distribution
SET native_status=LOWER(native_status)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Setting null native_status to 'unknown'..";
$sql="
UPDATE distribution
SET native_status='unknown'
WHERE native_status IS NULL OR trim(native_status)=''
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Populating column state_province_full..";
$sql="
-- Target value will be null if both values not present
UPDATE distribution
SET state_province_full=CONCAT_WS(':',
country,state_province
)
WHERE country IS NOT NULL AND state_province IS NOT NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Populating column county_parish_full..";
$sql="
UPDATE distribution
SET county_parish_full=CONCAT_WS(':',
country,state_province,county_parish
)
WHERE country IS NOT NULL 
AND state_province IS NOT NULL
AND county_parish IS NOT NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Populating column poldiv_full..";
$sql="
UPDATE distribution
SET poldiv_full=
CASE
WHEN country IS NOT NULL AND state_province IS NULL THEN country
WHEN state_province IS NOT NULL AND county_parish IS NULL THEN state_province_full
WHEN county_parish IS NOT NULL THEN county_parish_full
ELSE NULL
END
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Populating column poldiv_type..";
$sql="
UPDATE distribution
SET poldiv_type=
CASE
WHEN country IS NOT NULL AND state_province IS NULL THEN 'country'
WHEN state_province IS NOT NULL AND county_parish IS NULL THEN 'state_province'
WHEN county_parish IS NOT NULL THEN 'county_parish'
ELSE NULL
END
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Indexing the columns..";
$sql="
ALTER TABLE distribution
ADD INDEX (state_province_full),
ADD INDEX (county_parish_full),
ADD INDEX (poldiv_full),
ADD INDEX (poldiv_type)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;


?>