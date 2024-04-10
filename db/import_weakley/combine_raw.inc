<?php

/////////////////////////////////////////////////////////
// Combines raw data files into single file
/////////////////////////////////////////////////////////

echo "Combining raw data in table raw_weakley:\r\n";

echo "  Completing political division information...";
// Populate political divisions
$sql_poldivcodes="
SELECT DISTINCT stateProvinceCode
FROM `$tbl_weakley_poldivs_raw`
WHERE stateProvinceCode IS NOT NULL AND stateProvinceCode<>'';
";
$result = mysqli_query($dbh, $sql_poldivcodes);

while ($row = mysqli_fetch_assoc($result)) {
	$poldivcode = $row["stateProvinceCode"];
	$poldiv = get_poldivname($poldivcode);
	$sql="
	UPDATE `$tbl_weakley_poldivs_raw`
	SET stateProvince='$poldiv'
	WHERE stateProvinceCode='$poldivcode';
	";
	sql_execute_multiple($dbh, $sql);	
}
echo $done;

echo "  Inserting records for species exotic to part of E. North America...";
$sql="
INSERT INTO $tbl_raw (
taxon,
country,
stateProvince,
native_status
)
SELECT DISTINCT
w.taxon,
p.country,
p.stateProvince,
'Introduced'
FROM `$tbl_weakley_exotic_part_raw` w JOIN `$tbl_weakley_poldivs_raw` p
ON w.stateProvinceCode=p.stateProvinceCode
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Inserting records for species exotic to all of E. North America...";
// Note cartesian product
// Lists every taxon as exotic in every state or province
$sql="
INSERT INTO $tbl_raw (
taxon,
country,
stateProvince,
native_status
)
SELECT DISTINCT
w.taxon,
p.country,
p.stateProvince,
'Introduced'
FROM `$tbl_weakley_exotic_all_raw` w, `$tbl_weakley_poldivs_raw` p
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Inserting Old World species as exotic to all New World countries...";
// Note cartesian product again
// Inserts a record for every Old World taxon in every New World country,
// with status='Introduced'
$sql="
UPDATE `$tbl_weakley_origin_raw`
SET isOldWorld=1
WHERE origin IN (
'Asia',
'Australia',
'E. and se. Asia',
'Eurasia',
'Europe',
'India',
'Mediterranean Europe and Africa',
'Pacific Islands',
'Paleotropics',
'Subsaharan Africa',
'W. Africa',
'W. Asia',
'Garden origin'
);

INSERT INTO $tbl_raw (
taxon,
country,
native_status
)
SELECT DISTINCT
w.taxon,
c.country,
'Introduced'
FROM `$tbl_weakley_origin_raw` w, 
(
SELECT DISTINCT countryNameStd AS country
FROM countryName 
WHERE isNewWorld=1
) AS c
WHERE w.isOldWorld=1
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Inserting introduced records for species endemic to eastern N. America...";
// Note cartesian product
$sql="
INSERT INTO $tbl_raw (
taxon,
country,
native_status
)
SELECT DISTINCT
w.taxon,
c.country,
'Introduced'
FROM `$tbl_weakley_origin_raw` w, 
(
SELECT DISTINCT countryNameStd AS country
FROM countryName 
WHERE countryNameStd NOT IN ('Canada','United States')
) AS c
WHERE w.origin='Endemic' 
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>