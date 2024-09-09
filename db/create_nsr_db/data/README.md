# Political division lookup files

## Overview

The CVS files in this directory are used to build the core political division tables of the NSR. The source tables are from custom BIEN imports of geonames & gadm databases in postgres (see separate documentation).

## Files

### `country.csv`

\c geomnames

\COPY (SELECT country_id, country, iso, iso_alpha3, fips FROM country) TO '/tmp/country.csv' DELIMITER ',' CSV HEADER;

### `countryNames.txt`

\c geomnames




### `stateProvince.csv`

\c geomnames

\COPY (SELECT state_province_id, country, country_iso, state_province, state_province_ascii, state_province_code, state_province_code_full AS state_province_code_unique FROM state_province) TO '/tmp/stateProvince.csv' DELIMITER ',' CSV HEADER;

### `stateProvineName.csv`

\c geomnames

\COPY (SELECT b.state_province_name_id, b.state_province_name, a.country_iso, a.country, a.state_province_id, a.state_province, a.state_province_ascii FROM state_province a JOIN state_province_name b ON a.state_province_id=b.state_province_id) TO '/tmp/stateProvinceName.csv' DELIMITER ',' CSV HEADER;

### `gadm_admin_1.csv`

\c gadm

\COPY (SELECT * FROM gadm_admin_1) TO '/tmp/gadm_admin_1.csv' DELIMITER ',' CSV HEADER;




