/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/cbor/cb_cbor_map.h"
#include "common/cbor/cb_cbor_int.h"

void test_cb_cbor_map() {
  uint8_t ev_map[5] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF}; // encoded value
  uint8_t expect_map[5] = {0xA2, 0x0E, 0x00, 0x17, 0x15}; // [ 0x83, 0x0E, 0x00, 0x17, 0x15 ]
  assert(cb_cbor_encode_map_start(ev_map, 2, 4) == 1);
  assert(cb_cbor_encode_uint(14, ev_map + 1, 3) == 1);
  assert(cb_cbor_encode_uint(0, ev_map + 2, 2) == 1);
  assert(cb_cbor_encode_uint(23, ev_map + 3, 1) == 1);
  assert(cb_cbor_encode_uint(21, ev_map + 4, 1) == 1);
  assert(memcmp(expect_map, ev_map, 4) == 0);
}

void test_cb_cbor_map_indef() {
  uint8_t ev_map_indef[6] = {0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xFF}; // encoded value
  uint8_t expect_map_indef[6] = {0xBF, 0x0E, 0x00, 0x17, 0x15, 0xFF}; // [ 0x9F, 0x0E, 0x00, 0x17, 0x15, 0xFF ]
  assert(cb_cbor_encode_map_start_indef(ev_map_indef, 5) == 1);
  assert(cb_cbor_encode_uint(14, ev_map_indef + 1, 4) == 1);
  assert(cb_cbor_encode_uint(0, ev_map_indef + 2, 3) == 1);
  assert(cb_cbor_encode_uint(23, ev_map_indef + 3, 2) == 1);
  assert(cb_cbor_encode_uint(21, ev_map_indef + 4, 1) == 1);
  assert(cb_cbor_encode_map_stop_indef(ev_map_indef + 5, 1) == 1);
  assert(memcmp(expect_map_indef, ev_map_indef, 6) == 0);
}

// TODO: criterion or cmocka
int main() {
  test_cb_cbor_map();
  test_cb_cbor_map_indef();

  return EXIT_SUCCESS;
}
