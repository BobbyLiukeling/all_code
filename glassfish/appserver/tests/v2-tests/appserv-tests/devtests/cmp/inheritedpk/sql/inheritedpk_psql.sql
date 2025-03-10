DROP TABLE D cascade;
DROP TABLE C cascade;
DROP TABLE B cascade;
DROP TABLE A cascade;


CREATE TABLE A
(
    ID     INT          PRIMARY KEY,
    LASTNAME  VARCHAR(32) NULL,
    FIRSTNAME VARCHAR(32) NULL,
    HIREDATE  TIMESTAMP         NULL,
    BIRTHDATE TIMESTAMP         NULL,
    SALARY    FLOAT        NOT NULL
);

CREATE TABLE B
(
    ID TIMESTAMP          PRIMARY KEY,
    NAME   VARCHAR(32) NULL
);

CREATE TABLE C
(
    ID INT          PRIMARY KEY,
    NAME   VARCHAR(32) NULL
);

commit;

quit;
