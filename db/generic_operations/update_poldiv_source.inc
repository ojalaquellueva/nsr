<?php

////////////////////////////////////////////////////
// comma-delimited list of all checklist source codes
// for each taxon
/////////////////////////////////////////////////////

echo "Updating table `poldiv_source`:\n";

echo "  Populating GADM ids for countries...";
$sql="
UPDATE poldiv_source ps JOIN country c
ON ps.poldiv_id=c.country_id
SET 
ps.gid_0=c.country_iso_alpha3, 
ps.country=c.country
WHERE poldiv_type='country'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Populating GADM ids for states...";
$sql="
UPDATE poldiv_source ps JOIN state_province s
ON ps.poldiv_id=s.state_province_id
SET 
ps.gid_1=s.gid_1,
ps.state_province=s.state_province_std
WHERE poldiv_type='state_province'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>