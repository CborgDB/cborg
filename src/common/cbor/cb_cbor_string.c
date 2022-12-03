/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include <string.h>

#include "common/cbor/cb_cbor_string.h"
#include "common/cbor/cb_cbor_simple.h"
#include "common/cbor/cb_cbor_int.h"
#include "common/cbor/cb_cbor.h"

//////////////
// ENCODING //
//////////////

// STRING
size_t cb_cbor_encode_string_start(uint64_t len, uint8_t *ev, size_t size) {
  return _cb_cbor_encode_uint(len, ev, size, 0x60);
}

size_t cb_cbor_encode_string(char *s, uint64_t s_len, uint8_t *ev, size_t ev_size) {
  size_t written = cb_cbor_encode_string_start(s_len, ev, ev_size);
  if(written  > 0 && ev_size >= written + (size_t)s_len) {
    memcpy(ev + written, s, s_len);
    return written + s_len;
  }
  return 0;
}

size_t cb_cbor_encode_string_start_indef(uint8_t *ev, size_t size) {
  if (size >= 1) {
    *ev = 0x7F;
    return 1;
  }
  return 0;
}

size_t cb_cbor_encode_string_stop_indef(uint8_t *ev, size_t size) {
  return cb_cbor_encode_break(ev, size);
}

///////////////
// ACCESSORS //
///////////////

/**
 * @brief Returns the length of string contained in CBOR item 
 * @param[in]   item  A string type CBOR item
 * @param[out]  v     The length of the item
 * @retval 0  success
 * @retval -1  error
 */ 
int cb_cbor_get_string_length(const uint8_t *item, uint64_t *v) {
  return cb_cbor_get_uint(item, v);
}

///////////////
// OPERATORS //
///////////////

/**
 * @brief Compare string items a and b
 * @param[in] a A string type CBOR item
 * @param[in] b A string type CBOR item
 * @retval  0  (a == b)
 * @retval  1  (a > b)
 * @retval -1  (a < b)
 * @retval -2  error
 */ 
int cb_cbor_string_cmp(const uint8_t *a, const uint8_t *b) {
  uint64_t a_len;
  uint64_t b_len;
  if(cb_cbor_get_string_length(a, &a_len) != -1 && cb_cbor_get_string_length(b, &b_len) != -1) {
    if(a_len == b_len){
      int a_start_size = cb_cbor_get_uint_size(a);
      int b_start_size = cb_cbor_get_uint_size(b);
      int res = memcmp(a + a_start_size, b + b_start_size, a_len);
      return (res > 0) ? 1 : ((res < 0) ? -1 : 0);
    }
    return a_len > b_len ? 1 : -1;
  }
  return -2;
}
