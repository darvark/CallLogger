#ifndef RIG_H
#define RIG_H

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <hamlib/rig.h>

class rig_query
{
public:
    rig_query();


    RIG* init_rig(int rigType, const char* serial_port);
    void fetch_rig_params (RIG* my_rig, const char* serial_port);
    const char* map_enum_to_str(rmode_t rmode);
};

#endif // RIG_H
