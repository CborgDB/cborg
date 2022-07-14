/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifndef _CB_CLI_SCANNER_H
#define _CB_CLI_SCANNER_H

#include "cb_cli_token.h"

typedef struct {
  char *buf_start;
  char *buf_end;
  char *buf_current;
  token_t last_token;
} scanner_t;

scanner_t scanner_init(char *p_start, int p_len);

token_t scanner_next(scanner_t *s, int skip_space);

int scanner_has_finished(scanner_t *s);

void scanner_update_identifier_to_keyword(token_t *t);

#endif // _CB_CLI_SCANNER_H
