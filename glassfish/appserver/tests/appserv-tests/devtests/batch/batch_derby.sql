DROP TABLE JOBSTATUS
CREATE TABLE JOBSTATUS(id BIGINT, obj BLOB)
DROP TABLE STEPSTATUS
CREATE TABLE STEPSTATUS(id VARCHAR(512), obj BLOB)
DROP TABLE CHECKPOINTDATA
CREATE TABLE CHECKPOINTDATA(id VARCHAR(512), obj BLOB)
DROP TABLE JOBINSTANCEDATA
CREATE TABLE JOBINSTANCEDATA(id VARCHAR(512), obj BLOB)
DROP TABLE EXECUTIONINSTANCEDATA
CREATE TABLE EXECUTIONINSTANCEDATA(id VARCHAR(512), createtime TIMESTAMP, starttime TIMESTAMP, endtime TIMESTAMP, updatetime TIMESTAMP, parameters BLOB, jobinstanceid VARCHAR(512), batchstatus BLOB, exitstatus BLOB)
DROP TABLE STEPEXECUTIONINSTANCEDATA
CREATE TABLE STEPEXECUTIONINSTANCEDATA(id VARCHAR(512), jobexecid VARCHAR(512), stepexecid VARCHAR(512))