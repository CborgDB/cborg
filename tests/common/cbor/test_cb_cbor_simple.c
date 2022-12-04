/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common/cbor/cb_cbor_simple.h"

// INT
void test_cb_cbor_encode_null() {
  // TEST 1
  // test with size == 0 (no change)
  uint8_t ev_t1_s0[2] = {0xFF, 0xFF}; // encoded value
  uint8_t expect_t1_s0[2] = {0xFF, 0xFF}; // [ 0xFF, 0xFF ]
  assert(cb_cbor_encode_null(ev_t1_s0, 0) == 0);
  assert(memcmp(expect_t1_s0, ev_t1_s0, 2) == 0);

  // test with size == 1
  uint8_t ev_t1_s1[2] = {0xFF, 0xFF}; // encoded value
  uint8_t expect_t1_s1[2] = {0xF6, 0xFF}; // [ null, 0xFF ]
  assert(cb_cbor_encode_null(ev_t1_s1, 1) == 1);
  assert(memcmp(expect_t1_s1, ev_t1_s1, 2) == 0);

  // test with size == 2
  uint8_t ev_t1_s2[2] = {0xFF, 0xFF}; // encoded value
  uint8_t expect_t1_s2[2] = {0xF6, 0xFF}; // [ null, 0xFF ]
  assert(cb_cbor_encode_null(ev_t1_s2, 2) == 1);
  assert(memcmp(expect_t1_s2, ev_t1_s2, 2) == 0);

  // TEST 2 (same test with another end byte)
  // test with size == 0 (no change)
  uint8_t ev_t2_s0[2] = {0xFF, 0xAB}; // encoded value
  uint8_t expect_t2_s0[2] = {0xFF, 0xAB}; // [ 0xFF, 0xAB ]
  assert(cb_cbor_encode_null(ev_t2_s0, 0) == 0);
  assert(memcmp(expect_t2_s0, ev_t2_s0, 2) == 0);

  // test with size == 1
  uint8_t ev_t2_s1[2] = {0xFF, 0xAB}; // encoded value
  uint8_t expect_t2_s1[2] = {0xF6, 0xAB}; // [ null, 0xAB ]
  assert(cb_cbor_encode_null(ev_t2_s1, 1) == 1);
  assert(memcmp(expect_t2_s1, ev_t2_s1, 2) == 0);

  // test with size == 2
  uint8_t ev_t2_s2[2] = {0xFF, 0xAB}; // encoded value
  uint8_t expect_t2_s2[2] = {0xF6, 0xAB}; // [ null, 0xAB ]
  assert(cb_cbor_encode_null(ev_t2_s2, 2) == 1);
  assert(memcmp(expect_t2_s2, ev_t2_s2, 2) == 0);

}

void test_cb_cbor_encode_break() {
  // TEST 1
  // test with size == 0 (no change)
  uint8_t ev_t1_s0[2] = {0x00, 0x00}; // encoded value
  uint8_t expect_t1_s0[2] = {0x00, 0x00}; // [ 0x00, 0x00 ]
  assert(cb_cbor_encode_break(ev_t1_s0, 0) == 0);
  assert(memcmp(expect_t1_s0, ev_t1_s0, 2) == 0);

  // test with size == 1
  uint8_t ev_t1_s1[2] = {0x00, 0x00}; // encoded value
  uint8_t expect_t1_s1[2] = {0xFF, 0x00}; // [ break, 0x00 ]
  assert(cb_cbor_encode_break(ev_t1_s1, 1) == 1);
  assert(memcmp(expect_t1_s1, ev_t1_s1, 2) == 0);

  // test with size == 2
  uint8_t ev_t1_s2[2] = {0x00, 0x00}; // encoded value
  uint8_t expect_t1_s2[2] = {0xFF, 0x00}; // [ break, 0x00 ]
  assert(cb_cbor_encode_break(ev_t1_s2, 2) == 1);
  assert(memcmp(expect_t1_s2, ev_t1_s2, 2) == 0);

  // TEST 2 (same test with another end byte)
  // test with size == 0 (no change)
  uint8_t ev_t2_s0[2] = {0x00, 0xAB}; // encoded value
  uint8_t expect_t2_s0[2] = {0x00, 0xAB}; // [ 0x00, 0xAB ]
  assert(cb_cbor_encode_break(ev_t2_s0, 0) == 0);
  assert(memcmp(expect_t2_s0, ev_t2_s0, 2) == 0);

  // test with size == 1
  uint8_t ev_t2_s1[2] = {0xFF, 0xAB}; // encoded value
  uint8_t expect_t2_s1[2] = {0xFF, 0xAB}; // [ break, 0xAB ]
  assert(cb_cbor_encode_break(ev_t2_s1, 1) == 1);
  assert(memcmp(expect_t2_s1, ev_t2_s1, 2) == 0);

  // test with size == 2
  uint8_t ev_t2_s2[2] = {0xFF, 0xAB}; // encoded value
  uint8_t expect_t2_s2[2] = {0xFF, 0xAB}; // [ break, 0xAB ]
  assert(cb_cbor_encode_break(ev_t2_s2, 2) == 1);
  assert(memcmp(expect_t2_s2, ev_t2_s2, 2) == 0);

}

// TODO: criterion or cmocka
int main() {
  test_cb_cbor_encode_null();
  test_cb_cbor_encode_break();

  return EXIT_SUCCESS;
}
