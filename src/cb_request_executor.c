/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifdef __linux__
#define _GNU_SOURCE
#include <linux/limits.h> // PATH_MAX
#endif


#include "common/cbor/cb_cbor.h"
#include "common/cbor/cb_cbor_int.h"
#include "common/cbor/cb_cbor_string.h"
#include "cb_msg.h"
#include "cb_request.h"
#include "cb_request_executor.h"
#include "cb_ops.h"
#include "common/cb_fs.h"

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <limits.h>

#define DATABASES_DIRECTORY "./databases"

/**
 * create_db
 * payload :
 *  - string db_name;
 */
void cb_request_execute_create_db(uint8_t *msg_payload, response_t *res) {
  char db_name[255] = {0};
  uint64_t db_name_len = 0;
  cb_cbor_get_string_length(msg_payload, &db_name_len);
  memcpy(db_name, msg_payload + cb_cbor_get_uint_size(msg_payload),
         db_name_len);
  db_name[db_name_len] = 0;
  int ret = cb_ops_create_db(db_name);

  if(ret == 0) {
    size_t written = cb_cbor_encode_string_definite("Database created.\n", 18, res->payload, 4096);
    res->msg_length = written + 18;
  } else if (ret == -2) {
    size_t written = cb_cbor_encode_string_definite("Database already exists.\n", 25, res->payload, 4096);
    res->msg_length = written + 18;
  } else if (ret == -1){
    size_t written = cb_cbor_encode_string_definite("Database cannot created.\n", 25, res->payload, 4096);
    res->msg_length = written + 18;
  }
}

/**
 * drop_db
 * payload :
 *  - string db_name;
 */
void cb_request_execute_drop_db(uint8_t *msg_payload, response_t *res) {
  char db_name[255] = {0};
  uint64_t db_name_len = 0;
  cb_cbor_get_string_length(msg_payload, &db_name_len);
  memcpy(db_name, msg_payload + cb_cbor_get_uint_size(msg_payload),
         db_name_len);
  db_name[db_name_len] = 0;
  int ret = cb_ops_drop_db(db_name);

  if(ret == 0) {
    size_t written = cb_cbor_encode_string_definite("Database deleted.\n", 18, res->payload, 4096);
    res->msg_length = written + 18;
  } else if (ret == -2) {
    size_t written = cb_cbor_encode_string_definite("Database not exists.\n", 21, res->payload, 4096);
    res->msg_length = written + 18;
  } else if (ret == -1){
    size_t written = cb_cbor_encode_string_definite("Database cannot deleted.\n", 25, res->payload, 4096);
    res->msg_length = written + 18;
  }
}

/**
 * create_collection
 * payload :
 *  - string db_name;
 *  - string collection_name;
 */
void cb_request_execute_create_collection(uint8_t *msg_payload, response_t *res) {
  char db_name[255] = {0};
  uint64_t db_name_len = 0;
  char coll_name[255] = {0};
  uint64_t coll_name_len = 0;
  cb_cbor_get_string_length(msg_payload, &db_name_len);
  memcpy(db_name, msg_payload + cb_cbor_get_uint_size(msg_payload),
         db_name_len);
  db_name[db_name_len] = 0;

  uint8_t *p_coll =
      msg_payload + cb_cbor_get_uint_size(msg_payload) + db_name_len;
  cb_cbor_get_string_length(p_coll, &coll_name_len);
  memcpy(coll_name, p_coll + cb_cbor_get_uint_size(p_coll), coll_name_len);
  coll_name[coll_name_len] = 0;
  int ret = cb_ops_create_collection(db_name, coll_name);

  if(ret == 0) {
    size_t written = cb_cbor_encode_string_definite("Collection created.\n", 20, res->payload, 4096);
    res->msg_length = written + 18;
  } else if (ret == -1) {
    size_t written = cb_cbor_encode_string_definite("Collection already exists.\n", 27, res->payload, 4096);
    res->msg_length = written + 18;
  } else if (ret == -2){
    size_t written = cb_cbor_encode_string_definite("Collection cannot created.\n", 27, res->payload, 4096);
    res->msg_length = written + 18;
  }
}

/**
 * drop_collection
 * payload :
 *  - string db_name;
 *  - string collection_name;
 */
void cb_request_execute_drop_collection(uint8_t *msg_payload, response_t *res) {
  char db_name[255] = {0};
  uint64_t db_name_len = 0;
  char coll_name[255] = {0};
  uint64_t coll_name_len = 0;
  cb_cbor_get_string_length(msg_payload, &db_name_len);
  memcpy(db_name, msg_payload + cb_cbor_get_uint_size(msg_payload),
         db_name_len);
  db_name[db_name_len] = 0;

  uint8_t *p_coll =
      msg_payload + cb_cbor_get_uint_size(msg_payload) + db_name_len;
  cb_cbor_get_string_length(p_coll, &coll_name_len);
  memcpy(coll_name, p_coll + cb_cbor_get_uint_size(p_coll), coll_name_len);
  coll_name[coll_name_len] = 0;

  int ret = cb_ops_drop_collection(db_name, coll_name);

  if(ret == 0) {
    size_t written = cb_cbor_encode_string_definite("Collection deleted.\n", 20, res->payload, 4096);
    res->msg_length = written + 18;
  } else if (ret == -1) {
    size_t written = cb_cbor_encode_string_definite("Collection not exists.\n", 23, res->payload, 4096);
    res->msg_length = written + 18;
  } else if (ret == -2){
    size_t written = cb_cbor_encode_string_definite("Collection cannot deleted.\n", 27, res->payload, 4096);
    res->msg_length = written + 18;
  }
}

/**
 * insert_one
 * payload :
 *  - string db_name
 *  - string collection_name;
 *  - item
 */
void cb_request_execute_insert_one(uint8_t *msg_payload, response_t *res) {
  char db_name[255] = {0};
  uint64_t db_name_len = 0;
  char coll_name[255] = {0};
  uint64_t coll_name_len = 0;
  cb_cbor_get_string_length(msg_payload, &db_name_len);
  memcpy(db_name, msg_payload + cb_cbor_get_uint_size(msg_payload),
         db_name_len);
  db_name[db_name_len] = 0;

  uint8_t *p_coll =
      msg_payload + cb_cbor_get_uint_size(msg_payload) + db_name_len;
  cb_cbor_get_string_length(p_coll, &coll_name_len);
  memcpy(coll_name, p_coll + cb_cbor_get_uint_size(p_coll), coll_name_len);
  coll_name[coll_name_len] = 0;

  uint8_t *p_item = p_coll + cb_cbor_get_uint_size(p_coll) + coll_name_len;
  char full_path[PATH_MAX + 1];
  snprintf(full_path, sizeof(full_path), "%s/%s/%s", DATABASES_DIRECTORY,
           db_name, coll_name);
  int fd_temp = cb_fs_open(full_path);
  int ret = cb_ops_insert_one(fd_temp, p_item, cb_cbor_get_uint_size(p_item));

  if(ret > 0) {
    size_t written = cb_cbor_encode_string_definite("Item inserted.\n", 15, res->payload, 4096);
    res->msg_length = written + 18;
  } else {
    size_t written = cb_cbor_encode_string_definite("An error has occurred.\n", 23, res->payload, 4096);
    res->msg_length = written + 18;
  }

  cb_fs_close(fd_temp);
}

/**
 * find_one
 * payload :
 *  - string db_name
 *  - string collection_name;
 *  - item
 */
void cb_request_execute_find_one(uint8_t *msg_payload, response_t *res) {
  char db_name[255] = {0};
  uint64_t db_name_len = 0;
  char coll_name[255] = {0};
  uint64_t coll_name_len = 0;
  cb_cbor_get_string_length(msg_payload, &db_name_len);
  memcpy(db_name, msg_payload + cb_cbor_get_uint_size(msg_payload),
         db_name_len);
  db_name[db_name_len] = 0;

  uint8_t *p_coll =
      msg_payload + cb_cbor_get_uint_size(msg_payload) + db_name_len;
  cb_cbor_get_string_length(p_coll, &coll_name_len);
  memcpy(coll_name, p_coll + cb_cbor_get_uint_size(p_coll), coll_name_len);
  coll_name[coll_name_len] = 0;

  uint8_t *p_item = p_coll + cb_cbor_get_uint_size(p_coll) + coll_name_len;
  char full_path[PATH_MAX + 1];
  snprintf(full_path, sizeof(full_path), "%s/%s/%s", DATABASES_DIRECTORY,
           db_name, coll_name);
  int fd_temp = cb_fs_open(full_path);
  int ret = cb_ops_find_one(fd_temp, p_item, cb_cbor_get_uint_size(p_item), 0);

  if(ret >= 0) {
    size_t written = cb_cbor_encode_string_definite("Item found.\n", 12, res->payload, 4096);
    res->msg_length = written + 18;
  } else if(ret == -2){
    size_t written = cb_cbor_encode_string_definite("Item not found.\n", 16, res->payload, 4096);
    res->msg_length = written + 18;
  } else if(ret == -1){
    size_t written = cb_cbor_encode_string_definite("An error has occurred.\n", 23, res->payload, 4096);
    res->msg_length = written + 18;
  }

  cb_fs_close(fd_temp);
}

/**
 * update_one
 * payload :
 *  - string db_name
 *  - string collection_name;
 *  - old item
 *  - new item
 */
void cb_request_execute_update_one(uint8_t *msg_payload, response_t *res) {
  char db_name[255] = {0};
  uint64_t db_name_len = 0;
  char coll_name[255] = {0};
  uint64_t coll_name_len = 0;
  cb_cbor_get_string_length(msg_payload, &db_name_len);
  memcpy(db_name, msg_payload + cb_cbor_get_uint_size(msg_payload),
         db_name_len);
  db_name[db_name_len] = 0;

  uint8_t *p_coll =
      msg_payload + cb_cbor_get_uint_size(msg_payload) + db_name_len;
  cb_cbor_get_string_length(p_coll, &coll_name_len);
  memcpy(coll_name, p_coll + cb_cbor_get_uint_size(p_coll), coll_name_len);
  coll_name[coll_name_len] = 0;

  uint8_t *p_item1 = p_coll + cb_cbor_get_uint_size(p_coll) + coll_name_len;
  uint8_t *p_item2 = p_item1 + cb_cbor_get_uint_size(p_coll);

  char full_path[PATH_MAX + 1];
  snprintf(full_path, sizeof(full_path), "%s/%s/%s", DATABASES_DIRECTORY,
           db_name, coll_name);
  int fd_temp = cb_fs_open(full_path);
  int ret = cb_ops_update_one(fd_temp, p_item1, cb_cbor_get_uint_size(p_item1), p_item2, cb_cbor_get_uint_size(p_item2), 0);

  if(ret > 0) {
    size_t written = cb_cbor_encode_string_definite("Item updated.\n", 14, res->payload, 4096);
    res->msg_length = written + 18;
  } else if(ret == -2){
    size_t written = cb_cbor_encode_string_definite("Item not found.\n", 16, res->payload, 4096);
    res->msg_length = written + 18;
  } else if(ret == -1){
    size_t written = cb_cbor_encode_string_definite("An error has occurred.\n", 23, res->payload, 4096);
    res->msg_length = written + 18;
  }

  cb_fs_close(fd_temp);
}

/**
 * update_all
 * payload :
 *  - string db_name
 *  - string collection_name;
 *  - old item
 *  - new item
 */
void cb_request_execute_update_all(uint8_t *msg_payload, response_t *res) {
    char db_name[255] = {0};
  uint64_t db_name_len = 0;
  char coll_name[255] = {0};
  uint64_t coll_name_len = 0;
  cb_cbor_get_string_length(msg_payload, &db_name_len);
  memcpy(db_name, msg_payload + cb_cbor_get_uint_size(msg_payload),
         db_name_len);
  db_name[db_name_len] = 0;

  uint8_t *p_coll =
      msg_payload + cb_cbor_get_uint_size(msg_payload) + db_name_len;
  cb_cbor_get_string_length(p_coll, &coll_name_len);
  memcpy(coll_name, p_coll + cb_cbor_get_uint_size(p_coll), coll_name_len);
  coll_name[coll_name_len] = 0;

  uint8_t *p_item1 = p_coll + cb_cbor_get_uint_size(p_coll) + coll_name_len;
  uint8_t *p_item2 = p_item1 + cb_cbor_get_uint_size(p_coll);

  char full_path[PATH_MAX + 1];
  snprintf(full_path, sizeof(full_path), "%s/%s/%s", DATABASES_DIRECTORY,
           db_name, coll_name);
  int fd_temp = cb_fs_open(full_path);
  int ret = cb_ops_update_all(fd_temp, p_item1, cb_cbor_get_uint_size(p_item1), p_item2, cb_cbor_get_uint_size(p_item2), 0);

  if(ret > 0) {
    size_t written = cb_cbor_encode_string_definite("Items updated.\n", 14, res->payload, 4096);
    res->msg_length = written + 18;
  } else if(ret == -2){
    size_t written = cb_cbor_encode_string_definite("Item not found.\n", 16, res->payload, 4096);
    res->msg_length = written + 18;
  } else if(ret == -1){
    size_t written = cb_cbor_encode_string_definite("An error has occurred.\n", 23, res->payload, 4096);
    res->msg_length = written + 18;
  }

  cb_fs_close(fd_temp);
}

/**
 * delete_one
 * payload :
 *  - string db_name
 *  - string collection_name;
 *  - item
 */
void cb_request_execute_delete_one(uint8_t *msg_payload, response_t *res) {
  char db_name[255] = {0};
  uint64_t db_name_len = 0;
  char coll_name[255] = {0};
  uint64_t coll_name_len = 0;
  cb_cbor_get_string_length(msg_payload, &db_name_len);
  memcpy(db_name, msg_payload + cb_cbor_get_uint_size(msg_payload),
         db_name_len);
  db_name[db_name_len] = 0;

  uint8_t *p_coll =
      msg_payload + cb_cbor_get_uint_size(msg_payload) + db_name_len;
  cb_cbor_get_string_length(p_coll, &coll_name_len);
  memcpy(coll_name, p_coll + cb_cbor_get_uint_size(p_coll), coll_name_len);
  coll_name[coll_name_len] = 0;

  uint8_t *p_item = p_coll + cb_cbor_get_uint_size(p_coll) + coll_name_len;
  char full_path[PATH_MAX + 1];
  snprintf(full_path, sizeof(full_path), "%s/%s/%s", DATABASES_DIRECTORY,
           db_name, coll_name);
  int fd_temp = cb_fs_open(full_path);
  int ret = cb_ops_delete_one(fd_temp, p_item, cb_cbor_get_uint_size(p_item));

  if(ret > 0) {
    size_t written = cb_cbor_encode_string_definite("Item deleted.\n", 14, res->payload, 4096);
    res->msg_length = written + 18;
  } else if(ret == -2){
    size_t written = cb_cbor_encode_string_definite("Item not found.\n", 16, res->payload, 4096);
    res->msg_length = written + 18;
  } else if(ret == -1){
    size_t written = cb_cbor_encode_string_definite("An error has occurred.\n", 23, res->payload, 4096);
    res->msg_length = written + 18;
  }

  cb_fs_close(fd_temp);
}

/**
 * delete_all
 * payload :
 *  - string db_name
 *  - string collection_name;
 *  - item
 */
void cb_request_execute_delete_all(uint8_t *msg_payload, response_t *res) {
  char db_name[255] = {0};
  uint64_t db_name_len = 0;
  char coll_name[255] = {0};
  uint64_t coll_name_len = 0;
  cb_cbor_get_string_length(msg_payload, &db_name_len);
  memcpy(db_name, msg_payload + cb_cbor_get_uint_size(msg_payload),
         db_name_len);
  db_name[db_name_len] = 0;

  uint8_t *p_coll =
      msg_payload + cb_cbor_get_uint_size(msg_payload) + db_name_len;
  cb_cbor_get_string_length(p_coll, &coll_name_len);
  memcpy(coll_name, p_coll + cb_cbor_get_uint_size(p_coll), coll_name_len);
  coll_name[coll_name_len] = 0;

  uint8_t *p_item = p_coll + cb_cbor_get_uint_size(p_coll) + coll_name_len;
  char full_path[PATH_MAX + 1];
  snprintf(full_path, sizeof(full_path), "%s/%s/%s", DATABASES_DIRECTORY,
           db_name, coll_name);
  int fd_temp = cb_fs_open(full_path);
  int ret = cb_ops_delete_all(fd_temp, p_item, cb_cbor_get_uint_size(p_item));

  if(ret > 0) {
    size_t written = cb_cbor_encode_string_definite("Items deleted.\n", 15, res->payload, 4096);
    res->msg_length = written + 18;
  } else if(ret == -2){
    size_t written = cb_cbor_encode_string_definite("Item not found.\n", 16, res->payload, 4096);
    res->msg_length = written + 18;
  } else if(ret == -1){
    size_t written = cb_cbor_encode_string_definite("An error has occurred.\n", 23, res->payload, 4096);
    res->msg_length = written + 18;
  }

  cb_fs_close(fd_temp);
}

/**
 * list dbs
 */
void cb_request_execute_list_dbs(uint8_t *msg_payload, response_t *res) {
  char **list = NULL;
  size_t list_size = 0;

  int ret = cb_ops_list_dbs(&list, &list_size);

  if(ret == 0){
    res->msg_length = 0;
    for(size_t i = 0; i < list_size; i++){
      size_t written = cb_cbor_encode_string_definite(list[i], strlen(list[i]), res->payload + res->msg_length, 4096 - res->msg_length);
      res->msg_length += written;
    }
    res->msg_length += 18;
  } else {
    size_t written = cb_cbor_encode_string_definite("An error has occurred.\n", 23, res->payload, 4096);
    res->msg_length = written + 18;
  }
  cb_fs_list_free(list, list_size);
}

/**
 * list collections
 * payload:
 *  - string db_name
 */
void cb_request_execute_list_collections(uint8_t *msg_payload, response_t *res) {
  char db_name[255] = {0};
  uint64_t db_name_len = 0;
  cb_cbor_get_string_length(msg_payload, &db_name_len);
  memcpy(db_name, msg_payload + cb_cbor_get_uint_size(msg_payload),
         db_name_len);
  db_name[db_name_len] = 0;

  char **list = NULL;
  size_t list_size = 0;

  int ret = cb_ops_list_collections(db_name, &list, &list_size);

  if(ret == 0){
    res->msg_length = 0;
    for(size_t i = 0; i < list_size; i++){
      size_t written = cb_cbor_encode_string_definite(list[i], strlen(list[i]), res->payload + res->msg_length, 4096 - res->msg_length);
      res->msg_length += written;
    }
    res->msg_length += 18;
  } else {
    size_t written = cb_cbor_encode_string_definite("An error has occurred.\n", 23, res->payload, 4096);
    res->msg_length = written + 18;
  }
  cb_fs_list_free(list, list_size);
}

void cb_request_executor(request_t *req, response_t *res) {
  switch (req->op_code) {
  case OP_CREATE_DB:
    cb_request_execute_create_db(req->payload, res);
    break;
  case OP_DROP_DB:
    cb_request_execute_drop_db(req->payload, res);
    break;
  case OP_CREATE_COLLECTION:
    cb_request_execute_create_collection(req->payload, res);
    break;
  case OP_DROP_COLLECTION:
    cb_request_execute_drop_collection(req->payload, res);
    break;
  case OP_INSERT_ONE:
    cb_request_execute_insert_one(req->payload, res);
    break;
  case OP_FIND_ONE:
    cb_request_execute_find_one(req->payload, res);
    break;
  case OP_UPDATE_ONE:
    cb_request_execute_update_one(req->payload, res);
    break;
  case OP_UPDATE_ALL:
    cb_request_execute_update_all(req->payload, res);
    break;
  case OP_DELETE_ONE:
    cb_request_execute_delete_one(req->payload, res);
    break;
  case OP_DELETE_ALL:
    cb_request_execute_delete_all(req->payload, res);
    break;
  case OP_LIST_DBS:
    cb_request_execute_list_dbs(req->payload, res);
    break;
  case OP_LIST_COLLECTIONS:
    cb_request_execute_list_collections(req->payload, res);
    break;
  default: {
    size_t written = cb_cbor_encode_string_definite("Unknown op_code.\n", 17,
                                                  res->payload, 4096);
    res->msg_length = written + 18;
  } break;
  }
}
