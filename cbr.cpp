#include "cbr.h"

cbr::cbr(dbmanager *db):
    db(db)
{
    cfg->load_settings(p, conf_file);
}

cbr::~cbr()
{
    delete db;
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

    //    --------info sent------- -------info rcvd--------
    //QSO:  freq mo date       time call          rst exch   call          rst exch   t
    //QSO: ***** ** yyyy-mm-dd nnnn ************* nnn ****** ************* nnn ****** n
    //QSO:  3799 PH 2000-10-26 0711 AA1ZZZ          59  05     K9QZO         59  04     0
    //QSO: 14256 PH 2000-10-26 0711 AA1ZZZ          59  05     P29AS         59  28     0
    //QSO: 21250 PH 2000-10-26 0711 AA1ZZZ          59  05     4S7TWG        59  22     0
    //QSO: 28530 PH 2000-10-26 0711 AA1ZZZ          59  05     JT1FAX        59  23     0
    //QSO:  7250 PH 2000-10-26 0711 AA1ZZZ          59  05     WA6MIC        59  03     0
    //END-OF-LOG:
    return h1;
}

QString cbr::log_start()
{
    QString start = "    --------info sent------- -------info rcvd--------"
                    "QSO:  freq mo date       time call          rst exch   call          rst exch   t"
                    "QSO: ***** ** yyyy-mm-dd nnnn ************* nnn ****** ************* nnn ****** n";

    return start;
}

QString cbr::create_log()
{
    QString log;
    log + prepareHeader();
    log + log_start();

    if(db->isOpen())
         log = db->printToADIF();

    qDebug() << log;
    return log;
}

void cbr::saveFile(QString cbrFile)
{
    QFile file(cbrFile);
          if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
          {
              // We're going to streaming text to the file
              QTextStream stream(&file);

              stream << create_log();

              file.close();
              qDebug() << "Writing finished";
          }
}
