'''
Created on 10 wrz 2017
@author: iwaniuk
'''
import sqlite3
from idlelib.replace import replace

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
        
        conection = sqlite3.connect(self.dbName)
        
        print("Connection to DB {} established.".format(self.dbName))


    def execute_query(self, query):
        '''
        Executing query in DB. Both DB and query are params
        to this method
        '''

        dbconnection = self.open_DB(self.dbName)
        with dbconnection:
            cursor = dbconnection.cursor()
            cursor.execute(query)
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
        `freq` NUMERIC NOT NULL,
        `mode` TEXT NOT NULL,
        `power` INTEGER NOT NULL,
        `date` TEXT,
        `time` TEXT,
        `qsl` TEXT,
        `rst_s` NUMERIC NOT NULL,
        `rst_r` NUMERIC NOT NULL,
        `details` TEXT
        );"""

        dbconnection = self.open_DB(self.dbfile)
        
        with dbconnection:
            cursor = dbconnection.cursor()
            cursor.execute(query)
            result = cursor.fetchall()
            for row in result:
                print("Fetched result: {row}".format(**locals()))

            
