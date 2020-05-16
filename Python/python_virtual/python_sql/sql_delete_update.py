import MySQLdb
conn = MySQLdb.Connect(
  host = "127.0.0.1",
  port = 3306,
  user = "root",
  passwd = "520lkl",
  db = "pytohn",
  charset = "utf8"
  )

cursor = conn.cursor()

sql = "select * from student"
cursor.execute(sql)
print(cursor.rowcount)

re = cursor.fetchall()
print(re)

for row in re:
  print("userid=%s,username=%s" % row)


# try:
#   sql_insert = "insert into student(id,name) values(2,'name2')"
#   cursor.execute(sql_insert)
#   print(cursor.rowcount)

#   sql_update = "update student set name='bobby' where name='name6'"
#   cursor.execute(sql_update)
#   print(cursor.rowcount)

#   sql_delete = "delete from student where id=5"
#   cursor.execute(sql_delete)
#   print(cursor.rowcount)

#   conn.commit()#将数据库更新，实现SQL语句的执行结果
#   sql = "select * from student"
#   cursor.execute(sql)
#   rs = cursor.fetchall()
#   print("*"*30)
#   print(rs)
# except Exception as e:
#   print(e)
#   conn.rollback()#让事物回滚到所有语句执行之前




