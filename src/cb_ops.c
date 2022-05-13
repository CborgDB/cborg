/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

#include "cb_cbor_int.h"
#include "cb_cbor_simple.h"
#include "cb_ops.h"

// Bad code to see performance improvement later :)

// Simple insert (Like append) to the end of the file O(1) ;)
ssize_t cb_ops_insert_one(int fd, const void *item, size_t item_size) {
  struct stat s;
  if (fstat(fd, &s) == 0)
    return pwrite(fd, item, item_size, s.st_size);
  return 0;
}

// Linear Search O(n/2)
// return
//  >0 : position found
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
  int ret;
  while((ret = cb_ops_update_one(fd, old, old_size, new, new_size, after_pos)) > 0);
  return ret;
}

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

int cb_ops_delete_all(int fd, void *item, size_t item_size) {
  int ret;
  while((ret = cb_ops_delete_one(fd,item,item_size)) > 0);
  return ret;
}
