<?php

////////////////////////////////////////////////
// Index main raw data tables after loading
////////////////////////////////////////////////

echo "Indexing table $tbl_raw...";
$sql="
ALTER TABLE $tbl_raw
ADD INDEX (id),
ADD INDEX (taxon_id),
ADD INDEX (taxon_rank),
ADD INDEX (family),
ADD INDEX (genus),
ADD INDEX (species),
ADD INDEX (taxon),
ADD INDEX (state_code),
ADD INDEX (country),
ADD INDEX (state_province),
ADD INDEX (native_status),
ADD INDEX (cult_status),
ADD INDEX (include);
";
sql_execute_multiple($sql);
echo $done;

?>