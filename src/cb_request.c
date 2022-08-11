/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */
#include "cb_request.h"
#include "cbor/cb_cbor_int.h"
#include "cbor/cb_cbor_string.h"
#include "cb_msg.h"
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

// HANDLE REQUEST
/**
 * uint64_t msg_length;
 * uint64_t op_code;
 * payload_t payload;
 *
 */
int cb_request_handle(int fd, request_t *req, response_t *res) {
  size_t nread = 0;

  res->op_code = OP_REPLY;
  
  if((nread = read(fd, req->payload, 9)) != 9) {
    size_t written = cb_cbor_encode_string_definite("Request Error: on read msg_length\n", 34, res->payload, 4096);
    res->msg_length = written + 18;
    return -1;
  }
  
  if (cb_cbor_get_uint(req->payload, &(req->msg_length)) == -1) {
    size_t written = cb_cbor_encode_string_definite("Request Error: msg_length is invalid\n", 37, res->payload, 4096);
    res->msg_length = written + 18;
    return -1;
  }

  // GET OP_CODE
  if((nread = read(fd, req->payload, 9)) != 9) {
    size_t written = cb_cbor_encode_string_definite("Request Error: on read op_code\n", 31, res->payload, 4096);
    res->msg_length = written + 18;
    return -1;
  }

  if (cb_cbor_get_uint(req->payload, &(req->op_code)) == -1) {
    size_t written = cb_cbor_encode_string_definite("Request Error: op_code is invalid\n", 34, res->payload, 4096);
    res->msg_length = written + 18;
    return -1;
  }

  if((nread = read(fd, req->payload, req->msg_length - 18)) != req->msg_length -18) {
    size_t written = cb_cbor_encode_string_definite("Request Error: on read payload (msg_length may be incorrect)\n", 61, res->payload, 4096);
    res->msg_length = written + 18;
    return -1;
  }

  return 0;
}
