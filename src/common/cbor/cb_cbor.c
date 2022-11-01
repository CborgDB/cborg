/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include "common/cbor/cb_cbor.h"
#include "common/cb_endianness.h"

size_t _cb_cbor_encode_uint8(uint8_t v, uint8_t *ev,
                                            size_t size, uint8_t offset) {
  if (v < 24) {
    if (size >= 1) {
      ev[0] = v + offset;
      return 1;
    }
  } else {
    if (size >= 2) {
      ev[0] = 24 + offset;
      ev[1] = v;
      return 2;
    }
  }
  return 0;
}

size_t _cb_cbor_encode_uint16(uint16_t v, uint8_t *ev,
                                             size_t size, uint8_t offset) {
  if (size >= 3) {
    ev[0] = 25 + offset;
#ifdef IS_BIG_ENDIAN
    *((uint16_t *)(ev + 1)) = v;
#else
    *((uint16_t *)(ev + 1)) = cb_bswap16(v);
#endif
    return 3;
  }
  return 0;
}

size_t _cb_cbor_encode_uint32(uint32_t v, uint8_t *ev,
                                             size_t size, uint8_t offset) {
  if (size >= 5) {
    ev[0] = 26 + offset;
#ifdef IS_BIG_ENDIAN
    *((uint32_t *)(ev + 1)) = v;
#else
    *((uint32_t *)(ev + 1)) = cb_bswap32(v);
#endif
    return 5;
  }
  return 0;
}

size_t _cb_cbor_encode_uint64(uint64_t v, uint8_t *ev,
                                             size_t size, uint8_t offset) {
  if (size >= 9) {
    ev[0] = 27 + offset;
#ifdef IS_BIG_ENDIAN
    *((uint64_t *)(ev + 1)) = v;
#else
    *((uint64_t *)(ev + 1)) = cb_bswap64(v);
#endif
    return 9;
  }
  return 0;
}

size_t _cb_cbor_encode_uint(uint64_t v, uint8_t *ev,
                                           size_t size, uint8_t offset) {
  if (v <= UINT16_MAX)
    if (v <= UINT8_MAX)
      return _cb_cbor_encode_uint8(v, ev, size, offset);
    else
      return _cb_cbor_encode_uint16(v, ev, size, offset);
  else if (v <= UINT32_MAX)
    return _cb_cbor_encode_uint32(v, ev, size, offset);
  else
    return _cb_cbor_encode_uint64(v, ev, size, offset);
}

uint8_t cb_cbor_get_uint8(const uint8_t *item) {
  uint8_t ai = CBOR_AI(*item);
  return ai < 24 ? ai : item[1];
}

uint16_t cb_cbor_get_uint16(const uint8_t *item) {
  const uint8_t *p = item + 1;
  return (p[1] << 0) | (p[0] << 8);
}

uint32_t cb_cbor_get_uint32(const uint8_t *item) {
  const uint8_t *p = item + 1;
  return (p[3] << 0) | (p[2] << 8) | (p[1] << 16) | (p[0] << 24);
}

uint64_t cb_cbor_get_uint64(const uint8_t *item) {
  const uint8_t *p = item + 1;
  return (
    ((uint64_t)(p[7]) << 0) | ((uint64_t)(p[6]) << 8) |
    ((uint64_t)(p[5]) << 16) | ((uint64_t)(p[4]) << 24) |
    ((uint64_t)(p[3]) << 32) | ((uint64_t)(p[2]) << 40) |
    ((uint64_t)(p[1]) << 48) | ((uint64_t)(p[0]) << 56));
}
