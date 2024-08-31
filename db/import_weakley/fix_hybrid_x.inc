<?php

///////////////////////////////////////////////////////////////
// converts any encoded hybrid "x" characters to a 
// simple plain ascii "x"
///////////////////////////////////////////////////////////////

// Use this version if php not transmitting extended ascii to MySQL.
// You can tell because the literal query works if you enter it directly
// in the MySQL command line, but doesn't work if sent by php
$encoded_x = mb_convert_encoding('×', "UTF-8", mb_detect_encoding('×'));

echo "  Standarizing hybrid 'x'...";
$sql="
UPDATE `$tbl_raw`
SET `$fld_scientific_name`=REPLACE(`$fld_scientific_name`,'$encoded_x','x');
";

sql_execute_multiple($dbh, $sql);
echo $done;

?>
