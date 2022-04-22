/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#include "cb_fs.h"

#define FAKE_DIRECTORY "./fake_directory"
#define FAKE_FILE "./fake_directory/fake_file"
#define FAKE_FILE_REMOVE "./fake_directory/fake_file_remove"
#define FAKE_SUB_DIRECTORY "./fake_directory/fake_sub_directory"
#define FAKE_SUB_DIRECTORY_REMOVE "./fake_directory/fake_sub_directory_remove"
#define FAKE_SUB_FILE "./fake_directory/fake_sub_directory/fake_sub_file"

void init() {
  assert(cb_fs_mkdir(FAKE_DIRECTORY) == 0);
}

// rmdir: recursively
void destroy() {
  assert(cb_fs_rmdir(FAKE_DIRECTORY) == 0);
}

void test_cb_fs_mkdir() {
  assert(cb_fs_mkdir(FAKE_SUB_DIRECTORY) == 0);
  assert(cb_fs_mkdir(FAKE_SUB_DIRECTORY_REMOVE) == 0);
}

void test_cb_fs_touch() {
  assert(cb_fs_touch(FAKE_FILE) == 0);
  assert(cb_fs_touch(FAKE_SUB_FILE) == 0);
  assert(cb_fs_touch(FAKE_FILE_REMOVE) == 0);
}

void test_cb_fs_dir_exists() {
  assert(cb_fs_dir_exists(FAKE_DIRECTORY));
  assert(cb_fs_dir_exists(FAKE_SUB_DIRECTORY));
}

void test_cb_fs_file_exists() {
  assert(cb_fs_file_exists(FAKE_FILE));
  assert(cb_fs_file_exists(FAKE_SUB_FILE));
  assert(cb_fs_file_exists(FAKE_FILE_REMOVE));
}

void test_cb_fs_remove() {
  assert(cb_fs_remove(FAKE_FILE_REMOVE) == 0);
}

// rmdir: empty directory
void test_cb_fs_rmdir() {
  assert(cb_fs_rmdir(FAKE_SUB_DIRECTORY_REMOVE) == 0);
}

// TODO: criterion or cmocka
int main() {
  init();

  // TESTS
  test_cb_fs_mkdir();
  test_cb_fs_touch();
  test_cb_fs_dir_exists();
  test_cb_fs_file_exists();
  test_cb_fs_remove();
  test_cb_fs_rmdir();

  destroy();

  return EXIT_SUCCESS;
}
