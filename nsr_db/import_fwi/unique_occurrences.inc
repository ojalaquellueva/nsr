<?php

//////////////////////////////////////////////////
// Save unique occurrences to main raw table and 
//////////////////////////////////////////////////

echo "Extracting unique occurrences:\r\n";

//////////////////////////////////////////////////////
// Assign numeric ranks to native status to allow 
// selecting of single value to apply to each species
//////////////////////////////////////////////////////

echo "  Country occurrences...";
$sql="
DROP TABLE IF EXISTS fwi_occurrences_temp;
CREATE TABLE fwi_occurrences_temp LIKE fwi_occurrences;
INSERT INTO fwi_occurrences_temp SELECT DISTINCT * FROM fwi_occurrences;
DROP TABLE fwi_occurrences;
RENAME TABLE fwi_occurrences_temp TO fwi_occurrences;

INSERT INTO fwi_raw_temp (
source_name,
region,
country, 
family, 
genus, 
species, 
taxon, 
taxon_rank, 
native_status_all,
cult_status_all
)
SELECT 
'$src',
region,
country, 
family, 
genus, 
species, 
taxon, 
taxon_rank, 
GROUP_CONCAT(native_status SEPARATOR ', '),
GROUP_CONCAT(cult_status SEPARATOR ', ')
FROM (
SELECT DISTINCT
'$src',
b.region,
b.country, 
family, 
genus, 
species, 
taxon, 
taxon_rank, 
native_status,
cult_status
FROM fwi_occurrences a JOIN fwi_region_country b 
ON a.region=b.region
WHERE b.region IN ('bahamas','caymanIsland','cuba','hispaniola','jamaica','puertoRico','virginIslands')
) AS a
GROUP BY region, country, family, taxon
ORDER BY region, country, family, taxon
;
";
sql_execute_multiple($sql);
echo $done;

echo "  Region occurrences...";
$sql="
INSERT INTO fwi_raw_temp (
source_name,
region,
family, 
genus, 
species, 
taxon, 
taxon_rank, 
native_status_all,
cult_status_all
)
SELECT 
'$src',
region,
family, 
genus, 
species, 
taxon, 
taxon_rank, 
GROUP_CONCAT(native_status SEPARATOR ', '),
GROUP_CONCAT(cult_status SEPARATOR ', ')
FROM (
SELECT DISTINCT
'$src',
region,
family, 
genus, 
species, 
taxon, 
taxon_rank, 
native_status,
cult_status
FROM fwi_occurrences 
WHERE region IN ('greaterAntilles','lesserAntillles','westIndies')
) AS a
GROUP BY region, family, taxon
ORDER BY region, family, taxon
;
";
sql_execute_multiple($sql);
echo $done;

// This next part is tricky. The logic here is based on the fact
// that multiple opinions per species apply to different subspecies of
// that same species. What we are doing here is providing a single status
// for the entire species, including all subspecies.
echo "  Inferring final native status...";
$sql="
-- Only one classificatication
UPDATE fwi_raw_temp
SET native_status=native_status_all 
WHERE native_status_all NOT LIKE '%,%'
;

-- Multiple classificatications
UPDATE fwi_raw_temp
SET native_status= 
CASE
WHEN TRIM(native_status_all)='absent' THEN 'absent'
WHEN TRIM(native_status_all)='absent, endemic' THEN 'native'
WHEN TRIM(native_status_all)='absent, endemic, introduced' THEN 'native'
WHEN TRIM(native_status_all)='absent, endemic, native' THEN 'native'
WHEN TRIM(native_status_all)='absent, endemic, native, introduced' THEN 'native'
WHEN TRIM(native_status_all)='absent, introduced' THEN 'introduced'
WHEN TRIM(native_status_all)='absent, introduced, introduced' THEN 'introduced'
WHEN TRIM(native_status_all)='absent, introduced, native' THEN 'native'
WHEN TRIM(native_status_all)='absent, native' THEN 'native'
WHEN TRIM(native_status_all)='absent, native, endemic' THEN 'native'
WHEN TRIM(native_status_all)='absent, native, introduced' THEN 'native'
WHEN TRIM(native_status_all)='endemic' THEN 'endemic'
WHEN TRIM(native_status_all)='endemic, absent' THEN 'native'
WHEN TRIM(native_status_all)='endemic, absent, introduced' THEN 'native'
WHEN TRIM(native_status_all)='endemic, absent, native' THEN 'native'
WHEN TRIM(native_status_all)='endemic, introduced' THEN 'native'
WHEN TRIM(native_status_all)='endemic, native' THEN 'native'
WHEN TRIM(native_status_all)='endemic, native, absent' THEN 'native'
WHEN TRIM(native_status_all)='introduced' THEN 'introduced'
WHEN TRIM(native_status_all)='introduced, absent' THEN 'introduced'
WHEN TRIM(native_status_all)='introduced, absent, introduced' THEN 'introduced'
WHEN TRIM(native_status_all)='introduced, absent, native' THEN 'native'
WHEN TRIM(native_status_all)='introduced, endemic, introduced' THEN 'native'
WHEN TRIM(native_status_all)='introduced, introduced' THEN 'introduced'
WHEN TRIM(native_status_all)='introduced, introduced, absent' THEN 'introduced'
WHEN TRIM(native_status_all)='introduced, native' THEN 'native'
WHEN TRIM(native_status_all)='introduced, native, introduced' THEN 'native'
WHEN TRIM(native_status_all)='native' THEN 'native'
WHEN TRIM(native_status_all)='native, absent' THEN 'native'
WHEN TRIM(native_status_all)='native, absent, endemic' THEN 'native'
WHEN TRIM(native_status_all)='native, absent, introduced' THEN 'native'
WHEN TRIM(native_status_all)='native, endemic' THEN 'native'
WHEN TRIM(native_status_all)='native, endemic, absent' THEN 'native'
WHEN TRIM(native_status_all)='native, introduced' THEN 'native'
WHEN TRIM(native_status_all)='native, introduced, absent' THEN 'native'
WHEN TRIM(native_status_all)='introduced, endemic' THEN 'native'
WHEN TRIM(native_status_all)='native, absent, endemic, introduced' THEN 'native'
WHEN TRIM(native_status_all)='native, introduced, endemic' THEN 'native'
WHEN TRIM(native_status_all)='native, absent, introduced, endemic' THEN 'native'
WHEN TRIM(native_status_all)='introduced, endemic, absent' THEN 'native'
WHEN TRIM(native_status_all)='native, endemic, introduced' THEN 'native'
ELSE native_status
END
;
";
sql_execute_multiple($sql);
echo $done;

echo "  Inferring final cultivated status...";
$sql="
-- Only one classificatication
UPDATE fwi_raw_temp
SET cult_status='cultivated' 
WHERE cult_status_all LIKE '%cult%'
;
";
sql_execute_multiple($sql);
echo $done;

?>