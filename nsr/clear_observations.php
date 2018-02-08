<?php

////////////////////////////////////////
// Delete all observations for this job
////////////////////////////////////////

include "dbw2_open.php";

if ($echo_on) echo "Clearing current job from table observations...";
$sql="
DELETE FROM observation 
WHERE $JOB_WHERE_NA 
;
";
sql_execute_multiple($sql);
if ($echo_on) echo $done;

mysql_close($dbw2);

?>