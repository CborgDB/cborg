/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifndef _CB_OPS_H
#define _CB_OPS_H

#include <unistd.h>
#include <sys/types.h>

ssize_t cb_ops_insert_one(int fd, const void *data, size_t data_size);

off_t cb_ops_find_one(int fd, void *data, size_t data_size, off_t after_pos);

int cb_ops_update_one(int fd, void *old, size_t old_size, void *new,
                  size_t new_size, off_t after_pos);

int cb_ops_update_all(int fd, void *old, size_t old_size, void *new,
                  size_t new_size, off_t after_pos);

int cb_ops_delete_one(int fd, void *data, size_t data_size);

int cb_ops_delete_all(int fd, void *data, size_t data_size);

#endif // _CB_OPS_H
