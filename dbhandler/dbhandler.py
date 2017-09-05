import sqlite3

class DataBaseHandler:

    dbfile = 'test.db'


    def __init__(self, dbfile):
        self.dbfile = dbfile


    def open_DB(self, dbfile=None):
        if dbfile is not None:
            self.dbfile = dbfile
        connection = sqlite3.connect(dbfile)
        return connection


    def execute_query(self, dbfile, query):
        dbconnection = self.open_DB(dbfile)
        cursor = dbconnection.cursor()

        try:
            cursor.execute(query)
            data = cursor.fetchall()
        except:
            raise sqlite3.Error("Can't execute query")


    def create_table(self, dbfile):
        query = """
        CREATE TABLE qso (
        id integer PRIMARY KEY,
        station_name text,
        frequency text,
        band text,
        modulation text,
        qso_date text,
        start_time text,
        end_time text,
        rst_send integer,
        rst_recv integer,
        locator text,
        operator text,
        details text
        );"""

        try:
            dbconnection = self.open_DB(dbfile)
            cursor = dbconnection.cursor()
            cursor.execute(query)
            result = cursor.fetchall()
        except:
            pass