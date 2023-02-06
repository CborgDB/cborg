/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifndef _CB_CBOR_SIMPLE_H
#define _CB_CBOR_SIMPLE_H

#include <unistd.h>
#include <stdint.h>

//////////////
// ENCODING //
//////////////

size_t cb_cbor_encode_false(uint8_t *ev, size_t size);

size_t cb_cbor_encode_true(uint8_t *ev, size_t size);

size_t cb_cbor_encode_null(uint8_t *ev, size_t size);

size_t cb_cbor_encode_undefined(uint8_t *ev, size_t size);

size_t cb_cbor_encode_break(uint8_t *ev, size_t size);

#endif // _CB_CBOR_SIMPLE_H
