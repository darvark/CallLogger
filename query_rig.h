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

/* inclusion guard */
#ifndef __QUERY_RIG_H__
#define __QUERY_RIG_H__

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <hamlib/rig.h>

RIG* init_rig(int rigType, const char* serial_port);
void fetch_rig_params (RIG* my_rig, const char* serial_port);
const char* map_enum_to_str(rmode_t rmode);

#endif /* __QUERY_RIG_H__ */
