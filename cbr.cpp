#include "cbr.h"

cbr::cbr()
{

}

QString cbr::prepareHeader()
{
    QString h1 = "START-OF-LOG: 3.0\n"
    "CALLSIGN: \n"
    "CONTEST: \n"
    "CATEGORY-OPERATOR: \n"
    "CATEGORY-ASSISTED: \n"
    "CATEGORY-BAND: \n"
    "CATEGORY-POWER: \n"
    "CATEGORY-MODE: \n"
    "CATEGORY-TRANSMITTER: \n"
    "CATEGORY-OVERLAY: \n"
    "CLAIMED-SCORE: \n"
    "CERTIFICATE: \n"
    "CLUB: \n"
    "LOCATION: \n"
    "CREATED-BY: Contest Logger \n"
    "NAME: \n"
    "ADDRESS: \n"
    "ADDRESS-CITY: \n"
    "ADDRESS-STATE-PROVINCE: \n"
    "ADDRESS-POSTALCODE: \n"
    "ADDRESS-COUNTRY: \n"
    "OPERATORS: \n"
    "SOAPBOX: \n"
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
}


