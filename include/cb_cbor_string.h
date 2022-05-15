/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifndef _CB_CBOR_STRING_H
#define _CB_CBOR_STRING_H

#include <unistd.h>
#include <stdint.h>

//////////////
// ENCODING //
//////////////

ssize_t cb_cbor_encode_string_start(uint64_t len, uint8_t *ev, ssize_t size);

ssize_t cb_cbor_encode_string_definite(char *s, uint64_t s_len, uint8_t *ev, ssize_t ev_size);

///////////////
// ACCESSORS //
///////////////

int cb_cbor_get_string_length(const uint8_t *item, uint64_t *v);

///////////////
// OPERATORS //
///////////////

int cb_cbor_string_cmp(const uint8_t *a, const uint8_t *b);

#endif // _CB_CBOR_STRING_H
