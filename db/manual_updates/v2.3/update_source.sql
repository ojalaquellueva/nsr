-- -------------------------------------------------------------------
-- Corrections to citations in table source
-- -------------------------------------------------------------------

/* 
This manual update uses import from bibtex files
Not yet supported by main DB pipeline
*/


-- Source newguinea
DROP TABLE IF EXISTS citation_raw;
CREATE TABLE citation_raw (
citation TEXT DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
-- Use dummy dos line endings to trick into loading as single row
LOAD DATA LOCAL INFILE '/home/boyle/bien/nsr/data/db/newguinea/newguinea.bib.no-line-endings' 
INTO TABLE citation_raw 
LINES TERMINATED BY '\r'
;
UPDATE source s, citation_raw c
SET s.citation=c.citation
WHERE s.source_name='newguinea'
;
DROP TABLE IF EXISTS citation_raw;

-- Source fwi
DROP TABLE IF EXISTS citation_raw;
CREATE TABLE citation_raw (
citation TEXT DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
-- Use dummy dos line endings to trick into loading as single row
LOAD DATA LOCAL INFILE '/home/boyle/bien/nsr/data/db/fwi/fwi.bib.no-line-endings' 
INTO TABLE citation_raw 
LINES TERMINATED BY '\r'
;
UPDATE source s, citation_raw c
SET s.citation=c.citation
WHERE s.source_name='fwi'
;
DROP TABLE IF EXISTS citation_raw;

-- source flbr
CREATE TABLE citation_raw (
citation TEXT DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_general_ci;
-- Use dummy dos line endings to trick into loading as single row
LOAD DATA LOCAL INFILE '/home/boyle/bien/nsr/data/db/flbr/flbr.bib.no-line-endings' 
INTO TABLE citation_raw 
LINES TERMINATED BY '\r'
;
UPDATE source s, citation_raw c
SET s.citation=c.citation
WHERE s.source_name='flbr'
;
DROP TABLE IF EXISTS citation_raw;

