/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifndef _CB_OPT_H
#define _CB_OPT_H

#include <stdint.h>

void usage(const char * progname);

void print_version();

void cb_getopt(int argc, char const *argv[], uint16_t *port);

#endif // _CB_OPT_H
