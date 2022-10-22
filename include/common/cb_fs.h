/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifndef _CB_FS_H
#define _CB_FS_H


/**
 * @brief Create directory like mkdir command
 * @param[in] path Path of the directory (including directory name)
 * @returns
 *     0 on success
 *    -1 on failed and an error code is stored in errno to any of the values documented for the mkdir(2) system call
 * @see cb_fs_rmdir
 */
int cb_fs_mkdir(const char *path);

/**
 * @brief Remove directory recursively
 * @param[in] path Path of the directory (including directory name)
 * @returns
 *     0 on success
 *    -1 on failed and may be an error code is stored in errno to any of the values documented for the rmdir(2) system call
 * @see cb_fs_mkdir
 */
int cb_fs_rmdir(const char *dir_path);

/**
 * @brief List of directories like ls command
 * @param[in] path Path of the directory
 * @param[out] list_dir An allocated array of allocated strings (ending with the charater '\0')
 * @param[out] list_size Size of allocated array
 * @returns
 *     0 on success
 *    -1 cannot open directory and errno is set to any of the values documented for the opendir(3) library function
 *    -2 realloc failed and errno is set to any of the values documented for the realloc(3) library function
 *    -3 strdup failed and errno is set to any of the values documented for the strdup(3) library function
 *    -4 readdir failed and errno is set to any of the values documented for the readdir(3) library function
 *    -5 cannot open directory and may be realloc, strdup or readdir has failed and errno is set to any of the values documented for the closedir(3) library function
 * @see cb_fs_list_free
 */
int cb_fs_ls_dir(const char *dir_path, char ***list_dir, size_t *list_size);

/**
 * @brief List of regular files like ls command
 * @param[in] path Path of the directory
 * @param[out] list_dir An allocated array of allocated strings (ending with the charater '\0')
 * @param[out] list_size Size of allocated array
 * @returns
 *     0 on success
 *    -1 cannot open directory and errno is set to any of the values documented for the opendir(3) library function
 *    -2 realloc failed and errno is set to any of the values documented for the realloc(3) library function
 *    -3 strdup failed and errno is set to any of the values documented for the strdup(3) library function
 *    -4 readdir failed and errno is set to any of the values documented for the readdir(3) library function
 *    -5 cannot open directory and may be realloc, strdup or readdir has failed and errno is set to any of the values documented for the closedir(3) library function
 * @see cb_fs_list_free
 */
int cb_fs_ls_file(const char *dir_path, char ***list_files, size_t *list_size);

/**
 * @brief Free of strings and the array
 * @param[in] list An allocated array of allocated strings
 * @param size Size of allocated array
 * @see cb_fs_ls_dir
 * @see cb_fs_ls_file
 */
void cb_fs_list_free(char **list, size_t size);

/**
 * @brief Create a file
 * @param[in] path Path of the file (including file name)
 * @returns 
 *     0 on success
 *    -1 if an error occurred during file creation an error code is stored in errno to any of the values documented for the open(2) system call
 *    >0 the file descriptor that could not be closed and errno is set to any of the values documented for the close(2) system call
 * @see cb_fs_remove
 */
int cb_fs_touch(const char *path);

/**
 * @brief Remove a file
 * @param[in] path Path of the file (including file name)
 * @returns
 *     0 on success
 *    -1 on failed and an error code is stored in errno
 * @see cb_fs_touch
 */
int cb_fs_remove(const char *path);

/**
 * @brief Check if directory exists
 * @param[in] path Path of the directory
 * @returns
 *     1 on directory exists.
 *     0 on directory not exists.
 *    -1 on error and errno is set.
 *    -2 on path exists but it's not a directory
 * @see cb_fs_mkdir
 * @see cb_fs_rmdir
 * @see cb_fs_ls_dir
 */
int cb_fs_dir_exists(const char *path);

/**
 * @brief Check if file exists
 * @param[in] path Path of the file
 * @returns
 *     1 on file exists.
 *     0 on file not exists.
 *    -1 on error and errno is set.
 *    -2 on path exists but it's not a file
 * @see cb_fs_touch
 * @see cb_fs_remove
 * @see cb_fs_ls_file
 */
int cb_fs_file_exists(const char *path);

/**
 * @brief Open a file (create if not exists)
 * @param[in] path Path of the file
 * @returns
 *     >0 on success
 *    -1 on failed and an error code is stored in errno
 * @see cb_fs_close
 */
int cb_fs_open(const char *path);

/**
 * @brief Close a file opened previously with cb_fs_open
 * @param fd File descriptor of the file (returned by cb_fs_open)
 * @returns
 *     0 on success
 *    -1 on failed and an error code is stored in errno
 * @see cb_fs_open
 */
int cb_fs_close(int fd);

#endif // _CB_FS_H
