#ifndef CONFIG_H
#define CONFIG_H

#include <libconfig.h++>
#include <QString>
#include <QDebug>

typedef struct params {
   QString callsign;
   QString dbfile;
   QString category;
   int rig;
} params;

class config
{
public:
    config();
    params &load_settings();
    int save_settings(QString callsign, QString dbfile, QString category, int rig);

    QString get_callsign(params &s);
    QString get_dbfile(params &s);
    QString get_category(params &s);
    int get_rig(params &s);
private:

};

#endif // CONFIG_H
