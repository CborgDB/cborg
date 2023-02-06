/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifndef _CB_CBOR_MAP_H
#define _CB_CBOR_MAP_H

#include <unistd.h>
#include <stdint.h>

//////////////
// ENCODING //
//////////////

size_t cb_cbor_encode_map_start(uint8_t *ev, size_t len, size_t size);

size_t cb_cbor_encode_map_start_indef(uint8_t *ev, size_t size);

size_t cb_cbor_encode_map_stop_indef(uint8_t *ev, size_t size);

#endif // _CB_CBOR_MAP_H
