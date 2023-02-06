/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cbor/cb_cbor_int.h"

// INT
void test_cb_cbor_encode_uint8() {
  // 1 byte
  uint8_t ev_one_byte[2] = {0xEF, 0xEF}; // encoded value
  uint8_t min_one_byte[2] = {0x00, 0xEF}; // 0
  uint8_t middle_one_byte[2] = {0x10, 0xEF}; // 16
  uint8_t max_one_byte[2] = {0x17, 0xEF}; // 23
  assert(cb_cbor_encode_uint8(0, ev_one_byte, 1) == 1);
  assert(memcmp(min_one_byte, ev_one_byte, 2) == 0);
  assert(cb_cbor_encode_uint8(16, ev_one_byte, 1) == 1);
  assert(memcmp(middle_one_byte, ev_one_byte, 2) == 0);
  assert(cb_cbor_encode_uint8(23, ev_one_byte, 1) == 1);
  assert(memcmp(max_one_byte, ev_one_byte, 2) == 0);

  // 2 bytes
  uint8_t ev_two_byte[2] = {0xFF, 0xEF};
  uint8_t min_two_byte[2] = {0x18, 0x18}; // 24
  uint8_t middle_two_byte[2] = {0x18, 0xAB}; // 171
  uint8_t max_two_byte[2] = {0x18, 0xFF};  // UINT8_MAX == 255

  assert(cb_cbor_encode_uint8(24, ev_two_byte, 2) == 2);
  assert(memcmp(min_two_byte, ev_two_byte, 2) == 0);
  assert(cb_cbor_encode_uint8(171, ev_two_byte, 2) == 2);
  assert(memcmp(middle_two_byte, ev_two_byte, 2) == 0);
  assert(cb_cbor_encode_uint8(UINT8_MAX, ev_two_byte, 2) == 2);
  assert(memcmp(max_two_byte, ev_two_byte, 2) == 0);

  // Size tests
  uint8_t ev_ts[2] = {0xFF, 0xEF};
  uint8_t no_change[2] = {0xFF, 0xEF};
  // 0
  assert(cb_cbor_encode_uint8(0, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 2) == 0);
  // 16
  assert(cb_cbor_encode_uint8(16, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 2) == 0);
  // 23
  assert(cb_cbor_encode_uint8(23, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 2) == 0);
  // 24
  assert(cb_cbor_encode_uint8(24, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 2) == 0);
  assert(cb_cbor_encode_uint8(24, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 2) == 0);
  // 171
  assert(cb_cbor_encode_uint8(171, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 2) == 0);
  assert(cb_cbor_encode_uint8(171, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 2) == 0);
  // UINT8_MAX
  assert(cb_cbor_encode_uint8(UINT8_MAX, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 2) == 0);
  assert(cb_cbor_encode_uint8(UINT8_MAX, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 2) == 0);
}

void test_cb_cbor_encode_uint16() {
  // encoded value
  uint8_t ev[3] = {0xFF, 0xEF, 0xEF};
  // CBOR(0x190100) == UINT8_MAX + 1
  uint8_t min[3] = {0x19, 0x01, 0x00};
  // CBOR(0x19ABCD) == 43981
  uint8_t middle[3] = {0x19, 0xAB, 0xCD};
  // CBOR(0x19FFFF) == UINT16_MAX
  uint8_t max[3] = {0x19, 0xFF, 0xFF};

  assert(cb_cbor_encode_uint16(256, ev, 3) == 3);
  assert(memcmp(min, ev, 3) == 0);
  assert(cb_cbor_encode_uint16(43981, ev, 3) == 3);
  assert(memcmp(middle, ev, 3) == 0);
  assert(cb_cbor_encode_uint16(UINT16_MAX, ev, 3) == 3);
  assert(memcmp(max, ev, 3) == 0);

  // Size tests
  uint8_t ev_ts[3] = {0xFF, 0xEF, 0xEF}; // encoded value
  uint8_t no_change[3] = {0xFF, 0xEF, 0xEF};
  // UINT8_MAX + 1 == 256
  assert(cb_cbor_encode_uint16(256, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 3) == 0);
  assert(cb_cbor_encode_uint16(256, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 3) == 0);
  assert(cb_cbor_encode_uint16(256, ev_ts, 2) == 0);
  assert(memcmp(no_change, ev_ts, 3) == 0);
  // 43981
  assert(cb_cbor_encode_uint16(43981, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 3) == 0);
  assert(cb_cbor_encode_uint16(43981, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 3) == 0);
  assert(cb_cbor_encode_uint16(43981, ev_ts, 2) == 0);
  assert(memcmp(no_change, ev_ts, 3) == 0);
  // UINT16_MAX
  assert(cb_cbor_encode_uint16(UINT16_MAX, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 3) == 0);
  assert(cb_cbor_encode_uint16(UINT16_MAX, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 3) == 0);
  assert(cb_cbor_encode_uint16(UINT16_MAX, ev_ts, 2) == 0);
  assert(memcmp(no_change, ev_ts, 3) == 0);
}

void test_cb_cbor_encode_uint32() {
  // encoded value
  uint8_t ev[5] = {0xFF, 0xEF, 0xEF, 0xEF, 0xEF};
  // CBOR(0x1A00010000) == UINT16_MAX + 1
  uint8_t min[5] = {0x1A, 0x00, 0x01, 0x00, 0x00};
  // CBOR(0x1AABCD1234) == 2882343476
  uint8_t middle[5] = {0x1A, 0xAB, 0xCD, 0x12, 0x34};
  // CBOR(0x1AFFFFFFFF) == UINT32_MAX
  uint8_t max[5] = {0x1A, 0xFF, 0xFF, 0xFF, 0xFF};

  assert(cb_cbor_encode_uint32(65536U, ev, 5) == 5);
  assert(memcmp(min, ev, 5) == 0);
  assert(cb_cbor_encode_uint32(2882343476U, ev, 5) == 5);
  assert(memcmp(middle, ev, 5) == 0);
  assert(cb_cbor_encode_uint32(UINT32_MAX, ev, 5) == 5);
  assert(memcmp(max, ev, 5) == 0);

  // Size tests
  uint8_t ev_ts[5] = {0xFF, 0xEF, 0xEF, 0xEF, 0xEF}; // encoded value
  uint8_t no_change[5] = {0xFF, 0xEF, 0xEF, 0xEF, 0xEF};
  // UINT16_MAX + 1 == 65536
  assert(cb_cbor_encode_uint32(65536U, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_uint32(65536U, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_uint32(65536U, ev_ts, 2) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_uint32(65536U, ev_ts, 3) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_uint32(65536U, ev_ts, 4) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  // 2882343476
  assert(cb_cbor_encode_uint32(2882343476U, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_uint32(2882343476U, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_uint32(2882343476U, ev_ts, 2) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_uint32(2882343476U, ev_ts, 3) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_uint32(2882343476U, ev_ts, 4) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  // UINT32_MAX
  assert(cb_cbor_encode_uint32(UINT32_MAX, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_uint32(UINT32_MAX, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_uint32(UINT32_MAX, ev_ts, 2) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_uint32(UINT32_MAX, ev_ts, 3) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_uint32(UINT32_MAX, ev_ts, 4) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);

}

void test_cb_cbor_encode_uint64() {
  // encoded value
  uint8_t ev[9] = {0xFF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF};
  // CBOR(0x1B0000000100000000) == UINT32_MAX + 1 == 4294967296
  uint8_t min[9] = {0x1B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00};
  // CBOR(0x1BABCD123434567890) == 12379813812177893520
  uint8_t middle[9] = {0x1B, 0xAB, 0xCD, 0xEF, 0x12, 0x34, 0x56, 0x78, 0x90};
  // CBOR(0x1BFFFFFFFFFFFFFFFF) == UINT64_MAX
  uint8_t max[9] = {0x1B, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  
  assert(cb_cbor_encode_uint64(4294967296ULL, ev, 9) == 9);
  assert(memcmp(min, ev, 9) == 0);
  assert(cb_cbor_encode_uint64(12379813812177893520ULL, ev, 9) == 9);
  assert(memcmp(middle, ev, 9) == 0);
  assert(cb_cbor_encode_uint64(UINT64_MAX, ev, 9) == 9);
  assert(memcmp(max, ev, 9) == 0);

  // Size tests
  uint8_t ev_ts[9] = {0xFF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF};
  uint8_t no_change[9] = {0xFF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF};
  // UINT32_MAX + 1 == 4294967296
  assert(cb_cbor_encode_uint64(4294967296ULL, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(4294967296ULL, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(4294967296ULL, ev_ts, 2) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(4294967296ULL, ev_ts, 3) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(4294967296ULL, ev_ts, 4) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(4294967296ULL, ev_ts, 5) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(4294967296ULL, ev_ts, 6) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(4294967296ULL, ev_ts, 7) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(4294967296ULL, ev_ts, 8) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  // 2882343476
  assert(cb_cbor_encode_uint64(12379813812177893520ULL, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(12379813812177893520ULL, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(12379813812177893520ULL, ev_ts, 2) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(12379813812177893520ULL, ev_ts, 3) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(12379813812177893520ULL, ev_ts, 4) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(12379813812177893520ULL, ev_ts, 5) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(12379813812177893520ULL, ev_ts, 6) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(12379813812177893520ULL, ev_ts, 7) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(12379813812177893520ULL, ev_ts, 8) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  // UINT64_MAX
  assert(cb_cbor_encode_uint64(UINT64_MAX, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(UINT64_MAX, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(UINT64_MAX, ev_ts, 2) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(UINT64_MAX, ev_ts, 3) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(UINT64_MAX, ev_ts, 4) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(UINT64_MAX, ev_ts, 5) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(UINT64_MAX, ev_ts, 6) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(UINT64_MAX, ev_ts, 7) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_uint64(UINT64_MAX, ev_ts, 8) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
}

void test_cb_cbor_encode_uint() {
  uint8_t ev[9] = {0xFF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF};
  // go to _cb_cbor_encode_uint8
  assert(cb_cbor_encode_uint(0, ev, 9) == 1);
  assert(cb_cbor_encode_uint(UINT8_MAX, ev, 9) == 2);
  // go to _cb_cbor_encode_uint16 
  assert(cb_cbor_encode_uint(256, ev, 9) == 3); // UINT8_MAX + 1
  assert(cb_cbor_encode_uint(UINT16_MAX, ev, 9) == 3);
  // go to _cb_cbor_encode_uint32
  assert(cb_cbor_encode_uint(65536U, ev, 9) == 5);
  assert(cb_cbor_encode_uint(UINT32_MAX, ev, 9) == 5); // UINT8_MAX + 1
  // go to _cb_cbor_encode_uint64
  assert(cb_cbor_encode_uint(4294967296ULL, ev, 9) == 9); // UINT32_MAX + 1
  assert(cb_cbor_encode_uint(UINT64_MAX, ev, 9) == 9);
}

// NEGINT
void test_cb_cbor_encode_negint8() {
  // 1 byte
  uint8_t ev_one_byte[2] = {0xEF, 0xEF}; // encoded value
  uint8_t min_one_byte[2] = {0x20, 0xEF}; // negative(0) == -1
  uint8_t middle_one_byte[2] = {0x30, 0xEF}; // negative(15) == -16
  uint8_t max_one_byte[2] = {0x37, 0xEF}; // negative(23) == -24
  assert(cb_cbor_encode_negint8(0, ev_one_byte, 1) == 1);
  assert(memcmp(min_one_byte, ev_one_byte, 2) == 0);
  assert(cb_cbor_encode_negint8(16, ev_one_byte, 1) == 1);
  assert(memcmp(middle_one_byte, ev_one_byte, 2) == 0);
  assert(cb_cbor_encode_negint8(23, ev_one_byte, 1) == 1);
  assert(memcmp(max_one_byte, ev_one_byte, 2) == 0);

  // 2 bytes
  uint8_t ev_two_byte[2] = {0xFF, 0xEF}; // encoded value
  uint8_t min_two_byte[2] = {0x38, 0x18}; // negative(24) == -25
  uint8_t middle_two_byte[2] = {0x38, 0xAB}; // negative(171) == -172
  uint8_t max_two_byte[2] = {0x38, 0xFF};  // negative(UINT8_MAX) == -256

  assert(cb_cbor_encode_negint8(24, ev_two_byte, 2) == 2);
  assert(memcmp(min_two_byte, ev_two_byte, 2) == 0);
  assert(cb_cbor_encode_negint8(171, ev_two_byte, 2) == 2);
  assert(memcmp(middle_two_byte, ev_two_byte, 2) == 0);
  assert(cb_cbor_encode_negint8(UINT8_MAX, ev_two_byte, 2) == 2);
  assert(memcmp(max_two_byte, ev_two_byte, 2) == 0);

  // Size tests
  uint8_t ev_ts[2] = {0xFF, 0xEF}; // encoded value
  uint8_t no_change[2] = {0xFF, 0xEF};
  // 0
  assert(cb_cbor_encode_negint8(0, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 2) == 0);
  // 16
  assert(cb_cbor_encode_uint8(16, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 2) == 0);
  // 23
  assert(cb_cbor_encode_uint8(23, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 2) == 0);
  // 24
  assert(cb_cbor_encode_negint8(24, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 2) == 0);
  assert(cb_cbor_encode_negint8(24, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 2) == 0);
  // 171
  assert(cb_cbor_encode_negint8(171, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 2) == 0);
  assert(cb_cbor_encode_negint8(171, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 2) == 0);
  // UINT8_MAX
  assert(cb_cbor_encode_negint8(UINT8_MAX, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 2) == 0);
  assert(cb_cbor_encode_negint8(UINT8_MAX, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 2) == 0);
}

void test_cb_cbor_encode_negint16() {
  // encoded value
  uint8_t ev[3] = {0xFF, 0xEF, 0xEF};
  // CBOR(0x390100) == negative(UINT8_MAX + 1) == -257
  uint8_t min[3] = {0x39, 0x01, 0x00};
  // CBOR(0x39ABCD) == negative(43981) == -43982
  uint8_t middle[3] = {0x39, 0xAB, 0xCD};
  // CBOR(0x39FFFF) == negative(UINT16_MAX) == -UINT16_MAX - 1
  uint8_t max[3] = {0x39, 0xFF, 0xFF};

  assert(cb_cbor_encode_negint16(256, ev, 3) == 3);
  assert(memcmp(min, ev, 3) == 0);
  assert(cb_cbor_encode_negint16(43981, ev, 3) == 3);
  assert(memcmp(middle, ev, 3) == 0);
  assert(cb_cbor_encode_negint16(UINT16_MAX, ev, 3) == 3);
  assert(memcmp(max, ev, 3) == 0);

  // Size tests
  uint8_t ev_ts[3] = {0xFF, 0xEF, 0xEF}; // encoded value
  uint8_t no_change[3] = {0xFF, 0xEF, 0xEF};
  // UINT8_MAX + 1 == 256
  assert(cb_cbor_encode_negint16(256, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 3) == 0);
  assert(cb_cbor_encode_negint16(256, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 3) == 0);
  assert(cb_cbor_encode_negint16(256, ev_ts, 2) == 0);
  assert(memcmp(no_change, ev_ts, 3) == 0);
  // 43981
  assert(cb_cbor_encode_negint16(43981, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 3) == 0);
  assert(cb_cbor_encode_negint16(43981, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 3) == 0);
  assert(cb_cbor_encode_negint16(43981, ev_ts, 2) == 0);
  assert(memcmp(no_change, ev_ts, 3) == 0);
  // UINT16_MAX
  assert(cb_cbor_encode_negint16(UINT16_MAX, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 3) == 0);
  assert(cb_cbor_encode_negint16(UINT16_MAX, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 3) == 0);
  assert(cb_cbor_encode_negint16(UINT16_MAX, ev_ts, 2) == 0);
  assert(memcmp(no_change, ev_ts, 3) == 0);
}

void test_cb_cbor_encode_negint32() {
  // encoded value
  uint8_t ev[5] = {0xFF, 0xEF, 0xEF, 0xEF, 0xEF};
  // CBOR(0x3A00010000) == negative(UINT16_MAX + 1) == -65537
  uint8_t min[5] = {0x3A, 0x00, 0x01, 0x00, 0x00};
  // CBOR(0x3AABCD1234) == negative(2882343476) == -2882343477
  uint8_t middle[5] = {0x3A, 0xAB, 0xCD, 0x12, 0x34};
  // CBOR(0x3AFFFFFFFF) == negative(UINT32_MAX) == -UINT32_MAX - 1
  uint8_t max[5] = {0x3A, 0xFF, 0xFF, 0xFF, 0xFF};

  assert(cb_cbor_encode_negint32(65536U, ev, 5) == 5);
  assert(memcmp(min, ev, 5) == 0);
  assert(cb_cbor_encode_negint32(2882343476U, ev, 5) == 5);
  assert(memcmp(middle, ev, 5) == 0);
  assert(cb_cbor_encode_negint32(UINT32_MAX, ev, 5) == 5);
  assert(memcmp(max, ev, 5) == 0);

  // Size tests
  uint8_t ev_ts[5] = {0xFF, 0xEF, 0xEF, 0xEF, 0xEF}; // encoded value
  uint8_t no_change[5] = {0xFF, 0xEF, 0xEF, 0xEF, 0xEF};
  // UINT16_MAX + 1 == 65536
  assert(cb_cbor_encode_negint32(65536U, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_negint32(65536U, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_negint32(65536U, ev_ts, 2) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_negint32(65536U, ev_ts, 3) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_negint32(65536U, ev_ts, 4) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  // 2882343476
  assert(cb_cbor_encode_negint32(2882343476U, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_negint32(2882343476U, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_negint32(2882343476U, ev_ts, 2) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_negint32(2882343476U, ev_ts, 3) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_negint32(2882343476U, ev_ts, 4) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  // UINT32_MAX
  assert(cb_cbor_encode_negint32(UINT32_MAX, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_negint32(UINT32_MAX, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_negint32(UINT32_MAX, ev_ts, 2) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_negint32(UINT32_MAX, ev_ts, 3) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);
  assert(cb_cbor_encode_negint32(UINT32_MAX, ev_ts, 4) == 0);
  assert(memcmp(no_change, ev_ts, 5) == 0);

}

void test_cb_cbor_encode_negint64() {
  // encoded value
  uint8_t ev[9] = {0xFF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF};
  // CBOR(0x3B0000000100000000) == negative(UINT32_MAX + 1) == -4294967297
  uint8_t min[9] = {0x3B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00};
  // CBOR(0x3BABCD123434567890) == negative(12379813812177893520)
  uint8_t middle[9] = {0x3B, 0xAB, 0xCD, 0xEF, 0x12, 0x34, 0x56, 0x78, 0x90};
  // CBOR(0x3BFFFFFFFFFFFFFFFF) == negative(UINT64_MAX) 
  uint8_t max[9] = {0x3B, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  
  assert(cb_cbor_encode_negint64(4294967296ULL, ev, 9) == 9);
  assert(memcmp(min, ev, 9) == 0);
  assert(cb_cbor_encode_negint64(12379813812177893520ULL, ev, 9) == 9);
  assert(memcmp(middle, ev, 9) == 0);
  assert(cb_cbor_encode_negint64(UINT64_MAX, ev, 9) == 9);
  assert(memcmp(max, ev, 9) == 0);

  // Size tests
  uint8_t ev_ts[9] = {0xFF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF};
  uint8_t no_change[9] = {0xFF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF};
  // UINT32_MAX + 1 == 4294967296
  assert(cb_cbor_encode_negint64(4294967296ULL, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(4294967296ULL, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(4294967296ULL, ev_ts, 2) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(4294967296ULL, ev_ts, 3) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(4294967296ULL, ev_ts, 4) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(4294967296ULL, ev_ts, 5) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(4294967296ULL, ev_ts, 6) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(4294967296ULL, ev_ts, 7) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(4294967296ULL, ev_ts, 8) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  // 2882343476
  assert(cb_cbor_encode_negint64(12379813812177893520ULL, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(12379813812177893520ULL, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(12379813812177893520ULL, ev_ts, 2) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(12379813812177893520ULL, ev_ts, 3) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(12379813812177893520ULL, ev_ts, 4) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(12379813812177893520ULL, ev_ts, 5) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(12379813812177893520ULL, ev_ts, 6) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(12379813812177893520ULL, ev_ts, 7) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(12379813812177893520ULL, ev_ts, 8) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  // UINT64_MAX
  assert(cb_cbor_encode_negint64(UINT64_MAX, ev_ts, 0) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(UINT64_MAX, ev_ts, 1) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(UINT64_MAX, ev_ts, 2) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(UINT64_MAX, ev_ts, 3) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(UINT64_MAX, ev_ts, 4) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(UINT64_MAX, ev_ts, 5) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(UINT64_MAX, ev_ts, 6) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(UINT64_MAX, ev_ts, 7) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
  assert(cb_cbor_encode_negint64(UINT64_MAX, ev_ts, 8) == 0);
  assert(memcmp(no_change, ev_ts, 9) == 0);
}

void test_cb_cbor_encode_negint() {
  uint8_t ev[9] = {0xFF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF, 0xEF};
  // go to _cb_cbor_encode_negint8
  assert(cb_cbor_encode_negint(0, ev, 9) == 1);
  assert(cb_cbor_encode_negint(UINT8_MAX, ev, 9) == 2);
  // go to _cb_cbor_encode_negint16 
  assert(cb_cbor_encode_negint(256, ev, 9) == 3); // UINT8_MAX + 1
  assert(cb_cbor_encode_negint(UINT16_MAX, ev, 9) == 3);
  // go to _cb_cbor_encode_negint32
  assert(cb_cbor_encode_negint(65536U, ev, 9) == 5);
  assert(cb_cbor_encode_negint(UINT32_MAX, ev, 9) == 5); // UINT8_MAX + 1
  // go to _cb_cbor_encode_negint64
  assert(cb_cbor_encode_negint(4294967296ULL, ev, 9) == 9); // UINT32_MAX + 1
  assert(cb_cbor_encode_negint(UINT64_MAX, ev, 9) == 9);
}

void test_cb_cbor_get_uint() {

}

void test_cb_cbor_get_uint_size() {

}

// TODO: criterion or cmocka
int main() {
  ///////////
  // TESTS //
  ///////////

  // uint
  test_cb_cbor_encode_uint8();
  test_cb_cbor_encode_uint16();
  test_cb_cbor_encode_uint32();
  test_cb_cbor_encode_uint64();
  test_cb_cbor_encode_uint();

  // negint
  test_cb_cbor_encode_negint8();
  test_cb_cbor_encode_negint16();
  test_cb_cbor_encode_negint32();
  test_cb_cbor_encode_negint64();
  test_cb_cbor_encode_negint();

  test_cb_cbor_get_uint();
  test_cb_cbor_get_uint_size();

  return EXIT_SUCCESS;
}
