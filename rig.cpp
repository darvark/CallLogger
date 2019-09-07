#include "rig.h"

rig_query::rig_query() {}

/*
 * initialize all needed params and connection to rig
 * return rig handler
 */
RIG* rig_query::init_rig(int rigType, const char* serial_port)
{
    RIG *my_rig; /* handle to rig (nstance) */
    rig_model_t myrig_model;
    /* Turn off backend debugging ouput */
    rig_set_debug_level(RIG_DEBUG_NONE);

    hamlib_port_t myport;
    /* may be overriden by backend probe */
    myport.type.rig = RIG_PORT_SERIAL;
    myport.parm.serial.rate = 115200;
    myport.parm.serial.data_bits = 8;
    myport.parm.serial.stop_bits = 1;
    myport.parm.serial.parity = RIG_PARITY_NONE;
    myport.parm.serial.handshake = RIG_HANDSHAKE_HARDWARE;
    strncpy(myport.pathname, serial_port, FILPATHLEN - 1);
    rig_load_all_backends();
    myrig_model = rigType;

    //initialize rig
    my_rig = rig_init(myrig_model);
    if (!my_rig) {
        qDebug() << "Unknown rig\nPlease check riglist.h\n";
        exit(1); /* whoops! something went wrong (mem alloc?) */
    }

    return my_rig;
}

/* maps rig modulation enum to string */
QString rig_query::map_enum_to_str(rmode_t rmode)
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
      case (RIG_MODE_PKTAM): return "PKTAM";
      case (RIG_MODE_TESTS_MAX): return "TESTS_MAX";
    }
    return "";
}

QString rig_query::fetch_vfo(RIG* my_rig, const char* serial_port)
{
    vfo_t vfo;
    //Open rig connection
    strncpy(my_rig->state.rigport.pathname, serial_port, FILPATHLEN - 1);
    retcode = rig_open(my_rig);
    if (retcode != RIG_OK) {
        qDebug() << "rig_open: error = " + QString(rigerror(retcode));
        exit(2);
    }

    int vfo_nr = rig_get_vfo(my_rig, &vfo);

    rig_close(my_rig); /* close port */
    rig_cleanup(my_rig); /* if you care about memory */

    if (vfo_nr != 1)
        return "B";

    return "A";
}

double rig_query::fetch_freq(RIG *radio, const char *serial_port)
{
    freq_t freq;

    strncpy(radio->state.rigport.pathname, serial_port, FILPATHLEN - 1);
    retcode = rig_open(radio);

    if (retcode != RIG_OK) {
        qDebug() << "rig_open: error = " + QString(rigerror(retcode));
        exit(2);
    }

    //get freg of selected vfo
    retcode = rig_get_freq(radio, RIG_VFO_CURR, &freq);

    rig_close(radio); /* close port */
    rig_cleanup(radio); /* if you care about memory */

    return freq;
}

QString rig_query::fetch_mode(RIG *radio, const char *serial_port)
{
    rmode_t mode;
    int retcode;
    pbwidth_t width;

    //Open rig connection
    strncpy(radio->state.rigport.pathname, serial_port, FILPATHLEN - 1);
    retcode = rig_open(radio);
    if (retcode != RIG_OK) {
        qDebug() << "rig_open: error = " + QString(rigerror(retcode));
        exit(2);
    }

    retcode = rig_get_mode(radio, RIG_VFO_CURR, &mode, &width);

    rig_close(radio); /* close port */
    rig_cleanup(radio); /* if you care about memory */

    return map_enum_to_str(mode);
}
/*
 * query rig for declared params and print it to stdout
 */
//void rig_query::fetch_rig_params(RIG* my_rig, const char* serial_port)
//{
//    freq_t freq; /* frequency */
//    rmode_t rmode; /* radio mode of operation */
//    pbwidth_t width;
//    int retcode; /* generic return code from functions */

//    //Open rig connection
//    strncpy(my_rig->state.rigport.pathname, serial_port, FILPATHLEN - 1);
//    retcode = rig_open(my_rig);
//    if (retcode != RIG_OK) {
//        printf("rig_open: error = %s\n", rigerror(retcode));
//        exit(2);
//    }
//    printf("Port %s opened ok\n", serial_port);

//    printf("\nGet various raw rig values:\n");

//    //get freg of selected vfo
//    retcode = rig_get_freq(my_rig, RIG_VFO_CURR, &freq);
//    if (retcode == RIG_OK ) {
//        printf("rig_get_freq: freq = %.2" PRIfreq"\n", freq);
//    } else {
//        printf("rig_get_freq: error = %s \n", rigerror(retcode));
//    }

//    //get current modulation
//    retcode = rig_get_mode(my_rig, RIG_VFO_CURR, &rmode, &width);
//    if (retcode == RIG_OK ) {
//        printf("rig_get_mode: mode = %s \n", map_enum_to_str(rmode));
//    } else {
//        printf("rig_get_mode: error = %s \n", rigerror(retcode));
//    }

//    rig_close(my_rig); /* close port */
//    rig_cleanup(my_rig); /* if you care about memory */
//    printf("port %s closed ok \n", serial_port);
//}
