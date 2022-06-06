/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifndef _CB_FS_H
#define _CB_FS_H

int cb_fs_mkdir(const char *path);

int cb_fs_rmdir(const char *dir_path);

int cb_fs_ls_dir(const char *dir_path, char *list, size_t list_size);

int cb_fs_ls_file(const char *dir_path, char *list, size_t list_size);

int cb_fs_touch(const char *path);

int cb_fs_remove(const char *path);

int cb_fs_dir_exists(const char *path);

int cb_fs_file_exists(const char *path);

int cb_fs_open(const char *path);

int cb_fs_close(int fd);

#endif // _CB_FS_H
