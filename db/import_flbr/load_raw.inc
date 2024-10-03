<?php

////////////////////////////////////////////////
// Loading the main "raw" data table from the two
// true raw tables. Only loads species, subspecies
// and variety. Higher taxa will be added 
// automatically, and forms aren't worth the trouble
// because of inconsistent format of forma names
////////////////////////////////////////////////

// Inner join ensures that only accepted taxon names
// will be added
// NULL phylum excludes fungi etc.
echo "Combining raw data tables to table $tbl_raw...";
$sql="
INSERT INTO $tbl_raw (
taxon_id,
taxon_rank,
taxon_with_author,
family, 
genus, 
species, 
taxon, 
state_code, 
country, 
state_province, 
native_status, 
cult_status,
include
)
SELECT
taxonID,
CASE
WHEN taxonRank='ESPECIE' THEN 'species'
WHEN taxonRank='SUB_ESPECIE' THEN 'subspecies'
WHEN taxonRank='VARIEDADE' THEN 'variety'
ELSE NULL
END,
scientificName,
family, 
genus, 
TRIM(CONCAT_WS(' ',IFNULL(genus,''), IFNULL(specificEpithet,''))), 
CASE
WHEN infraspecificEpithet IS NOT NULL AND TRIM(infraspecificEpithet)<>'' THEN
TRIM(CONCAT_WS(' ',IFNULL(genus,''), IFNULL(specificEpithet,''), 'subsp.', infraspecificEpithet))
ELSE TRIM(CONCAT_WS(' ',IFNULL(genus,''), IFNULL(specificEpithet,'')))
END,
locality, 
'Brazil', 
NULL, 
CASE
WHEN establishmentMeans='CULTIVADA' THEN 'introduced'
WHEN establishmentMeans='NATIVA' THEN 'native'
WHEN establishmentMeans='NATURALIZADA' THEN 'introduced'
ELSE NULL
END, 
CASE
WHEN establishmentMeans='CULTIVADA' THEN 'cultivated'
ELSE NULL
END, 
1
FROM $tbl_taxon_raw a JOIN $tbl_dist_raw b
ON a.taxonID=b.id
WHERE b.countryCode IS NOT NULL
AND taxonRank IN ('ESPECIE','SUB_ESPECIE','VARIEDADE')
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "Fixing infraspecific rank indicator...";
$sql="
UPDATE $tbl_raw
SET taxon=REPLACE(taxon,'subsp.','var.')
WHERE taxon_rank='variety'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>