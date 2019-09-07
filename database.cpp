#include "database.h"

database::database()
{

}

const char* database::qstrTocstr(QString* s)
{
    return s->toStdString().c_str();
}
static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
   int i;
   (void) NotUsed;

   for(i = 0; i<argc; i++)
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

   printf("\n");
   return EXIT_SUCCESS;
}


sqlite3* database::db_open_connection(QString& dbname)
{
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    (void) zErrMsg;
    rc = sqlite3_open(qstrTocstr(&dbname), &db);

    if(rc)
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));

    return db;
}

void database::close_db(sqlite3* db)
{
    sqlite3_close(db);
}

int database::create_database(QString& dbname)
{
    sqlite3 *db;
    char *zErrMsg = nullptr;
    int rc;

    (void) zErrMsg;

    if (QFile::exists(dbname))
        printf("Database file already exist\n");

    else
    {
        rc = sqlite3_open(qstrTocstr(&dbname), &db);

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

int database::insert_data(QString& dbname, QString& callsign, float freq, QString& mode,
                QString& date, QString& time, int rst_s, int rst_r, QString& exchange)
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
        sqlite3_bind_text(stmt, 1, qstrTocstr(&callsign), callsign.length(), nullptr);
        sqlite3_bind_double(stmt, 2, freq);
        sqlite3_bind_text(stmt, 3, qstrTocstr(&mode), mode.length(), nullptr);
        sqlite3_bind_text(stmt, 4, qstrTocstr(&date), date.length(), nullptr);
        sqlite3_bind_text(stmt, 5, qstrTocstr(&time), time.length(), nullptr);
        sqlite3_bind_int(stmt, 6, rst_s);
        sqlite3_bind_int(stmt, 7, rst_r);
        sqlite3_bind_text(stmt, 8, qstrTocstr(&exchange), exchange.length(), nullptr);

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

int database::execute_query(QString& sql, sqlite3 *db)
{
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_exec(db, qstrTocstr(&sql), callback, nullptr, &zErrMsg);

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
