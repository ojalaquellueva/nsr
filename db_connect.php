<?php

// old-style mysql connection
// use for legacy scripts until can get around to updating them
// connect to mysql
$dbh = mysql_connect($HOST,$USERW,$PWDW,FALSE,128);
if (!$dbh) die("\r\nCould not connect to database!\r\n");

// Connect to database
$sql="USE `".$DB."`;";
sql_execute_multiple($sql);

?>