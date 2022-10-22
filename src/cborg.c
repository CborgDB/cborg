/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifdef __linux__

#define _GNU_SOURCE
#include <linux/limits.h> // PATH_MAX

#elif __APPLE__

#include <sys/event.h>
#include <sys/time.h>
#include <sys/types.h>

#endif

#include <arpa/inet.h> // htons()
#include <errno.h>
#include <fcntl.h>
#include <inttypes.h>
#include <limits.h>
#include <netinet/in.h> // sockaddr_in
#include <stdio.h>      // perror()
#include <stdlib.h>     // exit(), EXIT_FAILURE, EXIT_SUCCES
#include <string.h>     // strlen()
#include <sys/socket.h> // socket()
#include <unistd.h>

#include "cb_ops.h"
#include "cb_opt.h"
#include "cb_request.h"
#include "cb_request_executor.h"
#include "common/cb_fs.h"
#include "common/cbor/cb_cbor.h"
#include "common/cbor/cb_cbor_int.h"
#include "common/cbor/cb_cbor_string.h"
#include "common/net/server.h"

#define DATABASES_DIRECTORY "./databases"

#ifdef __linux__

int main(int argc, char const *argv[]) {
  server_t server;
  uint16_t port = 30000;
  cb_getopt(argc, argv, &port);

  cb_net_server_init(&server);
  cb_net_server_bind(&server, port);
  cb_net_server_listen(&server, 1);

  cb_fs_mkdir(DATABASES_DIRECTORY);

  printf("CborgDB is running on port %hu.\n", port);

  socket_t client;

  while (1) {
    client = cb_net_server_accept(&server);
    printf("Client connected :)\n");
    char s[] = "Welcome to CborgDB !\n";
    //write(client, s, strlen(s));
    
    char fake_buffer[9];
    //while (fcntl(client, F_GETFD) != -1 || errno != EBADF) {
    while (recv(client.fd, fake_buffer, 9, MSG_PEEK)>0) {
      request_t req;
      response_t res;
      if (cb_request_handle(client.fd, &req, &res) == 0) {
        cb_request_executor(&req, &res);
      }
      // bad code: send reply
      uint8_t encoded_response[4096];
      cb_cbor_encode_uint64(res.msg_length, encoded_response, 4096);
      cb_cbor_encode_uint64(res.op_code, encoded_response + 9, 4096);
      memcpy(encoded_response + 18, res.payload, res.msg_length - 18);
      write(client.fd, encoded_response, res.msg_length);
    }
    printf("Connection closed by the client.\n");
  }
  cb_net_socket_destroy(&client);
  cb_net_server_destroy(&server);

  return EXIT_SUCCESS;
}

#elif __APPLE__ || __OpenBSD__ || __FreeBSD__ || __NetBSD__ || BSD

int main(int argc, char const *argv[]) {
  server_t server;
  uint16_t port = 30000;
  cb_getopt(argc, argv, &port);

  cb_net_server_init(&server);
  cb_net_server_bind(&server, port);
  cb_net_server_listen(&server, 10);

  cb_fs_mkdir(DATABASES_DIRECTORY);

  printf("CborgDB is running on port %hu.\n", port);
  socket_t client;

  int kq = kqueue();
  struct kevent ev_set;
  struct kevent ev_list[10];
  EV_SET(&ev_set, server.socket.fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
  kevent(kq, &ev_set, 1, NULL, 0, NULL);

  while (1) {
    int num_events = kevent(kq, NULL, 0, ev_list, 10, NULL);

    for (int i = 0; i < num_events; i++) {
      int event_fd = ev_list[i].ident;
      //printf("event_fd=%d server=%d\n", event_fd, server.socket.fd);
      if (event_fd == server.socket.fd) {
        client = cb_net_server_accept(&server);
        EV_SET(&ev_set, client.fd, EVFILT_READ, EV_ADD, 0, 0, NULL);
        kevent(kq, &ev_set, 1, NULL, 0, NULL);
        printf("Client #%d connected.\n", client.fd);
      } else if (ev_list[i].flags & EV_EOF) {
        int event_fd = ev_list[i].ident;
        printf("Client #%d disconnected.\n", event_fd);
        EV_SET(&ev_set, event_fd, EVFILT_READ, EV_DELETE, 0, 0, NULL);
        kevent(kq, &ev_set, 1, NULL, 0, NULL);
        close(event_fd);
      } else if (ev_list[i].filter & EVFILT_READ) {
        char fake_buffer[9];
        if (recv(event_fd, fake_buffer, 9, MSG_PEEK) > 0) {
          request_t req;
          response_t res;
          if (cb_request_handle(ev_list[i].ident, &req, &res) == 0) {
            cb_request_executor(&req, &res);
          }
          uint8_t encoded_response[4096];
          cb_cbor_encode_uint64(res.msg_length, encoded_response, 4096);
          cb_cbor_encode_uint64(res.op_code, encoded_response + 9, 4096);
          memcpy(encoded_response + 18, res.payload, res.msg_length - 18);
          write(event_fd, encoded_response, res.msg_length);
        }
      }
    }
  }
  
  cb_net_server_destroy(&server);

  return EXIT_SUCCESS;
}

#endif
