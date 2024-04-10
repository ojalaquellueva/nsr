REVOKE ALL PRIVILEGES ON nsr_dev.* FROM nsr_read@localhost;
REVOKE ALL PRIVILEGES ON nsr_dev.* FROM nsr@localhost;

GRANT SELECT ON nsr_dev.* TO 'nsr_read'@'localhost';

GRANT SELECT, INSERT, UPDATE, DELETE, ALTER, CREATE ROUTINE
ON nsr_dev.* TO 'nsr'@'localhost';
GRANT EXECUTE ON `nsr_dev`.* TO 'nsr'@'localhost';
GRANT DROP ON TABLE nsr_dev.* TO 'nsr'@'localhost';
GRANT CREATE ON TABLE nsr_dev.* TO 'nsr'@'localhost';

FLUSH PRIVILEGES;