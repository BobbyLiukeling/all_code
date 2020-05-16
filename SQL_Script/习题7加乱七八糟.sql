set nocount on
use Book
if Exists(select name from sysobjects where NAME = 'avg_price' and type='P')
drop procedure avg_price
go
create procedure avg_price @price int output
as 
set @price=
(select AVG(bookprice) as 平均价格
from book)
print @price 

exec avg_price 1


--在 pubs 数据库中创建存储过程 max_price，根据指定的图书类型（输入参数）返回该类图书的最高单价（输出参数）。要求在创建存储过程前要先判断该存储过程是否已存在，如果存在，则将其删除。
use Book
go
if Exists(select name from sysobjects where NAME = 'max_price' and type='P')
drop procedure max_price
go
create procedure max_price @bookname varchar(10) output
as
select MAX(bookprice)as 最高价格
from book
group by bookname



exec  max_price 'web' 
print @bookname
drop procedure avg_price,max_price

drop procedure  info

--无法创建数据库用户
--数据库名称-安全性-用户-右键

--1.1将“经济类图书”价格提高10%
select price=price*1.1
from class,book
where book.classNO=class.classNo and classname='经济类'

--1.2将入库数量最多的图书单价下调10%
select price=price*0.9
from book
where shopNum=MAX(shopNum)

--1.3删除读者“张小娟”的借书记录
delete from returnbook
where readerNO in
(select readerNo
from book
where readername='张小娟')


--1.4创建一个视图，该视图为在借书的总价60元以上的读者编号、姓名和所借图书的总价
IF EXISTS(SELECT 1 FROM sys.views WHERE name='price_over_60')
drop view price_over_60
go
CREATE VIEW price_over_60
WITH SCHEMABINDING,VIEW_METADATA
AS
SELECT reader.readerNo,readername,sum(price)
FROM reader,returnbook,
where reader.readerNo=returnbook.readerNo
group by readerNo
having sum(price)>=60
WITH CHECK OPTION

--1.5创建一个视图，该视图为年龄在25-35岁之间的读者属性列包括读者编号、姓名、年龄、工作单位所借图书名称和借书日期。

IF EXISTS(SELECT 1 FROM sys.views WHERE name='age_between_25_35')
drop view age_between_25_35
go
create view age_between_25_35
WITH SCHEMABINDING,VIEW_METADATA
as
declare @age int
select reader.readerNo as 编号,readername as 姓名,workUnit as 工作单位，@age=(DateName(year,GetDate())-cast(SUBSTRING('identifycard',7,4))as int)as 年龄,bookname as 借书的图书名称,borrowDate as 借书日期
from reader, returnbook
where reader.readerNo=returnbook.readerNo and (@age between 25 and 35)
WITH CHECK OPTION

declare @time int
select @time=DateName(year,GetDate())
print @time


dbcc checkalloc('Book')
                                         