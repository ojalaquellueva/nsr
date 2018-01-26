<?php

//////////////////////////////////////////////////////
// Make temporary copy of table observation for 
// export, with changes.
// Dump table as results file to data directory
//////////////////////////////////////////////////////

include "dbw_open.php";

if ($echo_on) echo "Saving results to $resultsfile:\r\n";

if ($echo_on) echo "  Creating duplicate table for export...";
$sql="
DROP TABLE IF EXISTS observation_temp;
CREATE TABLE observation_temp LIKE observation;
INSERT INTO observation_temp SELECT * FROM observation;
ALTER TABLE observation_temp
DROP COLUMN is_in_cache;
";
sql_execute_multiple($sql);
if ($echo_on) echo "done\r\n";

if ($echo_on) echo "  Setting NULLs to empty string...";
if (!(null_to_empty_string('observation_temp'))) die("Error\r\n.");
if ($echo_on) echo "done\r\n";


if ($echo_on) echo "  Exporting file...";
$cmd="mysql -u $USERW --password=$PWDW -B $DB_BATCH -e 'select * from observation_temp' > $resultsfile";
exec($cmd);
if ($echo_on) echo $done;

if ($echo_on) echo "  Cleaning up...";
$sql="
DROP TABLE IF EXISTS observation_temp;
";
sql_execute_multiple($sql);
if ($echo_on) echo "done\r\n";

include "db_close.php";

?>