#ifndef MAIN_H
#define MAIN_H
#include "sqlite3.h"

extern char *zErrMsg;
extern int rc; // return code
extern sqlite3 *database;
extern const char *comando;
extern sqlite3_stmt *stmt;
extern const char *pzTest;
extern void log_query(string txt);
extern string orario();

#endif