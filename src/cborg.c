/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */
#include <stdio.h> // perror()
#include <stdlib.h> // exit(), EXIT_FAILURE, EXIT_SUCCES
#include <unistd.h>
#include <sys/socket.h> // socket()
#include <netinet/in.h> // sockaddr_in
#include <arpa/inet.h> // htons() 

#include <string.h> // strlen()

int main(int argc, char const *argv[]) {
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
  
  printf("CborgDB is running on port 30000.\n");

  int client;
  socklen_t slen = sizeof(address);
  if ((client = accept(fd, (struct sockaddr *)&(address), &slen)) < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  char s[] = "Welcome to CborgDB !\n";
  write(client, s, strlen(s));

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
