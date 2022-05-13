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

ssize_t cb_cbor_encode_null(uint8_t *ev, ssize_t size);

#endif // _CB_CBOR_SIMPLE_H
