<?php

///////////////////////////////////////////////////////////////
// converts any encoded hybrid "x" characters to a 
// simple plain ascii "x"
///////////////////////////////////////////////////////////////

$plain_x="x";

// Use this version if extended ascii is transmitted correctly by php
//$encoded_x="×";

// Use this version if php not transmitting extended ascii to MySQL.
// You can tell because the literal query works if you enter it directly
// in the MySQL command line, but doesn't work if sent by php
// If warning or error thrown, see here for details:
// https://php.watch/versions/8.2/utf8_encode-utf8_decode-deprecated
// Note: function mb_convert_encoding() requires extension mb_string
$encoded_x= mb_convert_encoding('×', 'ISO-8859-1', 'UTF-8');

echo "  Standarizing hybrid 'x'...";

// The double plain x version covers cases where extended ascii characters is 
// not being recognized
$sql="
UPDATE `$tbl_raw`
SET `$fld_scientific_name`=REPLACE(`$fld_scientific_name`,'$encoded_x','$plain_x');
";
//echo "\r\nSQL=\r\n$sql\r\n";

sql_execute_multiple($dbh, $sql);
echo $done;

?>
