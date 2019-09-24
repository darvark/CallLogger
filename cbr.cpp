#include "cbr.h"

cbr::cbr(dbmanager *db, config *cfg):
    baza(db),
    konfiguracja(cfg)
{ }

cbr::~cbr()
{
}

QString cbr::prepareHeader()
{
    QString configfile = "contest_logger.conf";
    if (QFileInfo::exists(configfile))
    {
        konfiguracja->load_settings(&cfg_params, configfile);
    }

    QString h1 = "START-OF-LOG: 3.0\n"
    "CALLSIGN: " + cfg_params.callsign + "\n"
    "CONTEST: " + cfg_params.contest + "\n"
    "CATEGORY-OPERATOR: " + cfg_params.cat_operators + "\n"
    "CATEGORY-ASSISTED: " + cfg_params.cat_assisted + "\n"
    "CATEGORY-BAND: " + cfg_params.cat_band + "\n"
    "CATEGORY-POWER: " + cfg_params.cat_power + "\n"
    "CATEGORY-MODE: " + cfg_params.cat_mode + "\n"
    "CATEGORY-TRANSMITTER: " + cfg_params.cat_signal + "\n"
    "CATEGORY-OVERLAY: " + cfg_params.cat_overlay + "\n"
    "CLAIMED-SCORE: \n"
    "CERTIFICATE: \n"
    "CLUB: " + cfg_params.klub + "\n"
    "LOCATION: \n"
    "CREATED-BY: Contest Logger \n"
    "NAME: \n"
    "ADDRESS: " + cfg_params.adress + "\n"
    "ADDRESS-CITY: \n"
    "ADDRESS-STATE-PROVINCE: \n"
    "ADDRESS-POSTALCODE: \n"
    "ADDRESS-COUNTRY: \n"
    "OPERATORS: \n"
    "SOAPBOX: " + cfg_params.cat_soapbox + "\n"
    "SOAPBOX: \n";

    qDebug() << "stworzono header";
    return h1;
}

QString cbr::log_start()
{
    QString start = "    --------info sent------- -------info rcvd--------\n"
                    "QSO:\tfreq\tmo\tdate\ttime call\t\trst\texch\tcall\trst\texcht\n"
                    "QSO: ***** ** yyyy-mm-dd nnnn ************* nnn ****** ************* nnn ****** n\n";
    qDebug() << "stworzono start logu";
    return start;
}

QString cbr::create_log()
{
    QString log;
    log += prepareHeader();
    log += log_start();

    qDebug() << "w createlog";
    if(baza->isOpen())
    {
        qDebug() << "w createlog";
         log += baza->printToADIF();
    }
    else
    {
        qDebug() << "Baza nie otwarta";
    }
    log += "END-OF-LOG:";

    qDebug() << "stworzono log" << log;
    return log;
}

void cbr::saveFile(QString cbrFile)
{
//    cfg.load_settings(p, conf_file);

    qDebug() << "w save file";
    QFile file(cbrFile);
    if(file.open(QIODevice::ReadWrite))
    {
        qDebug() << "otwarto plik";
        QTextStream stream(&file);

        stream << create_log();

        file.close();
        qDebug() << "Writing finished";
    }
}
