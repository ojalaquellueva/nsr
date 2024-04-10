-- ---------------------------------------------------------------
-- Alter schema of table source to (partly) match GNRS DB
-- Not yet added to DB pipeline
-- ---------------------------------------------------------------

ALTER TABLE source RENAME COLUMN source_citation TO citation;
