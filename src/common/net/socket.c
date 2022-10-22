/**
 * Copyright (c) 2022-present Adil Benhlal <abenhlal@cborgdb.com>
 * 
 */

#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

#include "common/net/socket.h"

#define h_addr h_addr_list[0]

void cb_net_socket_init(socket_t *s) {
  if ((s->fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }
}

void cb_net_socket_destroy(socket_t *s) { close(s->fd); }

socket_t *cb_net_socket_new() {
  socket_t *s = (socket_t *)malloc(sizeof(socket_t));
  cb_net_socket_init(s);
  return s;
}

void cb_net_socket_delete(socket_t *s) {
  cb_net_socket_destroy(s);
  free(s);
}

ssize_t cb_net_socket_read(socket_t *s, void *buf, size_t nbyte) {
  return read(s->fd, buf, nbyte);
}

ssize_t cb_net_socket_write(socket_t *s, void *buf, size_t nbyte) {
  return write(s->fd, buf, nbyte);
}

void cb_net_socket_connect(socket_t *s, const char *hostname, uint16_t port) {
  struct hostent *hostinfo = NULL;
  struct sockaddr_in sin = {0};

  hostinfo = gethostbyname(hostname);
  if (hostinfo == NULL) {
    fprintf(stderr, "Unknown host %s.\n", hostname);
    exit(EXIT_FAILURE);
  }
  sin.sin_addr = *(struct in_addr *)hostinfo->h_addr;
  sin.sin_port = htons(port);
  sin.sin_family = AF_INET;

  if (connect(s->fd, (struct sockaddr *)&sin, sizeof(struct sockaddr)) == -1) {
    perror("connect()");
    exit(errno);
  }
}
