<?php

/////////////////////////////////////////////////////
// Update native_status field (establishment)
/////////////////////////////////////////////////////

echo "  Updating native status in column `establishment`...";
$sql="
UPDATE $tbl_raw 
SET establishment=
CASE
WHEN introduced='0' THEN 'native'
WHEN introduced='1' THEN 'introduced'
ELSE 'unknown'
END
;
UPDATE $tbl_raw 
SET establishment='introduced'
WHERE introduced='0' AND location_doubtful=1
;
ALTER TABLE $tbl_raw
ADD INDEX (establishment)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>