import os
import unittest
import dbhandler

class TestDB(unittest.TestCase):
    def test_openDB(self):
        db = dbhandler.DataBaseHandler('testOne.db')
        db.open_DB()
        self.assertTrue(os.path.exists('testOne.db'))

        db.open_DB('testTwo.db')
        self.assertTrue(os.path.exists('testTwo.db'))

    def test_tableCreation(self):
        pass

if __name__ == '__main__':
    unittest.main()