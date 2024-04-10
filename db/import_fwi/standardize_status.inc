<?php

//////////////////////////////////////////////////////
// Standardized status codes in raw data
// leave blank if raw table does not have status
// codes; populate fixed status codes when load to
// staging table in final step
//////////////////////////////////////////////////////

$tbl = "fwi_occurrences";

echo "Standardizing native status:\r\n";
echo "  introduced...";
$sql="
UPDATE $tbl
SET native_status=status_verbatim
;
-- Introduced
UPDATE $tbl
SET native_status=
CASE
WHEN native_status LIKE '%cultivated%' THEN 'introduced'
WHEN native_status LIKE '%exotic%' THEN 'introduced'
WHEN native_status LIKE '%invasive%' THEN 'introduced'
WHEN native_status LIKE '%natiralized%' THEN 'introduced'
WHEN native_status LIKE '%aturalized%' THEN 'introduced'
WHEN native_status LIKE '%escaped%' THEN 'introduced'
ELSE native_status
END
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  absent...";
$sql="
-- Treating blanks as absent, although such species are typically
-- listed as cultivated on other islands
UPDATE $tbl
SET native_status=
CASE
WHEN native_status LIKE '%absent%' THEN 'absent'
WHEN native_status LIKE '%doubful%' THEN 'absent'
WHEN native_status LIKE '%doubtful%' THEN 'absent'
WHEN native_status LIKE '%dubious%' THEN 'absent'
WHEN native_status IS NULL OR trim(native_status)='' THEN 'absent'
ELSE native_status
END
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  native/endemic...";
$sql="

-- Endemic & native
UPDATE $tbl
SET native_status=
CASE
WHEN native_status LIKE '%endemic%' THEN 'endemic'
WHEN native_status LIKE '%native%' THEN 'native'
WHEN native_status='Navassa' THEN 'native'
WHEN native_status='possible' THEN 'native'
WHEN native_status='St. Thomas' THEN 'native'
WHEN native_status LIKE '%hybrid%' THEN 'native'
ELSE native_status
END
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "Standardizing cultivated status...";
$sql="
UPDATE $tbl
SET cult_status=
CASE
WHEN status_verbatim LIKE '%cult%' THEN 'cultivated'
ELSE NULL
END
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "Adjusting native status for cultivated species...";
// Assume introduced if cultivated and species was coded
// as absent
$sql="
UPDATE $tbl
SET native_status='introduced'
WHERE cult_status='cultivated'
AND (
	native_status IS NULL 
	OR trim(native_status)=''
	OR native_status='absent'
)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>