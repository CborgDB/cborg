/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#include "common/cb_fs.h"

#define FAKE_FILE_OPEN "./fake_file_open"
#define FAKE_DIRECTORY "./fake_directory"
#define FAKE_FILE "./fake_directory/fake_file"
#define FAKE_FILE_REMOVE "./fake_directory/fake_file_remove"
#define FAKE_SUB_DIRECTORY "./fake_directory/fake_sub_directory"
#define FAKE_SUB_DIRECTORY_REMOVE "./fake_directory/fake_sub_directory_remove"
#define FAKE_SUB_FILE "./fake_directory/fake_sub_directory/fake_sub_file"
#define FAKE_DBS_DIRECTORY "./fake_dbs_directory"
#define FAKE_DB_A_DIRECTORY "./fake_dbs_directory/db_a"
#define FAKE_DB_B_DIRECTORY "./fake_dbs_directory/db_b"
#define FAKE_COLLECTION_A_IN_DB_A "./fake_dbs_directory/db_a/coll_a"
#define FAKE_COLLECTION_B_IN_DB_A "./fake_dbs_directory/db_a/coll_b"

void init() {
  assert(cb_fs_mkdir(FAKE_DIRECTORY) == 0);

  // dbs and collections for ls_dir and ls_file
  assert(cb_fs_mkdir(FAKE_DBS_DIRECTORY) == 0);
  assert(cb_fs_mkdir(FAKE_DB_A_DIRECTORY) == 0);
  assert(cb_fs_mkdir(FAKE_DB_B_DIRECTORY) == 0);
  assert(cb_fs_touch(FAKE_COLLECTION_A_IN_DB_A) == 0);
  assert(cb_fs_touch(FAKE_COLLECTION_B_IN_DB_A) == 0);
}

// rmdir: recursively
void destroy() {
  assert(cb_fs_rmdir(FAKE_DIRECTORY) == 0);
  assert(cb_fs_rmdir(FAKE_DBS_DIRECTORY) == 0);
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

void test_cb_fs_open_close() {
  // test_cb_fs_open
  int fd = cb_fs_open(FAKE_FILE_OPEN);
  assert(fd != -1);
  assert(fcntl(fd, F_GETFD) != -1);
  
  // test_cb_fs_close
  close(fd);
  assert(fcntl(fd, F_GETFD) == -1);
}

void test_cb_fs_ls_dir() {
  char **list_dir;
  size_t list_size;

  cb_fs_ls_dir(".", &list_dir, &list_size);
  for(size_t i = 0; i <list_size; i++){
    printf("list_dir[%zu] = %s\n", i, list_dir[i]);
  }
  cb_fs_list_free(list_dir, list_size);
}

void test_cb_fs_ls_file() {
  char **list_files;
  size_t list_size;

  cb_fs_ls_file(".", &list_files, &list_size);
  for(size_t i = 0; i <list_size; i++){
    printf("list_files[%zu] = %s\n", i, list_files[i]);
  }
  cb_fs_list_free(list_files, list_size);

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
  test_cb_fs_open_close();
  test_cb_fs_ls_dir();
  test_cb_fs_ls_file();

  destroy();

  return EXIT_SUCCESS;
}
