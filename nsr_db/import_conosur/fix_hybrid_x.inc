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
$encoded_x2= 'Ã—';
$encoded_x3= utf8_decode('Ã—');
$encoded_x4= "×";

echo "  Standarizing hybrid 'x'...";

// The double plain x version covers cases where extended ascii characters is 
// not being recognized. The whitespace after $plain_x in the first query separates
// any hybrid x prefixes from the following epithet
// The second query removes any double spaces inserted by the first; this is 
// necessary if hybrid x's already delimited by whitespace
$sql="
UPDATE `$tbl_raw` 
SET `$fld_scientific_name`=
CASE 
WHEN `$fld_scientific_name` LIKE '%$encoded_x%' THEN REPLACE(`$fld_scientific_name`,'$encoded_x','$plain_x ')
WHEN `$fld_scientific_name` LIKE '%$encoded_x2%' THEN REPLACE(`$fld_scientific_name`,'$encoded_x2','$plain_x ')
WHEN `$fld_scientific_name` LIKE '%$encoded_x3%' THEN REPLACE(`$fld_scientific_name`,'$encoded_x3','$plain_x ')
WHEN `$fld_scientific_name` LIKE '%$encoded_x4%' THEN REPLACE(`$fld_scientific_name`,'$encoded_x4','$plain_x ')
ELSE `$fld_scientific_name`
END
;
UPDATE `$tbl_raw` 
SET `$fld_scientific_name`= REPLACE(`$fld_scientific_name`,'  ',' ')
;
";
//echo "\r\nSQL=\r\n$sql\r\n";

sql_execute_multiple($dbh, $sql);
echo $done;

?>
