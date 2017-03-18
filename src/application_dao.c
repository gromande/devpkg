#include "application_dao.h"
#include "sqlite3.h"
#include "dbg.h"
#include <stdlib.h>

#define DB_FILE "data/devpkg.db"

sqlite3 *open_db() {
  sqlite3 *db;
	if(sqlite3_open(DB_FILE, &db) == SQLITE_OK) {
    return db;
  } else {
    log_err("Error opening database", sqlite3_errmsg(db));
    return NULL;
  }
}

Application *get_application(char *url) {
  return NULL;
}

Application **get_all_applications() {
  return NULL;
}

int store_application(Application *application) {
  return -1;
}

int remove_application(char *url) {
  return -1;
}

int update_application(Application *application) {
  return -1;
}

int close_db(sqlite3 *db) {
  if(sqlite3_close(db) == SQLITE_OK) {
    return 0;
  } else {
    log_err("Error closing database", sqlite3_errmsg(db));
    return -1;
  }
}
