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
sql_execute_multiple($dbw2, $sql);
if ($echo_on) echo $done;

mysqli_close($dbw2);

?>