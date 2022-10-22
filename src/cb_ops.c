/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifdef __linux__
#define _GNU_SOURCE
#include <linux/limits.h> // PATH_MAX
#endif

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>

#include "common/cb_fs.h"
#include "common/cbor/cb_cbor_int.h"
#include "common/cbor/cb_cbor_simple.h"
#include "cb_ops.h"

#define DATABASES_DIRECTORY "./databases"

// Bad code to see performance improvement later :)

// return
//  0 : db created
//  -2 = db exist
//  -1 = erreur -> errno
int cb_ops_create_db(const char *db_name) {
  char full_path[PATH_MAX + 1];
  snprintf(full_path, sizeof(full_path), "%s/%s", DATABASES_DIRECTORY, db_name);

  if(cb_fs_dir_exists(full_path) == 1)
    return -2;
  
  return cb_fs_mkdir(full_path);
}

// return
//  0 : db deleted
//  -2 = db not exist
//  -1 = erreur -> errno
int cb_ops_drop_db(const char *db_name) {
  char full_path[PATH_MAX + 1];
  snprintf(full_path, sizeof(full_path), "%s/%s", DATABASES_DIRECTORY, db_name);

  if(cb_fs_dir_exists(full_path) != 1)
    return -2;
  
  return cb_fs_rmdir(full_path);
}
// return:
// 0: OK
// -1: Cannot open directory
int cb_ops_list_dbs(char ***list, size_t *list_size) {
  return cb_fs_ls_dir(DATABASES_DIRECTORY,list,list_size);
}

// return
//  0 : collection created
//  -2 = collection exist
//  -1 = erreur -> errno
int cb_ops_create_collection(const char *db_name, const char *collection_name) {
  char full_path[PATH_MAX + 1];
  snprintf(full_path, sizeof(full_path), "%s/%s/%s", DATABASES_DIRECTORY, db_name, collection_name);

  if(strlen(db_name) == 0)
    return -3;

  if(cb_fs_file_exists(full_path) == 1)
    return -2;
  
  return cb_fs_touch(full_path);
}

// return
//  0 : collection deleted
//  -2 = collection not exist
//  -1 = erreur -> errno
int cb_ops_drop_collection(const char *db_name, const char *collection_name) {
  char full_path[PATH_MAX + 1];
  snprintf(full_path, sizeof(full_path), "%s/%s/%s", DATABASES_DIRECTORY, db_name, collection_name);

  if(strlen(db_name) == 0)
    return -3;

  if(cb_fs_file_exists(full_path) != 1)
    return -2;
  
  return cb_fs_remove(full_path);
}

// return
//  0 : success
//  -2 = insuficient size
//  -1 = erreur -> errno
int cb_ops_list_collections(const char *db_name, char ***list, size_t *list_size) {
  char full_path[PATH_MAX + 1];
  snprintf(full_path, sizeof(full_path), "%s/%s", DATABASES_DIRECTORY, db_name);
  return cb_fs_ls_file(full_path, list, list_size);
}

// Simple insert (Like append) to the end of the file O(1) ;)
ssize_t cb_ops_insert_one(int fd, const void *item, size_t item_size) {
  struct stat s;
  if (fstat(fd, &s) == 0)
    return pwrite(fd, item, item_size, s.st_size);
  return 0;
}

// Linear Search O(n/2)
// return
//  >=0 : position found
//  -2 = not found
//  -1 = erreur -> errno
off_t cb_ops_find_one(int fd, void *item, size_t item_size, off_t start_pos) {
  int ret = 0;
  uint8_t buf[9];
  while ((ret = pread(fd, buf, 9, start_pos)) != 0) {
    if (cb_cbor_int_eq(item, buf) == 1)
      return start_pos;
    int size_item_buf = cb_cbor_get_uint_size(buf);
    // if (size_item_buf == -1) then item is null (0xF6) -> skip one byte
    start_pos += (size_item_buf != -1 ? size_item_buf : 1);
  }
  return ret == 0 ? -2 : ret;
}

// Replace first item O(n/2)
// Not atomic: If the execution goes wrong then the file becomes corrupted
int cb_ops_update_one(int fd, void *old, size_t old_size, void *new,
                  size_t new_size, off_t after_pos) {
  off_t position;
  if ((position = cb_ops_find_one(fd, old, old_size, after_pos)) >= 0) {
    if (old_size > new_size) {
      int ret = 0;
      uint8_t tmp;
      off_t cur = position + old_size;
      // from position + old_size - 1 to the end
      while ((ret = pread(fd, &tmp, 1, cur) > 0)) {
        // TODO: How to handle the problem if pread or pwrite fails?
        pwrite(fd, &tmp, 1, cur - (old_size - new_size));
        cur++;
      }
      struct stat s;
      fstat(fd, &s);
      // truncate the end of file
      ftruncate(fd, s.st_size - (old_size - new_size));
    } else if (old_size < new_size) {
      int ret = 0;
      uint8_t tmp;
      struct stat s;
      fstat(fd, &s);
      off_t cur = s.st_size - 1;
      // from the end to the position + old_size - 1
      while ((ret = pread(fd, &tmp, 1, cur) > 0)) {
        if(cur < position + (off_t)old_size)
          break;
        // TODO: How to handle the problem if pread or pwrite fails?
        pwrite(fd, &tmp, 1, cur + (new_size - old_size) );
        cur--;
      }
    }
    // write the item
    return pwrite(fd, new, new_size, position);
  }

  return position;
}

int cb_ops_update_all(int fd, void *old, size_t old_size, void *new,
                  size_t new_size, off_t after_pos) {
  uint64_t count = 0;
  int ret;
  while((ret = cb_ops_update_one(fd, old, old_size, new, new_size, after_pos)) > 0) {
    count++;
  }
  return (ret == -2 && count > 0) ? count : ret;
}

// return
//  >0 : item deleted
//  -2 = not found
//  -1 = erreur -> errno
int cb_ops_delete_one(int fd, void *item, size_t item_size) {
  off_t position;
  if ((position = cb_ops_find_one(fd, item, item_size, 0)) >= 0) {
    int ret = 0;
    uint8_t tmp;
    off_t cur = position + item_size;
    while ((ret = pread(fd, &tmp, 1, cur) > 0)) {
      // TODO: How to handle the problem if pread or pwrite fails?
      pwrite(fd, &tmp, 1, cur - item_size);
      cur++;
    }
    struct stat s;
    fstat(fd, &s);
    ftruncate(fd, s.st_size - item_size);
    return 1;
  }
  return position;
}

// return
//  >0 : items deleted
//  -2 = not found
//  -1 = erreur -> errno
int cb_ops_delete_all(int fd, void *item, size_t item_size) {
  uint64_t count = 0;
  int ret;

  while((ret = cb_ops_delete_one(fd,item,item_size)) > 0) {
    count++;
  }
  return (ret == -2 && count > 0) ? count : ret;
}
