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
      qDebug() << "Database: connection established";
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
        success = false;
    }
    else
    {
        success = true;
    }

    return success;
}

bool dbmanager::addrecord(QString& callsign, double freq, QString& mode,
                          QString& date, QString& time, int rst_s, int rst_r,
                          QString& exchange, QString &moja_exchange)
{
   bool success = false;
   // you should check if args are ok first...
   QSqlQuery query(m_db);
   query.prepare("INSERT INTO qso (callsign, freq, mode, date, time, rst_s, rst_r, exchange, moja_exchange) " \
                 "VALUES (:callsign, :freq, :mode, :date, :time, :rst_s, :rst_r, :exchange, :moja_exchange);");
   query.bindValue(":callsign", callsign);
   query.bindValue(":freq", freq);
   query.bindValue(":mode", mode);
   query.bindValue(":date", date);
   query.bindValue(":time", time);
   query.bindValue(":rst_s", rst_s);
   query.bindValue(":rst_r", rst_r);
   query.bindValue(":exchange", exchange);
   query.bindValue(":moja_exchange", moja_exchange);

   if(query.exec())
   {
       success = true;
   }
   else
   {
        qDebug() << "add new record error:  " << query.lastError();
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
    }
}

QString dbmanager::printAllRecords() const
{
    QString result = "<table width=100%><tbody><tr><td>Call</td>"
                     "<td>FREQ</td><td>MODE</td><td>DATE</td><td>TIME</td>"
                     "<td>RST_S</td><td>RST_R</td><td>EXCHANGE</td></tr>";

    QSqlQuery query("SELECT * FROM qso", m_db);

    query.exec();
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
    }
    return result + "</tbody><table>";
}

QString dbmanager::mapModulation(QString *mode) const
{
    if (QString().compare(*mode, QString("SSB"), Qt::CaseInsensitive) != 1)
    {
        return "PH";
    }
    else if (QString().compare(*mode, QString("CW"), Qt::CaseInsensitive) != 1)
    {
        return "CW";
    }
    else if (QString().compare(*mode, QString("RTTY"), Qt::CaseInsensitive) != 1)
    {
        return "RY";
    }
    else if (QString().compare(*mode, QString("FM"), Qt::CaseInsensitive) != 1)
    {
        return "FM";
    }
    else if (QString().compare(*mode, QString("DIGI"), Qt::CaseInsensitive) != 1)
    {
        return "DG";
    }
    return "MIXED";
}

QString dbmanager::printToADIF() const
{
    QString result;
    QSqlQuery query("SELECT * FROM qso", m_db);

    query.exec();
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
        int idmyech = query.record().indexOf("moja_exchange");

        QString qso = query.value(idcall).toString();
        double freq = query.value(idfreq).toDouble();
        QString mode = query.value(idmode).toString();
        QString date = query.value(iddate).toString();
        QString time = query.value(idtime).toString();
        QString rst_s = query.value(idrst_s).toString();
        QString rst_r = query.value(idrst_r).toString();
        QString exch = query.value(idech).toString();
        QString myexch = query.value(idmyech).toString();

        config cfg;
        params par;
        QString f = "contest_logger.conf";
        cfg.load_settings(&par, f);

        result += "QSO: \t" + QString::number(freq) + "\t" + mapModulation(&mode) + "\t" + date + "\t" + time + "\t" + par.callsign + "\t" + rst_s + "\t" + myexch
                + "\t" + qso + "\t" + rst_r + "\t" + exch + "\t" + "0" + "\n";
    }
    return result;
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
