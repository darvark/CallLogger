'''
Created on 13 wrz 2017

@author: iwaniuk
'''
import os
import shutil
import unittest
from DBHandler.dbhandler import DBHandler
from qso.qsomanager import QSOManager

class Test(unittest.TestCase):

    def setUp(self):
        if os.path.exists('ut_test.db'):
            shutil.rmtree('ut_test.db', 'Test db was not removed')


    def tearDown(self):
        shutil.rmtree('ut_test.db', 'Test db was not removed')
    
    
    def testCreateDB(self):
        d = DBHandler('ut_test.db')
        d.createDB()
        r = os.path.exists('ut_test.db')
        self.assertTrue(r, "Database does not exist")
        
        
    def checkTableExist(self):
        import sqlite3
        con = sqlite3.connect('ut_test.db')
        with con:
            cr = con.cursor()
            cr.execute("SELECT name FROM sqlite_master WHERE type='table' AND name='qso';")
            r = cr.fetchall()
            return r
        
        
    def testCreateTable(self):
        d = DBHandler('ut_test.db')
        d.create_table()
        result = self.checkTableExist()
        self.assertEqual(result[0][0], 'qso')
   
        
    def checkRecord(self):
        import sqlite3
        con = sqlite3.connect('ut_test.db')
        with con:
            cr = con.cursor()
            cr.execute("select * from qso")
            r = cr.fetchall()
#             print("Checking record: {r}".format(**locals()))
            return r
   
        
    def testInsert(self):
        q = QSOManager('ut_test.db')
        
        qso = {'callsign':'sp6mi',
            'freq':14200,
            'mode':'ssb',
            'date':'2017-09-09',
            'time':'10:04',
            'rst_s':59,
            'rst_r':59,
            'power':100,
            'qsl':'N',
            'details':'test one'}
        
        q.add_qso_to_db(qso)
        result = self.checkRecord()
        self.assertEqual(result[0][1], 'sp6mi')
        self.assertEqual(result[0][8], 100)
        
        

if __name__ == "__main__":
    #import sys;sys.argv = ['', 'Test.testCreateDB']
    unittest.main()