/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cb_cbor_string.h"

void test_cb_cbor_encode_string() {
  // Size tests
  uint8_t ev_zero[109] = {0xEF, 0xEF};
  // 0xEF at the end expects no change
  uint8_t expected_ev_zero[7] = {0x60, 0xEF};

  assert(cb_cbor_encode_string_definite("", 0, ev_zero, 109) == 1);
  assert(memcmp(ev_zero, expected_ev_zero, 2) == 0);

  uint8_t ev_one_byte[109] = {0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF};
  // 0xEF at the end expects no change
  uint8_t expected_ev_one_byte[7] = {0x65, 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0xEF};

  assert(cb_cbor_encode_string_definite("Hello", 5, ev_one_byte, 109) == 6);
  assert(memcmp(ev_one_byte, expected_ev_one_byte, 7) == 0);

  uint8_t ev[109] = {0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF,
                     0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF,
                     0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF,
                     0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF};
  // 0xEF at the end expects no change
  uint8_t expected_ev[34] = {
      0x78, 0x1F, 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x77, 0x6F, 0x72, 0x6C,
      0x64, 0x20, 0x21, 0x20, 0x43, 0x62, 0x6F, 0x72, 0x67, 0x44, 0x42, 0x20,
      0x69, 0x73, 0x20, 0x68, 0x65, 0x72, 0x65, 0x20, 0x21, 0xEF};

  assert(cb_cbor_encode_string_definite("Hello world ! CborgDB is here !", 31,
                                        ev, 109) == 33);
  assert(memcmp(ev, expected_ev, 34) == 0);
}

void test_cb_cbor_get_string_length() {
  // Size tests
  uint8_t ev_zero[109] = {0xEF, 0xEF};
  // 0xEF at the end expects no change
  uint8_t expected_ev_zero[7] = {0x60, 0xEF};

  assert(cb_cbor_encode_string_definite("", 0, ev_zero, 109) == 1);
  assert(memcmp(ev_zero, expected_ev_zero, 2) == 0);

  uint64_t ev_len_zero;
  assert(cb_cbor_get_string_length(ev_zero, &ev_len_zero) == 0);
  assert(ev_len_zero == 0);

  uint8_t ev_one_byte[109] = {0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF};
  // 0xEF at the end expects no change
  uint8_t expected_ev_one_byte[7] = {0x65, 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0xEF};

  assert(cb_cbor_encode_string_definite("Hello", 5, ev_one_byte, 109) == 6);
  assert(memcmp(ev_one_byte, expected_ev_one_byte, 7) == 0);

  uint64_t ev_len_one_byte;
  assert(cb_cbor_get_string_length(ev_one_byte, &ev_len_one_byte) == 0);
  assert(ev_len_one_byte == 5);

  uint8_t ev[109] = {0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF,
                     0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF,
                     0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF,
                     0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF};
  // 0xEF at the end expects no change
  uint8_t expected_ev[34] = {
      0x78, 0x1F, 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x77, 0x6F, 0x72, 0x6C,
      0x64, 0x20, 0x21, 0x20, 0x43, 0x62, 0x6F, 0x72, 0x67, 0x44, 0x42, 0x20,
      0x69, 0x73, 0x20, 0x68, 0x65, 0x72, 0x65, 0x20, 0x21, 0xEF};

  assert(cb_cbor_encode_string_definite("Hello world ! CborgDB is here !", 31,
                                        ev, 109) == 33);
  assert(memcmp(ev, expected_ev, 34) == 0);

  uint64_t ev_len;
  assert(cb_cbor_get_string_length(ev, &ev_len) == 0);
  assert(ev_len == 31);
}

void test_cb_cbor_string_cmp() {
  uint8_t ev_a[109];
  uint8_t ev_b[109];
  // EQUAL
  assert(cb_cbor_encode_string_definite("", 0, ev_a, 109) == 1);
  assert(cb_cbor_encode_string_definite("", 0, ev_b, 109) == 1);
  assert(cb_cbor_string_cmp(ev_a, ev_b) == 0);

  assert(cb_cbor_encode_string_definite("Hello", 5, ev_a, 109) == 6);
  assert(cb_cbor_encode_string_definite("Hello", 5, ev_b, 109) == 6);
  assert(cb_cbor_string_cmp(ev_a, ev_b) == 0);

  assert(cb_cbor_encode_string_definite("Hello world ! CborgDB is here !", 31,
                                        ev_a, 109) == 33);
  assert(cb_cbor_encode_string_definite("Hello world ! CborgDB is here !", 31,
                                        ev_b, 109) == 33);
  assert(cb_cbor_string_cmp(ev_a, ev_b) == 0);

  // LESS THAN / GREATER THAN
  assert(cb_cbor_encode_string_definite("Hell", 4, ev_a, 109) == 5);
  assert(cb_cbor_encode_string_definite("Hello", 5, ev_b, 109) == 6);
  assert(cb_cbor_string_cmp(ev_a, ev_b) == -1); // lt
  assert(cb_cbor_string_cmp(ev_b, ev_a) == 1); // gt

  assert(cb_cbor_encode_string_definite("Helln", 5, ev_a, 109) == 6);
  assert(cb_cbor_encode_string_definite("Hello", 5, ev_b, 109) == 6);
  assert(cb_cbor_string_cmp(ev_a, ev_b) == -1); // lt
  assert(cb_cbor_string_cmp(ev_b, ev_a) == 1); // gt

  assert(cb_cbor_encode_string_definite("Hello world ! CborgDB is here", 29,
                                        ev_a, 109) == 31);
  assert(cb_cbor_encode_string_definite("Hello world ! CborgDB is here !", 31,
                                        ev_b, 109) == 33);
  assert(cb_cbor_string_cmp(ev_a, ev_b) == -1); // lt
  assert(cb_cbor_string_cmp(ev_b, ev_a) == 1); // gt

  assert(cb_cbor_encode_string_definite("Hello world ! CborgDB is herd", 29,
                                        ev_a, 109) == 31);
  assert(cb_cbor_encode_string_definite("Hello world ! CborgDB is here", 29,
                                        ev_b, 109) == 31);
  assert(cb_cbor_string_cmp(ev_a, ev_b) == -1); // lt
  assert(cb_cbor_string_cmp(ev_b, ev_a) == 1); // gt
}

// TODO: criterion or cmocka
int main() {
  test_cb_cbor_encode_string();
  test_cb_cbor_get_string_length();
  test_cb_cbor_string_cmp();

  return EXIT_SUCCESS;
}
