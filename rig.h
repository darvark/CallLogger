#ifndef RADIO_H
#define RADIO_H

#include <QString>
#include <QDebug>
#include <hamlib/rig.h>

typedef struct rig_params{
    QString mode;
    double freq;
    QString vfo;
};

RIG* init_rig(int rigType, const char* serial_port);
void fetch_rig_params (RIG* my_rig, const char* serial_port, rig_params* r);
const char* map_enum_to_str(rmode_t rmode);
void close_rig(RIG* my_rig);
void open_rig(RIG* my_rig, const char* serial_port);


#endif // RADIO_H
