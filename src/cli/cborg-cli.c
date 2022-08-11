/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifdef __linux__
#define _POSIX_C_SOURCE 200809L
#define h_addr h_addr_list[0] /* for backward compatibility */
#include <strings.h>
#endif

#include <arpa/inet.h> // htons()
#include <ctype.h>
#include <errno.h>
#include <inttypes.h>
#include <netdb.h>      // struct hostent
#include <netinet/in.h> // sockaddr_in
#include <stdio.h>      // perror()
#include <stdlib.h>     // exit(), EXIT_FAILURE, EXIT_SUCCES
#include <string.h>     // strlen()
#include <sys/socket.h> // socket()
#include <unistd.h>

#include "cbor/cb_cbor.h"
#include "cbor/cb_cbor_int.h"
#include "cbor/cb_cbor_string.h"
#include "cli/cb_cli_help.h"
#include "cli/cb_cli_interpreter.h"
#include "cli/cb_cli_parser.h"
#include "cli/cb_cli_scanner.h"
#include "cli/cb_cli_token.h"

int init_socket() {
  int fd;
  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }
  return fd;
}

void connect_socket(int fd, const char *hostname, uint16_t port) {
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

  if (connect(fd, (struct sockaddr *)&sin, sizeof(struct sockaddr)) == -1) {
    perror("connect()");
    exit(errno);
  }
}

void close_socket(int fd) {
  if (close(fd) < 0) {
    perror("close failed");
    exit(EXIT_FAILURE);
  }
}

void print_prompt(const char *db_in_use) {
  printf(CSHL "CborgDB(%s)" CRESET " > ", db_in_use);
  fflush(stdout);
}

int main(int argc, char const *argv[]) {
  scanner_t s;
  parser_t p;
  interpreter_t i;
  char buffer[4096];
  char db_in_use[255] = {0};
  int fd = 0; 
  fd = init_socket(); // init socket
  connect_socket(fd, "127.0.0.1", 30000); // connect to the server
  while (i.status != INTERPRETER_EXIT) {
    print_prompt(db_in_use);
    size_t nread = read(fileno(stdin), buffer, 4096);

    s = scanner_init(buffer, nread);
    p = parser_init(&s);
    i = interpreter_init(&p, db_in_use, buffer, 4096, fd);

    parse_command(&p);
    describe_parse_tree(&p, &(p.tree));
    interpret(&i);

  }
  // close socket
  return EXIT_SUCCESS;
}
