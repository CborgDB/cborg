/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include "cb_cbor.h"
#include "cb_cbor_int.h"
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

static inline uint8_t cb_cbor_get_uint8(const uint8_t *item);

static inline uint16_t cb_cbor_get_uint16(const uint8_t *item);

static inline uint32_t cb_cbor_get_uint32(const uint8_t *item);

static inline uint64_t cb_cbor_get_uint64(const uint8_t *item);

//////////////
// ENCODING //
//////////////

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

///////////////
// ACCESSORS //
///////////////

int cb_cbor_get_uint(const uint8_t *item, uint64_t *value) {
  uint8_t ai = CBOR_AI(*item);
  if(ai < 24)
    *value = ai;
  else if (ai == 24)
    *value = cb_cbor_get_uint8(item);
  else if (ai == 25)
    *value = cb_cbor_get_uint16(item);
  else if (ai == 26)
    *value = cb_cbor_get_uint32(item);
  else if (ai == 27)
    *value = cb_cbor_get_uint64(item);
  else
    return -1;
  return 0;
}

int cb_cbor_get_uint_size(const uint8_t *item) {
  uint8_t ai = CBOR_AI(*item);
  if(ai < 24)
    return 1;
  else if (ai == 24)
    return 2;
  else if (ai == 25)
    return 3;
  else if (ai == 26)
    return 5;
  else if (ai == 27)
    return 9;
  else
    return -1;
}

///////////////
// OPERATORS //
///////////////

// TODO: Maybe use memcmp ?
int cb_cbor_int_eq(const uint8_t *a, const uint8_t *b) {
  uint64_t a_value, b_value;
  if(CBOR_MT(*a) == CBOR_MT(*b)){
    if((!cb_cbor_get_uint(a, &a_value)) && (!cb_cbor_get_uint(b, &b_value)))
      return a_value == b_value;
    else
      return -1;
  }
  return 0;
}

int cb_cbor_int_strict_eq(const uint8_t *a, const uint8_t *b) {
  if(CBOR_AI(*a) == CBOR_AI(*b))
    return cb_cbor_int_eq(a, b);
  return 0;
}

int cb_cbor_int_not_eq(const uint8_t *a, const uint8_t *b) {

  return !cb_cbor_int_eq(a, b);
}

int cb_cbor_int_strict_not_eq(const uint8_t *a, const uint8_t *b) {
  return !cb_cbor_int_strict_eq(a, b);
}

int cb_cbor_int_lt(const uint8_t *a, const uint8_t *b) {
  uint64_t a_value, b_value;
  uint8_t a_mt = CBOR_MT(*a);
  uint8_t b_mt = CBOR_MT(*b);
  if (a_mt == 0 && b_mt == 0) {
    if((!cb_cbor_get_uint(a, &a_value)) && (!cb_cbor_get_uint(b, &b_value)))
      return a_value < b_value;
  } else if (a_mt == 1 && b_mt == 1) {
    if((!cb_cbor_get_uint(a, &a_value)) && (!cb_cbor_get_uint(b, &b_value)))
      return a_value > b_value;
  } else {
    return a_mt > b_mt;
  }
  return -1;
}

int cb_cbor_int_gt(const uint8_t *a, const uint8_t *b) {
  return !cb_cbor_int_lt(a, b) && !cb_cbor_int_eq(a, b);
}

int cb_cbor_int_lt_eq(const uint8_t *a, const uint8_t *b) {
  return cb_cbor_int_lt(a, b) || cb_cbor_int_eq(a, b);
}

int cb_cbor_int_gt_eq(const uint8_t *a, const uint8_t *b) {
  return !cb_cbor_int_lt(a, b) || cb_cbor_int_eq(a, b);
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

static inline uint8_t cb_cbor_get_uint8(const uint8_t *item) {
  uint8_t ai = CBOR_AI(*item);
  return ai < 24 ? ai : item[1];
}

static inline uint16_t cb_cbor_get_uint16(const uint8_t *item) {
#ifdef IS_BIG_ENDIAN
  return *(item+1);
#else
  return cb_bswap16(*(item+1));
#endif
}

static inline uint32_t cb_cbor_get_uint32(const uint8_t *item) {
#ifdef IS_BIG_ENDIAN
  return *(item+1);
#else
  return cb_bswap32(*(item+1));
#endif
}

static inline uint64_t cb_cbor_get_uint64(const uint8_t *item) {
#ifdef IS_BIG_ENDIAN
  return *(item+1);
#else
  return cb_bswap64(*(item+1));
#endif
}
