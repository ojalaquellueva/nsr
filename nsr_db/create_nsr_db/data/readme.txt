Political division lookup files

Derived from custom BIEN import of geonames database in postgres (see separate documentation).

country.csv:

\COPY (SELECT country_id, country, iso, iso_alpha3, fips FROM country) TO '/tmp/country.csv' DELIMITER ',' CSV HEADER;

countryNames.txt:



stateProvince.csv:

\COPY (SELECT state_province_id, country, country_iso, state_province, state_province_ascii, state_province_code, state_province_code_full AS state_province_code_unique FROM state_province) TO '/tmp/stateProvince.csv' DELIMITER ',' CSV HEADER;

stateProvineName.csv:

\COPY (SELECT b.state_province_name_id, b.state_province_name, a.country_iso, a.country, a.state_province_id, a.state_province, a.state_province_ascii FROM state_province a JOIN state_province_name b ON a.state_province_id=b.state_province_id) TO '/tmp/stateProvinceName.csv' DELIMITER ',' CSV HEADER;

