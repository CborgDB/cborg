/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include "tools/cli/cb_cli_parser.h"

#include <stdio.h>

parser_t parser_init(scanner_t *s) {
  return (parser_t){.s = s, .status = PARSER_OK};
}

void parse_help(parser_t *p, node_cmd_help_t *help) {
  scanner_next(p->s, 1);
  scanner_update_identifier_to_keyword(&(p->s->last_token));
  help->cmd = p->s->last_token;
  switch (help->cmd.value) {
  case TOKEN_SHOW:
  case TOKEN_USE:
  case TOKEN_CREATE:
  case TOKEN_DROP:
  case TOKEN_DB:
  case TOKEN_END:
    break;
  default:
    parser_set_error(p, P_ERR_UNKNOWN_COMMAND);
    printf("error: %s: \"%.*s\"\n", parser_error_string[P_ERR_UNKNOWN_COMMAND],
           (int)(help->cmd.end - help->cmd.start), help->cmd.start);
    break;
  }
}

void parse_show(parser_t *p, node_cmd_show_t *show) {
  scanner_next(p->s, 1);
  scanner_update_identifier_to_keyword(&(p->s->last_token));
  show->entity_type = p->s->last_token;
  switch (show->entity_type.value) {
  case TOKEN_DBS:
  case TOKEN_COLLECTIONS:
    break;
  default:
    parser_set_error(p, P_ERR_DBS_OR_COLLECTIONS_EXPECTED);
    printf("error: %s: \"%.*s\"\n",
           parser_error_string[P_ERR_DBS_OR_COLLECTIONS_EXPECTED],
           (int)(show->entity_type.end - show->entity_type.start),
           show->entity_type.start);
    break;
  }
}

void parse_use(parser_t *p, node_cmd_use_t *use) {
  scanner_next(p->s, 1);
  use->db_name = p->s->last_token;
  switch (use->db_name.value) {
  case TOKEN_IDENTIFIER:
    break;
  default:
    parser_set_error(p, P_ERR_IDENTIFIER_EXPECTED);
    printf("error: %s: \"%.*s\"\n",
           parser_error_string[P_ERR_IDENTIFIER_EXPECTED],
           (int)(use->db_name.end - use->db_name.start), use->db_name.start);
    break;
  }
}

void parse_create_drop(parser_t *p, node_cmd_create_drop_t *cd) {
  scanner_next(p->s, 1);
  scanner_update_identifier_to_keyword(&(p->s->last_token));
  cd->entity_type = p->s->last_token;
  switch (cd->entity_type.value) {
  case TOKEN_COLLECTION:
  case TOKEN_DB:
    scanner_next(p->s, 1);
    cd->name = p->s->last_token;
    if (cd->name.value != TOKEN_IDENTIFIER)
      parser_set_error(p, P_ERR_IDENTIFIER_EXPECTED);
    break;
  default:
    parser_set_error(p, P_ERR_ENTITY_TYPE_EXPECTED);
    break;
  }
}

void parse_arg_function(parser_t *p, int *arg_is_positive, token_t *arg) {
  scanner_next(p->s, 1);
  if (p->s->last_token.value == TOKEN_SIGN) {
    if (*(p->s->last_token.start) == '-') {
      *arg_is_positive = 0;
    } else {
      *arg_is_positive = 1;
    }
    scanner_next(p->s, 0);
  } else {
    *arg_is_positive = 1;
  }

  *arg = p->s->last_token;
  if (p->s->last_token.value != TOKEN_NUMBER)
    parser_set_error(p, P_ERR_NUMBER_EXPECTED);
}

void parse_db_function_one_arg(parser_t *p, node_cmd_db_t *db) {
  scanner_next(p->s, 0);
  if (p->s->last_token.value == TOKEN_LPAREN) {
    parse_arg_function(p, &(db->arg1_is_positive), &(db->arg1));
    scanner_next(p->s, 1);
    if (p->s->last_token.value != TOKEN_RPAREN)
      parser_set_error(p, P_ERR_RPAREN_EXPECTED);
  } else {
    parser_set_error(p, P_ERR_LPAREN_EXPECTED);
  }
}

void parse_db_function_two_arg(parser_t *p, node_cmd_db_t *db) {
  scanner_next(p->s, 0);
  if (p->s->last_token.value == TOKEN_LPAREN) {
    parse_arg_function(p, &(db->arg1_is_positive), &(db->arg1));
    scanner_next(p->s, 1);
    if (p->s->last_token.value == TOKEN_COMMA)
      parse_arg_function(p, &(db->arg2_is_positive), &(db->arg2));
    scanner_next(p->s, 1);
    if (p->s->last_token.value != TOKEN_RPAREN)
      parser_set_error(p, P_ERR_RPAREN_EXPECTED);
  } else {
    parser_set_error(p, P_ERR_LPAREN_EXPECTED);
  }
}

void parse_db_function(parser_t *p, node_cmd_db_t *db) {
  scanner_next(p->s, 0);
  scanner_update_identifier_to_keyword(&(p->s->last_token));
  db->operation = p->s->last_token;
  switch (db->operation.value) {
  case TOKEN_INSERTONE:
  case TOKEN_FINDONE:
  case TOKEN_DELETEONE:
  case TOKEN_DELETEALL:
    parse_db_function_one_arg(p, db);
    break;
  case TOKEN_UPDATEONE:
  case TOKEN_UPDATEALL:
    parse_db_function_two_arg(p, db);
    break;
  default:
    parser_set_error(p, P_ERR_UNKNOWN_OPERATION);
    break;
  }
}

void parse_db(parser_t *p, node_cmd_db_t *db) {
  scanner_next(p->s, 0);
  // db.
  if (p->s->last_token.value == TOKEN_DOT) {
    scanner_next(p->s, 0);
    db->is_an_operation = 1;
    db->coll_name = p->s->last_token;
    // db.<coll_name>
    if (db->coll_name.value == TOKEN_IDENTIFIER) {
      scanner_next(p->s, 0);
      // db.<coll_name>.
      if (p->s->last_token.value == TOKEN_DOT) {
        parse_db_function(p, db);
      } else {
        parser_set_error(p, P_ERR_DOT_EXPECTED);
      }
    } else {
      parser_set_error(p, P_ERR_INVALID_COLL_NAME);
    }
  } else if (p->s->last_token.value == TOKEN_WHITESPACE ||
             p->s->last_token.value == TOKEN_END) {
    // db
    db->is_an_operation = 0;
  } else {
    parser_set_error(p, P_ERR_ERROR_COMMAND);
  }
}

void parse_command(parser_t *p) {
  scanner_next(p->s, 1);
  scanner_update_identifier_to_keyword(&(p->s->last_token));
  p->tree.kind = p->s->last_token;
  switch (p->s->last_token.value) {
  case TOKEN_HELP:
    parse_help(p, (node_cmd_help_t *)&(p->tree.cmd));
    break;
  case TOKEN_SHOW:
    parse_show(p, (node_cmd_show_t *)&(p->tree.cmd));
    break;
  case TOKEN_USE:
    parse_use(p, (node_cmd_use_t *)&(p->tree.cmd));
    break;
  case TOKEN_CREATE:
  case TOKEN_DROP:
    parse_create_drop(p, (node_cmd_create_drop_t *)&(p->tree.cmd));
    break;
  case TOKEN_DB:
    parse_db(p, (node_cmd_db_t *)&(p->tree.cmd));
    break;
  case TOKEN_EXIT:
  case TOKEN_END:
    return;
    break;
  default:
    parser_set_error(p, P_ERR_UNKNOWN_COMMAND);
    return;
    break;
  }

  if (!scanner_has_finished(p->s)) {
    scanner_next(p->s, 1);
    if (p->s->last_token.value != TOKEN_END)
      parser_set_error(p, P_ERR_ERROR_COMMAND);
  }
}

void parser_set_error(parser_t *p, parser_error_code code) {
  p->status = PARSER_ERROR;
  p->error.code = code;
  p->error.token_in_error = p->s->last_token;
}

void describe_parse_tree(parser_t *p, parse_tree_t *tree) {
  if (tree->kind.value == TOKEN_END)
    printf("kind=\"%d\" string=\"\\n\" ", tree->kind.value);
  else
    printf("kind=\"%d\" string=\"%.*s\" ", tree->kind.value,
           (int)(tree->kind.end - tree->kind.start), tree->kind.start);
  switch (tree->kind.value) {
  case TOKEN_SHOW:
    printf("entity_type=\"%d\" string=\"%.*s\" ",
           tree->cmd.show.entity_type.value,
           (int)(tree->cmd.show.entity_type.end -
                 tree->cmd.show.entity_type.start),
           tree->cmd.show.entity_type.start);
    break;
  case TOKEN_HELP:
    if (tree->cmd.help.cmd.value != TOKEN_END)
      printf("cmd=\"%d\" string=\"%.*s\" ", tree->cmd.help.cmd.value,
             (int)(tree->cmd.help.cmd.end - tree->cmd.help.cmd.start),
             tree->cmd.help.cmd.start);
    break;
  case TOKEN_USE:
    printf("db_name=\"%d\" string=\"%.*s\" ", tree->cmd.use.db_name.value,
           (int)(tree->cmd.use.db_name.end - tree->cmd.use.db_name.start),
           tree->cmd.use.db_name.start);
    break;
  case TOKEN_CREATE:
  case TOKEN_DROP:
    printf("entity_type=\"%d\" string=\"%.*s\" ",
           tree->cmd.create_drop.entity_type.value,
           (int)(tree->cmd.create_drop.entity_type.end -
                 tree->cmd.create_drop.entity_type.start),
           tree->cmd.create_drop.entity_type.start);
    printf("name=\"%d\" string=\"%.*s\" ", tree->cmd.create_drop.name.value,
           (int)(tree->cmd.create_drop.name.end -
                 tree->cmd.create_drop.name.start),
           tree->cmd.create_drop.name.start);
    break;
  case TOKEN_DB:
    printf("is_an_operation=\"%d\" ", tree->cmd.db.is_an_operation);
    if (tree->cmd.db.is_an_operation == 1) {
      printf("coll_name=\"%d\" string=\"%.*s\" ", tree->cmd.db.coll_name.value,
             (int)(tree->cmd.db.coll_name.end - tree->cmd.db.coll_name.start),
             tree->cmd.db.coll_name.start);
      printf("operation=\"%d\" string=\"%.*s\" ", tree->cmd.db.operation.value,
             (int)(tree->cmd.db.operation.end - tree->cmd.db.operation.start),
             tree->cmd.db.operation.start);
      printf("arg1=\"%d\" string=\"%.*s\" ", tree->cmd.db.arg1.value,
             (int)(tree->cmd.db.arg1.end - tree->cmd.db.arg1.start),
             tree->cmd.db.arg1.start);
      printf("arg1_is_positive=\"%d\" ", tree->cmd.db.arg1_is_positive);
      printf("arg2=\"%d\" string=\"%.*s\" ", tree->cmd.db.arg2.value,
             (int)(tree->cmd.db.arg2.end - tree->cmd.db.arg2.start),
             tree->cmd.db.arg2.start);
      printf("arg2_is_positive=\"%d\" ", tree->cmd.db.arg2_is_positive);
    }
    break;
  default:
    break;
  }
  printf("parser_status=\"%d\"\n", p->status);
}
