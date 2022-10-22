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
#include <string.h>

#include "common/cb_fs.h"
#include "common/cbor/cb_cbor_int.h"
#include "cb_ops.h"

int fd_uint;
int fd_negint;
int fd_int;

void init(){
  fd_uint = open("./uint.cb", O_RDWR | O_CREAT | O_TRUNC, 0644);
  assert(fd_uint > 0);
  fd_negint = open("./negint.cb", O_RDWR | O_CREAT | O_TRUNC, 0644);
  assert(fd_negint > 0);
  fd_int = open("./int.cb", O_RDWR | O_CREAT | O_TRUNC, 0644);
  assert(fd_int > 0);

  // databases
  cb_fs_mkdir("./databases");
}

void destroy() {
  cb_fs_close(fd_uint);
  cb_fs_close(fd_negint);
  cb_fs_close(fd_int);
  cb_fs_rmdir("./databases");
}

void test_cb_ops_insert_one() {
  // UINT8
  uint8_t ev_uint8[2];
  ssize_t ev_uint8_size;

  ev_uint8_size = cb_cbor_encode_uint8(23,ev_uint8,2);
  assert(cb_ops_insert_one(fd_uint, ev_uint8, ev_uint8_size) == 1);
  ev_uint8_size = cb_cbor_encode_uint8(255,ev_uint8,2);
  assert(cb_ops_insert_one(fd_uint, ev_uint8, ev_uint8_size) == 2);
  ev_uint8_size = cb_cbor_encode_uint8(0,ev_uint8,2);
  assert(cb_ops_insert_one(fd_uint, ev_uint8, ev_uint8_size) == 1);
  ev_uint8_size = cb_cbor_encode_uint8(24,ev_uint8,2);
  assert(cb_ops_insert_one(fd_uint, ev_uint8, ev_uint8_size) == 2);

  struct stat s_uint8;
  assert(fstat(fd_uint, &s_uint8) == 0);
  assert(s_uint8.st_size == 6);

  // NEGINT8
  uint8_t ev_negint8[2];
  ssize_t ev_negint8_size;

  ev_negint8_size = cb_cbor_encode_negint8(23,ev_negint8,2);
  assert(cb_ops_insert_one(fd_negint, ev_negint8, ev_negint8_size) == 1);
  ev_negint8_size = cb_cbor_encode_negint8(255,ev_negint8,2);
  assert(cb_ops_insert_one(fd_negint, ev_negint8, ev_negint8_size) == 2);
  ev_negint8_size = cb_cbor_encode_negint8(0,ev_negint8,2);
  assert(cb_ops_insert_one(fd_negint, ev_negint8, ev_negint8_size) == 1);
  ev_negint8_size = cb_cbor_encode_negint8(24,ev_negint8,2);
  assert(cb_ops_insert_one(fd_negint, ev_negint8, ev_negint8_size) == 2);

  struct stat s_negint8;
  assert(fstat(fd_negint, &s_negint8) == 0);
  assert(s_negint8.st_size == 6);

  // INT8
  uint8_t ev_int8[2];
  ssize_t ev_int8_size;

  ev_int8_size = cb_cbor_encode_uint8(23,ev_int8,2);
  assert(cb_ops_insert_one(fd_int, ev_int8, ev_int8_size) == 1);
  ev_int8_size = cb_cbor_encode_negint8(24,ev_int8,2);
  assert(cb_ops_insert_one(fd_int, ev_int8, ev_int8_size) == 2);
  ev_int8_size = cb_cbor_encode_uint8(255,ev_int8,2);
  assert(cb_ops_insert_one(fd_int, ev_int8, ev_int8_size) == 2);
  ev_int8_size = cb_cbor_encode_negint8(0,ev_int8,2);
  assert(cb_ops_insert_one(fd_int, ev_int8, ev_int8_size) == 1);
  ev_int8_size = cb_cbor_encode_uint8(0,ev_int8,2);
  assert(cb_ops_insert_one(fd_int, ev_int8, ev_int8_size) == 1);
  ev_int8_size = cb_cbor_encode_negint8(255,ev_int8,2);
  assert(cb_ops_insert_one(fd_int, ev_int8, ev_int8_size) == 2);
  ev_int8_size = cb_cbor_encode_uint8(24,ev_int8,2);
  assert(cb_ops_insert_one(fd_int, ev_int8, ev_int8_size) == 2);
  ev_int8_size = cb_cbor_encode_negint8(23,ev_int8,2);
  assert(cb_ops_insert_one(fd_int, ev_int8, ev_int8_size) == 1);

  struct stat s_int8;
  assert(fstat(fd_int, &s_int8) == 0);
  assert(s_int8.st_size == 12);
}

void test_cb_ops_find_one() {
    // UINT8
  uint8_t ev_uint8[2];
  ssize_t ev_uint8_size;

  ev_uint8_size = cb_cbor_encode_uint8(23,ev_uint8,2);
  assert(cb_ops_find_one(fd_uint, ev_uint8, ev_uint8_size,0) >= 0);
  ev_uint8_size = cb_cbor_encode_uint8(255,ev_uint8,2);
  assert(cb_ops_find_one(fd_uint, ev_uint8, ev_uint8_size,0) >= 0);
  ev_uint8_size = cb_cbor_encode_uint8(0,ev_uint8,2);
  assert(cb_ops_find_one(fd_uint, ev_uint8, ev_uint8_size,0) >= 0);
  ev_uint8_size = cb_cbor_encode_uint8(24,ev_uint8,2);
  assert(cb_ops_find_one(fd_uint, ev_uint8, ev_uint8_size,0) >= 0);
  // not found
  ev_uint8_size = cb_cbor_encode_uint8(15,ev_uint8,2);
  assert(cb_ops_find_one(fd_uint, ev_uint8, ev_uint8_size,0) == -2);
  ev_uint8_size = cb_cbor_encode_uint8(150,ev_uint8,2);
  assert(cb_ops_find_one(fd_uint, ev_uint8, ev_uint8_size,0) == -2);

  struct stat s_uint8;
  assert(fstat(fd_uint, &s_uint8) == 0);
  assert(s_uint8.st_size == 6);

  // NEGINT8
  uint8_t ev_negint8[2];
  ssize_t ev_negint8_size;

  ev_negint8_size = cb_cbor_encode_negint8(23,ev_negint8,2);
  assert(cb_ops_find_one(fd_negint, ev_negint8, ev_negint8_size,0) >= 0);
  ev_negint8_size = cb_cbor_encode_negint8(255,ev_negint8,2);
  assert(cb_ops_find_one(fd_negint, ev_negint8, ev_negint8_size,0) >= 0);
  ev_negint8_size = cb_cbor_encode_negint8(0,ev_negint8,2);
  assert(cb_ops_find_one(fd_negint, ev_negint8, ev_negint8_size,0) >= 0);
  ev_negint8_size = cb_cbor_encode_negint8(24,ev_negint8,2);
  assert(cb_ops_find_one(fd_negint, ev_negint8, ev_negint8_size,0) >= 0);
  // not found
  ev_negint8_size = cb_cbor_encode_negint8(15,ev_negint8,2);
  assert(cb_ops_find_one(fd_negint, ev_negint8, ev_negint8_size,0) == -2);
  ev_negint8_size = cb_cbor_encode_negint8(150,ev_negint8,2);
  assert(cb_ops_find_one(fd_negint, ev_negint8, ev_negint8_size,0) == -2);

  struct stat s_negint8;
  assert(fstat(fd_negint, &s_negint8) == 0);
  assert(s_negint8.st_size == 6);

  // INT8
  uint8_t ev_int8[2];
  ssize_t ev_int8_size;

  ev_int8_size = cb_cbor_encode_uint8(23,ev_int8,2);
  assert(cb_ops_find_one(fd_int, ev_int8, ev_int8_size,0) >= 0);
  ev_int8_size = cb_cbor_encode_negint8(24,ev_int8,2);
  assert(cb_ops_find_one(fd_int, ev_int8, ev_int8_size,0) >= 0);
  ev_int8_size = cb_cbor_encode_uint8(255,ev_int8,2);
  assert(cb_ops_find_one(fd_int, ev_int8, ev_int8_size,0) >= 0);
  ev_int8_size = cb_cbor_encode_negint8(0,ev_int8,2);
  assert(cb_ops_find_one(fd_int, ev_int8, ev_int8_size,0) >= 0);
  ev_int8_size = cb_cbor_encode_uint8(0,ev_int8,2);
  assert(cb_ops_find_one(fd_int, ev_int8, ev_int8_size,0) >= 0);
  ev_int8_size = cb_cbor_encode_negint8(255,ev_int8,2);
  assert(cb_ops_find_one(fd_int, ev_int8, ev_int8_size,0) >= 0);
  ev_int8_size = cb_cbor_encode_uint8(24,ev_int8,2);
  assert(cb_ops_find_one(fd_int, ev_int8, ev_int8_size,0) >= 0);
  ev_int8_size = cb_cbor_encode_negint8(23,ev_int8,2);
  assert(cb_ops_find_one(fd_int, ev_int8, ev_int8_size,0) >= 0);

  // not found
  ev_int8_size = cb_cbor_encode_negint8(15,ev_int8,2);
  assert(cb_ops_find_one(fd_int, ev_int8, ev_int8_size,0) == -2);
  ev_int8_size = cb_cbor_encode_negint8(150,ev_int8,2);
  assert(cb_ops_find_one(fd_int, ev_int8, ev_int8_size,0) == -2);
  ev_int8_size = cb_cbor_encode_uint8(15,ev_int8,2);
  assert(cb_ops_find_one(fd_int, ev_int8, ev_int8_size,0) == -2);
  ev_int8_size = cb_cbor_encode_uint8(150,ev_int8,2);
  assert(cb_ops_find_one(fd_int, ev_int8, ev_int8_size,0) == -2);

  struct stat s_int8;
  assert(fstat(fd_int, &s_int8) == 0);
  assert(s_int8.st_size == 12);

}

void test_cb_ops_update_one() {
    // UINT8
  uint8_t old_ev_uint8[2];
  ssize_t old_ev_uint8_size;
  uint8_t new_ev_uint8[2];
  ssize_t new_ev_uint8_size;
  struct stat s_uint8;

  old_ev_uint8_size = cb_cbor_encode_uint8(23,old_ev_uint8,2);
  new_ev_uint8_size = cb_cbor_encode_uint8(0,new_ev_uint8,2);
  assert(cb_ops_update_one(fd_uint, old_ev_uint8, old_ev_uint8_size, new_ev_uint8, new_ev_uint8_size, 0) > 0);
  assert(fstat(fd_uint, &s_uint8) == 0);
  assert(s_uint8.st_size == 6);

  old_ev_uint8_size = cb_cbor_encode_uint8(24,old_ev_uint8,2);
  new_ev_uint8_size = cb_cbor_encode_uint8(23,new_ev_uint8,2);
  assert(cb_ops_update_one(fd_uint, old_ev_uint8, old_ev_uint8_size, new_ev_uint8, new_ev_uint8_size, 0) > 0);
  assert(fstat(fd_uint, &s_uint8) == 0);
  assert(s_uint8.st_size == 5);
  
  old_ev_uint8_size = cb_cbor_encode_uint8(23,old_ev_uint8,2);
  new_ev_uint8_size = cb_cbor_encode_uint8(255,new_ev_uint8,2);
  assert(cb_ops_update_one(fd_uint, old_ev_uint8, old_ev_uint8_size, new_ev_uint8, new_ev_uint8_size, 0) > 0);
  assert(fstat(fd_uint, &s_uint8) == 0);
  assert(s_uint8.st_size == 6);
}

void test_cb_ops_update_all() {
  // UINT8
  uint8_t old_ev_uint8[2];
  ssize_t old_ev_uint8_size;
  uint8_t new_ev_uint8[2];
  ssize_t new_ev_uint8_size;
  struct stat s_uint8;

  old_ev_uint8_size = cb_cbor_encode_uint8(255,old_ev_uint8,2);
  new_ev_uint8_size = cb_cbor_encode_uint8(23,new_ev_uint8,2);
  assert(cb_ops_update_all(fd_uint, old_ev_uint8, old_ev_uint8_size, new_ev_uint8, new_ev_uint8_size, 0) != -1);
  assert(fstat(fd_uint, &s_uint8) == 0);
  assert(s_uint8.st_size == 4);

  old_ev_uint8_size = cb_cbor_encode_uint8(0,old_ev_uint8,2);
  new_ev_uint8_size = cb_cbor_encode_uint8(24,new_ev_uint8,2);
  assert(cb_ops_update_all(fd_uint, old_ev_uint8, old_ev_uint8_size, new_ev_uint8, new_ev_uint8_size, 0) != -1);
  assert(fstat(fd_uint, &s_uint8) == 0);
  assert(s_uint8.st_size == 6);
}

void test_cb_ops_delete_one() {
  // UINT8
  uint8_t ev_uint8[2];
  ssize_t ev_uint8_size;
  struct stat s_uint8;

  ev_uint8_size = cb_cbor_encode_uint8(23,ev_uint8,2);
  assert(cb_ops_delete_one(fd_uint, ev_uint8, ev_uint8_size) != -1);
  assert(fstat(fd_uint, &s_uint8) == 0);
  assert(s_uint8.st_size == 5);
}

void test_cb_ops_delete_all() {
  // UINT8
  uint8_t ev_uint8[2];
  ssize_t ev_uint8_size;
  struct stat s_uint8;

  ev_uint8_size = cb_cbor_encode_uint8(23,ev_uint8,2);
  assert(cb_ops_delete_all(fd_uint, ev_uint8, ev_uint8_size) != -1);
  assert(fstat(fd_uint, &s_uint8) == 0);
  assert(s_uint8.st_size == 4);
}

void test_cb_ops_create_db() {
  assert(cb_ops_create_db("cyborg") == 0);
  assert(cb_ops_create_db("droid") == 0);

  assert(cb_ops_create_db("cyborg") == -2);
  assert(cb_ops_create_db("droid") == -2);
}

void test_cb_ops_list_dbs() {
  char **list = NULL;
  size_t list_size = 0;
  assert(cb_ops_list_dbs(&list, &list_size) == 0);

  assert(list_size == 2);
  if(strcmp("cyborg", list[0]) == 0){
    assert(strcmp("cyborg", list[0]) == 0);
    assert(strcmp("droid", list[1]) == 0);
  } else {
    assert(strcmp("droid", list[0]) == 0);
    assert(strcmp("cyborg", list[1]) == 0);
  }
  cb_fs_list_free(list, list_size);
}

void test_cb_ops_create_collection() {
  assert(cb_ops_create_collection("cyborg","users") == 0);
  assert(cb_ops_create_collection("cyborg","others") == 0);

  assert(cb_ops_create_collection("cyborg","users") == -2);
  assert(cb_ops_create_collection("cyborg","others") == -2);
}

void test_cb_ops_list_collections() {
  char **list = NULL;
  size_t list_size = 0;
  assert(cb_ops_list_collections("cyborg", &list, &list_size) == 0);

  assert(list_size == 2);
  if(strcmp("users", list[0]) == 0){
    assert(strcmp("users", list[0]) == 0);
    assert(strcmp("others", list[1]) == 0);
  } else {
    assert(strcmp("others", list[0]) == 0);
    assert(strcmp("users", list[1]) == 0);
  }
  cb_fs_list_free(list, list_size);
}

void test_cb_ops_drop_collection() {
  assert(cb_ops_drop_collection("cyborg","users") == 0);
  assert(cb_ops_drop_collection("cyborg","others") == 0);

  assert(cb_ops_drop_collection("cyborg","users") == -2);
  assert(cb_ops_drop_collection("cyborg","others") == -2);
}

void test_cb_ops_drop_db() {
  assert(cb_ops_drop_db("cyborg") == 0);
  assert(cb_ops_drop_db("droid") == 0);

  assert(cb_ops_drop_db("cyborg") == -2);
  assert(cb_ops_drop_db("droid") == -2);
}

// TODO: criterion or cmocka
int main() {
  init();

  // TESTS
  test_cb_ops_insert_one();
  test_cb_ops_find_one();
  test_cb_ops_update_one();
  test_cb_ops_update_all();
  test_cb_ops_delete_one();
  test_cb_ops_delete_all();
  test_cb_ops_create_db();
  //test_cb_ops_list_dbs();
  test_cb_ops_create_collection();
  //test_cb_ops_list_collections();
  test_cb_ops_drop_collection();
  test_cb_ops_drop_db();

  destroy();

  return EXIT_SUCCESS;
}
