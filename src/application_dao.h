#ifndef APPLICATION_DAO_H
#define APPLICATION_DAO_H

#include "sqlite3.h"

typedef struct Application {
  char *url;
  char *location;
} Application;

sqlite3 *open_db();
Application *get_application(char *url);
Application **get_all_applications();
int store_application(Application *application);
int remove_application(char *url);
int update_application(Application *application);
int close_db(sqlite3 *db);
#endif
