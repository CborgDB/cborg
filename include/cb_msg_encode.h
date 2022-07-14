/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifndef _CB_MSG_ENCODE_H
#define _CB_MSG_ENCODE_H

#include <stdint.h>
#include <stddef.h>

size_t cb_msg_encode_create_db(uint8_t *msg, size_t msg_size, char *db_name,
                        size_t db_len);

size_t cb_msg_encode_drop_db(uint8_t *msg, size_t msg_size, char *db_name,
                      size_t db_len);

size_t cb_msg_encode_create_collection(uint8_t *msg, size_t msg_size, char *db_name,
                                size_t db_len, char *coll_name,
                                size_t coll_len);

size_t cb_msg_encode_drop_collection(uint8_t *msg, size_t msg_size, char *db_name,
                              size_t db_len, char *coll_name, size_t coll_len);

size_t cb_msg_encode_insert_one(uint8_t *msg, size_t msg_size, char *db_name,
                         size_t db_len, char *coll_name, size_t coll_len,
                         uint64_t value, int positive);

size_t cb_msg_encode_find_one(uint8_t *msg, size_t msg_size, char *db_name,
                       size_t db_len, char *coll_name, size_t coll_len,
                       uint64_t value, int positive);

size_t cb_msg_encode_update_one(uint8_t *msg, size_t msg_size, char *db_name,
                         size_t db_len, char *coll_name, size_t coll_len,
                         uint64_t old_value, int old_positive,
                         uint64_t new_value, int new_positive);

size_t cb_msg_encode_update_all(uint8_t *msg, size_t msg_size, char *db_name,
                         size_t db_len, char *coll_name, size_t coll_len,
                         uint64_t old_value, int old_positive,
                         uint64_t new_value, int new_positive);

size_t cb_msg_encode_delete_one(uint8_t *msg, size_t msg_size, char *db_name,
                         size_t db_len, char *coll_name, size_t coll_len,
                         uint64_t value, int positive);

size_t cb_msg_encode_delete_all(uint8_t *msg, size_t msg_size, char *db_name,
                         size_t db_len, char *coll_name, size_t coll_len,
                         uint64_t value, int positive);

size_t cb_msg_encode_list_databases(uint8_t *msg, size_t msg_size);

size_t cb_msg_encode_list_collections(uint8_t *msg, size_t msg_size, char *db_name,
                               size_t db_len);

#endif // _CB_MSG_ENCODE_H
