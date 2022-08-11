/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include "cli/cb_cli_help.h"

#include <stdio.h>

void cb_cli_help() {
  printf(
    CPAR "Usage:" CRESET "\n\n"
    "    " CCMD "help <command>" CRESET "\n\n"
    CPAR "Commands:" CRESET "\n"
    "    " CSUB "show" CRESET "\n"
    "    " CSUB "use" CRESET "\n"
    "    " CSUB "create" CRESET "\n"
    "    " CSUB "drop" CRESET "\n"
    "    " CSUB "db" CRESET "\n"
  );
}

void cb_cli_help_show() {
  printf(CPAR "Usage:" CRESET "\n\n"
    "    " CCMD "show <entity>" CRESET "\n\n"
    CPAR "Entities:" CRESET "\n"
    "    " CSUB "dbs" CRESET ": list databases\n"
    "    " CSUB "collections" CRESET ": list collections in the database that you are currently using. (show: help use)\n"
  );
}

void cb_cli_help_use(){
  printf(
    CPAR "Usage:" CRESET "\n\n"
    "    " CCMD "use <database>" CRESET "\n\n"
    CPAR "Database:" CRESET "\n"
    "    " CSUB "<database>" CRESET ": name of the database that you have already created. (show: help create)\n"
  );
}

void cb_cli_help_create(){
  printf(
    CPAR "Usage:" CRESET "\n\n"
    "    " CCMD "create <entity> <identifier>" CRESET "\n"
    CPAR "Entities:" CRESET "\n"
    "    " CSUB "db" CRESET "\n"
    "    " CSUB "collection" CRESET "\n"
    CPAR "Identifier:" CRESET "\n"
    "    " CSUB "<identifier>" CRESET ": name of the entity (must be unique for db entity / must be unique in the db for collection entity)\n"
  );
}

void cb_cli_help_drop(){
  printf(
    CPAR "Usage:" CRESET "\n\n"
    "    " CCMD "drop <entity> <identifier>" CRESET "\n\n"
    CPAR "Entities:" CRESET "\n"
    "    " CSUB "db" CRESET "\n"
    "    " CSUB "collection" CRESET "\n"
    CPAR "Identifier:" CRESET "\n"
    "    " CSUB "<identifier>" CRESET ": name of the entity (must exist for db entity / must exist in the db for collection entity)\n"
  );
}

void cb_cli_help_db(){
  printf(
    CPAR "Usage:" CRESET "\n\n"
    "    " CCMD "db" CRESET "\n"
    "        print the database that you are currently use.\n\n"
    "    " CCMD "db" CDOT "." CCMD "<collection>" CDOT "." CCMD "<operation>(<args>)" CRESET "\n"
    "        perform an operation in a collection of db\n\n"
    CPAR "Collection:" CRESET "\n"
    "    " CSUB "<collection>" CRESET ": identifier of an existing collection in the db.\n\n"
    CPAR "Operations:" CRESET "\n"
    "    " CSUB "insertOne" CRESET ": <args> = <item>\n"
    "    " CSUB "findOne" CRESET ":   <args> = <item>\n"
    "    " CSUB "updateOne" CRESET ": <args> = <old_item>, <new_item>\n"
    "    " CSUB "updateAll" CRESET ": <args> = <old_item>, <new_item>\n"
    "    " CSUB "deleteOne" CRESET ": <args> = <item>\n"
    "    " CSUB "deleteAll" CRESET ": <args> = <item>\n\n"
    CPAR "Args:" CRESET "\n"
    "    " CSUB "<item>" CRESET ", " CSUB "<old_item>" CRESET ", " CSUB "<new_item>" CRESET ": CBOR item (Currently supports CBOR items of type unsigned integer and negative integer)\n"
    "        " CARG "<unsigned integer>" CRESET ": number [0 .. 2^64 -1]\n"
    "        " CARG "<negative integer>" CRESET ": number [-2^64 .. -1]\n"
    "        " CARG "<byte string>" CRESET ":      currently not supported\n"
    "        " CARG "<text string>" CRESET ":      currently not supported\n"
    "        " CARG "<array>" CRESET ":            currently not supported\n"
    "        " CARG "<map>" CRESET ":              currently not supported\n"
    "        " CARG "<tagged>" CRESET ":           currently not supported\n"
    "        " CARG "<simple/float>" CRESET ":     currently not supported\n"
    "" CRESET ""
  );
}
