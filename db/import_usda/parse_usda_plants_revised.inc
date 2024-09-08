<?php

// ******************************
// **** UNDER CONSTRUCTION! *****
// ******************************

//////////////////////////////////////////////////////////
// Unpacks USDA plants download into multiple
// state checklists
//
// For the purposes of this application, all these checklists
// can be treated as a single source. All lists are 
// "comprehensive", in the sense that any species not on the 
// list can safely be assumed to be introduced. However, 
// native status at the state level for the lower 48 states
// is generally unknown. State status CANNOT be inherited from 
// the entire country; a species listed as "native" for the 
// entire lower 48 may still be introduced in a particular 
// state. Introduced status at the state level is 
// not indicated by USDA. The only status that is inherited
// at the state (or province) level is if the species is introduced for the
// entire lower 48 (or Canada)
// Native status is only accurate at the country level and
// selected sub-country entities, as indicated below.
//
// Code  	Native Status Jurisdiction
// L48	Lower 48 States
// AK	Alaska
// HI	Hawaii
// PR	Puerto Rico
// VI	U.S. Virgin Islands
// CAN	Canada
// GL	Greenland (Denmark)
// SPM	St. Pierre and Miquelon (France)
// Also note that for non-vasculars, native status is evaluated
// ONLY at scale of North America (NativeStatus=NA)
//
// Note that column `PLANTSFloristicArea` is not used
//////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////
// Functions
//////////////////////////////////////////////////////////

// List of political divisions codes used by USDA Plants
function is_usda_poldiv($str) {
	$arr = array(
		'USA',
		'AL',
		'AK',
		'AZ',
		'AR',
		'CA',
		'CO',
		'CT',
		'DE',
		'DC',
		'FL',
		'GA',
		'HI',
		'ID',
		'IL',
		'IN',
		'IA',
		'KS',
		'KY',
		'LA',
		'ME',
		'MD',
		'MA',
		'MI',
		'MN',
		'MS',
		'MO',
		'MT',
		'NE',
		'NV',
		'NH',
		'NJ',
		'NM',
		'NY',
		'NC',
		'ND',
		'OH',
		'OK',
		'OR',
		'PA',
		'RI',
		'SC',
		'SD',
		'TN',
		'TX',
		'UT',
		'VT',
		'VA',
		'WA',
		'WV',
		'WI',
		'WY',
		'PR',
		'VI',
		'CAN',
		'AB',
		'BC',
		'MB',
		'NB',
		'LB',
		'NF',
		'NT',
		'NS',
		'NU',
		'ON',
		'PE',
		'QC',
		'SK',
		'YT',
		'DEN',
		'GL',
		'FRA',
		'SPM'
	); 

	if (in_array($str,$arr)) {
 		return true;
 	} else {
 		return false;
 	}
}	
	
// Function to translate political division abbreviations used by USDA
// to complete names used by this application
function get_usda_poldivname($str) {
	$arr = array(
		'USA' => 'United States',
		'AL' => 'Alabama',
		'AK' => 'Alaska',
		'AZ' => 'Arizona',
		'AR' => 'Arkansas',
		'CA' => 'California',
		'CO' => 'Colorado',
		'CT' => 'Connecticut',
		'DE' => 'Delaware',
		'DC' => 'District of Columbia',
		'FL' => 'Florida',
		'GA' => 'Georgia',
		'HI' => 'Hawaii',
		'ID' => 'Idaho',
		'IL' => 'Illinois',
		'IN' => 'Indiana',
		'IA' => 'Iowa',
		'KS' => 'Kansas',
		'KY' => 'Kentucky',
		'LA' => 'Louisiana',
		'ME' => 'Maine',
		'MD' => 'Maryland',
		'MA' => 'Massachusetts',
		'MI' => 'Michigan',
		'MN' => 'Minnesota',
		'MS' => 'Mississippi',
		'MO' => 'Missouri',
		'MT' => 'Montana',
		'NE' => 'Nebraska',
		'NV' => 'Nevada',
		'NH' => 'New Hampshire',
		'NJ' => 'New Jersey',
		'NM' => 'New Mexico',
		'NY' => 'New York',
		'NC' => 'North Carolina',
		'ND' => 'North Dakota',
		'OH' => 'Ohio',
		'OK' => 'Oklahoma',
		'OR' => 'Oregon',
		'PA' => 'Pennsylvania',
		'RI' => 'Rhode Island',
		'SC' => 'South Carolina',
		'SD' => 'South Dakota',
		'TN' => 'Tennessee',
		'TX' => 'Texas',
		'UT' => 'Utah',
		'VT' => 'Vermont',
		'VA' => 'Virginia',
		'WA' => 'Washington',
		'WV' => 'West Virginia',
		'WI' => 'Wisconsin',
		'WY' => 'Wyoming',
		'PR' => 'Puerto Rico',
		'VI' => 'Virgin Islands',
		'CAN' => 'Canada',
		'AB' => 'Alberta',
		'BC' => 'British Columbia',
		'MB' => 'Manitoba',
		'NB' => 'New Brunswick',
		'LB' => 'Labrador',
		'NF' => 'Newfoundland',
		'NT' => 'Northwest Territories',
		'NS' => 'Nova Scotia',
		'NU' => 'Nunavut',
		'ON' => 'Ontario',
		'PE' => 'Prince Edward Island',
		'QC' => 'Quebec',
		'SK' => 'Saskatchewan',
		'YT' => 'Yukon',
		'DEN' => 'Denmark',
		'GL' => 'Greenland',
		'FRA' => 'France',
		'SPM' => 'St. Pierre and Miquelon'
	);
 	
 	return strtr($str,$arr);
}

// Function to return country code for a state-level political division
function get_usda_countrycode($str) {
	$arr = array(
		'AL' => 'USA',
		'AK' => 'USA',
		'AZ' => 'USA',
		'AR' => 'USA',
		'CA' => 'USA',
		'CO' => 'USA',
		'CT' => 'USA',
		'DE' => 'USA',
		'DC' => 'USA',
		'FL' => 'USA',
		'GA' => 'USA',
		'HI' => 'USA',
		'ID' => 'USA',
		'IL' => 'USA',
		'IN' => 'USA',
		'IA' => 'USA',
		'KS' => 'USA',
		'KY' => 'USA',
		'LA' => 'USA',
		'ME' => 'USA',
		'MD' => 'USA',
		'MA' => 'USA',
		'MI' => 'USA',
		'MN' => 'USA',
		'MS' => 'USA',
		'MO' => 'USA',
		'MT' => 'USA',
		'NE' => 'USA',
		'NV' => 'USA',
		'NH' => 'USA',
		'NJ' => 'USA',
		'NM' => 'USA',
		'NY' => 'USA',
		'NC' => 'USA',
		'ND' => 'USA',
		'OH' => 'USA',
		'OK' => 'USA',
		'OR' => 'USA',
		'PA' => 'USA',
		'RI' => 'USA',
		'SC' => 'USA',
		'SD' => 'USA',
		'TN' => 'USA',
		'TX' => 'USA',
		'UT' => 'USA',
		'VT' => 'USA',
		'VA' => 'USA',
		'WA' => 'USA',
		'WV' => 'USA',
		'WI' => 'USA',
		'WY' => 'USA',
		'PR' => 'USA',
		'VI' => 'USA',
		'AB' => 'CAN',
		'BC' => 'CAN',
		'MB' => 'CAN',
		'NB' => 'CAN',
		'LB' => 'CAN',
		'NF' => 'CAN',
		'NT' => 'CAN',
		'NS' => 'CAN',
		'NU' => 'CAN',
		'ON' => 'CAN',
		'PE' => 'CAN',
		'QC' => 'CAN',
		'SK' => 'CAN',
		'YT' => 'CAN',
		'GL' => 'DEN',
		'SPM' => 'FRA'
	);
 	
 	return strtr($str,$arr);
}

// Function to determine if political division abbreviation
// is a country. If not, treat as stateProvince.
function is_usda_country_code($str) {
	$arr = array(
		'USA',
		'CAN',
		'DEN',
		'FRA'
	); 
	
	if (in_array($str,$arr)) {
		return true;
	} else {
		return false;
	}
}

// Function to associate a political division (abbreviation) with its 
// native status region (abbreviation) 
// This does not include: NativeStatus "NA (N)" which applies only to 
// bryophytes and requires special handling. Easy to check as this
// particular status only appears by itself
// Also does not include poldiv "USA", also requires special
// handling because it is comprised of multiple native status regions
function get_nativeStatusRegion($str) {
	$arr = array(
		'AL' => 'L48',
		'AK' => 'AK',
		'AZ' => 'L48',
		'AR' => 'L48',
		'CA' => 'L48',
		'CO' => 'L48',
		'CT' => 'L48',
		'DE' => 'L48',
		'DC' => 'L48',
		'FL' => 'L48',
		'GA' => 'L48',
		'HI' => 'HI',
		'ID' => 'L48',
		'IL' => 'L48',
		'IN' => 'L48',
		'IA' => 'L48',
		'KS' => 'L48',
		'KY' => 'L48',
		'LA' => 'L48',
		'ME' => 'L48',
		'MD' => 'L48',
		'MA' => 'L48',
		'MI' => 'L48',
		'MN' => 'L48',
		'MS' => 'L48',
		'MO' => 'L48',
		'MT' => 'L48',
		'NE' => 'L48',
		'NV' => 'L48',
		'NH' => 'L48',
		'NJ' => 'L48',
		'NM' => 'L48',
		'NY' => 'L48',
		'NC' => 'L48',
		'ND' => 'L48',
		'OH' => 'L48',
		'OK' => 'L48',
		'OR' => 'L48',
		'PA' => 'L48',
		'RI' => 'L48',
		'SC' => 'L48',
		'SD' => 'L48',
		'TN' => 'L48',
		'TX' => 'L48',
		'UT' => 'L48',
		'VT' => 'L48',
		'VA' => 'L48',
		'WA' => 'L48',
		'WV' => 'L48',
		'WI' => 'L48',
		'WY' => 'L48',
		'PR' => 'PR',
		'VI' => 'VI',
		'CAN' => 'CAN',
		'AB' => 'CAN',
		'BC' => 'CAN',
		'MB' => 'CAN',
		'NB' => 'CAN',
		'LB' => 'CAN',
		'NF' => 'CAN',
		'NT' => 'CAN',
		'NS' => 'CAN',
		'NU' => 'CAN',
		'ON' => 'CAN',
		'PE' => 'CAN',
		'QC' => 'CAN',
		'SK' => 'CAN',
		'YT' => 'CAN',
		'DEN' => 'GL',
		'GL' => 'GL',
		'FRA' => 'SPM',
		'SPM' => 'SPM'
	); 
 	
 	return strtr($str,$arr);
 }

// Function to convert USDA status codes to native status
// value used by this application
function get_nativeStatus($str) {
	$arr = array(
		'N' => 'native',
		'N?' => 'native',
		'NI' => 'unknown',
		'NI?' => 'unknown',
		'GP' => 'introduced',
		'GP?' => 'introduced',
		'I' => 'introduced',
		'I?' => 'introduced',
		'N?I' => 'unknown',
		'W' => 'introduced',
		'W?' => 'introduced'
	); 
	
 	return strtr($str,$arr);
}

/* // DON'T BOTHER! Only 9 records return get_cultStatus='cultivated' 

// Function to convert USDA status codes to cultivated status
// value used by this application
function get_cultStatus($str) {
	$arr = array(
		'N' => 'unknown',
		'N?' => 'unknown',
		'NI' => 'unknown',
		'NI?' => 'unknown',
		'GP' => 'cultivated',
		'GP?' => 'cultivated',
		'I' => 'unknown',
		'I?' => 'unknown',
		'N?I' => 'unknown',
		'W' => 'unknown',
		'W?' => 'unknown'
	); 
	
 	return strtr($str,$arr);
}

*/

// Array of all L48 state-level codes
$stateL48Arr = array(
	'AL',
	'AZ',
	'AR',
	'CA',
	'CO',
	'CT',
	'DE',
	'DC',
	'FL',
	'GA',
	'ID',
	'IL',
	'IN',
	'IA',
	'KS',
	'KY',
	'LA',
	'ME',
	'MD',
	'MA',
	'MI',
	'MN',
	'MS',
	'MO',
	'MT',
	'NE',
	'NV',
	'NH',
	'NJ',
	'NM',
	'NY',
	'NC',
	'ND',
	'OH',
	'OK',
	'OR',
	'PA',
	'RI',
	'SC',
	'SD',
	'TN',
	'TX',
	'UT',
	'VT',
	'VA',
	'WA',
	'WV',
	'WI',
	'WY'
);

// Array of all state-level codes
$provArr = array(
	'AB',
	'BC',
	'MB',
	'NB',
	'LB',
	'NF',
	'NT',
	'NS',
	'NU',
	'ON',
	'PE',
	'QC',
	'SK',
	'YT'
);


//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////
// Main
//////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////
// Generate tables of:
// 1. Distinct distribution + native status combinations
// 2. Atomic native status by single region assertions
//////////////////////////////////////////////////////////

// Create foreign key by concatenating StateAndProvince + NativeStatus,
// casting NULL to ''
echo "  Creating foreign key on StateAndProvince + NativeStatus in table '$tbl_raw':\n";

echo "    Adding FK column `distNativeStatus`...";
$sql="
ALTER TABLE $tbl_raw
ADD COLUMN distNativeStatus VARCHAR(500) DEFAULT NULL
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Populating FK...";
$sql="
UPDATE $tbl_raw
SET distNativeStatus=CONCAT_WS('@', 
IFNULL(StateAndProvince,''),
IFNULL(NativeStatus,'')
)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Indexing FK...";
$sql="
ALTER TABLE $tbl_raw
ADD INDEX distNativeStatus_idx (distNativeStatus)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

// Extract distinct values of distNativeStatus, StateAndProvince and NativeStatus, 
// setting distNativeStatus as the primary key
echo "  Extracting table `usda_distNativeStatus` of unique values of StateAndProvince and NativeStatus...";

echo "    Creating table...";
$sql="
DROP TABLE IF EXISTS usda_distNativeStatus;
CREATE TABLE usda_distNativeStatus AS
SELECT DISTINCT distNativeStatus, 
StateAndProvince, 
NativeStatus
FROM $tbl_raw
ORDER BY distNativeStatus, StateAndProvince, NativeStatus
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Setting primary key...";
$sql="
ALTER TABLE usda_distNativeStatus;
ADD PRIMARY KEY (distNativeStatus)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Adding remaining indexes primary key...";
$sql="
ALTER TABLE usda_distNativeStatus;
ADD INDEX (StateAndProvince),
ADD INDEX (NativeStatus)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

// Create table to hold the atomic native status assertions linked
// to the concatenated distribution + native status record identified
// by primary key distNativeStatus in table usda_distNativeStatus
// Except for pkey, don't add indexes until after table populated
echo "  Creating table `usda_nativeStatus`...";
$sql="
DROP TABLE IF EXISTS usda_nativeStatus;
CREATE TABLE usda_nativeStatus (
id INT NOT NULL AUTO_INCREMENT PRIMARY KEY,
distNativeStatus VARCHAR(500) NOT NULL,
country VARCHAR(50) NOT NULL,
state_province VARCHAR(100) DEFAULT NULL,
native_status VARCHAR(50) DEFAULT NULL
);
";
sql_execute_multiple($dbh, $sql);
echo $done;

//////////////////////////////////////////////////////////
// Extract native status checklist records based on column 
// `NativeStatus`
//////////////////////////////////////////////////////////
echo "  Extracting state/province-level distribution records from table `usda_distNativeStatus`:\n";

// Loop through each record of raw distribution + native status table
$sql_native_status="
SELECT distNativeStatus, 
StateAndProvince, 
NativeStatus
FROM usda_distNativeStatus
;
";

$result = mysqli_query($dbh, $sql_native_status);
$nrows = mysqli_num_rows($result);
$curr_row = 1;
echo "    Processing row $curr_row of $nrows     ";

while ($row = mysqli_fetch_assoc($result)) {
	$distNativeStatus = trim($row["distNativeStatus"] ?? '');
	$distString = trim($row["StateAndProvince"] ?? '');
	$nativeString = trim($row["NativeStatus"] ?? '');	
	
	echo "\r    Processing row $curr_row of $nrows     ";
	//echo "\n\ndistn = $distString\r\n  nativeStatus = $nativeString";
	
	// Unpack distribution string to an array
	if (is_null($distString)) {
		$distArr[0]='Unknown';
	} else {
		// Parse distribution string
		// Because each token is globally-unique, do not need to intepret nesting
		// Therefore, replace paretheses with commas and use the commas as only 
		// delimiter
		$distString=str_replace("(",",",$distString);
		$distString=str_replace(")",",",$distString);
		
		// Remove USA+, just special annotation for US territories, same as USA. 
		$distString=str_replace("USA+","",$distString);
		
		// Break the string into tokens
		$poldivArr=explode(",",$distString);
	}	
	
	// Unpack native status string to an array
	unset($nativeStatusCombinedArr);
	if ($nativeString=="") {
		$nativeStatusCombinedArr[0]='unknown';
	} else {
		// Parse native status string
		// Native string is different; status abbreviations must be intepreted
		// relative to the regional abbreviations that precede them.
		// Commas alone preserve these relationships
		// Each token consists of two parts: (1) Native status region, and
		// (2) Native status code. These will be further broken down later.
		
		// Break the string into tokens
		$nativeStatusCombinedArr=explode(",",$nativeString);
	}
	
	// Loop through each element in distribution array and add record for
	// state/province level political divisions 
	foreach ($poldivArr AS $poldiv) {
		$poldiv = trim($poldiv ?? '');

		// Set SQL columns to null
		$nativeStatus = null;
		
		// Compose insert portion of the SQL; this is constant
		$sql_insert = "
		INSERT INTO usda_nativeStatus (
		distNativeStatus,
		country,
		state_province,
		native_status		
		)	
		";
		$sql_select = "";
		
		// Filter out countries and any mispelled political divisions 
		if (is_usda_poldiv($poldiv) && !is_usda_country_code($poldiv)) {			
			$countryCode = get_usda_countrycode($poldiv);
			$country = get_usda_poldivname($countryCode);
			$stateProvince = get_usda_poldivname($poldiv);
			
			// reset all temporary variables
			$currNativeStatusRegion = null;
			$nativeStatusCode = null;
			$currNativeStatus = null;
			
			// get code for USDA native status jurisdiction relevant 
			// to this political division
			$nativeStatusRegion = get_nativeStatusRegion($poldiv);
			//echo "\r\n  $poldiv: nativeStatusRegion=$nativeStatusRegion ";

			// get native status region and status
			// $status_found=false;
			foreach ($nativeStatusCombinedArr as $nativeStatusCombined) {
				$nativeStatusCombined=trim($nativeStatusCombined ?? '');
				$nativeStatusArr = explode(" ",$nativeStatusCombined);
				
				if ($nativeStatusArr[0]=="unknown" || $nativeStatusArr[0]=="")	{
					$currNativeStatusRegion="unknown";				
				} else {
					// Split again into region and native status parts
					$currNativeStatusRegion = trim($nativeStatusArr[0] ?? '');
					$nativeStatusCode = trim(str_replace(")","",str_replace("(","",$nativeStatusArr[1])) ?? '');
					$currNativeStatus = get_nativeStatus($nativeStatusCode);
					
				}
				//echo "\r\n    NSCombined=$nativeStatusCombined, currNSRegion=$currNativeStatusRegion, currNS=$currNativeStatus";
				
				// Use native status only if the current native status region is relevant 
				// to this political division. 
				if ($currNativeStatusRegion==$nativeStatusRegion || $nativeString=="") {
					// Check if current native status is relevant to this political division 
					$nativeStatus = $currNativeStatus;
				
					// For political divisions of Canada and L48, set native status 
					// to "unknown" if "native". In such cases, local status is 
					// uncertain: a species may be introduced locally, even if it is 
					// native for the country at a whole. USDA considers a species 
					// "native" to the Lower 48 if it is native anywhere in the Lower
					// 48 -- even if it is introduced in some states
					if (($nativeStatusRegion=="L48" || $nativeStatusRegion=="CAN") 
					&& $nativeStatus=="native") $nativeStatus = "unknown";
					if (is_null($nativeStatus) || $nativeStatus=="") $nativeStatus="unknown";
					//echo " Updated to: nativeStatus=$nativeStatus";
			
					// Compose remainder of SQL		
					// These are the values to be inserted			
					$sql_select="
					VALUES (
					'$distNativeStatus',
					'$country',
					'$stateProvince',
					'$nativeStatus'
					);
					";

					// Prepare SQL 
					$sql=$sql_insert."\r\n ".$sql_select;
	
					// add record to new table
					sql_execute_multiple($dbh, $sql);					
					
				}
			}
		}			
	}
	$curr_row++;
}

$curr_row = $curr_row-1;
echo "\r    Processing row $curr_row of $nrows...done\r\n";

//////////////////////////////////////////////////////////
// For Canada and L48 only, add each introduced species
// to each state or province as "not native"
//////////////////////////////////////////////////////////
echo "  Adding missing state/province-level records of introduced species:\r\n";

// Loop through each record of raw table
$sql_native_status="
SELECT distNativeStatus, 
StateAndProvince, 
NativeStatus
FROM usda_distNativeStatus
;
";

$result = mysqli_query($dbh, $sql_native_status);
$nrows = mysqli_num_rows($result);
$curr_row = 1;
echo "    Processing row $curr_row of $nrows     ";

while ($row = mysqli_fetch_assoc($result)) {
	$distNativeStatus = trim($row["distNativeStatus"] ?? '');
	$distString = trim($row["StateAndProvince"] ?? '');
	$nativeString = trim($row["NativeStatus"] ?? '');	
	
	echo "\r    Processing row $curr_row of $nrows     ";
	//echo "\r\n\r\ndist = $distString\r\n  nativeString = $nativeString";
	
	// Unpack distribution string to an array
	unset($distArr);
	if (is_null($distString)) {
		$distArr[0]='Unknown';
	} else {
		// Parse distribution string
		// Because each token is globally-unique, do not need to intepret nesting
		// Therefore, replace paretheses with commas and use the commas as only 
		// delimiter
		$distString=str_replace("(",",",$distString);
		$distString=str_replace(")",",",$distString);
		
		// Remove USA+, just special annotation for US territories, same as USA. 
		$distString=str_replace("USA+","",$distString);
		
		// Break the string into tokens
		$poldivArr=explode(",",$distString);
	}	
	
	// Unpack native status string to an array
	unset($nativeStatusCombinedArr);
	if ($nativeString=="") {
		$nativeStatusCombinedArr[0]='unknown';
	} else {
		// Parse native status string
		// Native string is different; status abbreviations must be intepreted
		// relative to the regional abbreviations that precede them.
		// Commas alone preserve these relationships
		// Each token consists of two parts: (1) Native status region, and
		// (2) Native status code. These will be further broken down later.
		
		// Break the string into tokens
		$nativeStatusCombinedArr=explode(",",$nativeString);
	}
	
	// Loop through each element in distribution array and add record for
	// state/province level political divisions 
	foreach ($poldivArr AS $poldiv) {
		$poldiv = trim($poldiv ?? '');
		
		// Set SQLL columns to null
		$country = null;
		$stateProvince = null;
		$nativeStatus = null;
		
		// Set insert half of the SQL; this is constant
		$sql_insert = "
		INSERT INTO usda_nativeStatus (
		distNativeStatus,
		country,
		state_province,
		native_status		
		)	
		";
		$sql_select = "";
		
		// Process only country-level status for US or Canada 
		if ($poldiv=="USA" || $poldiv=="CAN") {			
			$country = get_usda_poldivname($poldiv);
			
			// set relevant native status jurisdiction 
			// For US, only interested in L48
			$nativeStatusRegion="L48";
			if ($poldiv=="CAN") $nativeStatusRegion="CAN";
			//echo "\r\n  $poldiv: nativeStatusRegion=$nativeStatusRegion ";

			// get native status region and status
			foreach ($nativeStatusCombinedArr as $nativeStatusCombined) {
				$nativeStatusCombined=trim($nativeStatusCombined ?? '');
				$nativeStatusArr = explode(" ",$nativeStatusCombined);
				$currNativeStatusRegion = null;
				$currNativeStatus = null;
				
				if (!($nativeStatusArr[0]=="unknown" || $nativeStatusArr[0]=="")) {
					// Split again into region and native status parts
					$currNativeStatusRegion = trim($nativeStatusArr[0] ?? '');
					$nativeStatusCode = trim(str_replace(")","",str_replace("(","",$nativeStatusArr[1])) ?? '');
					$currNativeStatus = get_nativeStatus($nativeStatusCode);
					//echo "\r\n    NSCombined=$nativeStatusCombined, currNSRegion=$currNativeStatusRegion, currNS=$currNativeStatus";
				}
				
				// Use native status only if the current native status region is relevant 
				// to this political division AND nativeStatus='introduced'
				// NativeStatus set to "not native"; this means taxon introduced within
				// higher (containing) political division (in this case, country), but
				// not recorded for current political division. "introduced means recorded
				// for current political division and known to be introduced
				if ($currNativeStatusRegion==$nativeStatusRegion && $currNativeStatus=="introduced") {
					$nativeStatus = "introduced";
					//echo " Updated to: nativeStatus=$nativeStatus";
					
					if ($poldiv=="USA") {
						foreach ($stateL48Arr as $state) {
							$stateProv=get_usda_poldivname($state);
							
							// Check if entry already exists
							// for this species in this region
							$sql_existing_record="
							SELECT distNativeStatus 
							FROM usda_nativeStatus
							WHERE country='$country'
							AND state_province='$stateProv'
							AND distNativeStatus='$distNativeStatus'
							;
							";
							
							// Only add if no existing record
							if (sql_returns_records($dbh, $sql_existing_record)==false) {
								// Compose remainder of SQL		
								$sql_select="
								VALUES (
								'$distNativeStatus',
								'$country',
								'$stateProv',
								'not native'
								);
								";
							
								// Prepare final SQL 
								$sql=$sql_insert."\r\n ".$sql_select;
	
								// add record to new table
								sql_execute_multiple($dbh, $sql);
							}
						}
						
					} elseif ($poldiv=="CAN") {
						foreach ($provArr as $prov) {
							$stateProv=get_usda_poldivname($prov);

							// Check if entry already exists
							// for this species in this region
							$sql_existing_record="
							SELECT distNativeStatus 
							FROM usda_nativeStatus
							WHERE country='$country'
							AND state_province='$stateProv'
							AND distNativeStatus='$distNativeStatus'
							;
							";
							
							// Only add if no existing record
							if (sql_returns_records($dbh, $sql_existing_record)==false) {
								// Compose remainder of SQL		
								$sql_select="
								VALUES (
								'$distNativeStatus',
								'$country',
								'$stateProv',
								'not native'
								);
								";
							
								// Prepare final SQL 
								$sql=$sql_insert."\r\n ".$sql_select;
	
								// add record to new table
								sql_execute_multiple($dbh, $sql);
							}
						}					
					}					
				}
			}
		}			
	}
	$curr_row++;
}

$curr_row = $curr_row-1;
echo "\r    Processing row $curr_row of $nrows...done\r\n";

//////////////////////////////////////////////////////////
// Make duplicate "raw" table of unique, atomic native 
// status x region x taxon assertions
//////////////////////////////////////////////////////////

$tbl_raw2 = $tbl_raw . "2";

echo "  Creating table `$tbl_raw2` of atomic taxon x region x native status assertions...";

echo "    Indexing foreign key in table `usda_nativeStatus`..."
$sql="
ALTER TABLE usda_nativeStatus
ADD INDEX (distNativeStatus)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Generating table `$tbl_raw2`..."
$sql="
DROP TABLE IF EXISTS `$tbl_raw2`;
CREATE TABLE `$tbl_raw2` AS 
SELECT 
b.country,
b.state_province,
NULL AS county_parish,
a.family,
a.genus,
a.scientificName,
b.native_status,
NULL AS cult_status
FROM `$tbl_raw` a JOIN usda_nativeStatus b
ON a.distNativeStatus=b.distNativeStatus
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "    Indexing table `$tbl_raw2`...";
$sql="
ALTER TABLE $tbl_raw2;
ADD INDEX (country),
ADD INDEX (state_province),
ADD INDEX (family),
ADD INDEX (genus),
ADD INDEX (scientificName),
ADD INDEX (native_status)
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

//////////////////////////////////////////////////////////
// Rename original raw table and rename new to old
//////////////////////////////////////////////////////////


echo "  Renaming `$tbl_raw` TO `$tbl_raw_orig`...";
$tbl_raw_orig=$tbl_raw . "_orig";
$sql="
RENAME TABLE `$tbl_raw` TO `$tbl_raw_orig`;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Removing duplicate records from `$tbl_raw2` and renaming to `$tbl_raw`...";
$sql="
CREATE TABLE $tbl_raw LIKE $tbl_raw2;
INSERT INTO $tbl_raw SELECT DISTINCT * FROM $tbl_raw2;
DROP TABLE $tbl_raw2;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>