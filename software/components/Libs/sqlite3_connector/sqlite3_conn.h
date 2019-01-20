/** @file sqlite3_conn.h
 * 
 * @brief This module has the purpose to create a SQLite3 connector. 
 *
 * @par       
 * COPYRIGHT NOTICE: (c) 2018 Barr Group.  All rights reserved.
 */ 

#ifndef SQLITE3_CONN_H
#define SQLITE3_CONN_H

/**********
* INCLUDES
***********/
#include "sqlite3.h"

void db_init(void);

int db_open(const char *filename, sqlite3 **db);

int db_exec(sqlite3 *db, const char *sql);

#endif