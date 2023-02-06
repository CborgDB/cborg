/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifndef _CB_CBOR_BYTESTRING_H
#define _CB_CBOR_BYTESTRING_H

#include <unistd.h>
#include <stdint.h>

//////////////
// ENCODING //
//////////////

size_t cb_cbor_encode_bytestring_start(uint8_t *ev, size_t len, size_t size);

size_t cb_cbor_encode_bytestring(void *bs, uint64_t bs_len, uint8_t *ev, size_t ev_size);

size_t cb_cbor_encode_bytestring_start_indef(uint8_t *ev, size_t size);

size_t cb_cbor_encode_bytestring_stop_indef(uint8_t *ev, size_t size);

#endif // _CB_CBOR_BYTESTRING_H
