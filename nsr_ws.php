<?php

// Mode determines which database is used
$MODE = "ws";

/*
ini_set('display_errors', 1);
ini_set('display_startup_errors', 1);
error_reporting(E_ALL);
*/

/* 
Native Status Resolver (NSR)

A basic NSR webservice
For each valid combination of species+country+state_province+county_parish
Returns and evaluation of native status
Return format is xml (default) or json

url syntax:

http://bien.nceas.ucsb.edu/bien/apps/nsr/nsr_ws.php?species=Pinus%20ponderosa&country=United%20States&stateprovince=Arizona&countyparish=Pima&format=json

stateprovince, countyparish and format are optional

*/ 

$ws_includes_dir = "nsr_ws_includes";

// These parameters not needed for web service
// Set to TRUE as included in most WHERE clauses
$JOB_WHERE = " 1 ";
$BATCH_WHERE = " 1 ";
$JOB_WHERE_NA = " 1 ";
$BATCH_WHERE_NA = " 1 ";

// Get db connection parameters (in ALL CAPS)
include 'params.php';
//echo "<br />Exiting @ params...<br />";  exit(); 
include_once $CONFIG_DIR.'db_config.php';
//echo "<br />Exiting @ db_config...<br />";  exit();	

// Get type of request
// Assume resolve if not set
isset($_GET['do']) ? $do = $_GET['do'] : $do = "resolve";

if ($do=="poldivs" || $do=="resolve" || $do=="meta" ) {
	$format='xml'; // The default
	
	if ( isset($_GET['format']) ) {
		$format = strtolower($_GET['format']) == 'json' ? 'json' : 'xml'; 
	}
	
	// connect to the db
	$link = mysqli_connect($HOST,$USER,$PWD,$DB);
	
	// check connection
	if (mysqli_connect_errno()) {
		echo "Connection failed: ". mysqli_connect_error();
		exit();
	}
} else {
	echo "<strong>BAD REQUEST</strong>";
	exit();
}

if ($do == "meta" ) {
	// Ignore all other params except format (already handled above)
	// and return full metadata
	$sql="
	SELECT source_name AS source_code, source_name_full, source_url, 
		date_accessed, regional_scope, taxonomic_scope, source_citation
	FROM source
	ORDER BY source_name
	;
	";
} elseif ($do == "poldivs" ) {
	// Defaults
	$filter_by_checklist=false;
	$where_country="";

	// Get optional parameters, if any
	if ( isset($_GET['country']) || isset($_GET['checklist']) ) {
		// Preparing for security checks
		if (!mysqli_set_charset($link, 'latin1')) {
			echo ("<br />Error loading character set utf8<br />");
		}
		
		if ( isset($_GET['country']) ) {
			$country = $_GET['country'];
			
			// Security
			$country = mysqli_real_escape_string($link, $country);
			$country = addcslashes($country, '%_');

			// Form where criteria for country
			if ( isset($_GET['checklist']) ) {
				$where_country=strlen($country)<1 ? "" : " AND poldiv_name='$country' ";
			} else {
				$where_country=strlen($country)<1 ? "" : " AND country='$country' ";
			}
		}
		
		if ( isset($_GET['checklist']) ) {
			$checklist = $_GET['checklist'];

			// security
			$checklist = mysqli_real_escape_string($link, $checklist);
			$checklist = addcslashes($checklist, '%_');
		
			if ( $checklist=='true' ) {
				$filter_by_checklist=true;
			} elseif ( ! $checklist=='false' ) {			
				echo ("<br />Error: invalid option parameter 'checklist', must be true or false<br />");		
			}
		}
	}
	
	if ( $filter_by_checklist===false ) {
		// Get list of political divisions with any information at all
		// Queries table distribution
		$sql="
		SELECT DISTINCT country, state_province, county_parish 
		FROM distribution
		WHERE 1 $where_country
		ORDER BY country, state_province, county_parish 
		;
		";
	} else {
		// Get list of politcal divisions with comprehensive checklists only
		// Queries table poldiv_source
		
		// Currently returns countries only
		// Temporary solution until change table to support poldivs 
		// at all levels
		$sql="
		SELECT DISTINCT poldiv_name AS country, NULL AS state_province, NULL AS county_parish 
		FROM poldiv_source
		WHERE 1 $where_country
		ORDER BY poldiv_name, state_province, county_parish 
		;
		";	
	}
} elseif ($do == "resolve") {
	if ( isset($_GET['country']) && isset($_GET['species'])) {
	
		/* get the passed variable or set our own */

		$species = $_GET['species'];
		$country = $_GET['country'];
		isset($_GET['stateprovince']) ? $stateprovince = $_GET['stateprovince'] : $stateprovince = "";
		isset($_GET['countyparish']) ? $countyparish = $_GET['countyparish'] : $countyparish = "";
	
		/* activate to check starting character set
		$chrst = mysqli_character_set_name($link);
		echo "<br />Character set: $chrst<br />";
		*/
	
		// security
		// set the character set to allow proper use of escape 
		// function & escape any potentially malicious characters
		if (!mysqli_set_charset($link, 'latin1')) {
			echo ("<br />Error loading character set utf8<br />");
		}
		$species = mysqli_real_escape_string($link, $species);
		$species = addcslashes($species, '%_');
		$country = mysqli_real_escape_string($link, $country);
		$country = addcslashes($country, '%_');
		$stateprovince = mysqli_real_escape_string($link, $stateprovince);
		$stateprovince = addcslashes($stateprovince, '%_');
		$countyparish = mysqli_real_escape_string($link, $countyparish);
		$countyparish = addcslashes($countyparish, '%_');
	
		// get the genus from the species
		$nameparts=explode(' ',$species);
		$genus = $nameparts[0];
		
		// get the APGIII family from TNRS lookup
		$fam = "";
		$url_tnrs_base = 'http://tnrs.iplantc.org/tnrsm-svc/matchNames?retrieve=best&names=';
		$name=urlencode($species);
		$url_tnrs=$url_tnrs_base.$name;	
		$json = @file_get_contents($url_tnrs);
		if ( ! $json === false) {
			$tnrs_results = json_decode($json,true);
			$fam = $tnrs_results['items'][0]['family'];	
		}
	
		// Generate unique job #
		$job = "nsr_ws_" . date("Y-m-d-G:i:s").":".str_replace(".0","",strtok(microtime()," "));

		// Add records to new observation table
		include_once $ws_includes_dir."/"."add_observations.php";	
		include_once $ws_includes_dir."/"."standardize_observations.php";	

		// Mark results already in cache
		include_once "mark_observations.php";	

		// Process observations not in cache, then add to cache
		// Do only if >=1 observations not in cache
		$sql="
		SELECT id
		FROM observation
		WHERE is_in_cache=0
		LIMIT 1;
		";
		$result = mysqli_query($link,$sql) or die('Offending query:  '.$sql);	
		if (mysqli_num_rows($result)) {
			include_once "nsr.php";	
		} else {
			//echo "<br />All observations already in cache...<br />";
		}
	
		
		// Query the cached results
	
		// Form variable where criteria
		$where_stateprovince=strlen($stateprovince)<1?"state_province IS NULL":"state_province='$stateprovince'";
		$where_countyparish=strlen($countyparish)<1?"county_parish IS NULL":"county_parish='$countyparish'";
		
		// form the sql	
		$sql = "
		SELECT 
		family,
		IF(genus LIKE '%aceae','',genus) AS genus,
		IF(species NOT LIKE '% %','',species) AS species,
		country,
		IFNULL(state_province,'') AS state_province,
		IFNULL(county_parish,'') AS county_parish,
		native_status,
		native_status_reason,
		native_status_sources,
		isIntroduced,
		isCultivatedNSR AS isCultivated
		FROM cache
		WHERE species='$species'
		AND country='$country'
		AND $where_stateprovince
		AND $where_countyparish
		";
		
	} else {
		echo "<strong>Parameters species and/or country missing!</strong>";
	}
}
	
//echo "<br />SQL:<br />$sql<br />";

$result = mysqli_query($link,$sql) or die('Offending query:  '.$sql);

// create one master array of the records
$nsr_results = array();
if(mysqli_num_rows($result)) {
	while($nsr_result = mysqli_fetch_assoc($result)) {
		$nsr_results[] = array('nsr_result'=>$nsr_result);
	}
}

// output in chosen format
if ($format == 'json') {
	header('Content-type: application/json');
	echo json_encode(array('nsr_results'=>$nsr_results));
} else {
	header('Content-type: text/xml');
	echo '<nsr_results>';
	foreach($nsr_results as $index => $nsr_result) {
		if(is_array($nsr_result)) {
			foreach($nsr_result as $key => $value) {
				echo '<',$key,'>';
				if(is_array($value)) {
					foreach($value as $tag => $val) {
						echo '<',$tag,'>',$val,'</',$tag,'>';
					}
				}
				echo '</',$key,'>';
			}
		}
	}
	echo '</nsr_results>';
}

/* disconnect from the db */
@mysqli_close($link);

?>
