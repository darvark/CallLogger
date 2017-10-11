#!/bin/env python

from DBHandler.dbhandler import DBHandler
from qso.qsomanager import QSOManager


def main():
    d = DBHandler('test.db')
    d.createDB()
    d.create_table()

    q = QSOManager('test.db')

    q.fill_qso_data("sp6mi","14200","ssb","100","2017-09-27","14:45","n","59","59","none")

    print(q.search_qso("sp6mir"))
    
if __name__ == "__main__":
    main()
