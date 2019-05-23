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

/* require the user as the parameter */
// add a strlen check as well
if(isset($_GET['country']) && isset($_GET['species'])) {
	
	/* get the passed variable or set our own */
	$format = strtolower($_GET['format']) == 'json' ? 'json' : 'xml'; //xml is the default
	$species = $_GET['species'];
	$country = $_GET['country'];
	$stateprovince = $_GET['stateprovince'];
	$countyparish = $_GET['countyparish'];
	
	/* connect to the db */
	$link = mysqli_connect($HOST,$USER,$PWD,$DB);
	/* check connection */
	if (mysqli_connect_errno()) {
		echo "Connection failed: ". mysqli_connect_error();
		exit();
	}

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
	$url_tnrs_base='http://tnrs.iplantc.org/tnrsm-svc/matchNames?retrieve=best&names=';
	$name=urlencode($species);
	$url_tnrs=$url_tnrs_base.$name;	
	$json=file_get_contents($url_tnrs);
	$tnrs_results = json_decode($json,true);
	$fam = $tnrs_results['items'][0]['family'];	
	
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
	IF(genus LIKE '%aceae',NULL,genus) AS genus,
	IF(species NOT LIKE '% %',NULL,species) AS species,
	country,
	state_province,
	county_parish,
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
	if($format == 'json') {
		header('Content-type: application/json');
		echo json_encode(array('nsr_results'=>$nsr_results));
	}
	else {
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
}

?>
