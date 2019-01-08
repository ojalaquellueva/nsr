<?php

////////////////////////////////////////
// Delete all observations from cache
////////////////////////////////////////

include "dbw2_open.php";

$sql="
TRUNCATE cache;
";
sql_execute_multiple($dbh, $sql);

mysqli_close($dbw2);

?>