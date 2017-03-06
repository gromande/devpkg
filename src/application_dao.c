#include "application_dao.h"
#include "sqlite3.h"
#include "dbg.h"
#include <stdlib.h>

#define DB_FILE "../data/devpkg.db"

sqlite3 *open_db() {
  sqlite3 *db;
	sqlite3_open(DB_FILE, &db);
  check_mem(db);
  return db;
error:
  exit(EXIT_FAILURE);
}

Application *get_application(char *url) {
  return NULL;
}

Application **get_all_applications() {
  return NULL;
}

void store_application(Application *application) {

}

void remove_application(char *url) {

}

void update_application(Application *application) {

}

void close_db(sqlite3 *db) {
  check_mem(db);
  sqlite3_close(db);
error:
  exit(EXIT_FAILURE);
}
