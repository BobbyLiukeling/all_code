import pymysql

# 打开数据库连接
db = pymysql.connect(host='127.0.0.1', port=3306, user='root', passwd='520lkl', db='zhichengariticle',charset = "utf8",cursorclass=pymysql.cursors.DictCursor)



# 使用 cursor() 方法创建一个游标对象 cursor
# cur = db.cursor()
#
# # 使用 execute()  方法执行 SQL 查询
# cur.execute("SELECT VERSION()")
#
# # 使用 fetchone() 方法获取单条数据.
# data = cur.fetchone()
#
# print("Database version : %s " % data)
# # 关闭数据库连接
# db.close()

cursor = db.cursor()

sql = "INSERT INTO label(labelname) VALUES (%s)"
data = ( '买车',)
cursor.execute(sql, data)

db.close()