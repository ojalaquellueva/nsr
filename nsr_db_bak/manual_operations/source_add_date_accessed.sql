-- adds column date_accessed to table nsr.source
-- This is now done automatically by pipeline

alter table source
add column date_accessed varchar(10) default null;

update source
set date_accessed=
CASE
WHEN source_name='enquist' THEN '2014-07-30'
WHEN source_name='ipane' THEN '2014-03-10'
WHEN source_name='tropicos' THEN '2014-03-10'
WHEN source_name='usda' THEN '2014-03-10'
WHEN source_name='vascan' THEN '2014-03-10'
WHEN source_name='weakley' THEN '2014-07-30'
END
;