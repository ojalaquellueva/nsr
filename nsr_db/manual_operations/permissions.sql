REVOKE ALL PRIVILEGES ON nsr_test2.* FROM bien_read@localhost;
REVOKE ALL PRIVILEGES ON nsr_test2.* FROM bien_web@localhost;
REVOKE ALL PRIVILEGES ON nsr_test2.* FROM bien_write@localhost;
REVOKE ALL PRIVILEGES ON nsr_test2.* FROM nsr@localhost;

GRANT SELECT ON nsr_test2.* TO 'bien_read'@'localhost';

GRANT SELECT ON nsr_test2.* TO 'bien_web'@'localhost';

GRANT SELECT, INSERT, UPDATE, DELETE 
ON nsr_test2.* TO 'bien_write'@'localhost';
GRANT DROP ON TABLE nsr_test2.* TO 'bien_write'@'localhost';
GRANT CREATE ON TABLE nsr_test2.* TO 'bien_write'@'localhost';

GRANT ALL ON nsr_test2.* TO 'admin'@'localhost';

GRANT SELECT, INSERT, UPDATE, DELETE, ALTER 
ON nsr_test2.* TO 'nsr'@'localhost';
GRANT DROP ON TABLE nsr_test2.* TO 'nsr'@'localhost';
GRANT CREATE ON TABLE nsr_test2.* TO 'nsr'@'localhost';

FLUSH PRIVILEGES;