<?php

////////////////////////////////////////
// Delete all observations from cache
////////////////////////////////////////

include "dbw2_open.php";

$sql="
TRUNCATE cache;
";
sql_execute_multiple($sql);

mysql_close($dbw2);

?>