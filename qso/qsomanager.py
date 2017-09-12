'''
Created on 10 wrz 2017

@author: iwaniuk
'''

from DBHandler.dbhandler import DBHandler


class QSOManager():
    '''
    '''
    
    qso = {'callsign':'',
            'freq':0,
            'mode':'',
            'date':'0000-00-00',
            'time':'00:00',
            'rst_s':599,
            'rst_r':599,
            'power':0,
            'qsl':'N',
            'details':''}
    database = 'qso'

    db = DBHandler(database)

    def __init__(self):
        '''
        Constructor
        '''
        pass
    
    
    def fill_qso_data(self, station_name, freq, modulation, qso_date,
                end_time, rst_s, rst_r, power, qsl, details):
        '''
        Add new qso entry to db
        '''
        
        self.qso['callsign'] = station_name
        self.qso['freq'] = freq
        self.qso['mode'] = modulation
        self.qso['date'] = qso_date
        self.qso['time'] = end_time
        self.qso['rst_s'] = rst_s
        self.qso['rst_r'] = rst_r
        self.qso['power'] = power
        self.qso['qsl'] = qsl
        self.qso['details'] = details

        return self.qso
    
    
    def add_qso_to_db(self, qso, dbname):
        database = self.database
        param = (qso['callsign'], qso['freq'], qso['mode'], qso['date'], qso['time'], qso['rst_s'], qso['rst_r'], qso['power'], qso['qsl'], qso['details'])
        query = """INSERT INTO {dbname} VALUES (callsign, freq, mode, power, date, time,
        qsl, rst_s, rst_r, details),{param}""".format(**locals())
         
        self.db.execute_query(query)


    def edit_qso(self, qso_id, new_value):
        '''
        Edit existing qso
        '''

        pass


    def search_qso(self, **):
        '''
        Search qso
        '''

        pass


    def remove_qso(self, qso_id):
        '''
        Deleting qso from db
        '''
        
        pass