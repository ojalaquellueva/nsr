<?php

/////////////////////////////////////////////////////////////
// Fixes specific to this source, if any
//
// Leave content between this comment and closing line blank 
// if no source-specific fixes required
/////////////////////////////////////////////////////////////

echo "  Populating concatenated taxon name...";
$sql="
UPDATE `$tbl_raw`
SET taxon=TRIM(CONCAT_WS(' ',IFNULL(genus,''),
IF(IFNULL(genus,'')='','',epithet)
));
UPDATE `$tbl_raw`
SET taxon=NULL
WHERE taxon=''
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

// Fix entries for Musa and Eucalyptus
echo "  Fixing entries for Musa and Eucalyptus...";
$sql="
UPDATE `$tbl_raw`
SET 
taxon='Eucalyptus',
epithet='',
author=''
WHERE genus='Eucalyptus' 
;
UPDATE `$tbl_raw`
SET 
taxon='Musa',
epithet='',
author=''
WHERE genus='Musa' 
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>