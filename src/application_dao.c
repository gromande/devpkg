#include "application_dao.h"
#include "sqlite3.h"
#include "dbg.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>

#define DB_FILE               "data/devpkg.db"
#define GET_ALL_APPS_QUERY    "SELECT * FROM installed"
#define GET_APP_QUERY         "SELECT * FROM installed WHERE name='%s'"
#define INSERT_APP_QUERY      "INSERT INTO installed (name, url, location) VALUES ('%s', '%s', '%s')"
#define DELETE_APP_QUERY      "DELETE FROM installed WHERE name='%s'"
#define UPDATE_APP_QUERY      "UPDATE installed SET name='%s',url='%s',location='%s' WHERE name='%s'"

int execute_query(sqlite3 *db, char *query);

Application *create_application(Application *application, char **argv) {
  application->name = strdup(argv[0]);
  application->url = strdup(argv[1]);
  application->location = strdup(argv[2]);
  return application;
}

int process_single_row(void *input, int argc, char **argv, char **colName) {
  Application *application = input;
  application = create_application(application, argv);
  return 0;
}

int process_rows(void *input, int argc, char **argv, char **colName) {
  List *list = input;
  Application *application = malloc(sizeof(Application));
  application = create_application(application, argv);
  List_push(list, application);
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
  asprintf(&query, GET_APP_QUERY, name);
  if (sqlite3_exec(db, query, process_single_row, application, &errmsg) == SQLITE_OK) {
    free(query);
    return application;
  } else {
    log_err("Error getting application: %s", errmsg);
    free(query);
    sqlite3_free(errmsg);
    return NULL;
  }
}

List *get_all_applications(sqlite3 *db) {
  char *errmsg = NULL;
  List *applications = List_create();
  if (sqlite3_exec(db, GET_ALL_APPS_QUERY, process_rows, applications, &errmsg) == SQLITE_OK) {
    return applications;
  } else {
    log_err("Error getting all applications: %s", errmsg);
    sqlite3_free(errmsg);
    return NULL;
  }
}

int store_application(sqlite3 *db, Application *application) {
  char *query = NULL;
  asprintf(&query, INSERT_APP_QUERY, application->name, application->url, application->location);
  return execute_query(db, query);
}

int delete_application(sqlite3 *db, char *name) {
  char *query = NULL;
  asprintf(&query, DELETE_APP_QUERY, name);
  return execute_query(db, query);
}

int update_application(sqlite3 *db, Application *application) {
  char *query = NULL;
  asprintf(&query, UPDATE_APP_QUERY, application->name, application->url,
    application->location, application->name);
  return execute_query(db, query);
}

int execute_query(sqlite3 *db, char *query) {
  int rc;
  sqlite3_stmt *stmt;

  sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);
  rc = sqlite3_step(stmt);
  sqlite3_finalize(stmt);
  free(query);

  if (rc == SQLITE_DONE) {
    return 0;
  } else {
    log_err("Error executing query: %s", sqlite3_errmsg(db));
    return -1;
  }
}

int close_db(sqlite3 *db) {
  if (sqlite3_close(db) == SQLITE_OK) {
    return 0;
  } else {
    log_err("Error closing database: %s", sqlite3_errmsg(db));
    return -1;
  }
}
