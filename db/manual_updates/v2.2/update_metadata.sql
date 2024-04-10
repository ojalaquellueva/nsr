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
'2.5',
'2.2',
'Minor schema change of table source to match GNRS',
'2024-04-10',
'2020-09-15',
'2.5',
'Merge db and core code into single repo',
'2024-04-10',
'@misc{nsr.app, author = {Boyle, B. L. and Maitner, B. and Barbosa, G. C. and Rethvick, S. Y. B. and Enquist, B. J.}, journal = {Botanical Information and Ecology Network}, title = {Native Species Resolver}, year = {2024}, url = {https://nsr.biendata.org/}, note = {Accessed <date_of_access>} }',
'',
''
);

