#ifndef CONFIG_H
#define CONFIG_H

#include <libconfig.h++>
#include <QString>
#include <QDebug>

typedef struct {
   QString callsign;
   QString dbfile;
   QString category;
   int rig;
   QString serial;
} params;

class config
{
public:
    config();
    void load_settings(params *);
    int save_settings(QString callsign, QString dbfile, QString category, int rig, QString serial);
private:
    libconfig::Config cfg;
};

#endif // CONFIG_H
