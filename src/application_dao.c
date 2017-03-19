#include "application_dao.h"
#include "sqlite3.h"
#include "dbg.h"
#include <stdlib.h>
#include <string.h>

#define DB_FILE               "data/devpkg.db"
#define GET_ALL_APPS_QUERY    "SELECT * FROM installed"
#define GET_APP_QUERY         "SELECT * FROM installed WHERE name='%s'"
#define INSERT_APP_QUERY      "INSERT INTO installed (name, url, location) VALUES ('%s', '%s', '%s')"
#define DELETE_APP_QUERY      "DELETE FROM installed WHERE name='%s'"
#define UPDATE_APP_QUERY      "UPDATE installed SET name='%s',url='%s',location='%s' WHERE name='%s'"

int callback(void *input, int argc, char **argv, char **colName) {
    Application *app = (Application *) input;
    app->name = strdup(argv[0]);
    app->url = strdup(argv[1]);
    app->location = strdup(argv[2]);
    return 0;
}

sqlite3 *open_db() {
  sqlite3 *db;
	if (sqlite3_open(DB_FILE, &db) == SQLITE_OK) {
    return db;
  } else {
    log_err("Error opening database: %s", sqlite3_errmsg(db));
    return NULL;
  }
}

Application *get_application(sqlite3 *db, char *name) {
  char *query;
  char *errmsg;
  Application *application = malloc(sizeof(Application));
  int rc;
  asprintf(&query, GET_APP_QUERY, name);
  if (sqlite3_exec(db, query, callback, application, &errmsg) == SQLITE_OK) {
    return application;
  } else {
    log_err("Error getting application", errmsg);
    sqlite3_free(errmsg);
    return NULL;
  }
}

Application **get_all_applications(sqlite3 *db) {
  char *errmsg = NULL;
  int rc;
  log_err("query: %s", GET_ALL_APPS_QUERY);
  if (sqlite3_exec(db, GET_ALL_APPS_QUERY, callback, NULL, &errmsg) == SQLITE_OK) {
    return NULL;
  } else {
    log_err("Error getting all applications", errmsg);
    sqlite3_free(errmsg);
    return NULL;
  }
}

int store_application(sqlite3 *db, Application *application) {
  return -1;
}

int remove_application(sqlite3 *db, char *name) {
  return -1;
}

int update_application(sqlite3 *db, Application *application) {
  return -1;
}

int close_db(sqlite3 *db) {
  if (sqlite3_close(db) == SQLITE_OK) {
    return 0;
  } else {
    log_err("Error closing database", sqlite3_errmsg(db));
    return -1;
  }
}
