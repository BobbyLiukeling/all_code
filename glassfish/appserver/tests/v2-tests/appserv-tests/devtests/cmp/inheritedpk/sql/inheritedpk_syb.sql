DROP TABLE D
DROP TABLE C
DROP TABLE B
DROP TABLE A
go


CREATE TABLE A
(
    ID     INT          PRIMARY KEY NOT NULL,
    LASTNAME  VARCHAR(32) NULL,
    FIRSTNAME VARCHAR(32) NULL,
    HIREDATE  DATETIME     NULL,
    BIRTHDATE DATETIME     NULL,
    SALARY    FLOAT        NOT NULL
)

CREATE TABLE B
(
    ID DATETIME          PRIMARY KEY NOT NULL,
    NAME   VARCHAR(32) NULL
)

CREATE TABLE C
(
    ID INT          PRIMARY KEY NOT NULL,
    NAME   VARCHAR(32) NULL
)

go
