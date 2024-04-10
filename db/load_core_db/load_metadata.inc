<?php

///////////////////////////////////////////////////////////////
// Populate metadata table
///////////////////////////////////////////////////////////////

echo "Populating metadata table:\r\n";

echo "  Clearing table...";
$sql="
TRUNCATE meta;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Inserting version information...";
$sql="
INSERT INTO meta (
db_version,
code_version,
build_date
)
VALUES (
'$DB_VERSION',
'$CODE_VERSION',
CURRENT_TIME()
)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>