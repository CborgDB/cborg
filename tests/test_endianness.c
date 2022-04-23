/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include <assert.h>
#include <stdlib.h>

#include "cb_endianness.h"

void test_cb_bswap16() {
  assert(cb_bswap16(0xDBBD) == 0xBDDB);
  assert(cb_bswap16(cb_bswap16(0xDBBD)) == 0xDBBD);
  assert(cb_bswap16(0xABCD) == 0xCDAB);
  assert(cb_bswap16(cb_bswap16(0xABCD)) == 0xABCD);
  assert(cb_bswap16(0x0000) == 0x0000);
  assert(cb_bswap16(cb_bswap16(0x0000)) == 0x0000);
  assert(cb_bswap16(0xFFFF) == 0xFFFF);
  assert(cb_bswap16(cb_bswap16(0xFFFF)) == 0xFFFF);
}

void test_cb_bswap32() {
  assert(cb_bswap32(0xDBABCDBD) == 0xBDCDABDB);
  assert(cb_bswap32(cb_bswap32(0xDBABCDBD)) == 0xDBABCDBD);
  assert(cb_bswap32(0xABCDEF98) == 0x98EFCDAB);
  assert(cb_bswap32(cb_bswap32(0xABCDEF98)) == 0xABCDEF98);
  assert(cb_bswap32(0x00000000) == 0x00000000);
  assert(cb_bswap32(cb_bswap32(0x00000000)) == 0x00000000);
  assert(cb_bswap32(0xFFFFFFFF) == 0xFFFFFFFF);
  assert(cb_bswap32(cb_bswap32(0xFFFFFFFF)) == 0xFFFFFFFF);
}

void test_cb_bswap64() {
  assert(cb_bswap64(0xABCDEF0123456789) == 0x8967452301EFCDAB);
  assert(cb_bswap64(cb_bswap64(0xABCDEF0123456789)) == 0xABCDEF0123456789);
  assert(cb_bswap64(0x123456789ABCDEF8) == 0xF8DEBC9A78563412);
  assert(cb_bswap64(cb_bswap64(0x123456789ABCDEF8)) == 0x123456789ABCDEF8);
  assert(cb_bswap64(0x0000000000000000) == 0x0000000000000000);
  assert(cb_bswap64(cb_bswap64(0x0000000000000000)) == 0x0000000000000000);
  assert(cb_bswap64(0xFFFFFFFFFFFFFFFF) == 0xFFFFFFFFFFFFFFFF);
  assert(cb_bswap64(cb_bswap64(0xFFFFFFFFFFFFFFFF)) == 0xFFFFFFFFFFFFFFFF);
}

void test_cb_is_little_endian() {
#ifdef IS_BIG_ENDIAN
  assert(cb_is_little_endian() == 0);
  assert((!cb_is_little_endian()) == 1);
#else
  assert(cb_is_little_endian() == 1);
  assert((!cb_is_little_endian()) == 0);
#endif
}

// TODO: criterion or cmocka
int main() {
  ///////////
  // TESTS //
  ///////////
  test_cb_bswap16();
  test_cb_bswap32();
  test_cb_bswap64();
  test_cb_is_little_endian();

  return EXIT_SUCCESS;
}
