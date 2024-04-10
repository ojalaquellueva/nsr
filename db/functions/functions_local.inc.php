<?php

/////////////////////////////////////////////////////////
// Temporary location for testing PHP functions locally
// before commiting to submodule "includes"
/////////////////////////////////////////////////////////

function db_exists($dbname, $uname, $pwd) {
	/////////////////////////////////////////////////////
	// Returns TRUE if (local) MySQL database dbname 
	// exists, else FALSE
	/////////////////////////////////////////////////////

    $connection;
    $connection = new PDO("mysql:host=localhost", $uname, $pwd);
    $connection->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION); 
    $stmt = $connection->prepare("SELECT SCHEMA_NAME FROM INFORMATION_SCHEMA.SCHEMATA WHERE SCHEMA_NAME =:dbname");
    $stmt->execute(array(":dbname"=>$dbname));
    $row=$stmt->fetch(PDO::FETCH_ASSOC);

    if ($stmt->rowCount() == 1) {
        Return TRUE;
    } else { 
    	Return FALSE; 
    }
}

function NA_to_null($db_con, $tbl) {
	// Converts N A (from R) to NULL for all columns in table

	if (exists_table($db_con, $tbl)===false) return "Failed to fix quotes: table '$tbl' doesn't exist!";
	$test_sql="SELECT * FROM `$tbl`;";
	//if (sql_returns_records($db_con, $test_sql)) return true;
	if (sql_returns_records($db_con, $test_sql)===false) {
		//echo "no records in table!";
		return true;
	}
	
	$field_type_list = sql_field_type_list($db_con, $tbl,"|");

	// make new $fld_list array of char-type fields only
	foreach ($field_type_list as $field_type) {
		$fldtyp = explode("|",$field_type);
		$fld = $fldtyp[0];
		$typ = $fldtyp[1];
		if (strpos($typ,"char")) $fld_list[]=$fld;
		//echo "\r\nField: $fld, type: $typ";
	}
	foreach ($fld_list as $fld) {
		//echo "Updating field $fld\r\n";
		$sql = "UPDATE $tbl SET `$fld`=NULL WHERE TRIM(`$fld`)='NA';";
		//echo $sql."\r\n";
		$msg_fail="Failed to convert empty strings to NULL in table `$tbl`.  ";
		if (sql_execute($db_con, $sql,true,true,'',$msg_fail));
	}
	return true;
}

function csvtoarray($file,$delimiter,$lines)
{
    if (($handle = fopen($file, "r")) === false) {
    	die("can't open the file.");
    }

    $f_csv = fgetcsv($handle, 4000, $delimiter);
    $f_array = array();

    while ($row = fgetcsv($handle, 4000, $delimiter)) {
            $f_array[] = array_combine($f_csv, $row);
    }

    fclose($handle);
    $f_array = array_slice($f_array, 0, $lines); // Get requested subset
    
    return $f_array;
}

?>