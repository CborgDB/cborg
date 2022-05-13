/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifndef _CB_CBOR_INT_H
#define _CB_CBOR_INT_H

#include <unistd.h>
#include <stdint.h>

//////////////
// ENCODING //
//////////////

// INT
ssize_t cb_cbor_encode_uint8(uint8_t v, uint8_t *ev, ssize_t size);

ssize_t cb_cbor_encode_uint16(uint16_t v, uint8_t *ev, ssize_t size);

ssize_t cb_cbor_encode_uint32(uint32_t v, uint8_t *ev, ssize_t size);

ssize_t cb_cbor_encode_uint64(uint64_t v, uint8_t *ev, ssize_t size);

ssize_t cb_cbor_encode_uint(uint64_t v, uint8_t *ev, ssize_t size);

// NEG INT
ssize_t cb_cbor_encode_negint8(uint8_t v, uint8_t *ev, ssize_t size);

ssize_t cb_cbor_encode_negint16(uint16_t v, uint8_t *ev, ssize_t size);

ssize_t cb_cbor_encode_negint32(uint32_t v, uint8_t *ev, ssize_t size);

ssize_t cb_cbor_encode_negint64(uint64_t v, uint8_t *ev, ssize_t size);

ssize_t cb_cbor_encode_negint(uint64_t v, uint8_t *ev, ssize_t size);

///////////////
// ACCESSORS //
///////////////

int cb_cbor_get_uint(const uint8_t *item, uint64_t *value);

int cb_cbor_get_uint_size(const uint8_t *item);

///////////////
// OPERATORS //
///////////////

int cb_cbor_int_eq(const uint8_t *a, const uint8_t *b);

int cb_cbor_int_strict_eq(const uint8_t *a, const uint8_t *b);

int cb_cbor_int_not_eq(const uint8_t *a, const uint8_t *b);

int cb_cbor_int_strict_not_eq(const uint8_t *a, const uint8_t *b);

int cb_cbor_int_lt(const uint8_t *a, const uint8_t *b);

int cb_cbor_int_gt(const uint8_t *a, const uint8_t *b);

int cb_cbor_int_lt_eq(const uint8_t *a, const uint8_t *b);

int cb_cbor_int_gt_eq(const uint8_t *a, const uint8_t *b);

#endif // _CB_CBOR_INT_H
