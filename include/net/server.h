/**
 * Copyright (c) 2022-present Adil Benhlal <abenhlal@cborgdb.com>
 * 
 */

#ifndef _CB_NET_SERVER_H
#define _CB_NET_SERVER_H

#include <netinet/in.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "net/socket.h"

typedef struct server_t {
  socket_t socket;
  struct sockaddr_in address;
} server_t;

server_t *cb_net_server_new();

void cb_net_server_delete(server_t *s);

void cb_net_server_init(server_t *srv);

void cb_net_server_destroy(server_t *srv);

void cb_net_server_bind(server_t *srv, uint16_t port);

void cb_net_server_listen(server_t *srv, uint64_t backlog);

socket_t cb_net_server_accept(server_t *srv);

#endif
