DROP TABLE UNKNOWNPK1;
DROP TABLE UNKNOWNPK2;

CREATE TABLE UNKNOWNPK1
(
    id     DECIMAL(32)          PRIMARY KEY,
    name   VARCHAR(32) 
);

CREATE TABLE UNKNOWNPK2
(
    id     DECIMAL(32)          PRIMARY KEY,
    name   VARCHAR(32) 
);

commit;

quit;
