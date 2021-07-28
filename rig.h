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

RIG* init_rig(int rigType, const char* serial_port);
void fetch_rig_params(RIG* my_rig, /*const char* serial_port,*/ rig_params* r);
const char* map_enum_to_str(rmode_t rmode);
void close_rig(RIG* my_rig);
bool open_rig(RIG* my_rig, const char* serial_port);


//enum serial_parity_e  map_parity(QString parity)
//{
//    if (parity.compare("None"))
//        return RIG_PARITY_NONE;		/*!< No parity */
//    else if (parity.compare("Odd"))
//        return RIG_PARITY_ODD;		/*!< Odd */
//    else if (parity.compare("Even"))
//        return RIG_PARITY_EVEN;		/*!< Even */
//    else if (parity.compare("Mark"))
//        return RIG_PARITY_MARK;		/*!< Mark */
//    else if (parity.compare("Space"))
//        return RIG_PARITY_SPACE;
//}

//enum serial_handshake_e map_handshake(QString hand)
//{
//    if (hand.compare("None"))
//        return RIG_HANDSHAKE_NONE;/*!< No handshake */
//    else if (hand.compare("XonXoff"))
//        return RIG_HANDSHAKE_XONXOFF; /*!< Software XON/XOFF */
//    else if (hand.compare("Hardware"))
//        return RIG_HANDSHAKE_HARDWARE;	/*!< Hardware CTS/RTS */
//}
#endif // RADIO_H
