<?php

/////////////////////////////////////////////////////////////
// Fixes specific to this source, if any
//
// Leave content between this comment and closing line blank 
// if no source-specific fixes required
/////////////////////////////////////////////////////////////

echo "  Changing USVI and Puerto Rico to countries...";
$sql="
UPDATE `$tbl_raw`
SET
country='Puerto Rico',
state_province=NULL
WHERE state_province='Puerto Rico'
;
UPDATE `$tbl_raw`
SET
country='U.S. Virgin Islands',
state_province=NULL
WHERE state_province='Virgin Islands'
;
";
sql_execute_multiple($sql);
echo $done;

?>