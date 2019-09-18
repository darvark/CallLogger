#include "cbr.h"

cbr::cbr() { }

cbr::~cbr()
{
    delete p;
}

QString cbr::prepareHeader()
{
    QString h1 = "START-OF-LOG: 3.0\n"
    "CALLSIGN: " + p->callsign + "\n"
    "CONTEST: " + p->contest + "\n"
    "CATEGORY-OPERATOR: " + p->cat_operators + "\n"
    "CATEGORY-ASSISTED: " + p->cat_assisted + "\n"
    "CATEGORY-BAND: " + p->cat_band + "\n"
    "CATEGORY-POWER: " + p->cat_power + "\n"
    "CATEGORY-MODE: " + p->cat_mode + "\n"
    "CATEGORY-TRANSMITTER: " + p->cat_signal + "\n"
    "CATEGORY-OVERLAY: " + p->cat_overlay + "\n"
    "CLAIMED-SCORE: \n"
    "CERTIFICATE: \n"
    "CLUB: " + p->klub + "\n"
    "LOCATION: \n"
    "CREATED-BY: Contest Logger \n"
    "NAME: \n"
    "ADDRESS: " + p->adress + "\n"
    "ADDRESS-CITY: \n"
    "ADDRESS-STATE-PROVINCE: \n"
    "ADDRESS-POSTALCODE: \n"
    "ADDRESS-COUNTRY: \n"
    "OPERATORS: \n"
    "SOAPBOX: " + p->cat_soapbox + "\n"
    "SOAPBOX: \n";

    return h1;
}

QString cbr::log_start()
{
    QString start = "    --------info sent------- -------info rcvd--------"
                    "QSO:  freq mo date       time call          rst exch   call          rst exch   t"
                    "QSO: ***** ** yyyy-mm-dd nnnn ************* nnn ****** ************* nnn ****** n";

    return start;
}

QString cbr::create_log(dbmanager *database)
{
    QString log;
    log + prepareHeader();
    log + log_start();

    if(database->isOpen())
         log = database->printToADIF();

    log + "END-OF-LOG:";

    return log;
}

void cbr::saveFile(dbmanager *db, QString conf_file, QString cbrFile)
{
    cfg.load_settings(p, conf_file);

    QFile file(cbrFile);
          if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
          {// We're going to streaming text to the file
              QTextStream stream(&file);

              stream << create_log(db);

              file.close();
              qDebug() << "Writing finished";
          }
}
