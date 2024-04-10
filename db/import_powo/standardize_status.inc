<?php

//////////////////////////////////////////////////////
// Standardized status codes in raw data
// Notice conversion of "Absent" and "Doubtful"
// to "introduced". This is a temporary fix until
// I alter code to include separate category for
// "absent" in table distribution
//////////////////////////////////////////////////////

echo "  Standardizing status codes...";

//echo "  Native status...";
$sql="
UPDATE $tbl_raw
SET establishment=
CASE
WHEN establishment='Introduced' THEN 'introduced'
WHEN establishment='Native' THEN 'native'
WHEN establishment='Absent' THEN 'introduced'
WHEN establishment='Doubtful' THEN 'introduced'
ELSE establishment
END
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>