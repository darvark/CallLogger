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

            print(query)
            print(params)
            cursor.execute(query, params)
            data = cursor.fetchall()

            if data is not None:
                for row in data:
                    print("Fetched result: {row}".format(**locals()))


    def search_in_db(self):
        '''
        Returns list of dictionaries, each dict is a one record in db
        '''

        dbcontent = []
        dbconnection = sqlite3.connect(self.dbName)
        with dbconnection:
            dbconnection.row_factory = sqlite3.Row

            cursor = dbconnection.cursor()
            cursor.execute("SELECT * FROM qso")

            rows = cursor.fetchall()

            for row in rows:
                dbcontent.append(row)

        return dbcontent


    def create_table(self):
        '''
        Create table in database.
        '''

        query = """CREATE TABLE IF NOT EXISTS `qso`
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

    def edit_record(self, recordid, new_value):
        pass
