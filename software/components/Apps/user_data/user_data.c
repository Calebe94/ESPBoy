/** @file user_data.c
 * 
 * @brief This file has the purpose to create the ESPBoy database.
 * which will store all the ESPBoy runtime data, such as Audio volume, username, wifi password and more.
 * @par       
 * COPYRIGHT NOTICE: (c) 2018 Barr Group.  All rights reserved.
 */ 
/*********************
 *      INCLUDES
 *********************/
#include <sys/unistd.h>
#include "sqlite3.h"
#include "sqlite3_conn.h"
#include "user_data.h"

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

/*!
 * @brief Creates and initialize the ESPBoy Database
 */
void user_data_init()
{
    unlink("/spiffs/test1.db");
    unlink("/spiffs/test2.db");

    sqlite3 *db1;
    sqlite3 *db2;
    int rc;

    if (db_open("/spiffs/test1.db", &db1))
        return;
    if (db_open("/spiffs/test2.db", &db2))
        return;

    rc = db_exec(db1, "CREATE TABLE test1 (id INTEGER, content);");
    if (rc != SQLITE_OK) {
        sqlite3_close(db1);
        sqlite3_close(db2);
        return;
    }
    rc = db_exec(db2, "CREATE TABLE test2 (id INTEGER, content);");
    if (rc != SQLITE_OK) {
        sqlite3_close(db1);
        sqlite3_close(db2);
        return;
    }

    rc = db_exec(db1, "INSERT INTO test1 VALUES (1, 'Hello, World from test1');");
    if (rc != SQLITE_OK) {
        sqlite3_close(db1);
        sqlite3_close(db2);
        return;
    }
    rc = db_exec(db2, "INSERT INTO test2 VALUES (1, 'Hello, World from test2');");
    if (rc != SQLITE_OK) {
        sqlite3_close(db1);
        sqlite3_close(db2);
        return;
    }

    rc = db_exec(db1, "SELECT * FROM test1");
    if (rc != SQLITE_OK) {
        sqlite3_close(db1);
        sqlite3_close(db2);
        return;
    }
    rc = db_exec(db2, "SELECT * FROM test2");
    if (rc != SQLITE_OK) {
        sqlite3_close(db1);
        sqlite3_close(db2);
        return;
    }

    sqlite3_close(db1);
    sqlite3_close(db2);
}