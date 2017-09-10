'''
Created on 10 wrz 2017

@author: iwaniuk
'''

from DBHandler.dbhandler import DBHandler


class QSOManager():
    '''
    '''

    qso = {'station_name':'',
            'frequency':'',
            'modulation':'',
            'qso_date':'0000-00-00',
            'end_time':'00:00',
            'rst_send':'599',
            'rst_recv':'599',
            'power':'',
            'qsl':'N',
            'details':''}

    db = DBHandler()

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
        
        self.qso['station_name'] = station_name
        self.qso['frequency'] = freq
        self.qso['modulation'] = modulation
        self.qso['qso_date'] = qso_date
        self.qso['end_time'] = end_time
        self.qso['rst_send'] = rst_s
        self.qso['rst_recv'] = rst_r
        self.qso['power'] = power
        self.qso['qsl'] = qsl
        self.qso['details'] = details

        return self.qso
    
    
    def add_qso_to_db(self, qso):
        q = """INSERT """
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