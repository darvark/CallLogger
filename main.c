/*
 * Copyright 2019 <copyright holder> <email>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "query_rig.h"
#include "log_db.h"

int main(int argc, char** argv)
{
    (void) argc;
    (void) argv;
    RIG* r = init_rig(228, "/dev/ttyUSB0");
    fetch_rig_params(r, "/dev/ttyUSB0");

    
    create_database("test.db");
    sqlite3* d = db_open_connection("test.db");
    insert_data("test.db", "SP6MI", 14.200, "SSB", "2019-09-01", "12:04", 59, 59, "15");
    
    return 0;
}
