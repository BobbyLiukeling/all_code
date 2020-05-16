use Book 
;with name as
(select bookname
from book 
where bookid<9
)
select bookname,avg(bookprice)
from book
where bookname in (select * from name)
group by bookname

with expression
select column_list
from table_name1,table_name2
where expression
group by column_name
having expression
order by column_name

use Book
select * into hightbookprice
from book
where bookprice>50

select COUNT(bookname)
from book
where bookid<10
group by all bookname
--加上all后id大于10的信息依然不会统计，但是却会显示有这条记录

use Book
select bookname,价格=case
when bookprice>0 and bookprice<30 then '便宜'
when bookprice>30 and bookprice<60 then '一般'
else '贵'
end
from book


select *
from book 
order by bookname
compute avg(bookprice)by bookname



