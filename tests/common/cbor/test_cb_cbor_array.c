/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/cbor/cb_cbor_array.h"
#include "common/cbor/cb_cbor_int.h"

void test_cb_cbor_array() {
  uint8_t ev_array[4] = {0xFF, 0xFF, 0xFF, 0xFF}; // encoded value
  uint8_t expect_array[4] = {0x83, 0x0E, 0x00, 0x17}; // [ 0x83, 0x0E, 0x00, 0x17 ]
  assert(cb_cbor_encode_array_start(ev_array, 3, 4) == 1);
  assert(cb_cbor_encode_uint(14, ev_array + 1, 3) == 1);
  assert(cb_cbor_encode_uint(0, ev_array + 2, 2) == 1);
  assert(cb_cbor_encode_uint(23, ev_array + 3, 1) == 1);
  assert(memcmp(expect_array, ev_array, 4) == 0);
}

void test_cb_cbor_array_indef() {
  uint8_t ev_array_indef[5] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA}; // encoded value
  uint8_t expect_array_indef[5] = {0x9F, 0x0E, 0x00, 0x17, 0xFF}; // [ 0x9F, 0x0E, 0x00, 0x17, 0xFF ]
  assert(cb_cbor_encode_array_start_indef(ev_array_indef, 5) == 1);
  assert(cb_cbor_encode_uint(14, ev_array_indef + 1, 4) == 1);
  assert(cb_cbor_encode_uint(0, ev_array_indef + 2, 3) == 1);
  assert(cb_cbor_encode_uint(23, ev_array_indef + 3, 2) == 1);
  assert(cb_cbor_encode_array_stop_indef(ev_array_indef + 4, 1) == 1);
  assert(memcmp(expect_array_indef, ev_array_indef, 5) == 0);
}

// TODO: criterion or cmocka
int main() {
  test_cb_cbor_array();
  test_cb_cbor_array_indef();

  return EXIT_SUCCESS;
}
