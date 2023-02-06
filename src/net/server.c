/**
 * Copyright (c) 2022-present Adil Benhlal <abenhlal@cborgdb.com>
 * 
 */

#include "net/server.h"

#include <netinet/in.h>
#include <unistd.h>

void cb_net_server_init(server_t *srv) {
  cb_net_socket_init(&(srv->socket));
  int opt = 1;
  if (setsockopt(srv->socket.fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }
}

void cb_net_server_destroy(server_t *srv) {
  cb_net_socket_destroy(&(srv->socket));
}

server_t *cb_net_server_new() {
  server_t *srv = (server_t *)malloc(sizeof(server_t));
  cb_net_server_init(srv);
  return srv;
}

void cb_net_server_delete(server_t *srv) {
  cb_net_server_destroy(srv);
  free(srv);
}

void cb_net_server_bind(server_t *srv, uint16_t port) {
  srv->address.sin_family = AF_INET;
  srv->address.sin_addr.s_addr = INADDR_ANY;
  srv->address.sin_port = htons(port);
  if (bind(srv->socket.fd, (struct sockaddr *)&(srv->address),
           sizeof(srv->address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }
}

void cb_net_server_listen(server_t *srv, uint64_t backlog) {
  if (listen(srv->socket.fd, (int)backlog) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }
}

socket_t cb_net_server_accept(server_t *srv) {
  int new_s;
  socklen_t slen = sizeof(srv->address);
  if ((new_s = accept(srv->socket.fd, (struct sockaddr *)&(srv->address),
                      &slen)) < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  socket_t s = {.fd = new_s};
  return s;
}
