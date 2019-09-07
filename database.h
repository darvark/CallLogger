#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <QString>
#include <QFile>
#include <QDebug>


class database
{
public:
    database();

    int create_database(QString& dbname);
    sqlite3 *db_open_connection(QString& dbname);
    void close_db(sqlite3* db);
    int execute_query(QString& sql, sqlite3 *db);
    int insert_data(QString& dbname, QString& callsign, double freq,
                    QString& mode, QString& date, QString& time,
                    int rst_s, int rst_r, QString& exchange);

private:
    QString table = "CREATE TABLE IF NOT EXISTS qso(" \
            "callsign TEXT NOT NULL, " \
            "freq INTEGER NOT NULL, " \
            "mode TEXT NOT NULL, " \
            "date TEXT, " \
            "time TEXT, " \
            "rst_s INTEGER NOT NULL, " \
            "rst_r INTEGER NOT NULL, " \
            "exchange TEXT);";

    const char* qstrTocstr(QString* s);
};

#endif // DATABASE_H
