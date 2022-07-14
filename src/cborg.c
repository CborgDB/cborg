/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifdef __linux__
#define _GNU_SOURCE
#include <linux/limits.h> // PATH_MAX
#endif

#include <arpa/inet.h>  // htons()
#include <netinet/in.h> // sockaddr_in
#include <stdio.h>      // perror()
#include <stdlib.h>     // exit(), EXIT_FAILURE, EXIT_SUCCES
#include <string.h>     // strlen()
#include <sys/socket.h> // socket()
#include <unistd.h>
#include <inttypes.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#include "cb_cbor.h"
#include "cb_cbor_int.h"
#include "cb_cbor_string.h"
#include "cb_ops.h"
#include "cb_fs.h"
#include "cb_opt.h"
#include "cb_request.h"
#include "cb_request_executor.h"

#define DATABASES_DIRECTORY "./databases"

int main(int argc, char const *argv[]) {
  cb_getopt(argc, argv);

  // Init server
  int fd;
  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  int opt = 1;
  if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  uint16_t port = 30000;
  struct sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);
  if (bind(fd, (struct sockaddr *)&(address), sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  if (listen(fd, 100) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  cb_fs_mkdir(DATABASES_DIRECTORY);

  printf("CborgDB is running on port 30000.\n");

  int client;
  socklen_t slen = sizeof(address);

  while (1) {
    if ((client = accept(fd, (struct sockaddr *)&(address), &slen)) < 0) {
      perror("accept");
      exit(EXIT_FAILURE);
    }
    printf("Client connected :)\n");
    char s[] = "Welcome to CborgDB !\n";
    //write(client, s, strlen(s));
    
    char fake_buffer[9];
    //while (fcntl(client, F_GETFD) != -1 || errno != EBADF) {
    while (recv(client, fake_buffer, 9, MSG_PEEK)>0) {
      request_t req;
      response_t res;
      if (cb_request_handle(client, &req, &res) == 0) {
        cb_request_executor(&req, &res);
      }
      // bad code: send reply
      uint8_t encoded_response[4096];
      cb_cbor_encode_uint64(res.msg_length, encoded_response, 4096);
      cb_cbor_encode_uint64(res.op_code, encoded_response + 9, 4096);
      memcpy(encoded_response + 18, res.payload, res.msg_length - 18);
      write(client, encoded_response, res.msg_length);
    }
    printf("Connection closed by the client.\n");
  }
  if (close(client) < 0) {
    perror("close client failed");
    exit(EXIT_FAILURE);
  }

  if (close(fd) < 0) {
    perror("close server failed");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
