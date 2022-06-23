#ifndef KONFIGURACJA_H
#define KONFIGURACJA_H

#include <QDialog>
#include <QListWidget>
#include <QFileDialog>
#include <QCheckBox>
#include <QComboBox>
#include <QSerialPortInfo>
#include <QFile>
#include <QDebug>
#include "config.h"

namespace Ui {
class konfiguracja;
}

class configuration : public QDialog
{
    Q_OBJECT

public:
    explicit configuration(QWidget *parent = nullptr);
    ~configuration();

    int radio(QString radio);

private slots:

    void on_zapisz_clicked();

    void on_kasuj_clicked();
    
    void toUpper(const QString &text);

    QString on_assisted_stateChanged(int arg1);

private:
    Ui::konfiguracja *ui;
    config cfg;
    QString assisted;
    bool stala_wymiana = true;

    void dodaj_radia_do_listy(Ui::konfiguracja* ui);
    void ustaw_moc(Ui::konfiguracja* ui);
    void ustaw_mode(Ui::konfiguracja* ui);
    void ustaw_zawody(Ui::konfiguracja* ui);
    void ustaw_pasmo(Ui::konfiguracja* ui);
    void ustaw_operator(Ui::konfiguracja* ui);
    void ustaw_stacja(Ui::konfiguracja* ui);
    void ustaw_czas(Ui::konfiguracja* ui);
    void ustaw_nadajnik(Ui::konfiguracja* ui);
    void ustaw_overlay(Ui::konfiguracja* ui);

    void add_parity(Ui::konfiguracja* ui);
    void add_databits(Ui::konfiguracja* ui);
    void add_stopbits(Ui::konfiguracja* ui);
    void add_baudrate(Ui::konfiguracja* ui);
    void add_handshake(Ui::konfiguracja* ui);
    void dodaj_porty(Ui::konfiguracja* ui);

    std::map<QString, int> mapowanieradia{
        {"Hamlib Dummy", 1},
        {"Hamlib NET", 2},
        {"Yaesu FT-847", 101},
        {"Yaesu FT-1000D", 103},
        {"Yaesu MARK-V", 104},
        {"Yaesu FT-747GX", 105},
        {"Yaesu FT-757GX", 106},
        {"Yaesu FT-757GXII", 107},
        {"Yaesu FT-767GX", 109},
        {"Yaesu FT-736R", 110},
        {"Yaesu FT-840", 111},
        {"Yaesu FT-900", 113},
        {"Yaesu FT-920", 114},
        {"Yaesu FT-890", 115},
        {"Yaesu FT-990", 116},
        {"Yaesu FRG-100", 117},
        {"Yaesu FRG-9600", 118},
        {"Yaesu FRG-8800", 119},
        {"Yaesu FT-817", 120},
        {"Yaesu FT-100", 121},
        {"Yaesu FT-857", 122},
        {"Yaesu FT-897", 123},
        {"Yaesu FT-1000MP", 124},
        {"Yaesu MARK-V", 125},
        {"Yaesu VR-5000", 126},
        {"Yaesu FT-450", 127},
        {"Yaesu FT-950", 128},
        {"Yaesu FT-2000", 129},
        {"Yaesu FTDX-9000", 130},
        {"Yaesu FT-980", 131},
        {"Yaesu FT-DX5000", 132},
        {"Vertex Standard", 133},
        {"Yaesu FT-1200", 134},
        {"Yaesu FT-991", 135},
        {"Kenwood TS-50S", 201},
        {"Kenwood TS-440", 202},
        {"Kenwood TS-450S", 203},
        {"Kenwood TS-570D", 204},
        {"Kenwood TS-690S", 205},
        {"Kenwood TS-711", 206},
        {"Kenwood TS-790", 207},
        {"Kenwood TS-811", 208},
        {"Kenwood TS-850", 209},
        {"Kenwood TS-870S", 210},
        {"Kenwood TS-940S", 211},
        {"Kenwood TS-950SDX", 213},
        {"Kenwood TS-2000", 214},
        {"Kenwood R-5000", 215},
        {"Kenwood TS-570S", 216},
        {"Kenwood TH-D7A", 217},
        {"Kenwood TH-F6A", 219},
        {"Kenwood TH-F7E", 220},
        {"Elecraft K2", 221},
        {"Kenwood TS-930", 222},
        {"Kenwood TH-G71", 223},
        {"Kenwood TS-680S", 224},
        {"Kenwood TS-140S", 225},
        {"Kenwood TM-D700", 226},
        {"Kenwood TM-V7", 227},
        {"Kenwood TS-480", 228},
        {"Elecraft K3/KX3", 229},
        {"Kenwood TRC-80", 230},
        {"Kenwood TS-590S", 231},
        {"SigFox Transfox", 232},
        {"Kenwood TH-D72A", 233},
        {"Kenwood TM-D710", 234},
        {"FlexRadio 6xxx", 236},
        {"Kenwood TS-590SG", 237},
        {"Elecraft XG3", 238},
        {"Kenwood TS-990s", 239},
        {"Icom IC-1275", 302},
        {"Icom IC-271", 303},
        {"Icom IC-275", 304},
        {"Icom IC-471", 306},
        {"Icom IC-475", 307},
        {"Icom IC-706", 309},
        {"Icom IC-706MkII", 310},
        {"Icom IC-706MkIIG", 311},
        {"Icom IC-707", 312},
        {"Icom IC-718", 313},
        {"Icom IC-725", 314},
        {"Icom IC-726", 315},
        {"Icom IC-728", 316},
        {"Icom IC-735", 319},
        {"Icom IC-736", 320},
        {"Icom IC-737", 321},
        {"Icom IC-738", 322},
        {"Icom IC-746", 323},
        {"Icom IC-751", 324},
        {"Icom IC-756", 326},
        {"Icom IC-756PRO", 327},
        {"Icom IC-761", 328},
        {"Icom IC-765", 329},
        {"Icom IC-775", 330},
        {"Icom IC-781", 331},
        {"Icom IC-820H", 332},
        {"Icom IC-821H", 334},
        {"Icom IC-970", 335},
        {"Icom IC-R10", 336},
        {"Icom IC-R71", 337},
        {"Icom IC-R72", 338},
        {"Icom IC-R75", 339},
        {"Icom IC-R7000", 340},
        {"Icom IC-R7100", 341},
        {"Icom ICR-8500", 342},
        {"Icom IC-R9000", 343},
        {"Icom IC-910", 344},
        {"Icom IC-78", 345},
        {"Icom IC-746PRO", 346},
        {"Icom IC-756PROII", 347},
        {"Ten-Tec Omni", 351},
        {"Optoelectronics OptoScan535", 352},
        {"Optoelectronics OptoScan456", 353},
        {"Icom IC", 354},
        {"Icom IC-703", 355},
        {"Icom IC-7800", 356},
        {"Icom IC-756PROIII", 357},
        {"Icom IC-R20", 358},
        {"Icom IC-7000", 360},
        {"Icom IC-7200", 361},
        {"Icom IC-7700", 362},
        {"Icom IC-7600", 363},
        {"Ten-Tec Delta", 364},
        {"Icom IC-92D", 365},
        {"Icom IC-R9500", 366},
        {"Icom IC-7410", 367},
        {"Icom IC-9100", 368},
        {"Icom IC-RX7", 369},
        {"Icom IC-7100", 370},
        {"Icom ID-5100", 371},
        {"Icom IC-PCR1000", 401},
        {"Icom IC-PCR100", 402},
        {"Icom IC-PCR1500", 403},
        {"Icom IC-PCR2500", 404},
        {"AOR AR8200", 501},
        {"AOR AR8000", 502},
        {"AOR AR7030", 503},
        {"AOR AR5000", 504},
        {"AOR AR3030", 505},
        {"AOR AR3000A", 506},
        {"AOR AR2700", 508},
        {"AOR AR8600", 513},
        {"AOR AR5000A", 514},
        {"AOR AR7030", 515},
        {"AOR SR2200", 516},
        {"JRC NRD-525", 605},
        {"JRC NRD-535D", 606},
        {"JRC NRD-545", 607},
        {"Uniden BC780xlt", 801},
        {"Uniden BC245xlt", 802},
        {"Uniden BC895xlt", 803},
        {"Radio Shack", 804},
        {"Uniden BC250D", 806},
        {"Uniden BCD-396T", 810},
        {"Uniden BCD-996T", 811},
        {"Uniden BC898T", 812},
        {"Drake R-8A", 902},
        {"Drake R-8B", 903},
        {"Lowe HF-235", 1004},
        {"Racal RA6790/GM", 1103},
        {"Racal RA3702", 1105},
        {"Watkins-Johnson WJ-8888", 1204},
        {"Skanti TRP8000", 1402},
        {"Skanti TRP", 1404},
        {"Winradio WR-1000", 1501},
        {"Winradio WR-1500", 1502},
        {"Winradio WR-1550", 1503},
        {"Winradio WR-3100", 1504},
        {"Winradio WR-3150", 1505},
        {"Winradio WR-3500", 1506},
        {"Winradio WR-3700", 1507},
        {"Winradio WR-G313", 1509},
        {"Ten-Tec TT-550", 1601},
        {"Ten-Tec TT-538", 1602},
        {"Ten-Tec RX-320", 1603},
        {"Ten-Tec RX-340", 1604},
        {"Ten-Tec RX-350", 1605},
        {"Ten-Tec TT-516", 1607},
        {"Ten-Tec TT-565", 1608},
        {"Ten-Tec TT-585", 1609},
        {"Ten-Tec TT-588", 1611},
        {"Ten-Tec RX-331", 1612},
        {"Ten-Tec TT-599", 1613},
        {"Alinco DX-77", 1701},
        {"Kachina 505DSP", 1801},
        {"TAPR DSP-10", 2201},
        {"Flex-radio SDR-1000", 2301},
        {"DTTS Microwave", 2303},
        {"DTTS Microwave", 2304},
        {"RFTE KD-500", 2401},
        {"Elektor Elektor", 2501},
        {"SAT-Schneider DRT1", 2502},
        {"Coding Technologies", 2503},
        {"AmQRP DDS-60", 2506},
        {"Elektor Elektor", 2507},
        {"mRS miniVNA", 2508},
        {"SoftRock Si570", 2509},
        {"KTH-SDRkit", 2511},
        {"FiFi FiFi-SDR", 2512},
        {"AMSAT-UK FUNcube", 2513},
        {"N2ADR HiQSDR", 2514},
        {"Funkamatuer FA-SDR", 2515},
        {"AE9RB Si570", 2516},
        {"AE9RB Si570", 2517},
        {"AMSAT-UKF UNcube", 2518},
        {"Video4Linux SW/FM", 2601},
        {"Video4Linux2 SW/FM", 2602},
        {"Rohde&Schwarz ESMC", 2701},
        {"Rohde&Schwarz EB200", 2702},
        {"Philips/Simoco PRM8060", 2801},
        {"ADAT www.adat.ch", 2901},
        {"Icom IC-M700PRO", 3001},
        {"Icom IC-M802", 3002},
        {"Icom IC-M710", 3003}
    };
};

#endif // KONFIGURACJA_H
