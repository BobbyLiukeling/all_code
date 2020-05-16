# -*- coding:utf-8 -*-
"""
@author:SiriYang
@file:SQLite.py
@time:2018/11/26 8:35
"""

import sqlite3


class DB():
    def __init__(self):
        self.conn = sqlite3.connect('test.db')
        self.c = self.conn.cursor()

    def __del__(self):
        self.conn.close()

    def ceatTable(self):
        sql = '''CREATE TABLE VEHICLE
               (ID INT PRIMARY KEY     NOT NULL,
               NAME           TEXT    NOT NULL,
               WHEEL            INT     NOT NULL,
               COLOR           TEXT    NOT NULL);'''
        print(sql)
        self.c.execute(sql)

        self.conn.commit()

    def insertVehicle(self, id, name, wheel, color):
        sql = '''INSERT INTO VEHICLE (ID,NAME,WHEEL,COLOR) VALUES ({id}, '{name}', {wheel},'{color}')'''.format( \
            id=id, name=name, wheel=wheel, color=color)
        print(sql)
        self.c.execute(sql)

        self.conn.commit()

    def updateVehicle(self, id, name, wheel, color):
        sql = '''UPDATE VEHICLE SET NAME='{name}',WHEEL={wheel},COLOR='{color}' WHERE ID={id}'''.format( \
            id=id, name=name, wheel=wheel, color=color)
        print(sql)
        self.c.execute(sql)

        self.conn.commit()

    def selectVehicle(self):
        sql = "SELECT id, name, wheel,color  from VEHICLE"
        print(sql)
        cursor = self.c.execute(sql)
        print("ID   NAME    WHEEL   COLOR")
        for row in cursor:
            print("{id}    {name:8}  {wheel}     {color}".format(id=row[0], name=row[1], wheel=row[2], color=row[3]))

    def deletVehicle(self, id):
        sql = "DELETE from VEHICLE where ID={id};".format(id=id)
        print(sql)
        self.c.execute(sql)
        self.conn.commit()


if __name__ == '__main__':
    db = DB()

    print('-----------------creat table---------------------')
    db.ceatTable()

    print('-----------------insert data---------------------')
    db.insertVehicle(0, 'truck', 4, 'red')
    db.insertVehicle(1, 'bus', 4, 'blue')
    db.insertVehicle(2, 'taxi', 4, 'yellow')
    db.insertVehicle(3, 'tricycle', 3, 'red')
    db.insertVehicle(4, 'bicycle', 2, 'green')
    db.insertVehicle(5, 'car', 4, 'black')

    db.selectVehicle()

    print('----------------update data----------------------')

    db.updateVehicle(5, 'car', 4, 'white')

    db.selectVehicle()

    print('-----------------delete data---------------------')
    db.deletVehicle(3)

    db.selectVehicle()
