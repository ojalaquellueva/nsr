<?php

//////////////////////////////////////////////////////
// Standardized status codes in raw data
//////////////////////////////////////////////////////

echo "  Standardizing status codes...";

//echo "  Native status...";
$sql="
UPDATE tropicos_raw
SET native_status='endemic'
WHERE status_verbatim LIKE '%Endemic%'
;
UPDATE tropicos_raw
SET native_status='native'
WHERE status_verbatim LIKE '%Native%'
AND native_status IS NULL
;
UPDATE tropicos_raw
SET native_status='non-native'
WHERE (
status_verbatim LIKE '%Naturalized%'
OR status_verbatim LIKE '%Adventitious%'
OR status_verbatim LIKE '%Cultivated%'
OR status_verbatim LIKE '%Introduced%'
)
AND native_status IS NULL
;
UPDATE tropicos_raw
SET native_status='unknown'
WHERE native_status IS NULL;
";
sql_execute_multiple($dbh, $sql);
//echo $done;

//echo "  Cultivated status...";
$sql="
UPDATE tropicos_raw
SET cult_status='cultivated'
WHERE status_verbatim LIKE '%cultivated%'
;
UPDATE tropicos_raw
SET cult_status='unknown'
WHERE  cult_status IS NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>