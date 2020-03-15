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

    QString h1 = QString::fromStdString("START-OF-LOG: 3.0\n") +
    QString::fromStdString("\nCALLSIGN: ") + cfg_params.callsign +
    QString::fromStdString("\nCONTEST: ") + cfg_params.contest +
    QString::fromStdString("\nCATEGORY-OPERATOR: ") + cfg_params.cat_operators +
    QString::fromStdString("\nCATEGORY-ASSISTED: ") + cfg_params.cat_assisted +
    QString::fromStdString("\nCATEGORY-BAND: ") + cfg_params.cat_band +
    QString::fromStdString("\nCATEGORY-POWER: ") + cfg_params.cat_power +
    QString::fromStdString("\nCATEGORY-MODE: ") + cfg_params.cat_mode +
    QString::fromStdString("\nCATEGORY-TRANSMITTER: ") + cfg_params.cat_signal +
    QString::fromStdString("\nCATEGORY-OVERLAY: ") + cfg_params.cat_overlay +
    QString::fromStdString("\nCLAIMED-SCORE: ") +
    QString::fromStdString("\nCERTIFICATE: \n") +
    QString::fromStdString("CLUB: ") + cfg_params.klub +
    QString::fromStdString("\nLOCATION: \n") +
    QString::fromStdString("CREATED-BY: Contest Logger \n") +
    QString::fromStdString("NAME: \n") +
    QString::fromStdString("ADDRESS: ") + cfg_params.adress +
    QString::fromStdString("\nADDRESS-CITY: \n") +
    QString::fromStdString("ADDRESS-STATE-PROVINCE: \n") +
    QString::fromStdString("ADDRESS-POSTALCODE: \n") +
    QString::fromStdString("ADDRESS-COUNTRY: \n") +
    QString::fromStdString("OPERATORS: \n") +
    QString::fromStdString("SOAPBOX: ") + cfg_params.cat_soapbox +
    QString::fromStdString("\nSOAPBOX: \n");

    std::cout << h1.toStdString() << std::endl;
    return h1;
}

QString cbr::log_start()
{
    QString start = "    --------info sent------- -------info rcvd--------\n"
                    "QSO:\tfreq\tmo\tdate\ttime call\t\trst\texch\tcall\trst\texcht\n"
                    "QSO: ***** ** yyyy-mm-dd nnnn ************* nnn ****** ************* nnn ****** n\n";
    return start;
}

QString cbr::create_log()
{
    QString log;
    log += prepareHeader();
    log += log_start();

    if(baza->isOpen())
    {
         log += baza->printToADIF();
    }

    log += "END-OF-LOG:";

    return log;
}

void cbr::saveFile(QString cbrFile)
{
    QFile file(cbrFile);
    if(file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);

        stream << create_log();

        file.close();
    }
}
