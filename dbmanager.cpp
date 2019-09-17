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
    QSqlQuery query("SELECT * FROM qso", m_db);
    int idcallsign = query.record().indexOf("callsign");
    while (query.next())
    {
       QString callsign = query.value(idcallsign).toString();
       qDebug() << callsign;
    }
}

QString dbmanager::printAllRecords() const
{
    QString result = "<table width=100%><tbody><tr><td>Call</td>"
                     "<td>FREQ</td><td>MODE</td><td>DATE</td><td>TIME</td>"
                     "<td>RST_S</td><td>RST_R</td><td>EXCHANGE</td></tr>";
    QSqlQuery query("SELECT * FROM qso", m_db);
    //query.prepare("SELECT * FROM qso");

    query.exec();
//    callsign, freq, mode, date, time, rst_s, rst_r, exchange
    while (query.next())
    {
        int idcall = query.record().indexOf("callsign");
        int idfreq = query.record().indexOf("freq");
        int idmode = query.record().indexOf("mode");
        int iddate = query.record().indexOf("date");
        int idtime = query.record().indexOf("time");
        int idrst_s = query.record().indexOf("rst_s");
        int idrst_r = query.record().indexOf("rst_r");
        int idech = query.record().indexOf("exchange");
        QString qso = query.value(idcall).toString();
        double freq = query.value(idfreq).toDouble();
        QString mode = query.value(idmode).toString();
        QString date = query.value(iddate).toString();
        QString time = query.value(idtime).toString();
        QString rst_s = query.value(idrst_s).toString();
        QString rst_r = query.value(idrst_r).toString();
        QString exch = query.value(idech).toString();
        result += "<tr><td>" + qso + "</td><td>" + QString::number(freq) +
                "</td><td>" + mode + "</td><td>" + date + "</td><td>" +
                time + "</td><td>" + rst_s + "</td><td>" + rst_r + "</td><td>" + exch + "</td></tr>";
        qDebug() << "===" << result;
    }
    return result + "</tbody><table>";
//    return "";
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
