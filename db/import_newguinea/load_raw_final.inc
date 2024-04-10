<?php

///////////////////////////////////////////////////////
// Load country- and state-level observations
///////////////////////////////////////////////////////


echo "Extracting country and state observations to table `$tbl_raw_final`:\r\n";

echo "  Papua New Guinea...";
$sql="
INSERT INTO $tbl_raw_final (
taxon,
country,
state_province,
county_parish,
native_status
) 
SELECT
`fullname_expert_verified`,
'Papua New Guinea',
NULL,
NULL,
CASE
WHEN endemic='y' THEN 'endemic'
WHEN endemic='n' AND native='y' THEN 'native'
WHEN native<>'y' THEN 'introduced'
ELSE 'unknown'
END
FROM $tbl_raw
WHERE `PNG`='y'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Indonesia: Papua...";
$sql="
INSERT INTO $tbl_raw_final (
taxon,
country,
state_province,
county_parish,
native_status
) 
SELECT
`fullname_expert_verified`,
'Indonesia',
'Papua',
NULL,
CASE
WHEN endemic='y' THEN 'endemic'
WHEN endemic='n' AND native='y' THEN 'native'
WHEN native<>'y' THEN 'introduced'
ELSE 'unknown'
END
FROM $tbl_raw
WHERE `IDN`='y'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

echo "  Indonesia: West Papua...";
$sql="
INSERT INTO $tbl_raw_final (
taxon,
country,
state_province,
county_parish,
native_status
) 
SELECT
`fullname_expert_verified`,
'Indonesia',
'Papua Barat',
NULL,
CASE
WHEN endemic='y' THEN 'endemic'
WHEN endemic='n' AND native='y' THEN 'native'
WHEN native<>'y' THEN 'introduced'
ELSE 'unknown'
END
FROM $tbl_raw
WHERE `IDN`='y'
;
";
sql_execute_multiple($dbh, $sql);
echo $done;

?>