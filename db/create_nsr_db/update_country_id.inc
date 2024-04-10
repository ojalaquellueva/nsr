<?php

///////////////////////////////////////////////////
// Updates countryID in table countryName
///////////////////////////////////////////////////

echo "  Updating country_id in table countryName...";
$sql="
UPDATE countryName
SET countryID=NULL
;
UPDATE countryName a JOIN country b
ON a.countryNameStd=b.country
SET countryID=country_id
;
";
sql_execute_multiple($dbh, $sql);	
echo $done;

?>