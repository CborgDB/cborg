/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifndef _CB_CLI_PARSER_H
#define _CB_CLI_PARSER_H

#include "tools/cli/cb_cli_scanner.h"
/**
 * Grammar
 * 
 * Sentence : cmd
 * 
 * cmd
 *    : cmd_help
 *    | cmd_show
 *    | cmd_use
 *    | cmd_create
 *    | cmd_drop
 *    | cmd_db
 *    ;
 * 
 * cmd_help ->
 *    : 'help' 
 *    | 'help' WS ('show' | 'use' | 'create' | 'drop' | 'db' )
 * 
 * cmd_show -> 'show' WS 'dbs' | 'show' WS 'collections'
 * 
 * cmd_use -> 'use' WS STRING
 * 
 * cmd_create -> 'create' WS 'db' WS STRING | 'create' WS 'collection' WS STRING
 * 
 * cmd_drop -> 'drop' WS 'db' WS STRING | 'drop' WS 'collection' WS STRING
 * 
 * cmd_db ->
 *    : 'db'
 *    | 'db' DOT string DOT function_name LPAREN function_args RPAREN
 *    ;
 * 
 * function_name -> 
 *    : 'insertOne'
 *    | 'findOne'
 *    | 'updateOne'
 *    | 'updateAll'
 *    | 'deleteOne'
 *    | 'deleteAll' 
 *    ;
 * 
 * function_args ->
 *    : expression (COMMA expression)*
 * 
 * expression ->
 *    : SIGN? NUMBER
 *    ;
 * 
 * STRING -> [a-zA-Z]+[0-9a-zA-Z]*
 * 
 * LPAREN -> '('
 * RPAREN -> ')'
 * 
 * SIGN '+' | '-'
 * 
 * NUMBER -> SIGN? [1-9] [0-9]*
 * 
 * DOT -> '.'
 * 
 * COMMA -> ','
 * 
 * WS -> '[ \r\n\t]+'
 * 
 */

typedef struct {
  token_t cmd;
} node_cmd_help_t;

typedef struct {
  token_t entity_type;
} node_cmd_show_t;

typedef struct {
  token_t db_name;
} node_cmd_use_t;

typedef struct {
  token_t entity_type;
  token_t name;
} node_cmd_create_drop_t;

typedef struct {
  int is_an_operation;
  token_t coll_name;
  token_t operation;
  int arg1_is_positive;
  token_t arg1;
  int arg2_is_positive;
  token_t arg2;
} node_cmd_db_t;

typedef union {
  node_cmd_help_t help;
  node_cmd_show_t show;
  node_cmd_use_t use;
  node_cmd_create_drop_t create_drop;
  node_cmd_db_t db;
} node_cmd_t;

typedef struct {
  token_t kind;
  node_cmd_t cmd;
} parse_tree_t;

typedef enum {
  PARSER_OK,
  PARSER_ERROR,
} parser_status;

typedef enum {
  P_ERR_UNKNOWN_COMMAND,
  P_ERR_ERROR_COMMAND,
  P_ERR_INVALID_COLL_NAME,
  P_ERR_DOT_EXPECTED,
  P_ERR_UNKNOWN_OPERATION,
  P_ERR_LPAREN_EXPECTED,
  P_ERR_RPAREN_EXPECTED,
  P_ERR_NUMBER_EXPECTED,
  P_ERR_ENTITY_TYPE_EXPECTED,
  P_ERR_IDENTIFIER_EXPECTED,
  P_ERR_DBS_OR_COLLECTIONS_EXPECTED,
} parser_error_code;

static const char *parser_error_string[] = {
  "unknown command",
  "error command",
  "invalid collection name",
  "expected \".\"",
  "unknown operation",
  "expected \"(\"",
  "expected \")\"",
  "expected number",
  "expected entity type (db or collection)",
  "expected identifier",
  "expected \"dbs\" or \"collections\"",
};

typedef struct {
  token_t token_in_error;
  parser_error_code code;
} parser_error_t;

typedef struct {
  scanner_t *s;
  parser_status status;
  parser_error_t error;
  parse_tree_t tree;
} parser_t;

parser_t parser_init(scanner_t *s);

void parse_help(parser_t *p, node_cmd_help_t *node);

void parse_show(parser_t *p, node_cmd_show_t *node);

void parse_use(parser_t *p, node_cmd_use_t *node);

void parse_create(parser_t *p, node_cmd_create_drop_t *node);

void parse_drop(parser_t *p, node_cmd_create_drop_t *node);

void parse_db(parser_t *p, node_cmd_db_t *node);

void parse_command(parser_t *p);

void parser_set_error(parser_t *p, parser_error_code code);

void describe_parse_tree(parser_t *p, parse_tree_t *tree);

#endif // _CB_CLI_PARSER_H
