#include "dbmanager.h"

dbmanager::dbmanager(const QString& path)
{
   m_db = QSqlDatabase::addDatabase("QSQLITE","SQLITE");
   m_db.setDatabaseName(path);

   if (!m_db.open())
   {
      qDebug() << "Error: connection with database fail";
   }
   else
   {
      qDebug() << "Database: connection ok";
   }
}

dbmanager::~dbmanager()
{
    if (m_db.isOpen())
        m_db.close();
}

bool dbmanager::isOpen() const
{
    return m_db.isOpen();
}

bool dbmanager::createTable()
{
    bool success = false;

    QSqlQuery query(m_db);
    query.prepare(table);

    bool result = query.exec();
    if (!result)
    {
        qDebug() << "Couldn't create the table 'qso': one might already exist.";
        success = false;
    }
    else
    {
        qDebug() << "Created the table 'qso'";
        success = true;
    }

    return success;
}

bool dbmanager::addrecord(QString& callsign, double freq, QString& mode,
                          QString& date, QString& time, int rst_s, int rst_r, QString& exchange)
{
   bool success = false;
   // you should check if args are ok first...
   QSqlQuery query(m_db);
   query.prepare("INSERT INTO qso (callsign, freq, mode, date, time, rst_s, rst_r, exchange) " \
                 "VALUES (:callsign, :freq, :mode, :date, :time, :rst_s, :rst_r, :exchange);");
   query.bindValue(":callsign", callsign);
   query.bindValue(":freq", freq);
   query.bindValue(":mode", mode);
   query.bindValue(":date", date);
   query.bindValue(":time", time);
   query.bindValue(":rst_s", rst_s);
   query.bindValue(":rst_r", rst_r);
   query.bindValue(":exchange", exchange);

   if(query.exec())
   {
       success = true;
   }
   else
   {
        qDebug() << "add new record error:  "
                 << query.lastError();
   }

   return success;
}

void dbmanager::selectall()
{
    QSqlQuery query("SELECT * FROM qso");
    int idcallsign = query.record().indexOf("callsign");
    while (query.next())
    {
       QString callsign = query.value(idcallsign).toString();
       qDebug() << callsign;
    }
}

void dbmanager::printAllPersons() const
{
    QSqlQuery query("SELECT * FROM qso");
    int idqso = query.record().indexOf("callsign");
    while (query.next())
    {
        QString qso = query.value(idqso).toString();
        qDebug() << "===" << qso;
    }
}

bool dbmanager::callsignExists(const QString& callsign) const
{
    bool exists = false;

    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT name FROM qso WHERE callsign = (:callsign)");
    checkQuery.bindValue(":callsign", callsign);

    if (checkQuery.exec())
    {
        if (checkQuery.next())
        {
            exists = true;
        }
    }
    else
    {
        qDebug() << "callsign exists failed: " << checkQuery.lastError();
    }

    return exists;
}
// //////////////////////////////////////////////////
// IMPLEMENT: https://github.com/katecpp/sql_with_qt/blob/master/main.cpp
// //////////////////////////////////////////

// w MAINWINDOW
// Change to any path you wish
//static const QString path = "example.db";
//DbManager db(path);

//    if (db.isOpen())
//    {
//        db.createTable();   // Creates a table if it doens't exist. Otherwise, it will use existing table.
//        db.addPerson("A");
//        db.addPerson("B");
//        db.addPerson("C");
//        db.printAllPersons();
//        db.removePerson("C");
//        db.printAllPersons();
//        db.removeAllPersons();
//        qDebug() << "End";
//    }
//    else
//    {
//        qDebug() << "Database is not open!";
//}
