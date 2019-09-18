#include "konfiguracja.h"
#include "ui_konfiguracja.h"

konfiguracja::konfiguracja(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::konfiguracja)
{
    ui->setupUi(this);

    if (ui->wyborRadia->count() == 0)
    {
        dodaj_radia_do_listy(ui);
        ustaw_moc(ui);
        ustaw_mode(ui);
        ustaw_zawody(ui);
        ustaw_pasmo(ui);
        ustaw_operator(ui);
        ustaw_stacja(ui);
        ustaw_czas(ui);
        ustaw_nadajnik(ui);
        ustaw_overlay(ui);
    }
    connect(ui->znak, SIGNAL(textChanged(const QString &)), this, SLOT(toUpper(const QString &)));
}

konfiguracja::~konfiguracja()
{
    delete ui;
}

int konfiguracja::radio(QString radio)
{
    return mapowanieradia[radio];
}

void konfiguracja::on_zapisz_clicked()
{
    //mapowanie Qt::Checked status na bool'a
    bool exch = ui->wymianaBOx->checkState() == Qt::Checked ? true : false;
    QString assisted = ui->assisted->checkState() == Qt::Checked ? "ASSISTED" : "NON-ASSISTED";

    cfg.save_settings(ui->znak->text(), ui->plikbazy->text(),
                      radio(ui->wyborRadia->currentText()),
                      ui->serialPorts->currentText(),
                      ui->listaStacja->currentText(), ui->listaMoc->currentText(),
                      ui->listaMode->currentText(), ui->listaZawody->currentText(),
                      assisted, ui->listaPasmo->currentText(), ui->listaOperator->currentText(),
                      ui->listaSygnal->currentText(),
                      ui->soapbox->text(), ui->listaCzas->currentText(), ui->listaOverlay->currentText(),
                      ui->poleAdresu->text(), ui->email->text(), ui->klub->text(), exch,
                      ui->wzorWymiany->text());
    this->close();
}

void konfiguracja::on_kasuj_clicked()
{
    //wyczysc selekcje
    ui->znak->clear();
    ui->plikbazy->clear();
//    ui->portpolaczenia->clear();
    this->close();
}

void konfiguracja::dodaj_porty(Ui::konfiguracja* ui)
{
    Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
            ui->serialPorts->addItem(port.portName());
        }
}

void konfiguracja::dodaj_radia_do_listy(Ui::konfiguracja* ui)
{
    ui->wyborRadia->addItem("Hamlib Dummy");
    ui->wyborRadia->addItem("Hamlib rigctl");
    ui->wyborRadia->addItem("Yaesu FT-847");
    ui->wyborRadia->addItem("Yaesu FT-1000D");
    ui->wyborRadia->addItem("Yaesu MARK-V");
    ui->wyborRadia->addItem("Yaesu FT-747GX");
    ui->wyborRadia->addItem("Yaesu FT-757GX");
    ui->wyborRadia->addItem("Yaesu FT-757GXII");
    ui->wyborRadia->addItem("Yaesu FT-767GX");
    ui->wyborRadia->addItem("Yaesu FT-736R");
    ui->wyborRadia->addItem("Yaesu FT-840");
    ui->wyborRadia->addItem("Yaesu FT-900");
    ui->wyborRadia->addItem("Yaesu FT-920");
    ui->wyborRadia->addItem("Yaesu FT-890");
    ui->wyborRadia->addItem("Yaesu FT-990");
    ui->wyborRadia->addItem("Yaesu FRG-100");
    ui->wyborRadia->addItem("Yaesu FRG-9600");
    ui->wyborRadia->addItem("Yaesu FRG-8800");
    ui->wyborRadia->addItem("Yaesu FT-817");
    ui->wyborRadia->addItem("Yaesu FT-100");
    ui->wyborRadia->addItem("Yaesu FT-857");
    ui->wyborRadia->addItem("Yaesu FT-897");
    ui->wyborRadia->addItem("Yaesu FT-1000MP");
    ui->wyborRadia->addItem("Yaesu MARK-V");
    ui->wyborRadia->addItem("Yaesu VR-5000");
    ui->wyborRadia->addItem("Yaesu FT-450");
    ui->wyborRadia->addItem("Yaesu FT-950");
    ui->wyborRadia->addItem("Yaesu FT-2000");
    ui->wyborRadia->addItem("Yaesu FTDX-9000");
    ui->wyborRadia->addItem("Yaesu FT-980");
    ui->wyborRadia->addItem("Yaesu FT-DX5000");
    ui->wyborRadia->addItem("Vertex Standard");
    ui->wyborRadia->addItem("Yaesu FT-1200");
    ui->wyborRadia->addItem("Yaesu FT-991");
    ui->wyborRadia->addItem("Kenwood TS-50S");
    ui->wyborRadia->addItem("Kenwood TS-440");
    ui->wyborRadia->addItem("Kenwood TS-450S");
    ui->wyborRadia->addItem("Kenwood TS-570D");
    ui->wyborRadia->addItem("Kenwood TS-690S");
    ui->wyborRadia->addItem("Kenwood TS-711");
    ui->wyborRadia->addItem("Kenwood TS-790");
    ui->wyborRadia->addItem("Kenwood TS-811");
    ui->wyborRadia->addItem("Kenwood TS-850");
    ui->wyborRadia->addItem("Kenwood TS-870S");
    ui->wyborRadia->addItem("Kenwood TS-940S");
    ui->wyborRadia->addItem("Kenwood TS-950SDX");
    ui->wyborRadia->addItem("Kenwood TS-2000");
    ui->wyborRadia->addItem("Kenwood R-5000");
    ui->wyborRadia->addItem("Kenwood TS-570S");
    ui->wyborRadia->addItem("Kenwood TH-D7A");
    ui->wyborRadia->addItem("Kenwood TH-F6A");
    ui->wyborRadia->addItem("Kenwood TH-F7E");
    ui->wyborRadia->addItem("Elecraft K2");
    ui->wyborRadia->addItem("Kenwood TS-930");
    ui->wyborRadia->addItem("Kenwood TH-G71");
    ui->wyborRadia->addItem("Kenwood TS-680S");
    ui->wyborRadia->addItem("Kenwood TS-140S");
    ui->wyborRadia->addItem("Kenwood TM-D700");
    ui->wyborRadia->addItem("Kenwood TM-V7");
    ui->wyborRadia->addItem("Kenwood TS-480");
    ui->wyborRadia->addItem("Elecraft K3/KX3");
    ui->wyborRadia->addItem("Kenwood TRC-80");
    ui->wyborRadia->addItem("Kenwood TS-590S");
    ui->wyborRadia->addItem("SigFox Transfox");
    ui->wyborRadia->addItem("Kenwood TH-D72A");
    ui->wyborRadia->addItem("Kenwood TM-D710");
    ui->wyborRadia->addItem("FlexRadio 6xxx");
    ui->wyborRadia->addItem("Kenwood TS-590SG");
    ui->wyborRadia->addItem("Elecraft XG3");
    ui->wyborRadia->addItem("Kenwood TS-990s");
    ui->wyborRadia->addItem("Icom IC-1275");
    ui->wyborRadia->addItem("Icom IC-271");
    ui->wyborRadia->addItem("Icom IC-275");
    ui->wyborRadia->addItem("Icom IC-471");
    ui->wyborRadia->addItem("Icom IC-475");
    ui->wyborRadia->addItem("Icom IC-706");
    ui->wyborRadia->addItem("Icom IC-706MkII");
    ui->wyborRadia->addItem("Icom IC-706MkIIG");
    ui->wyborRadia->addItem("Icom IC-707");
    ui->wyborRadia->addItem("Icom IC-718");
    ui->wyborRadia->addItem("Icom IC-725");
    ui->wyborRadia->addItem("Icom IC-726");
    ui->wyborRadia->addItem("Icom IC-728");
    ui->wyborRadia->addItem("Icom IC-735");
    ui->wyborRadia->addItem("Icom IC-736");
    ui->wyborRadia->addItem("Icom IC-737");
    ui->wyborRadia->addItem("Icom IC-738");
    ui->wyborRadia->addItem("Icom IC-746");
    ui->wyborRadia->addItem("Icom IC-751");
    ui->wyborRadia->addItem("Icom IC-756");
    ui->wyborRadia->addItem("Icom IC-756PRO");
    ui->wyborRadia->addItem("Icom IC-761");
    ui->wyborRadia->addItem("Icom IC-765");
    ui->wyborRadia->addItem("Icom IC-775");
    ui->wyborRadia->addItem("Icom IC-781");
    ui->wyborRadia->addItem("Icom IC-820H");
    ui->wyborRadia->addItem("Icom IC-821H");
    ui->wyborRadia->addItem("Icom IC-970");
    ui->wyborRadia->addItem("Icom IC-R10");
    ui->wyborRadia->addItem("Icom IC-R71");
    ui->wyborRadia->addItem("Icom IC-R72");
    ui->wyborRadia->addItem("Icom IC-R75");
    ui->wyborRadia->addItem("Icom IC-R7000");
    ui->wyborRadia->addItem("Icom IC-R7100");
    ui->wyborRadia->addItem("Icom ICR-8500");
    ui->wyborRadia->addItem("Icom IC-R9000");
    ui->wyborRadia->addItem("Icom IC-910");
    ui->wyborRadia->addItem("Icom IC-78");
    ui->wyborRadia->addItem("Icom IC-746PRO");
    ui->wyborRadia->addItem("Icom IC-756PROII");
    ui->wyborRadia->addItem("Ten-Tec Omni");
    ui->wyborRadia->addItem("Optoelectronics OptoScan535");
    ui->wyborRadia->addItem("Optoelectronics OptoScan456");
    ui->wyborRadia->addItem("Icom IC");
    ui->wyborRadia->addItem("Icom IC-703");
    ui->wyborRadia->addItem("Icom IC-7800");
    ui->wyborRadia->addItem("Icom IC-756PROIII");
    ui->wyborRadia->addItem("Icom IC-R20");
    ui->wyborRadia->addItem("Icom IC-7000");
    ui->wyborRadia->addItem("Icom IC-7200");
    ui->wyborRadia->addItem("Icom IC-7700");
    ui->wyborRadia->addItem("Icom IC-7600");
    ui->wyborRadia->addItem("Ten-Tec Delta");
    ui->wyborRadia->addItem("Icom IC-92D");
    ui->wyborRadia->addItem("Icom IC-R9500");
    ui->wyborRadia->addItem("Icom IC-7410");
    ui->wyborRadia->addItem("Icom IC-9100");
    ui->wyborRadia->addItem("Icom IC-RX7");
    ui->wyborRadia->addItem("Icom IC-7100");
    ui->wyborRadia->addItem("Icom ID-5100");
    ui->wyborRadia->addItem("Icom IC-PCR1000");
    ui->wyborRadia->addItem("Icom IC-PCR100");
    ui->wyborRadia->addItem("Icom IC-PCR1500");
    ui->wyborRadia->addItem("Icom IC-PCR2500");
    ui->wyborRadia->addItem("AOR AR8200");
    ui->wyborRadia->addItem("AOR AR8000");
    ui->wyborRadia->addItem("AOR AR7030");
    ui->wyborRadia->addItem("AOR AR5000");
    ui->wyborRadia->addItem("AOR AR3030");
    ui->wyborRadia->addItem("AOR AR3000A");
    ui->wyborRadia->addItem("AOR AR2700");
    ui->wyborRadia->addItem("AOR AR8600");
    ui->wyborRadia->addItem("AOR AR5000A");
    ui->wyborRadia->addItem("AOR AR7030");
    ui->wyborRadia->addItem("AOR SR2200");
    ui->wyborRadia->addItem("JRC NRD-525");
    ui->wyborRadia->addItem("JRC NRD-535D");
    ui->wyborRadia->addItem("JRC NRD-545");
    ui->wyborRadia->addItem("Uniden BC780xlt");
    ui->wyborRadia->addItem("Uniden BC245xlt");
    ui->wyborRadia->addItem("Uniden BC895xlt");
    ui->wyborRadia->addItem("Radio Shack");
    ui->wyborRadia->addItem("Uniden BC250D");
    ui->wyborRadia->addItem("Uniden BCD-396T");
    ui->wyborRadia->addItem("Uniden BCD-996T");
    ui->wyborRadia->addItem("Uniden BC898T");
    ui->wyborRadia->addItem("Drake R-8A");
    ui->wyborRadia->addItem("Drake R-8B");
    ui->wyborRadia->addItem("Lowe HF-235");
    ui->wyborRadia->addItem("Racal RA6790/GM");
    ui->wyborRadia->addItem("Racal RA3702");
    ui->wyborRadia->addItem("Watkins-Johnson WJ-8888");
    ui->wyborRadia->addItem("Skanti TRP8000");
    ui->wyborRadia->addItem("Skanti TRP");
    ui->wyborRadia->addItem("Winradio WR-1000");
    ui->wyborRadia->addItem("Winradio WR-1500");
    ui->wyborRadia->addItem("Winradio WR-1550");
    ui->wyborRadia->addItem("Winradio WR-3100");
    ui->wyborRadia->addItem("Winradio WR-3150");
    ui->wyborRadia->addItem("Winradio WR-3500");
    ui->wyborRadia->addItem("Winradio WR-3700");
    ui->wyborRadia->addItem("Winradio WR-G313");
    ui->wyborRadia->addItem("Ten-Tec TT-550");
    ui->wyborRadia->addItem("Ten-Tec TT-538");
    ui->wyborRadia->addItem("Ten-Tec RX-320");
    ui->wyborRadia->addItem("Ten-Tec RX-340");
    ui->wyborRadia->addItem("Ten-Tec RX-350");
    ui->wyborRadia->addItem("Ten-Tec TT-516");
    ui->wyborRadia->addItem("Ten-Tec TT-565");
    ui->wyborRadia->addItem("Ten-Tec TT-585");
    ui->wyborRadia->addItem("Ten-Tec TT-588");
    ui->wyborRadia->addItem("Ten-Tec RX-331");
    ui->wyborRadia->addItem("Ten-Tec TT-599");
    ui->wyborRadia->addItem("Alinco DX-77");
    ui->wyborRadia->addItem("Kachina 505DSP");
    ui->wyborRadia->addItem("TAPR DSP-10");
    ui->wyborRadia->addItem("Flex-radio SDR-1000");
    ui->wyborRadia->addItem("DTTS Microwave");
    ui->wyborRadia->addItem("DTTS Microwave");
    ui->wyborRadia->addItem("RFT EKD-500");
    ui->wyborRadia->addItem("Elektor Elektor");
    ui->wyborRadia->addItem("SAT-Schneider DRT1");
    ui->wyborRadia->addItem("Coding Technologies");
    ui->wyborRadia->addItem("AmQRP DDS-60");
    ui->wyborRadia->addItem("Elektor Elektor");
    ui->wyborRadia->addItem("mRS miniVNA");
    ui->wyborRadia->addItem("SoftRock Si570");
    ui->wyborRadia->addItem("KTH-SDR kit");
    ui->wyborRadia->addItem("FiFi FiFi-SDR");
    ui->wyborRadia->addItem("AMSAT-UK FUNcube");
    ui->wyborRadia->addItem("N2ADR HiQSDR");
    ui->wyborRadia->addItem("Funkamatuer FA-SDR");
    ui->wyborRadia->addItem("AE9RB Si570");
    ui->wyborRadia->addItem("AE9RB Si570");
    ui->wyborRadia->addItem("AMSAT-UK FUNcube");
    ui->wyborRadia->addItem("Video4Linux SW/FM");
    ui->wyborRadia->addItem("Video4Linux2 SW/FM");
    ui->wyborRadia->addItem("Rohde Schwarz ESMC");
    ui->wyborRadia->addItem("Rohde Schwarz EB200");
    ui->wyborRadia->addItem("Philips/Simoco PRM8060");
    ui->wyborRadia->addItem("ADAT www.adat.ch");
    ui->wyborRadia->addItem("Icom IC-M700PRO");
    ui->wyborRadia->addItem("Icom IC-M802");
    ui->wyborRadia->addItem("Icom IC-M710");
}
//cateogry power
void konfiguracja::ustaw_moc(Ui::konfiguracja* ui)
{
    ui->listaMoc->addItem("HIGH");
    ui->listaMoc->addItem("LOW");
    ui->listaMoc->addItem("QRP");
}
//category mode
void konfiguracja::ustaw_mode(Ui::konfiguracja* ui)
{
    ui->listaMode->addItem("CW");
    ui->listaMode->addItem("DIGI");
    ui->listaMode->addItem("FM");
    ui->listaMode->addItem("RTTY");
    ui->listaMode->addItem("SSB");
    ui->listaMode->addItem("MIXED");
}
//category contest
void konfiguracja::ustaw_zawody(Ui::konfiguracja* ui)
{
    ui->listaZawody->addItem("AP-SPRINT");
    ui->listaZawody->addItem("ARRL-10");
    ui->listaZawody->addItem("ARRL-10-GHZ");
    ui->listaZawody->addItem("ARRL-160");
    ui->listaZawody->addItem("ARRL-222");
    ui->listaZawody->addItem("ARRL-DX-CW");
    ui->listaZawody->addItem("ARRL-DX-SSB");
    ui->listaZawody->addItem("ARRL-EME");
    ui->listaZawody->addItem("ARRL-RR-PH");
    ui->listaZawody->addItem("ARRL-RR-DIG");
    ui->listaZawody->addItem("ARRL-RR-CW");
    ui->listaZawody->addItem("ARRL-SCR");
    ui->listaZawody->addItem("ARRL-SS-CW");
    ui->listaZawody->addItem("ARRL-SS-SSB");
    ui->listaZawody->addItem("ARRL-UHF-AUG");
    ui->listaZawody->addItem("ARRL-VHF-JAN");
    ui->listaZawody->addItem("ARRL-VHF-JUN");
    ui->listaZawody->addItem("ARRL-VHF-SEP");
    ui->listaZawody->addItem("ARRL-RTTY");
    ui->listaZawody->addItem("BARTG-RTTY");
    ui->listaZawody->addItem("CQ-160-CW");
    ui->listaZawody->addItem("CQ-160-SSB");
    ui->listaZawody->addItem("CQ-WPX-CW");
    ui->listaZawody->addItem("CQ-WPX-RTTY");
    ui->listaZawody->addItem("CQ-WPX-SSB");
    ui->listaZawody->addItem("CQ-VHF");
    ui->listaZawody->addItem("CQ-WW-CW");
    ui->listaZawody->addItem("CQ-WW-RTTY");
    ui->listaZawody->addItem("CQ-WW-SSB");
    ui->listaZawody->addItem("DARC-WAEDC-CW");
    ui->listaZawody->addItem("DARC-WAEDC-RTTY");
    ui->listaZawody->addItem("DARC-WAEDC-SSB");
    ui->listaZawody->addItem("DL-DX-RTTY");
    ui->listaZawody->addItem("DRCG-WW-RTTY");
    ui->listaZawody->addItem("FCG-FQP");
    ui->listaZawody->addItem("IARU-HF");
    ui->listaZawody->addItem("JIDX-CW");
    ui->listaZawody->addItem("JIDX-SSB");
    ui->listaZawody->addItem("MN-QSO-PARTY");
    ui->listaZawody->addItem("NAQP-CW");
    ui->listaZawody->addItem("NAQP-SSB");
    ui->listaZawody->addItem("NAQP-RTTY");
    ui->listaZawody->addItem("NA-SPRINT-CW");
    ui->listaZawody->addItem("NA-SPRINT-SSB");
    ui->listaZawody->addItem("NA-SPRINT-RTTY");
    ui->listaZawody->addItem("NCCC-CQP");
    ui->listaZawody->addItem("NEQP");
    ui->listaZawody->addItem("OCEANIA-DX-CW");
    ui->listaZawody->addItem("OCEANIA-DX-SSB");
    ui->listaZawody->addItem("RDXC");
    ui->listaZawody->addItem("RSGB-IOTA");
    ui->listaZawody->addItem("SAC-CW");
    ui->listaZawody->addItem("SAC-SSB");
    ui->listaZawody->addItem("SPDXC");
    ui->listaZawody->addItem("SPDXC-RTTY");
    ui->listaZawody->addItem("STEW-PERRY");
    ui->listaZawody->addItem("TARA-RTTY");
    ui->listaZawody->addItem("WAG");
    ui->listaZawody->addItem("WW-DIGI");
}
//category assisted
QString konfiguracja::on_assisted_stateChanged(int arg1)
{
    return arg1 ? assisted = "ASSISTED" : assisted = "NON_ASSISTED";
}
//category band
void konfiguracja::ustaw_pasmo(Ui::konfiguracja* ui)
{
    ui->listaPasmo->addItem("ALL");
    ui->listaPasmo->addItem("160M");
    ui->listaPasmo->addItem("80M");
    ui->listaPasmo->addItem("40M");
    ui->listaPasmo->addItem("20M");
    ui->listaPasmo->addItem("15M");
    ui->listaPasmo->addItem("10M");
    ui->listaPasmo->addItem("6M");
    ui->listaPasmo->addItem("4M");
    ui->listaPasmo->addItem("2M");
    ui->listaPasmo->addItem("222");
    ui->listaPasmo->addItem("432");
    ui->listaPasmo->addItem("902");
    ui->listaPasmo->addItem("1.2G");
    ui->listaPasmo->addItem("2.3G");
    ui->listaPasmo->addItem("3.4G");
    ui->listaPasmo->addItem("5.7G");
    ui->listaPasmo->addItem("10G");
    ui->listaPasmo->addItem("24G");
    ui->listaPasmo->addItem("47G");
    ui->listaPasmo->addItem("75G");
    ui->listaPasmo->addItem("123G");
    ui->listaPasmo->addItem("134G");
    ui->listaPasmo->addItem("241G");
    ui->listaPasmo->addItem("Light");
    ui->listaPasmo->addItem("VHF-3-BAND and VHF-FM-ONLY");
}
//category power
void konfiguracja::ustaw_operator(Ui::konfiguracja *ui)
{
    ui->listaOperator->addItem("SINGLE_OP");
    ui->listaOperator->addItem("MULTI_OP");
    ui->listaOperator->addItem("CHECKLOG");
}
//category station
void konfiguracja::ustaw_stacja(Ui::konfiguracja* ui)
{
    ui->listaStacja->addItem("FIXED");
    ui->listaStacja->addItem("MOBILE");
    ui->listaStacja->addItem("PORTABLE");
    ui->listaStacja->addItem("ROVER");
    ui->listaStacja->addItem("ROVER-LIMITED");
    ui->listaStacja->addItem("ROVER-UNLIMITED");
    ui->listaStacja->addItem("EXPEDITION");
    ui->listaStacja->addItem("HQ");
    ui->listaStacja->addItem("SCHOOL");

}
//category time
void konfiguracja::ustaw_czas(Ui::konfiguracja* ui)
{
    ui->listaCzas->addItem("6-HOURS");
    ui->listaCzas->addItem("12-HOURS");
    ui->listaCzas->addItem("24-HOURS");
}

//category transmitter
void konfiguracja::ustaw_nadajnik(Ui::konfiguracja* ui)
{
    ui->listaSygnal->addItem("ONE");
    ui->listaSygnal->addItem("TWO");
    ui->listaSygnal->addItem("LIMITED");
    ui->listaSygnal->addItem("UNLIMITED");
    ui->listaSygnal->addItem("SWL");
}
//cateogry overlay
void konfiguracja::ustaw_overlay(Ui::konfiguracja* ui)
{
    ui->listaOverlay->addItem("CLASSIC");
    ui->listaOverlay->addItem("ROOKIE");
    ui->listaOverlay->addItem("TB_WIRES");
    ui->listaOverlay->addItem("NOVICE-TECH");
    ui->listaOverlay->addItem("OVER-50");
}

void konfiguracja::on_wymianaBOx_stateChanged(int arg1)
{
    if (arg1)
    {
        stala_wymiana = true;
    }
    else
    {
        stala_wymiana = false;
    }
}
//zwraca prawde jesli wymiana jest stala, bez inkrementacji
bool konfiguracja::wymiana(bool stala)
{
    return stala;
}
