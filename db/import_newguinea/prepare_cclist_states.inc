<?php

/////////////////////////////////////////////////////
// Extracts empirical table of states from the raw data
/////////////////////////////////////////////////////

echo "Preparing table of comprehensive checklist states...";
$tbl_cclist_states = $src . "_cclist_states";
$sql="
DROP TABLE IF EXISTS $tbl_cclist_states;
CREATE TABLE $tbl_cclist_states
SELECT DISTINCT
b.state_province_id,
b.country,
b.state_province_std
FROM $tbl_raw_final a JOIN state_province b
ON a.country=b.country AND a.state_province=b.state_province_std
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>