drop table SUPPLIERS
drop table PARTS
go

create table PARTS (
    PARTID INT PRIMARY KEY NOT NULL,
    NAME VARCHAR(15),
    COLOR VARCHAR(20),
    WEIGHT INT,
    PRICE FLOAT
)

create table SUPPLIERS (
    PARTID INT NOT NULL references PARTS(PARTID),
    SUPPLIERID INT NOT NULL,
    NAME VARCHAR(15), 
    STATUS INT,
    CITY VARCHAR(50),
    constraint PK_SUPPLIERS primary key(SUPPLIERID, PARTID)
)

go
