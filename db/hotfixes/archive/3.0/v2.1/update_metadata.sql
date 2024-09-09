-- ---------------------------------------------------------------
-- Add new version record to table meta
-- ---------------------------------------------------------------

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
'2.1',
'2.1',
'2024-04-10',
'2.4'
);
