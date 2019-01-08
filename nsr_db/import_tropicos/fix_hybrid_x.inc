<?php

///////////////////////////////////////////////////////////////
// converts any encoded hybrid "x" characters to a 
// simple plain ascii "x"
///////////////////////////////////////////////////////////////

$plain_x="x";

// Use this version if extended ascii is transmitted correctly by php
//$encoded_x="×";

// Use this version if php not transmitting extended ascii to MySQL.
// You can tell because the literal query works if you entire it directly
// in the MySQL command line, but doesn't work if sent by php
$encoded_x= utf8_decode('×');

echo "  Standarizing hybrid 'x'...";

// The double plain x version covers cases where extended ascii characters is 
// not being recognized
$sql="
UPDATE tropicos_raw 
SET taxon_with_author=REPLACE(taxon_with_author,'$encoded_x','$plain_x');
";
//echo "\r\nSQL=\r\n$sql\r\n";

sql_execute_multiple($dbh, $sql);
echo $done;

?>
