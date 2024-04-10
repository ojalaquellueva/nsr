<?php

/////////////////////////////////////////////////////////
// Extract all unique values of area_name, scrub using
// GNRS API and re-import results
/////////////////////////////////////////////////////////

/* 
// Development only
echo "####### WARNING: lines commented out in scrub_regions.inc! #########\n";
$regions_raw_file = $datapath . "nsr_regions.csv";
// Place above disabled section

// Place below disabled section
// END For development only
*/


// Parameter: set to true to echo sample of GNRS results to terminal
// Should normally be set to false
$echo_reponse=false;

echo "Scrubbing regions:\r\n";

echo "  Populating verbatim political divisions in `$tbl_raw`...";
// Must create new table to allow inserting multiple records in place of one
// All fields included except autoincrement primary key, which is generated
// anew
$tbl_raw_temp = $tbl_raw . "_temp";
$sql="
DROP TABLE IF EXISTS $tbl_raw_temp;
CREATE TABLE $tbl_raw_temp LIKE $tbl_raw;
INSERT INTO $tbl_raw_temp (
fqId,
query,
modified,
bibliographicCitation,
genus,
taxonomicStatus,
kingdom,
phylum,
family,
source,
namePublishedInYear,
name,
authors,
species,
`rank`,
reference,
accepted_fqId,
accepted_name,
accepted_author,
accepted_rank,
accepted_taxonomicStatus,
establishment,
featureId,
tdwgCode,
tdwgLevel,
area_name,
infraspecies,
occurrenceStatus,
threatStatus,
poldiv_full_verbatim,
country_verbatim,
state_province_verbatim,
county_parish_verbatim,
poldiv_full,
country_id,
state_province_id,
county_parish_id,
country,
state_province,
county_parish,
poldiv_matched,
match_status
)
SELECT 
a.fqId,
a.query,
a.modified,
a.bibliographicCitation,
a.genus,
a.taxonomicStatus,
a.kingdom,
a.phylum,
a.family,
a.source,
a.namePublishedInYear,
a.name,
a.authors,
a.species,
a.`rank`,
a.reference,
a.accepted_fqId,
a.accepted_name,
a.accepted_author,
a.accepted_rank,
a.accepted_taxonomicStatus,
a.establishment,
a.featureId,
a.tdwgCode,
a.tdwgLevel,
a.area_name,
a.infraspecies,
a.occurrenceStatus,
a.threatStatus,
a.poldiv_full_verbatim,
b.country,
b.state_province,
a.county_parish_verbatim,
a.poldiv_full,
a.country_id,
a.state_province_id,
a.county_parish_id,
a.country,
a.state_province,
a.county_parish,
a.poldiv_matched,
a.match_status
FROM $tbl_raw a JOIN $tbl_region_codes b
ON a.tdwgCode=b.code
;
DROP TABLE $tbl_raw;
RENAME TABLE $tbl_raw_temp TO $tbl_raw;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Updating FK poldiv_full_verbatim in `$tbl_raw`...";
$sql="
UPDATE $tbl_raw 
SET poldiv_full_verbatim=CONCAT_WS('@',
country_verbatim,
IFNULL(state_province_verbatim,''),
IFNULL(county_parish_verbatim,'')
)
WHERE country_verbatim IS NOT NULL
;
UPDATE $tbl_raw 
SET poldiv_full_verbatim=NULL
WHERE TRIM(poldiv_full)=''
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

// The before/after delimiters are to assist with converting tab-delimited
// to CSV
echo "  Extracting region names...";
$sql="
INSERT INTO $tbl_poldivs (
country_verbatim,
state_province_verbatim,
county_parish_verbatim
)
SELECT DISTINCT 
CONCAT('DBLQUOTE', country_verbatim, 'DBLQUOTE') AS country_verbatim,
CONCAT('DBLQUOTE', state_province_verbatim, 'DBLQUOTE') AS state_province_verbatim,
CONCAT('DBLQUOTE', county_parish_verbatim, 'DBLQUOTE') AS county_parish_verbatim
FROM powo_raw
WHERE country_verbatim IS NOT NULL
ORDER BY country_verbatim, state_province_verbatim, county_parish_verbatim
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Dumping to file...";
$regions_raw_file = $datapath . "nsr_regions.csv";

//$cmd="export MYSQL_PWD=$PWD; mysql -u $USER -e 'SELECT \"before\" AS user_id, area_name  AS country, \"after\" AS state_province, NULL AS county_parish FROM temp_regions' $DB > $regions_raw_file ";
$cmd="export MYSQL_PWD=$PWD; mysql -u $USER -e 'SELECT * FROM $tbl_poldivs' $DB > $regions_raw_file ";
//echo "\n\$cmd:\n$cmd\n";
exec($cmd, $output, $status);
if ($status) die("ERROR: dump-to-file command non-zero exit status (" . 		basename(__FILE__) . ")\r\n");
echo $done;

echo "  Fixing table `$tbl_poldivs`...";
$sql="
UPDATE $tbl_poldivs 
SET
country_verbatim=REPLACE(country_verbatim, 'DBLQUOTE', ''),
state_province_verbatim=REPLACE(state_province_verbatim, 'DBLQUOTE', ''),
county_parish_verbatim=REPLACE(county_parish_verbatim, 'DBLQUOTE', '')
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

# Convert to CSV
# Not a generic solution, but works in this particular case
echo "  Converting from tab-delimitted to CSV...";
$cmd="sed -i 's/,/@@@/g' $regions_raw_file";	// Transform literal commas
exec($cmd, $output, $status);
if ($status) die("ERROR: Comma-transform non-zero exit status (" . 		basename(__FILE__) . ")\r\n");

$cmd="sed -i 's/\t/,/g' $regions_raw_file";	// Convert tabs to comma delimitters
exec($cmd, $output, $status);
if ($status) die("ERROR: Tab-to-comma non-zero exit status (" . 		basename(__FILE__) . ")\r\n");

$cmd="sed -i 's/@@@/,/g' $regions_raw_file";		// Restore literal commas
exec($cmd, $output, $status);
if ($status) die("ERROR: Comma-restore non-zero exit status (" . 		basename(__FILE__) . ")\r\n");

$cmd="sed -i 's/DBLQUOTE/\"/g' $regions_raw_file"; // Restore opening quote
exec($cmd, $output, $status);
if ($status) die("ERROR: Restore-quotes non-zero exit status (" . 		basename(__FILE__) . ")\r\n");

$cmd="sed -i 's/NULL//g' $regions_raw_file"; // Set NULL to empty string
exec($cmd, $output, $status);
if ($status) die("ERROR: NULL-to-empty-string non-zero exit status (" . 		basename(__FILE__) . ")\r\n");
echo $done;

echo "  Scrubbing political divisions with GNRS...";
// Reimport the file as array & convert to json 
$csv = $regions_raw_file;
$csv_arr = array_map('str_getcsv', file($csv));
$json_data = json_encode($csv_arr);

// Set curl options
$ch = curl_init($gnrs_url);	
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
curl_setopt($ch, CURLOPT_FAILONERROR, true);
curl_setopt($ch, CURLOPT_POST, 1);	
curl_setopt($ch, CURLOPT_HTTPHEADER, array('Content-Type: application/json')); 
curl_setopt($ch, CURLOPT_POSTFIELDS, $json_data);	

// Send the API call
$response_json = curl_exec($ch);
$status = curl_getinfo($ch, CURLINFO_HTTP_CODE);
if ( $status != 201 && $status != 200 ) {
    die("Error: call to URL $url failed with status $status, response $response, curl_error " . curl_error($ch) . ", curl_errno " . curl_errno($ch) . "\r\n");
}
curl_close($ch);
echo $done;

// Process the response and load to database
$response =  json_decode($response_json);

// echo "\nStatus:\n";
// var_dump($status);
// echo "\nJSON response:\n";
// var_dump($response_json);
// echo "\\nResponse as array:\\n";
// var_dump($response);

if ($echo_reponse) {
	// Echo sample of GNRS results to terminal
	// For development only; turn off for production
	
	// Set format
	$mask = "%-12s %-25s %-15s %-25s %-25s %-20s %-15s \n";

	// Print header & sample of data
	echo sprintf($mask, "user_id", "country_verbatim", "country_id", "country", "match_method_country", "match_score_country", "match_status");

	$maxrows=12;	// Max rows to print
	$row=1;
	foreach ($response as $idx => $obs) {
		// Output row
		echo sprintf($mask, 
			$obs->user_id, 
			$obs->country_verbatim, 
			$obs->country_id, 
			$obs->country, 
			$obs->match_method_country, 
			$obs->match_score_country, 
			$obs->match_status
		);
		if ($row==$maxrows) break;
		$row++;
	}
}

echo "Loading GNRS results to database...";
foreach ($response as $idx => $obs) {
	// Insert row to results table
	$country_verbatim=$obs->country_verbatim;
	$state_province_verbatim=$obs->state_province_verbatim;
	$county_parish_verbatim=$obs->county_parish_verbatim;
	$poldiv_full_verbatim=$obs->poldiv_full;
	$country=$obs->country;
	$state_province=$obs->state_province;
	$county_parish=$obs->county_parish;
	$country_id=$obs->country_id;
	$state_province_id=$obs->state_province_id;
	$county_parish_id=$obs->county_parish_id;
	$match_method_country=$obs->match_method_country;
	$match_method_state_province=$obs->match_method_state_province;
	$match_method_county_parish=$obs->match_method_county_parish;
	$match_score_country=$obs->match_score_country;
	$match_score_state_province=$obs->match_score_state_province;
	$match_score_county_parish=$obs->match_score_county_parish;
	$poldiv_submitted=$obs->poldiv_submitted;
	$poldiv_matched=$obs->poldiv_matched;
	$match_status=$obs->match_status;
	$user_id=$obs->user_id;
	$country_iso=$obs->country_iso;
	$state_province_iso=$obs->state_province_iso;
	$county_parish_iso=$obs->county_parish_iso;

	$sql="
	INSERT INTO $tbl_poldivs_scrubbed (
		poldiv_full_verbatim,
		country_verbatim,
		state_province_verbatim,
		county_parish_verbatim,
		country,
		state_province,
		county_parish,
		country_id,
		state_province_id,
		county_parish_id,
		match_method_country,
		match_method_state_province,
		match_method_county_parish,
		match_score_country,
		match_score_state_province,
		match_score_county_parish,
		poldiv_submitted,
		poldiv_matched,
		match_status,
		country_iso,
		state_province_iso,
		county_parish_iso
	)
	VALUES (
		'$poldiv_full_verbatim',
		'$country_verbatim',
		'$state_province_verbatim',
		'$county_parish_verbatim',
		'$country',
		'$state_province',
		'$county_parish',
		'$country_id',
		'$state_province_id',
		'$county_parish_id',
		'$match_method_country',
		'$match_method_state_province',
		'$match_method_county_parish',
		'$match_score_country',
		'$match_score_state_province',
		'$match_score_county_parish',
		'$poldiv_submitted',
		'$poldiv_matched',
		'$match_status',
		'$country_iso',
		'$state_province_iso',
		'$county_parish_iso'
	)
	;
	";
	sql_execute_multiple($dbh, $sql);
}
echo $done;

# Remove duplicate rows from table
echo "Removing duplicates from table `$tbl_poldivs_scrubbed`...";
$tbl_tmp = $tbl_poldivs_scrubbed . "_tmp";
$sql="
CREATE TABLE $tbl_tmp LIKE $tbl_poldivs_scrubbed;
INSERT INTO $tbl_tmp SELECT DISTINCT * FROM $tbl_poldivs_scrubbed;
DROP TABLE $tbl_poldivs_scrubbed;
ALTER TABLE $tbl_tmp RENAME $tbl_poldivs_scrubbed;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "Updating column `poldiv_full` in table `$tbl_poldivs_scrubbed`...";
$sql="
UPDATE $tbl_poldivs_scrubbed 
SET poldiv_full=
CONCAT_WS('@',
IFNULL(country,''),
IFNULL(state_province,''),
IFNULL(county_parish,'')
)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "Making column `poldiv_full_verbatim` PK of table `$tbl_poldivs_scrubbed`...";
$sql="
ALTER TABLE $tbl_poldivs_scrubbed 
ADD PRIMARY KEY (poldiv_full_verbatim)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "Transferring GNRS results to `$tbl_raw`...";
$sql="
UPDATE $tbl_raw a JOIN $tbl_poldivs_scrubbed b
ON a.poldiv_full_verbatim=b.poldiv_full_verbatim
SET 
a.poldiv_full=b.poldiv_full,
a.country=b.country,
a.state_province=b.state_province,
a.county_parish=b.county_parish,
a.country_id=IF(b.country_id='',NULL,b.country_id),
a.state_province_id=IF(b.state_province_id='',NULL,b.state_province_id),
a.county_parish_id=IF(b.county_parish_id='', NULL, b.county_parish_id),
a.poldiv_matched=b.poldiv_matched,
a.match_status=b.match_status
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>