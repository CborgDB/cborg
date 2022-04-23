/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include "cb_cbor.h"
#include "cb_endianness.h"

static inline ssize_t _cb_cbor_encode_uint8(uint8_t v, uint8_t *ev,
                                            ssize_t size, uint8_t offset);

static inline ssize_t _cb_cbor_encode_uint16(uint16_t v, uint8_t *ev,
                                             ssize_t size, uint8_t offset);

static inline ssize_t _cb_cbor_encode_uint32(uint32_t v, uint8_t *ev,
                                             ssize_t size, uint8_t offset);

static inline ssize_t _cb_cbor_encode_uint64(uint64_t v, uint8_t *ev,
                                             ssize_t size, uint8_t offset);

static inline ssize_t _cb_cbor_encode_uint(uint64_t v, uint8_t *ev,
                                           ssize_t size, uint8_t offset);

// INT
ssize_t cb_cbor_encode_uint8(uint8_t v, uint8_t *ev, ssize_t size) {
  return _cb_cbor_encode_uint8(v, ev, size, 0);
}

ssize_t cb_cbor_encode_uint16(uint16_t v, uint8_t *ev, ssize_t size) {
  return _cb_cbor_encode_uint16(v, ev, size, 0);
}

ssize_t cb_cbor_encode_uint32(uint32_t v, uint8_t *ev, ssize_t size) {
  return _cb_cbor_encode_uint32(v, ev, size, 0);
}

ssize_t cb_cbor_encode_uint64(uint64_t v, uint8_t *ev, ssize_t size) {
  return _cb_cbor_encode_uint64(v, ev, size, 0);
}

ssize_t cb_cbor_encode_uint(uint64_t v, uint8_t *ev, ssize_t size) {
  return _cb_cbor_encode_uint(v, ev, size, 0);
}

// NEG INT
ssize_t cb_cbor_encode_negint8(uint8_t v, uint8_t *ev, ssize_t size) {
  return _cb_cbor_encode_uint8(v, ev, size, 0x20);
}

ssize_t cb_cbor_encode_negint16(uint16_t v, uint8_t *ev, ssize_t size) {
  return _cb_cbor_encode_uint16(v, ev, size, 0x20);
}

ssize_t cb_cbor_encode_negint32(uint32_t v, uint8_t *ev, ssize_t size) {
  return _cb_cbor_encode_uint32(v, ev, size, 0x20);
}

ssize_t cb_cbor_encode_negint64(uint64_t v, uint8_t *ev, ssize_t size) {
  return _cb_cbor_encode_uint64(v, ev, size, 0x20);
}

ssize_t cb_cbor_encode_negint(uint64_t v, uint8_t *ev, ssize_t size) {
  return _cb_cbor_encode_uint(v, ev, size, 0x20);
}

//////////////
// INTERNAL //
//////////////
static inline ssize_t _cb_cbor_encode_uint8(uint8_t v, uint8_t *ev,
                                            ssize_t size, uint8_t offset) {
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

static inline ssize_t _cb_cbor_encode_uint16(uint16_t v, uint8_t *ev,
                                             ssize_t size, uint8_t offset) {
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

static inline ssize_t _cb_cbor_encode_uint32(uint32_t v, uint8_t *ev,
                                             ssize_t size, uint8_t offset) {
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

static inline ssize_t _cb_cbor_encode_uint64(uint64_t v, uint8_t *ev,
                                             ssize_t size, uint8_t offset) {
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

static inline ssize_t _cb_cbor_encode_uint(uint64_t v, uint8_t *ev,
                                           ssize_t size, uint8_t offset) {
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
