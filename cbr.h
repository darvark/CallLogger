#ifndef ADIF_H
#define ADIF_H

#include <QString>
#include <QFile>
#include "config.h"
#include "dbmanager.h"

//zapis logu do pliku adif

//START-OF-LOG: 3.0
//CALLSIGN: AA1ZZZ
//CONTEST: CQ-WW-SSB
//CATEGORY-OPERATOR: SINGLE-OP
//CATEGORY-ASSISTED: NON-ASSISTED
//CATEGORY-BAND: ALL
//CATEGORY-POWER: HIGH
//CATEGORY-MODE: CW
//CATEGORY-TRANSMITTER: ONE
//CATEGORY-OVERLAY: ROOKIE
//CLAIMED-SCORE: 9447852
//CERTIFICATE: YES
//CLUB: My Contest Club
//LOCATION: WMA
//CREATED-BY: SuperLogger v1.0
//NAME: John Smith
//ADDRESS: 100 Main St
//ADDRESS-CITY: Uxbridge
//ADDRESS-STATE-PROVINCE: MA
//ADDRESS-POSTALCODE: 01569
//ADDRESS-COUNTRY: USA
//OPERATORS: K5ZD
//SOAPBOX: Put your comments here.
//SOAPBOX: Use multiple lines if needed.
//QSO:  3799 PH 2000-10-26 0711 AA1ZZZ          59  05     K9QZO         59  04     0
//QSO: 14256 PH 2000-10-26 0711 AA1ZZZ          59  05     P29AS         59  28     0
//QSO: 21250 PH 2000-10-26 0711 AA1ZZZ          59  05     4S7TWG        59  22     0
//QSO: 28530 PH 2000-10-26 0711 AA1ZZZ          59  05     JT1FAX        59  23     0
//QSO:  7250 PH 2000-10-26 0711 AA1ZZZ          59  05     WA6MIC        59  03     0
//END-OF-LOG:


class cbr
{
private:
    QString prepareHeader();
    QString log_start();
    QString create_log(dbmanager *database);
public:
    cbr();
    ~cbr();
    void saveFile(dbmanager *db, QString conf_file, QString cbrFile);

private:
    config cfg;
    params *p;
};

#endif // ADIF_H
