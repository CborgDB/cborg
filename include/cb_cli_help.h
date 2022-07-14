/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifndef _CB_CLI_HELP_H
#define _CB_CLI_HELP_H

#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define CYAN "\033[96m"
#define YELLLOW "\033[33m"
#define MAGENTA "\033[95m"
#define CRESET "\033[0m"

#define CDOT RED
#define CCMD CYAN
#define CPAR YELLLOW
#define CSUB GREEN
#define CARG MAGENTA
#define CSHL BLUE

void cb_cli_help();

void cb_cli_help_show();

void cb_cli_help_use();

void cb_cli_help_create();

void cb_cli_help_drop();

void cb_cli_help_db();

#endif // _CB_CLI_HELP_H
