#ifndef RIG_H
#define RIG_H

//#include <string.h>
//#include <unistd.h>
//#include <stdlib.h>
#include <QString>
#include <QDebug>
#include <hamlib/rig.h>

class rig_query
{
public:
    rig_query();
    RIG* init_rig(int rigType, const char* serial_port);
    double fetch_freq(RIG* radio, const char* serial_port);
    QString fetch_vfo(RIG* radio, const char* serial_port);
    void fetch_rig_params (RIG* my_rig, const char* serial_port);
    QString map_enum_to_str(rmode_t rmode);
    QString fetch_mode(RIG* radio, const char* serial_port);
private:
    int retcode;
};

#endif // RIG_H
