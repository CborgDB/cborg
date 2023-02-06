/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include <string.h>

#include "cbor/cb_cbor_bytestring.h"
#include "cbor/cb_cbor_simple.h"
#include "cbor/cb_cbor_int.h"
#include "cbor/cb_cbor.h"

size_t cb_cbor_encode_bytestring_start(uint8_t *ev, size_t len, size_t size) {
  return _cb_cbor_encode_uint(len, ev, size, 0x40);
}

size_t cb_cbor_encode_bytestring(void *bs, uint64_t bs_len, uint8_t *ev, size_t ev_size) {
  size_t written = cb_cbor_encode_bytestring_start(bs_len, ev, ev_size);
  if(written  > 0 && ev_size >= written + (size_t)bs_len) {
    memcpy(ev + written, bs, bs_len);
    return written + bs_len;
  }
  return 0;
}

size_t cb_cbor_encode_bytestring_start_indef(uint8_t *ev, size_t size) {
  if (size >= 1) {
    *ev = 0x5F;
    return 1;
  }
  return 0;
}

size_t cb_cbor_encode_bytestring_stop_indef(uint8_t *ev, size_t size) {
  return cb_cbor_encode_break(ev, size);
}
