/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include "cb_cbor.h"
#include "cb_cbor_int.h"

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
