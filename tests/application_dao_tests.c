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

char *test_close() {
  int ret;
  ret = close_db(db);
  mu_assert(ret == 0, "Failed to close db");
  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_open);
  mu_run_test(test_close);

  return NULL;
}

RUN_TESTS(all_tests);
