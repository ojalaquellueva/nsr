-- ---------------------------------------------------------------
-- Update table meta to new schema, ahead of database rebuild
-- Add old version information and insert new record
-- Not yet added to DB pipeline
-- Note: citation should load from bibtex file!
-- ---------------------------------------------------------------

-- Rename old table
ALTER TABLE meta RENAME TO meta_orig;

-- Create new table
CREATE TABLE meta (
id int unsigned auto_increment,
app_version VARCHAR(50) DEFAULT NULL,
db_version VARCHAR(50) DEFAULT NULL,
db_version_comments VARCHAR(250) DEFAULT NULL,
db_modified_date date,
db_full_build_date date,
code_version VARCHAR(50) DEFAULT NULL,
code_version_comments VARCHAR(250) DEFAULT NULL,
code_version_release_date date,
citation text,
publication text,
logo_path text,
PRIMARY KEY (id)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci
;


INSERT INTO meta (
db_version,
code_version,
db_modified_date,
db_full_build_date
)
SELECT
db_version,
api_core_version_compatible,
date_format(build_date, '%Y-%m-%d'),
'2020-09-15'
FROM meta_orig
;

INSERT INTO meta (
app_version,
db_version,
db_version_comments,
db_modified_date,
db_full_build_date,
code_version,
code_version_comments,
code_version_release_date,
citation,
publication,
logo_path
)
VALUES (
'2.5',
'2.1.1',
'Update DB metadata schema to match GNRS & TNRS',
'2024-04-10',
'2020-09-15',
'2.5',
'Merge db and core code into single repo',
'2024-04-10',
'@misc{nsr.app, author = {Boyle, B. L. and Maitner, B. and Barbosa, G. C. and Rethvick, S. Y. B. and Enquist, B. J.}, journal = {Botanical Information and Ecology Network}, title = {Native Species Resolver}, year = {2024}, url = {https://nsr.biendata.org/}, note = {Accessed <date_of_access>} }',
'',
''
);

