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

#include "log_db.h"

const char* table = "CREATE TABLE IF NOT EXISTS qso(" \
        "callsign TEXT NOT NULL, " \
        "freq INTEGER NOT NULL, " \
        "mode TEXT NOT NULL, " \
        "date TEXT, " \
        "time TEXT, " \
        "rst_s INTEGER NOT NULL, " \
        "rst_r INTEGER NOT NULL, " \
        "exchange TEXT);";

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
   int i;
   (void) NotUsed;

   for(i = 0; i<argc; i++)
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   
   printf("\n");
   return EXIT_SUCCESS;
}


sqlite3* db_open_connection(const char* dbname)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    (void) zErrMsg;
    rc = sqlite3_open(dbname, &db);

    if(rc)
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));

    return db;
}

void close_db(sqlite3* db)
{
    sqlite3_close(db);
}

int create_database(const char* dbname)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    (void) zErrMsg;

    if (access(dbname, F_OK) != -1)
        printf("Database file already exist\n");

    else
    {
        rc = sqlite3_open(dbname, &db);

        if(rc)
        {
            fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            return EXIT_FAILURE;
        }
        else
        {
            fprintf(stderr, "Database created successfully\n");
            execute_query(table, db);
            fprintf(stderr, "Table structure created successfully\n");
        }
        sqlite3_close(db);
    }

    return EXIT_SUCCESS;
}

int insert_data(const char* dbname, char* callsign, float freq, char* mode,
                char* date, char* time, int rst_s, int rst_r, char* exchange)
{
    int rc;
    sqlite3_stmt *stmt;
    
    sqlite3* db = db_open_connection(dbname);
    const char* query = "INSERT INTO qso (callsign, freq, mode, date, time, rst_s, rst_r, exchange) " \
         "VALUES (?1, ?2, ?3, ?4, ?5, ?6, ?7, ?8);";
    const char *pzTest;
     
    rc = sqlite3_prepare(db, query, strlen(query), &stmt, &pzTest);

    if(rc == SQLITE_OK)
    {
        sqlite3_bind_text(stmt, 1, callsign, strlen(callsign), 0);
        sqlite3_bind_double(stmt, 2, freq);
        sqlite3_bind_text(stmt, 3, mode, strlen(mode), 0);
        sqlite3_bind_text(stmt, 4, date, strlen(date), 0); 
        sqlite3_bind_text(stmt, 5, time, strlen(time), 0);
        sqlite3_bind_int(stmt, 6, rst_s);
        sqlite3_bind_int(stmt, 7, rst_r); 
        sqlite3_bind_text(stmt, 8, exchange, strlen(exchange), 0);

        rc = sqlite3_step(stmt);
        sqlite3_reset(stmt);
    }
    else
    {
        printf("Failed to bind parameter: %s\n\r", sqlite3_errstr(rc));
        printf("Failed to bind parameter: %s\n\r", sqlite3_errmsg(db));
        sqlite3_close(db);
        return EXIT_FAILURE;
    }

    sqlite3_finalize(stmt);
    close_db(db);

    return EXIT_SUCCESS;
}

int execute_query(const char* sql, sqlite3 *db)
{
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if(rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    else
        fprintf(stdout, "Table created successfully\n");

    sqlite3_close(db);

    return 0;
}

