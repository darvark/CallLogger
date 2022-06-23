#ifndef RADIO_H
#define RADIO_H

#include <QString>
#include <QDebug>
#include <hamlib/rig.h>
#include "config.h"

struct rig_params{
    QString mode;
    double freq;
    QString vfo;
};

struct connection_params{
    QString baudrate;
    QString databits;
    QString stopbit;
    QString parity;
    QString handshake;
};

RIG* init_rig(int rigType, const char* serial_port, comcfg &com_params);
void fetch_rig_params(RIG* my_rig, /*const char* serial_port,*/ rig_params* r);
const char* map_enum_to_str(rmode_t rmode);
void close_rig(RIG* my_rig);
bool open_rig(RIG* my_rig, const char* serial_port);
enum serial_handshake_e map_handshake(QString hand);
enum serial_parity_e map_parity(QString parity);



#endif // RADIO_H
