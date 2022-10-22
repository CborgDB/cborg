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
#include <stdlib.h>

#include "common/cb_fs.h"

int cb_fs_mkdir(const char *dir_path) { return mkdir(dir_path, 0755); }

// TODO: handle errors and update documentation
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

static inline int _cb_fs_ls(const char *dir_path, char ***list, size_t *list_size, int type) {
  DIR *dirp = NULL;
  struct dirent *entry = NULL;
  *list = NULL;
  *list_size = 0;
  int ret = 0;
  errno = 0;

  char **list_p = NULL;
  size_t size = 0;

  if ((dirp = opendir(dir_path)) == NULL)
    return -1;
  
  while ((entry = readdir(dirp)) != NULL) {
    char **list_tmp = list_p;
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
      continue;
    if (entry->d_type == type) {
      if((list_tmp = realloc(list_tmp, (size + 1) * sizeof(char**))) == NULL){
        ret = -2;
        goto err;
      }
        
      list_p = list_tmp;
      if((list_p[size] = strdup(entry->d_name)) == NULL){
        ret = -3;
        goto err;
      }
      size++;
    }
  }
  
  /**
   *  opendir returns
   *    - null on the end of list
   *    - null on error and errno is set
   */
  if(errno != 0){
    ret = -4;
    goto err;
  }
    

  *list_size = size;
  *list = list_p;

err:
  if(closedir(dirp) != 0) {
    ret = -5;
  }

  if(ret == 0)
    return 0;

  cb_fs_list_free(list_p, size);
  return ret;
}

int cb_fs_ls_dir(const char *dir_path, char ***list_dir, size_t *list_size) {
  return _cb_fs_ls(dir_path, list_dir, list_size, DT_DIR);
}

int cb_fs_ls_file(const char *dir_path, char ***list_files, size_t *list_size) {
  return _cb_fs_ls(dir_path, list_files, list_size, DT_REG);
}

void cb_fs_list_free(char **list, size_t size) {
  if(list != NULL){
    while(size > 0)
      free(list[--size]);
    free(list);
  }
}

int cb_fs_touch(const char *path) {
  int fd = open(path, O_WRONLY | O_CREAT, 0644);
  if (fd < 0)
    return -1;
  return close(fd) == 0 ? 0 : fd;
}

int cb_fs_remove(const char *path) { return unlink(path); }

int cb_fs_dir_exists(const char *path) {
  struct stat stats;
  if(stat(path, &stats) == -1)
    return errno == ENOENT ? 0 : -1;
  return S_ISDIR(stats.st_mode) ? 1 : -2;
}

int cb_fs_file_exists(const char *path) {
  struct stat stats;
  if(stat(path, &stats) == -1)
    return errno == ENOENT ? 0 : -1;
  return S_ISREG(stats.st_mode) ? 1 : -2;
}

int cb_fs_open(const char *path) { return open(path, O_RDWR | O_CREAT, 0644); }

int cb_fs_close(int fd) { return close(fd); }
