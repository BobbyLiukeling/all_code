DROP TABLE D
DROP TABLE C
DROP TABLE B
DROP TABLE A
go


CREATE TABLE A
(
    ID INT          PRIMARY KEY NOT NULL,
    NAME   VARCHAR(32) NULL
)

CREATE TABLE B
(
    ID     INT          PRIMARY KEY NOT NULL,
    NAME   VARCHAR(32) NULL,
    AID    INT          NULL,
    FOREIGN KEY (AID)   REFERENCES A (ID)
)

CREATE TABLE C
(
    ID   INT          PRIMARY KEY NOT NULL,
    NAME VARCHAR(32) NULL,
    AID   INT          NULL,
    BID   INT          NULL,
    FOREIGN KEY (AID)  REFERENCES A (ID),
    FOREIGN KEY (BID)  REFERENCES B (ID)
)

CREATE TABLE D
(
    ID   INT          PRIMARY KEY NOT NULL,
    NAME VARCHAR(32) NULL,
    AID   INT          NULL,
    BID   INT          NULL,
    CID   INT          NULL,
    FOREIGN KEY (AID)  REFERENCES A (ID),
    FOREIGN KEY (BID)  REFERENCES B (ID),
    FOREIGN KEY (CID)  REFERENCES C (ID)
)

go

