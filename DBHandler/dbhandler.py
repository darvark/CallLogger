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

        query = """
        CREATE TABLE qso (
        id integer PRIMARY KEY,
        station_name text,
        frequency text,
        modulation text,
        qso_date text,
        end_time text,
        rst_send integer,
        rst_recv integer,
        power text,
        qsl text,
        details text
        );"""

        dbconnection = self.open_DB(self.dbfile)
        
        with dbconnection:
            cursor = dbconnection.cursor()
            cursor.execute(query)
            result = cursor.fetchall()
            for row in result:
                print("Fetched result: {row}".format(**locals()))

            
