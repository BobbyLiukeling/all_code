drop table LINEITEM
drop table ORDERS
drop table VENDOR_PART
drop table VENDOR
drop table PART_DETAIL
drop table PART

go

/* Self-ref to identify Bill of Material (BOM)
 * Compound PK
 */
create table PART (
        PART_NUMBER             VARCHAR(15)     NOT NULL,
        REVISION                NUMERIC(2)      NOT NULL,
        DESCRIPTION             VARCHAR(255)    NULL,
        REVISION_DATE           DATETIME        NOT NULL,
        BOM_PART_NUMBER         VARCHAR(15)     NULL,
        BOM_REVISION            NUMERIC(2)      NULL,
        PRIMARY KEY (PART_NUMBER, REVISION)
)

go

alter table PART
        add CONSTRAINT FK_1 FOREIGN KEY (BOM_PART_NUMBER, BOM_REVISION) 
                REFERENCES PART (PART_NUMBER, REVISION)

go

/* Bean will be mapped to 2 tables (PART and PART_DETAIL)
 * BLOB column type
 * CLOB column type */
create table PART_DETAIL (
        PART_NUMBER     VARCHAR(15)     NOT NULL,
        REVISION        NUMERIC(2)      NOT NULL,
        SPECIFICATION   TEXT    NULL,
        DRAWING         IMAGE   NULL,
        PRIMARY KEY (PART_NUMBER, REVISION)
)

go

/* PK can be mapped to a primitive PK field type */
create table VENDOR (
        VENDOR_ID       INTEGER         NOT NULL, 
        NAME            VARCHAR(30)     NOT NULL,
        ADDRESS         VARCHAR(255)    NOT NULL,
        CONTACT         VARCHAR(255)    NOT NULL,
        PHONE           VARCHAR(30)     NOT NULL,
                             PRIMARY KEY (VENDOR_ID)
)

go

/* Can be used for unknown PK
 * 1-1 to PART
 * Compound FK
 */
create table VENDOR_PART (
        VENDOR_PART_NUMBER      NUMERIC(19)             NOT NULL,
        DESCRIPTION             VARCHAR(255)            NULL,
        PRICE                   DOUBLE PRECISION        NOT NULL,
        VENDOR_ID               INTEGER                 NOT NULL,
        PART_NUMBER             VARCHAR(15)             NOT NULL,
        PART_REVISION           NUMERIC(2)              NOT NULL,
                              PRIMARY KEY (VENDOR_PART_NUMBER),
        CONSTRAINT FK_2 FOREIGN KEY (VENDOR_ID) REFERENCES VENDOR (VENDOR_ID),
        CONSTRAINT FK_3 FOREIGN KEY (PART_NUMBER, PART_REVISION) REFERENCES PART (PART_NUMBER, REVISION),
        UNIQUE (PART_NUMBER, PART_REVISION)
)

go

create table ORDERS (
        ORDER_ID        INTEGER         NOT NULL,
        STATUS          CHAR(1)         NOT NULL,
        LAST_UPDATE     DATETIME        NOT NULL,
        DISCOUNT        NUMERIC(2)      NOT NULL,
                             PRIMARY KEY (ORDER_ID),
        SHIPMENT_INFO   VARCHAR(255)    NULL
)

go

/* Overlapping PK-FK
 * Uni-directional to VENDOR_PART */
create table LINEITEM (
        ORDER_ID                INTEGER         NOT NULL,
        ITEM_ID                 NUMERIC(3)      NOT NULL,
        QUANTITY                NUMERIC(3)      NOT NULL,
        VENDOR_PART_NUMBER      NUMERIC(19)     NOT NULL,
        CONSTRAINT FK_4 FOREIGN KEY (ORDER_ID) REFERENCES ORDERS (ORDER_ID),
        CONSTRAINT FK_5 FOREIGN KEY (VENDOR_PART_NUMBER) REFERENCES VENDOR_PART (VENDOR_PART_NUMBER),
        PRIMARY KEY (ORDER_ID, ITEM_ID)
)

go

