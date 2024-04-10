<?php

echo "  Indexing table `$tbl_raw_final`...";
$sql="
ALTER TABLE $tbl_raw_final 
ADD INDEX (country),
ADD INDEX (state_province)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>