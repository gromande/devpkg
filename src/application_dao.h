#ifndef APPLICATION_DAO_H
#define APPLICATION_DAO_H

#include "sqlite3.h"
#include "list.h"

typedef struct Application {
  char *name;
  char *url;
  char *location;
} Application;

sqlite3 *open_db();
Application *get_application(sqlite3 *db, char *name);
List *get_all_applications(sqlite3 *db);
int store_application(sqlite3 *db, Application *application);
int delete_application(sqlite3 *db, char *name);
int update_application(sqlite3 *db, Application *application);
int close_db(sqlite3 *db);
#endif
