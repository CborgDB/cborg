/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifndef _CB_CBOR_H
#define _CB_CBOR_H

#include <unistd.h>
#include <stdint.h>

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

#endif // _CB_CBOR_H
