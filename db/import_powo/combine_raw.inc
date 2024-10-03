<?php
// Create mysql tables identical in structure to raw text files
// And combines into single staging table

echo "Creating combined raw data table\n";

echo "  Indexing source tables...";
$sql="
ALTER TABLE $tbl_dist_raw
ADD PRIMARY KEY (plant_locality_id)
;
ALTER TABLE $tbl_dist_raw
ADD INDEX (plant_name_id)
;
ALTER TABLE $tbl_names_raw
ADD PRIMARY KEY (plant_name_id)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

// Join distribution and names tables, keeping all distribution
// records but only those names present in the distribution table.
// Note that $tbl_raw="powo_raw_combined"
// Some column names change to make compatible with existing
// import pipeline based on the old POWO schema
echo "  Creating & populating table `$tbl_raw`...";
$sql="
DROP TABLE IF EXISTS $tbl_raw;
CREATE TABLE $tbl_raw AS
SELECT
d.plant_locality_id AS powo_plant_locality_id,
d.tdwgCodeL3,
d.area AS area_name,
d.introduced,
d.extinct,
d.location_doubtful,
n.plant_name_id,
n.parent_plant_name_id,
n.accepted_plant_name_id,
n.powo_id,
n.family,
n.taxon_name AS name,
n.taxon_authors,
n.hybrid_formula,
n.taxon_rank AS `rank`,
n.taxon_status as taxonomicStatus,
n.nomenclatural_remarks,
n.geographic_area,
n.homotypic_synonym
FROM $tbl_dist_raw d LEFT JOIN $tbl_names_raw n
ON d.plant_name_id=n.plant_name_id
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>