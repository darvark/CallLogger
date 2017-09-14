'''
Created on 10 wrz 2017
@author: iwaniuk
'''
import sqlite3

class DBHandler():
    '''
    '''
    dbName = 'qso.db'


    def __init__(self, dbname=None):
        '''
        Constructor
        '''
        if dbname is not None:
            self.dbName = dbname
        
        
    def createDB(self):
        
        sqlite3.connect(self.dbName)
        
        print("Connection to DB {} established.".format(self.dbName))


#     def checkIfTableExist(self, dbName):
#         con = sqlite3.connect(dbName)
#         with con:
#             cr = con.cursor()
#             cr.execute("SELECT name FROM sqlite_master WHERE type='table' AND name='qso';")
#             r = cr.fetchall()
#             print("RESULT: {r}". format(**locals()))
#             if len(r) != 0:
#                 return True
#             else:
#                 return False
                    
    def execute_insert(self, params):
        '''
        Executing query in DB. Both DB and query are params
        to this method
        '''
        
        query = """INSERT  INTO qso (callsign, freq, mode, power, date, time, qsl, rst_s,
                rst_r, details) VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?)"""
        
        dbconnection = sqlite3.connect(self.dbName)
        with dbconnection:
            cursor = dbconnection.cursor()
            
#             print("Execute query")
            cursor.execute(query, params)
            data = cursor.fetchall()
 
            if data is not None:
                for row in data:
                    print("Fetched result: {row}".format(**locals()))


    def create_table(self):
        '''
        Create table in database.
        '''

        query = """CREATE TABLE `qso` 
        (`id` INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,
        `callsign` TEXT NOT NULL,
        `freq` INTEGER NOT NULL,
        `mode` TEXT NOT NULL,
        `power` INTEGER NOT NULL,
        `date` TEXT,
        `time` TEXT,
        `qsl` TEXT,
        `rst_s` INTEGER NOT NULL,
        `rst_r` INTEGER NOT NULL,
        `details` TEXT
        );"""

        dbconnection = sqlite3.connect(self.dbName)
        
        with dbconnection:
            cursor = dbconnection.cursor()
            cursor.execute(query)
            result = cursor.fetchall()
            for row in result:
                print("Fetched result: {row}".format(**locals()))

            
