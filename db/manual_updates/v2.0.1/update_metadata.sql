-- ---------------------------------------------------------------
-- Alter `meta` column names to distinguish between NSR api/core 
-- code and NSR db code versions & populate revised meta table.
-- ---------------------------------------------------------------

-- Create new table
DROP TABLE IF EXISTS meta;
CREATE TABLE meta (
id INT(11) UNSIGNED NOT NULL AUTO_INCREMENT, 
db_version VARCHAR(50) DEFAULT NULL,
code_version VARCHAR(50) DEFAULT NULL,
build_date timestamp,
api_core_version_compatible VARCHAR(50) DEFAULT NULL,
PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci
;

-- Update code_version with latest git tag for TNRS DB code.
-- DB version is the code version on date of build. Thus, code_version
-- can continuing incrementing by minor versions without
-- db_version changing, as long as database is not updated.
-- Be sure to update repo and tag with new version number
-- after building Db and executing all scripts in this directory. 
-- Leave DB version as is
INSERT INTO meta (
db_version,
code_version,
build_date,
api_core_version_compatible
)
VALUES (
'2.0',
'2.0.1',
'2020-09-15 00:00:00',
'2.3.1'
);
