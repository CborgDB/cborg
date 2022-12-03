/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include "common/cbor/cb_cbor_simple.h"
#include "common/cbor/cb_cbor.h"

size_t cb_cbor_encode_map_start(uint8_t *ev, size_t len, size_t size) {
  return _cb_cbor_encode_uint(len, ev, size, 0xA0);
}

size_t cb_cbor_encode_map_start_indef(uint8_t *ev, size_t size) {
  if (size >= 1) {
    *ev = 0xBF;
    return 1;
  }
  return 0;
}

size_t cb_cbor_encode_map_stop_indef(uint8_t *ev, size_t size) {
  return cb_cbor_encode_break(ev, size);
}
