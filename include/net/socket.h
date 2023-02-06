/**
 * Copyright (c) 2022-present Adil Benhlal <abenhlal@cborgdb.com>
 * 
 */

#ifndef _CB_NET_SOCKET_H
#define _CB_NET_SOCKET_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

typedef struct socket_t {
  int fd;
} socket_t;

socket_t *cb_net_socket_new();

void cb_net_socket_delete(socket_t *s);

void cb_net_socket_init(socket_t *s);

void cb_net_socket_destroy(socket_t *s);

ssize_t cb_net_socket_read(socket_t *s, void *buf, size_t len);

ssize_t cb_net_socket_write(socket_t *s, void *buf, size_t length);

void cb_net_socket_connect(socket_t *s, const char *hostname, uint16_t port);

#endif
