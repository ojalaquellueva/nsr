<?php

echo "  Loading table cultspp...";
$sql="
INSERT INTO cultspp (
source_id,
taxon
)
SELECT DISTINCT
$source_id,
taxon
FROM cultspp_staging
WHERE is_in_db=0
AND taxon_rank IN ('species','var.','susp.','fo.','variety','subspecies','forma','infraspecies','subspecific');
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>