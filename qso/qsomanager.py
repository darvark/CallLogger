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
    table = 'qso'

    def __init__(self, dbFile):
        '''
        Constructor
        '''
        self.dbFile = dbFile
        self.db = DBHandler(self.dbFile)

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

        self.add_qso_to_db(self.qso)


    def add_qso_to_db(self, qso):
        param = (qso['callsign'], qso['freq'], qso['mode'], qso['date'], qso['time'],
                 qso['rst_s'], qso['rst_r'], qso['power'], qso['qsl'], qso['details'])
        self.db.execute_insert(param)


    def edit_qso(self, qso_id, new_value):
        '''
        Edit existing qso
        '''

        recid = 0
        self.db.edit(recid, new_value)



    def search_qso(self, what):
        '''
        Search qso
        '''

        result = []
        find_result = {}
        result = self.db.search_in_db()

        for items in result:
            if what in items:
                find_result = items
                break
            else:
                find_result = None

        return find_result

    def remove_qso(self, qso_id):
        '''
        Deleting qso from db
        '''

        pass
