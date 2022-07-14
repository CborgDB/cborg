/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifndef _CB_REQUEST_H
#define _CB_REQUEST_H

#include <stdint.h>

typedef struct {
  uint64_t msg_length;
  uint64_t op_code;
  uint8_t payload[4096];
} request_t;

typedef request_t response_t;

int cb_request_handle(int fd, request_t *req, response_t *res);

#endif // _CB_REQUEST_H
