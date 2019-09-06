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
#ifndef __LOG_DB_H__
#define __LOG_DB_H__

#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int create_database(const char* dbname);
sqlite3 *db_open_connection(const char* dbname);
void close_db(sqlite3* db);
int execute_query(const char* sql, sqlite3 *db);
int insert_data(const char* dbname, char* callsign, float freq,
                char* mode, char* date, char* time,
                int rst_s, int rst_r, char* exchange);

#endif /* __LOG_DB_H__ */
