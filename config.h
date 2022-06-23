#ifndef CONFIG_H
#define CONFIG_H

#include <libconfig.h++>
#include <QString>
#include <QDebug>

typedef struct {
   QString callsign;
   QString dbfile;
   int rig;
   QString serial;
   //zwiazane z zawodami
   QString cat_station;
   QString cat_power;
   QString cat_mode;
   QString contest;
   QString cat_assisted;
   QString cat_band;
   QString cat_operators;
   QString cat_signal;
   QString cat_soapbox;
   QString cat_time;
   QString cat_overlay;
   QString adress;
   QString email;
   QString klub;
   bool czy_stala_wymiana; // czy stala
} params;

typedef struct {
    QString baudrate;
    QString databits;
    QString stopbit;
    QString parity;
    QString handshake;
} comcfg;


class config
{
public:
    config();
    ~config();
    void load_settings(params *p, comcfg *cc, QString &confFIle);
    int save_settings(params *p, comcfg *cc);
    void reset(params *s, comcfg *cc);
private:
    libconfig::Config cfg;
};

#endif // CONFIG_H
