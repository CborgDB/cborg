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

size_t cb_cbor_encode_string_start(uint64_t len, uint8_t *ev, size_t size);

size_t cb_cbor_encode_string(char *s, uint64_t s_len, uint8_t *ev, size_t ev_size);

size_t cb_cbor_encode_string_start_indef(uint8_t *ev, size_t size);

size_t cb_cbor_encode_string_stop_indef(uint8_t *ev, size_t size);

///////////////
// ACCESSORS //
///////////////

int cb_cbor_get_string_length(const uint8_t *item, uint64_t *v);

char* cb_cbor_get_string(const uint8_t *item);

///////////////
// OPERATORS //
///////////////

int cb_cbor_string_cmp(const uint8_t *a, const uint8_t *b);

#endif // _CB_CBOR_STRING_H
