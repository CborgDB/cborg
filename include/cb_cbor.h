/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifndef _CB_CBOR_H
#define _CB_CBOR_H

#include <unistd.h>
#include <stdint.h>

#define CBOR_MT(ib) (ib >> 5)
#define CBOR_AI(ib) (ib & 0x1F)

ssize_t _cb_cbor_encode_uint8(uint8_t v, uint8_t *ev,
                                            ssize_t size, uint8_t offset);

ssize_t _cb_cbor_encode_uint16(uint16_t v, uint8_t *ev,
                                             ssize_t size, uint8_t offset);

ssize_t _cb_cbor_encode_uint32(uint32_t v, uint8_t *ev,
                                             ssize_t size, uint8_t offset);

ssize_t _cb_cbor_encode_uint64(uint64_t v, uint8_t *ev,
                                             ssize_t size, uint8_t offset);

ssize_t _cb_cbor_encode_uint(uint64_t v, uint8_t *ev,
                                           ssize_t size, uint8_t offset);

uint8_t cb_cbor_get_uint8(const uint8_t *item);

uint16_t cb_cbor_get_uint16(const uint8_t *item);

uint32_t cb_cbor_get_uint32(const uint8_t *item);

uint64_t cb_cbor_get_uint64(const uint8_t *item);

#endif // _CB_CBOR_H
