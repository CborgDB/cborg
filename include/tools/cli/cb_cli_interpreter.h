/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifndef _CB_CLI_INTERPRETER_H
#define _CB_CLI_INTERPRETER_H

#include "tools/cli/cb_cli_parser.h"

#include <stddef.h>

typedef enum {
  INTERPRETER_OK,
  INTERPRETER_EXIT,
  INTERPRETER_INSUFFICIENT_SIZE,
  INTERPRETER_UNKNOWN_ERROR,
} interpreter_status;

typedef struct {
  interpreter_status status;
  parser_t *parser;
  char *db_in_use;
  char *buf;
  size_t buf_size;
  int fd;
} interpreter_t;

interpreter_t interpreter_init(parser_t *parser, char *db_in_use, char *buffer, size_t buffer_size, int fd);

void interpret(interpreter_t *i);

#endif // _CB_CLI_INTERPRETER_H
