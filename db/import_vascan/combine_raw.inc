<?php

/////////////////////////////////////////////////////////
// Combines raw data files into single file
/////////////////////////////////////////////////////////

echo "Combining separate raw data tables in table $tbl_raw...";

$sql="
INSERT INTO $tbl_raw (
id,
taxon,
taxon_rank,
country,
stateProvince,
native_status
)
SELECT DISTINCT
t.taxonID,
species,
taxonRank,
CASE 
WHEN countryCode='CA' THEN 'Canada'
WHEN countryCode='GL' THEN 'Denmark'
WHEN countryCode='FR' THEN 'France' 
ELSE countryCode
END,
locality,
IF(establishmentMeans='','non-native',establishmentMeans)
FROM $tbl_vascan_distribution_raw d JOIN $tbl_vascan_taxon_raw t
ON d.id=t.taxonID
WHERE t.acceptedNameUsageID=t.taxonID
AND t.species IS NOT NULL AND species NOT LIKE '% % %'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>