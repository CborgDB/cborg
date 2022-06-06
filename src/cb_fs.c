/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifdef __linux__
// To avoid error compilation on DT_DIR and DT_REG
// Warning d_type in entry is not supported by all filesystem types
#define _GNU_SOURCE
#include <linux/limits.h> // PATH_MAX
#endif

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "cb_fs.h"

int cb_fs_mkdir(const char *dir_path) { return mkdir(dir_path, 0777); }

int cb_fs_rmdir(const char *dir_path) {
  DIR *dirp;
  struct dirent *entry;
  char full_path[PATH_MAX + 1];

  if ((dirp = opendir(dir_path)) == NULL)
    return -1;

  while ((entry = readdir(dirp)) != NULL) {
    if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
      continue;

    snprintf(full_path, sizeof(full_path), "%s/%s", dir_path, entry->d_name);

    if (entry->d_type == DT_DIR && cb_fs_rmdir(full_path) == -1)
      return -1;
    else if (entry->d_type == DT_REG && unlink(full_path) == -1)
      return -1;
  }
  closedir(dirp);

  return rmdir(dir_path);
}

// Bad list (to send the string directly in cbor, waiting for cbor arrays)
int cb_fs_ls_dir(const char *dir_path, char *list, size_t list_size) {
  DIR *dirp;
  struct dirent *entry;
  size_t written = 0;
  if(list_size > 0)
    list[0] = '\0';

  if ((dirp = opendir(dir_path)) == NULL)
    return -1;

  while ((entry = readdir(dirp)) != NULL) {
    if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
      continue;
    if (entry->d_type == DT_DIR) {
      if(written + entry->d_namlen + 1 <= list_size){
        if(written > 0)
          list[written] = '\n';
        memcpy(list + written,entry->d_name, entry->d_namlen);
        list[written + entry->d_namlen] = '\0';
        written += entry->d_namlen + 1;
      } else {
        return -1;
      }
    }
  }
  
  return closedir(dirp);
}

int cb_fs_ls_file(const char *dir_path, char *list, size_t list_size) {
  DIR *dirp;
  struct dirent *entry;
  size_t written = 0;
  if(list_size > 0)
    list[0] = '\0';

  if ((dirp = opendir(dir_path)) == NULL)
    return -1;

  while ((entry = readdir(dirp)) != NULL) {
    if (entry->d_type == DT_REG) {
      if(written + entry->d_namlen + 1 <= list_size){
        if(written > 0)
          list[written] = '\n';
        memcpy(list + written,entry->d_name, entry->d_namlen);
        list[written + entry->d_namlen] = '\0';
        written += entry->d_namlen + 1;
      } else {
        return -1;
      }
    }
  }
  
  return closedir(dirp);
}

int cb_fs_touch(const char *path) {
  int fd = open(path, O_WRONLY | O_CREAT, 0644);
  if (fd < 0)
    return -1;
  return close(fd);
}

int cb_fs_remove(const char *path) { return unlink(path); }

int cb_fs_dir_exists(const char *path) {
  struct stat stats;
  return stat(path, &stats) == 0 && S_ISDIR(stats.st_mode);
}

int cb_fs_file_exists(const char *path) {
  struct stat stats;
  return stat(path, &stats) == 0 && S_ISREG(stats.st_mode);
}

int cb_fs_open(const char *path) { return open(path, O_RDWR | O_CREAT, 0644); }

int cb_fs_close(int fd) { return close(fd); }
