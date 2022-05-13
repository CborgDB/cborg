/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include "cb_cbor_simple.h"

ssize_t cb_cbor_encode_null(uint8_t *ev, ssize_t size) {
  if (size >= 1) {
    *ev = 0xF6;
    return 1;
  }
  return 0;
}
