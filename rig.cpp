#include "rig.h"

enum serial_parity_e map_parity(QString parity)
{
    if (parity.compare("None"))
        return RIG_PARITY_NONE;		/*!< No parity */
    else if (parity.compare("Odd"))
        return RIG_PARITY_ODD;		/*!< Odd */
    else if (parity.compare("Even"))
        return RIG_PARITY_EVEN;		/*!< Even */
    else if (parity.compare("Mark"))
        return RIG_PARITY_MARK;		/*!< Mark */
    else if (parity.compare("Space"))
        return RIG_PARITY_SPACE;
}

enum serial_handshake_e map_handshake(QString hand)
{
    if (hand.compare("None"))
        return RIG_HANDSHAKE_NONE;/*!< No handshake */
    else if (hand.compare("XonXoff"))
        return RIG_HANDSHAKE_XONXOFF; /*!< Software XON/XOFF */
    else if (hand.compare("Hardware"))
        return RIG_HANDSHAKE_HARDWARE;	/*!< Hardware CTS/RTS */
}

RIG* init_rig(int rigType, const char* serial_port, comcfg &com_params)
{
    RIG *my_rig; /* handle to rig (nstance) */
    rig_model_t myrig_model;
    printf("testrig: Hello, I am your main() !\n");
    /* Turn off backend debugging ouput */
    rig_set_debug_level(RIG_DEBUG_NONE);

    //dodac ladowanie paramsow z configa
    hamlib_port_t myport;
    /* wyciagnac dane z konfiga */
    myport.type.rig = RIG_PORT_SERIAL;
    myport.parm.serial.rate = com_params.baudrate.toInt(); //115200;
    myport.parm.serial.data_bits = com_params.databits.toInt(); //8;
    myport.parm.serial.stop_bits = com_params.stopbit.toInt(); //1;
    myport.parm.serial.parity = map_parity(com_params.parity); //RIG_PARITY_ODD;
    myport.parm.serial.handshake = map_handshake(com_params.handshake); //RIG_HANDSHAKE_HARDWARE;
    strncpy(myport.pathname, serial_port, strlen(serial_port));
    rig_load_all_backends();
    myrig_model = rigType;

    //initialize rig
    my_rig = rig_init(myrig_model);
    if (!my_rig) {
        fprintf(stderr,"Unknown rig num: %d\n", myrig_model);
        fprintf(stderr,"Please check riglist.h\n");
        exit(1); /* whoops! something went wrong (mem alloc?) */
    }

    return my_rig;
}

/* maps rig modulation enum to string */
const char* map_enum_to_str(rmode_t rmode)
{
  switch (rmode) {
      case (RIG_MODE_NONE): return "NONE";
      case (RIG_MODE_AM): return "AM";
      case (RIG_MODE_CW): return "CW";
      case (RIG_MODE_USB): return "USB";
      case (RIG_MODE_LSB): return "LSB";
      case (RIG_MODE_RTTY): return "RTTY";
      case (RIG_MODE_FM): return "FM";
      case (RIG_MODE_WFM): return "WFM";
      case (RIG_MODE_CWR): return "CWR";
      case (RIG_MODE_RTTYR): return "RTTYR";
      case (RIG_MODE_AMS): return "AMS";
      case (RIG_MODE_PKTLSB): return "PKTLSB";
      case (RIG_MODE_PKTUSB): return "PKTUSB";
      case (RIG_MODE_PKTFM): return "PKTFM";
      case (RIG_MODE_ECSSUSB): return "ECSSUSB";
      case (RIG_MODE_ECSSLSB): return "ECSSLSB";
      case (RIG_MODE_FAX): return "FAX";
      case (RIG_MODE_SAM): return "SAM";
      case (RIG_MODE_SAL): return "SAL";
      case (RIG_MODE_SAH): return "SAH";
      case (RIG_MODE_DSB): return "DSB";
      case (RIG_MODE_FMN): return "FMN";
//      case (RIG_MODE_PKTAM): return "PKTAM";
      case (RIG_MODE_TESTS_MAX): return "TESTS_MAX";
    }
    return "";
}

/*
 * query rig for declared params and print it to stdout
 */
void close_rig(RIG* my_rig)
{
    rig_close(my_rig); /* close port */
    rig_cleanup(my_rig);
}

bool open_rig(RIG* my_rig, const char* serial_port)
{
    int retcode;
    strncpy(my_rig->state.rigport.pathname, serial_port, strlen(serial_port));
    retcode = rig_open(my_rig);
    if (retcode != RIG_OK) {
        printf("rig_open: error = %s\n", rigerror(retcode));
        return false;
    }
    printf("Port %s opened ok\n", serial_port);
    return true;
}

void fetch_rig_params (RIG* my_rig,/* const char* serial_port,*/ rig_params* r)
{
    freq_t freq; /* frequency */
    rmode_t rmode; /* radio mode of operation */
    pbwidth_t width;
    vfo_t vfo;
    int retcode; /* generic return code from functions */

    //get freg of selected vfo
    retcode = rig_get_freq(my_rig, RIG_VFO_CURR, &freq);
    if (retcode == RIG_OK ) {
        r->freq = freq;
    } else {
        printf("rig_get_freq: error = %s \n", rigerror(retcode));
    }

    //get current modulation
    retcode = rig_get_mode(my_rig, RIG_VFO_CURR, &rmode, &width);
    if (retcode == RIG_OK ) {
        r->mode = QString(map_enum_to_str(rmode));
    } else {
        printf("rig_get_mode: error = %s \n", rigerror(retcode));
    }

    //get current modulation
    retcode = rig_get_vfo(my_rig, &vfo);
    if (retcode == RIG_OK ) {
        r->vfo = vfo == 1 ? QString("A") : QString("B");
    } else {
        printf("rig_get_vfo: error = %s \n", rigerror(retcode));
    }
}
