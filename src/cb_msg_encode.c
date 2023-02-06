/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include "cb_msg.h"
#include "cb_msg_encode.h"
#include "cbor/cb_cbor_int.h"
#include "cbor/cb_cbor_string.h"

#include <stdio.h>
#include <string.h>

static size_t cb_msg_header(uint8_t *msg, size_t msg_size, uint64_t len,
                            uint64_t op_code) {
  uint64_t written = 0;
  written += cb_cbor_encode_uint64(len, msg, msg_size);
  written += cb_cbor_encode_uint64(op_code, msg + 9, msg_size);
  if (written != 18)
    return 0;
  return written;
}

static size_t cb_msg_encode(uint8_t *msg, size_t msg_size, uint64_t op_code,
                            char *db_name, size_t db_len, char *coll_name,
                            size_t coll_len, uint64_t old_value,
                            int old_positive, uint64_t new_value,
                            int new_positive) {
  uint64_t total_written = 18;
  uint64_t written = 0;

  if (op_code != 20) {
    total_written += written = cb_cbor_encode_string(
        db_name, db_len, msg + total_written, msg_size - total_written);
    if (written == 0)
      return 0;
  }

  if (2 < op_code && op_code < 20) {
    written = cb_cbor_encode_string(
        coll_name, coll_len, msg + total_written, msg_size - total_written);
    total_written += written;

    if (written == 0)
      return 0;
  }

  if (4 < op_code && op_code < 20) {
    total_written += written =
        (old_positive ? cb_cbor_encode_uint(old_value, msg + total_written,
                                            msg_size - total_written)
                      : cb_cbor_encode_negint(old_value, msg + total_written,
                                              msg_size - total_written));
    if (written == 0)
      return 0;
  }

  if (op_code == 7 || op_code == 8) {
    total_written += written =
        (new_positive ? cb_cbor_encode_uint(new_value, msg + total_written,
                                            msg_size - total_written)
                      : cb_cbor_encode_negint(new_value, msg + total_written,
                                              msg_size - total_written));
    if (written == 0)
      return 0;
  }

  written = cb_msg_header(msg, msg_size, total_written, op_code);
  if (written == 0)
    return 0;

  return total_written;
}

size_t cb_msg_encode_create_db(uint8_t *msg, size_t msg_size, char *db_name,
                        size_t db_len) {
  return cb_msg_encode(msg, msg_size, OP_CREATE_DB, db_name, db_len, NULL, 0, 0, 0, 0, 0);
}

size_t cb_msg_encode_drop_db(uint8_t *msg, size_t msg_size, char *db_name,
                      size_t db_len) {
  return cb_msg_encode(msg, msg_size, OP_DROP_DB, db_name, db_len, NULL, 0, 0, 0, 0, 0);
}

size_t cb_msg_encode_create_collection(uint8_t *msg, size_t msg_size, char *db_name,
                                size_t db_len, char *coll_name,
                                size_t coll_len) {
  return cb_msg_encode(msg, msg_size, OP_CREATE_COLLECTION, db_name, db_len, coll_name, coll_len,
                       0, 0, 0, 0);
}

size_t cb_msg_encode_drop_collection(uint8_t *msg, size_t msg_size, char *db_name,
                              size_t db_len, char *coll_name, size_t coll_len) {
  return cb_msg_encode(msg, msg_size, OP_DROP_COLLECTION, db_name, db_len, coll_name, coll_len,
                       0, 0, 0, 0);
}

size_t cb_msg_encode_insert_one(uint8_t *msg, size_t msg_size, char *db_name,
                         size_t db_len, char *coll_name, size_t coll_len,
                         uint64_t value, int positive) {
  return cb_msg_encode(msg, msg_size, OP_INSERT_ONE, db_name, db_len, coll_name, coll_len,
                       value, positive, 0, 0);
}

size_t cb_msg_encode_find_one(uint8_t *msg, size_t msg_size, char *db_name,
                       size_t db_len, char *coll_name, size_t coll_len,
                       uint64_t value, int positive) {
  return cb_msg_encode(msg, msg_size, OP_FIND_ONE, db_name, db_len, coll_name, coll_len,
                       value, positive, 0, 0);
}

size_t cb_msg_encode_update_one(uint8_t *msg, size_t msg_size, char *db_name,
                         size_t db_len, char *coll_name, size_t coll_len,
                         uint64_t old_value, int old_positive,
                         uint64_t new_value, int new_positive) {
  return cb_msg_encode(msg, msg_size, OP_UPDATE_ONE, db_name, db_len, coll_name, coll_len,
                       old_value, old_positive, new_value, new_positive);
}

size_t cb_msg_encode_update_all(uint8_t *msg, size_t msg_size, char *db_name,
                         size_t db_len, char *coll_name, size_t coll_len,
                         uint64_t old_value, int old_positive,
                         uint64_t new_value, int new_positive) {
  return cb_msg_encode(msg, msg_size, OP_UPDATE_ALL, db_name, db_len, coll_name, coll_len,
                       old_value, old_positive, new_value, new_positive);
}

size_t cb_msg_encode_delete_one(uint8_t *msg, size_t msg_size, char *db_name,
                         size_t db_len, char *coll_name, size_t coll_len,
                         uint64_t value, int positive) {
  return cb_msg_encode(msg, msg_size, OP_DELETE_ONE, db_name, db_len, coll_name, coll_len,
                       value, positive, 0, 0);
}

size_t cb_msg_encode_delete_all(uint8_t *msg, size_t msg_size, char *db_name,
                         size_t db_len, char *coll_name, size_t coll_len,
                         uint64_t value, int positive) {
  return cb_msg_encode(msg, msg_size, OP_DELETE_ALL, db_name, db_len, coll_name, coll_len,
                       value, positive, 0, 0);
}

size_t cb_msg_encode_list_databases(uint8_t *msg, size_t msg_size) {
  return cb_msg_encode(msg, msg_size, OP_LIST_DBS, NULL, 0, NULL, 0, 0, 0, 0, 0);
}

size_t cb_msg_encode_list_collections(uint8_t *msg, size_t msg_size, char *db_name,
                               size_t db_len) {
  return cb_msg_encode(msg, msg_size, OP_LIST_COLLECTIONS, db_name, db_len, NULL, 0, 0, 0, 0, 0);
}
