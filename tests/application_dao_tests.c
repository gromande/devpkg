#include "minunit.h"
#include <application_dao.h>
#include <sqlite3.h>
#include <assert.h>

static sqlite3 *db = NULL;

char *test_open() {
  db = open_db();
  mu_assert(db != NULL, "Failed to open db");
  return NULL;
}

char *test_get_application() {
  Application *app = NULL;
  app = get_application(db, "appA");
  mu_assert(app != NULL, "Failed to get application");
  mu_assert(strcmp("appA",app->name) == 0, "Invalid application name");
  free(app);
  return NULL;
}

char *test_get_all_applications() {
  List *applications = NULL;
  applications = get_all_applications(db);
  mu_assert(applications != NULL, "Failed to get all applications");
  mu_assert(List_count(applications) > 0, "Invalid number of applications");
  List_clear_destroy(applications);
  return NULL;
}

char *test_store_application() {
  Application application;
  application.name = "Test App";
  application.url = "http://example.com/testapp";
  application.location = "/opt/testapp";

  int rc = store_application(db, &application);
  mu_assert(rc == 0, "Failed to store application");
  return NULL;
}

char *test_update_application() {
  Application application;
  application.name = "Test App";
  application.url = "http://example.com/testapp/something";
  application.location = "/otherlocation/testapp";

  int rc = update_application(db, &application);
  mu_assert(rc == 0, "Failed to update application");
  return NULL;
}

char *test_delete_application() {
  int rc = delete_application(db, "Test App");
  mu_assert(rc == 0, "Failed to delete application");
  return NULL;
}

char *test_close() {
  int ret;
  ret = close_db(db);
  mu_assert(ret == 0, "Failed to close db");
  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_open);
  mu_run_test(test_get_application);
  mu_run_test(test_get_all_applications);
  mu_run_test(test_store_application);
  mu_run_test(test_update_application);
  mu_run_test(test_delete_application);
  mu_run_test(test_close);

  return NULL;
}

RUN_TESTS(all_tests);
