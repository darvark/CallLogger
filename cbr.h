#ifndef ADIF_H
#define ADIF_H

#include <QString>
#include <QFile>
#include <QFileInfo>
#include "config.h"
#include "dbmanager.h"
#include <iostream>

class cbr
{
private:
    QString prepareHeader();
    QString log_start();
    QString create_log();
public:
    cbr(dbmanager *db, config *cfg);
    ~cbr();
    void saveFile(QString cbrFile);

private:
    dbmanager *baza;
    config *konfiguracja;
    params cfg_params;
};

#endif // ADIF_H
