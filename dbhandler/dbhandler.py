import sqlite3

class DataBaseHandler:
    '''
    Default DB file name is test.db. Correct file name
    must be provided in constructor
    '''

    dbfile = 'test.db'


    def __init__(self, dbfile):
        '''
        constructor
        '''

        self.dbfile = dbfile


    def open_db(self, dbfile=None):
        '''
        Open connection to DB. If file name to DB
        is not given then use default test.db name
        '''

        if dbfile is not None:
            self.dbfile = dbfile
        
        connection = sqlite3.connect(dbfile)
        
        return connection


    def execute_query(self, dbfile, query):
        '''
        Executing query in DB. Both DB and query are params
        to this method
        '''

        dbconnection = self.open_DB(dbfile)
        cursor = dbconnection.cursor()

        try:
            cursor.execute(query)
            data = cursor.fetchall()

            return data

        except:
            raise sqlite3.Error("Can't execute query")


    def create_table(self, dbfile):
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

        try:
            dbconnection = self.open_DB(dbfile)
            cursor = dbconnection.cursor()
            cursor.execute(query)
            result = cursor.fetchall()

            return result

        except:
            raise sqlite3.Error("Table creation failed. Try again")