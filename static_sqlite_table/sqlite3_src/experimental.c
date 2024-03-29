/*
** 2005 January 20
**
** The author disclaims copyright to this source code.  In place of
** a legal notice, here is a blessing:
**
**    May you do good and not evil.
**    May you find forgiveness for yourself and forgive others.
**    May you share freely, never taking more than you give.
**
*************************************************************************
** This file contains C code routines that are not a part of the official
** SQLite API.  These routines are unsupported.
**
** $Id: experimental.c,v 1.2 2005/04/29 04:26:02 tabuleiro Exp $
*/
#include "sqliteInt.h"

/*
** Set all the parameters in the compiled SQL statement to NULL.
*/
int sqlite3_clear_bindings(sqlite3_stmt *pStmt){
  int i;
  int rc = SQLITE_OK;
  for(i=1; rc==SQLITE_OK && i<=sqlite3_bind_parameter_count(pStmt); i++){
    rc = sqlite3_bind_null(pStmt, i);
  }
  return rc;
}

/*
** Sleep for a little while.  Return the amount of time slept.
*/
int sqlite3_sleep(int ms){
  return sqlite3OsSleep(ms);
}
