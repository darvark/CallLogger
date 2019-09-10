#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QDebug>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlRecord>

class dbmanager
{
public:
    dbmanager(const QString& path);
    ~dbmanager();
    bool addrecord(QString& callsign, double freq, QString& mode,
                   QString& date, QString& time, int rst_s, int rst_r, QString& exchange);
    void selectall();
    bool createTable();
    bool isOpen() const;
    void printAllPersons() const;
    bool callsignExists(const QString& callsign) const;
private:
    QSqlDatabase m_db;
    QString table = "CREATE TABLE IF NOT EXISTS qso(" \
            "callsign TEXT NOT NULL, " \
            "freq INTEGER NOT NULL, " \
            "mode TEXT NOT NULL, " \
            "date TEXT, " \
            "time TEXT, " \
            "rst_s INTEGER NOT NULL, " \
            "rst_r INTEGER NOT NULL, " \
            "exchange TEXT);";
};

#endif // DBMANAGER_H
