-- ---------------------------------------------------------------
-- Update updata metadata
-- Not yet added to DB pipeline
-- Note: citation should load from bibtex file!
-- ---------------------------------------------------------------

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
'2.5.1',
'2.3',
'Add data dictionary tables',
'2024-04-17',
'2020-09-15',
'2.5.1',
'Add data dictionary API calls',
'2024-04-17',
'@misc{nsr.app, author = {Boyle, B. L. and Maitner, B. and Barbosa, G. C. and Rethvick, S. Y. B. and Enquist, B. J.}, journal = {Botanical Information and Ecology Network}, title = {Native Species Resolver}, year = {2024}, url = {https://nsr.biendata.org/}, note = {Accessed <date_of_access>} }',
'',
''
);

