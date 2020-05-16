use Book
drop index PK_book on book
use Book 
go
if exists(select name from sysindexes  where name='index_name')
drop index index_name on book
go 
create unique nonclustered index index_name
on book(bookid)
with fillfactor=30
go
select bookname,bookprice
from book
where bookprice=(
select MAX(bookprice)
from book 
where bookid<10)

use Book
go
declare cursor_name scroll cursor for
select bookname,bookid
from book
where bookprice>30
open cursor_name
fetch from cursor_name
while (@@fetch_status!=-1)
begin
fetch from cursor_name
end
close cursor_name
deallocate cursor_name

