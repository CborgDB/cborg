/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifndef _CB_ENDIANNESS_H
#define _CB_ENDIANNESS_H

#include <stdint.h>

int cb_is_little_endian();

uint16_t cb_bswap16(uint16_t v);

uint32_t cb_bswap32(uint32_t v);

uint64_t cb_bswap64(uint64_t v);

#endif // _CB_ENDIANNESS_H
