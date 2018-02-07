<?php

//////////////////////////////////////////
// fix misc errors in state_province
//////////////////////////////////////////

echo "Fixing errors in political division tables:\r\n";

echo "  country...";
$sql="
UPDATE countryName
SET countryNameStd='Aland Islands'
WHERE countryNameStd LIKE '%land Islands'
;
UPDATE countryName
SET countryNameStd='Reunion'
WHERE countryNameStd='RÃ©union'
;
UPDATE countryName
SET countryNameStd='Saint Barthelemy'
WHERE countryNameStd LIKE 'Saint Barth%'
;

-- Some missing values
INSERT INTO countryName (
countryName,
countryID,
isoCode,
countryCode3Char,
countryNameStd
)
VALUES
(
'Iran',
109,
'IR',
'IRN',
'Iran, Islamic Republic of'
),
(
'Saint Barthelemy',
27,
'BL',
'BLM',
'Saint Barthelemy'
),
(
'Sint Maarten',
211,
'SX',
'SXM',
'Sint Maarten (Dutch part)'
),
(
'Sint-Maarten',
211,
'SX',
'SXM',
'Sint Maarten (Dutch part)'
),
(
'Virgin Islands (US)',
239,
'VG',
'VGB',
'U.S. Virgin Islands'
)
;
";
sql_execute_multiple($sql);
echo $done;


echo "  state_province...";
$sql="
UPDATE state_province
SET 
state_province_ascii='Estado de Veracruz',
state_province_std='Veracruz'
WHERE country_iso='MX'  
AND state_province_ascii='Estado de Veracruz-Llave'
;
UPDATE state_province
SET 
state_province_ascii='Estado de Michoacan',
state_province_std='Michoacan'
WHERE country_iso='MX'  
AND state_province_ascii='Estado de Michoacan de Ocampo'
;
UPDATE state_province
SET 
state_province_ascii='Estado de Coahuila',
state_province_std='Coahuila'
WHERE country_iso='MX'  
AND state_province_ascii='Estado de Coahuila de Zaragoza'
;
";
sql_execute_multiple($sql);
echo $done;

echo "  state_province_name...";
$sql="
UPDATE state_province_name
SET 
state_province_ascii='Estado de Veracruz',
state_province_std='Veracruz'
WHERE country_iso='MX'  
AND state_province_ascii='Estado de Veracruz-Llave'
;
UPDATE state_province_name
SET 
state_province_ascii='Estado de Michoacan',
state_province_std='Michoacan'
WHERE country_iso='MX'  
AND state_province_ascii='Estado de Michoacan de Ocampo'
;
UPDATE state_province_name
SET 
state_province_ascii='Estado de Coahuila',
state_province_std='Coahuila'
WHERE country_iso='MX'  
AND state_province_ascii='Estado de Coahuila de Zaragoza'
;
";
sql_execute_multiple($sql);
echo $done;

?>