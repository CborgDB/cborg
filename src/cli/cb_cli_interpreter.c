/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include "cli/cb_cli_interpreter.h"
#include "cb_msg_encode.h"
#include "cli/cb_cli_help.h"
#include "cbor/cb_cbor_int.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

interpreter_t interpreter_init(parser_t *parser, char *db_in_use, char *buffer,
                               size_t buffer_size, int fd) {
  return (interpreter_t){.status = INTERPRETER_OK,
                         .parser = parser,
                         .db_in_use = db_in_use,
                         .buf = buffer,
                         .buf_size = buffer_size,
                         .fd = fd};
}

void interpreter_recv_reply(interpreter_t *i) {
  uint8_t reply[4096];
  size_t nread = read(i->fd,reply,9);

  uint64_t msg_length;
  cb_cbor_get_uint(reply,&msg_length);

  nread = read(i->fd,reply + 9,msg_length - 9);
  uint64_t op_code;
  cb_cbor_get_uint(reply + 9,&op_code);
  
  uint64_t ib_string_size = cb_cbor_get_uint_size(reply + 18);
  printf("\n%.*s\n", msg_length - 18 - ib_string_size, reply+18+ib_string_size);
}

void interpreter_recv_reply_show(interpreter_t *i) {
  uint8_t reply[4096];
  size_t nread = read(i->fd,reply,9);

  uint64_t msg_length;
  cb_cbor_get_uint(reply,&msg_length);

  nread = read(i->fd,reply + 9,msg_length - 9);
  uint64_t op_code;
  cb_cbor_get_uint(reply + 9,&op_code);
  
  uint8_t *p = reply + 18;
  uint64_t len = msg_length - 18;
  printf("\n");
  while(len > 0) {
    uint64_t ib_string_size = cb_cbor_get_uint_size(p);
    uint64_t string_len = 0;
    cb_cbor_get_uint(p, &string_len);
    printf("- %.*s\n", string_len, p + ib_string_size);
    p += ib_string_size + string_len;
    len -= ib_string_size + string_len;
  }
  printf("\n");
}

void interpret_show_dbs(interpreter_t *i, node_cmd_show_t *show) {
  char buffer[4096];
  size_t written = cb_msg_encode_list_databases(buffer, 4096);
  write(i->fd, buffer, written);
  interpreter_recv_reply_show(i);
}

void interpret_show_collections(interpreter_t *i, node_cmd_show_t *show) {
  char buffer[4096];
  size_t written = cb_msg_encode_list_collections(buffer, 4096, i->db_in_use,
                                                  strlen(i->db_in_use));
  write(i->fd, buffer, written);
  interpreter_recv_reply_show(i);
}

void interpret_create_db(interpreter_t *i, node_cmd_create_drop_t *create) {
  char buffer[4096];
  size_t written = cb_msg_encode_create_db(
      buffer, 4096, create->name.start, create->name.end - create->name.start);
  write(i->fd, buffer, written);
  interpreter_recv_reply(i);
}

void interpret_create_collection(interpreter_t *i,
                                 node_cmd_create_drop_t *create) {
  char buffer[4096];
  size_t written = cb_msg_encode_create_collection(
      buffer, 4096, i->db_in_use, strlen(i->db_in_use), create->name.start,
      create->name.end - create->name.start);
  write(i->fd, buffer, written);
  interpreter_recv_reply(i);
}

void interpret_drop_db(interpreter_t *i, node_cmd_create_drop_t *create) {
  char buffer[4096];
  size_t written = cb_msg_encode_drop_db(buffer, 4096, create->name.start,
                                         create->name.end - create->name.start);
  write(i->fd, buffer, written);
  interpreter_recv_reply(i);
}

void interpret_drop_collection(interpreter_t *i,
                               node_cmd_create_drop_t *create) {
  char buffer[4096];
  size_t written = cb_msg_encode_drop_collection(
      buffer, 4096, i->db_in_use, strlen(i->db_in_use), create->name.start,
      create->name.end - create->name.start);
  write(i->fd, buffer, written);
  interpreter_recv_reply(i);
}

void interpret_db_insert_one(interpreter_t *i, node_cmd_db_t *db) {
  size_t written = 0;
  uint64_t v = strtoull(db->arg1.start, NULL, 10);
  v = db->arg1_is_positive || errno == ERANGE ? v : v - 1;
  errno = 0;
  char buffer[4096];
  written = cb_msg_encode_insert_one(
      buffer, 4096, i->db_in_use, strlen(i->db_in_use), db->coll_name.start,
      db->coll_name.end - db->coll_name.start, v, db->arg1_is_positive);
  write(i->fd, buffer, written);
  interpreter_recv_reply(i);
}

void interpret_db_find_one(interpreter_t *i, node_cmd_db_t *db) {
  size_t written = 0;
  uint64_t v = strtoull(db->arg1.start, NULL, 10);
  v = db->arg1_is_positive || errno == ERANGE ? v : v - 1;
  errno = 0;
  char buffer[4096];
  written = cb_msg_encode_find_one(
      buffer, 4096, i->db_in_use, strlen(i->db_in_use), db->coll_name.start,
      db->coll_name.end - db->coll_name.start, v, db->arg1_is_positive);
  write(i->fd, buffer, written);
  interpreter_recv_reply(i);
}

void interpret_db_update_one(interpreter_t *i, node_cmd_db_t *db) {
  size_t written = 0;

  uint64_t v1 = strtoull(db->arg1.start, NULL, 10);
  v1 = db->arg1_is_positive || errno == ERANGE ? v1 : v1 - 1;
  errno = 0;

  uint64_t v2 = strtoull(db->arg2.start, NULL, 10);
  v2 = db->arg2_is_positive || errno == ERANGE ? v2 : v2 - 1;
  errno = 0;

  char buffer[4096];
  written = cb_msg_encode_update_one(
      buffer, 4096, i->db_in_use, strlen(i->db_in_use), db->coll_name.start,
      db->coll_name.end - db->coll_name.start, v1, db->arg1_is_positive, v2,
      db->arg2_is_positive);
  write(i->fd, buffer, written);
  interpreter_recv_reply(i);
}

void interpret_db_update_all(interpreter_t *i, node_cmd_db_t *db) {
  size_t written = 0;

  uint64_t v1 = strtoull(db->arg1.start, NULL, 10);
  v1 = db->arg1_is_positive || errno == ERANGE ? v1 : v1 - 1;
  errno = 0;

  uint64_t v2 = strtoull(db->arg2.start, NULL, 10);
  v2 = db->arg2_is_positive || errno == ERANGE ? v2 : v2 - 1;
  errno = 0;

  char buffer[4096];
  written = cb_msg_encode_update_all(
      buffer, 4096, i->db_in_use, strlen(i->db_in_use), db->coll_name.start,
      db->coll_name.end - db->coll_name.start, v1, db->arg1_is_positive, v2,
      db->arg2_is_positive);
  write(i->fd, buffer, written);
  interpreter_recv_reply(i);
}

void interpret_db_delete_one(interpreter_t *i, node_cmd_db_t *db) {
  size_t written = 0;
  uint64_t v = strtoull(db->arg1.start, NULL, 10);
  v = db->arg1_is_positive || errno == ERANGE ? v : v - 1;
  errno = 0;
  char buffer[4096];
  written = cb_msg_encode_delete_one(
      buffer, 4096, i->db_in_use, strlen(i->db_in_use), db->coll_name.start,
      db->coll_name.end - db->coll_name.start, v, db->arg1_is_positive);
  write(i->fd, buffer, written);
  interpreter_recv_reply(i);
}

void interpret_db_delete_all(interpreter_t *i, node_cmd_db_t *db) {
  size_t written = 0;
  uint64_t v = strtoull(db->arg1.start, NULL, 10);
  v = db->arg1_is_positive || errno == ERANGE ? v : v - 1;
  errno = 0;
  char buffer[4096];
  written = cb_msg_encode_delete_all(
      buffer, 4096, i->db_in_use, strlen(i->db_in_use), db->coll_name.start,
      db->coll_name.end - db->coll_name.start, v, db->arg1_is_positive);
  write(i->fd, buffer, written);
  interpreter_recv_reply(i);
}

void interpret_show(interpreter_t *i, node_cmd_show_t *show) {
  switch (show->entity_type.value) {
  case TOKEN_DBS:
    interpret_show_dbs(i, show);
    break;
  case TOKEN_COLLECTIONS:
    interpret_show_collections(i, show);
    break;
  default:
    break;
  }
}

void interpret_help(interpreter_t *i, node_cmd_help_t *help) {
  switch (help->cmd.value) {
  case TOKEN_END:
    cb_cli_help();
    break;
  case TOKEN_SHOW:
    cb_cli_help_show();
    break;
  case TOKEN_USE:
    cb_cli_help_use();
    break;
  case TOKEN_CREATE:
    cb_cli_help_create();
    break;
  case TOKEN_DROP:
    cb_cli_help_drop();
    break;
  case TOKEN_DB:
    cb_cli_help_db();
    break;
  default:
    break;
  }
}

void interpret_use(interpreter_t *i, node_cmd_use_t *use) {
  switch (use->db_name.value) {
  case TOKEN_IDENTIFIER: {
    char *db_name = use->db_name.start;
    int db_length = use->db_name.end - use->db_name.start;
    strncpy(i->db_in_use, db_name, db_length);
    i->db_in_use[db_length] = '\0';
  } break;
  default:
    break;
  }
}

void interpret_create(interpreter_t *i, node_cmd_create_drop_t *create) {
  switch (create->entity_type.value) {
  case TOKEN_DB:
    interpret_create_db(i, create);
    break;
  case TOKEN_COLLECTION:
    interpret_create_collection(i, create);
    break;
  default:
    break;
  }
}

void interpret_drop(interpreter_t *i, node_cmd_create_drop_t *drop) {
  switch (drop->entity_type.value) {
  case TOKEN_DB:
    interpret_drop_db(i, drop);
    break;
  case TOKEN_COLLECTION:
    interpret_drop_collection(i, drop);
    break;
  default:
    break;
  }
}

void interpret_db(interpreter_t *i, node_cmd_db_t *db) {
  if (db->is_an_operation) {
    size_t written = 0;
    switch (db->operation.value) {
    case TOKEN_INSERTONE:
      interpret_db_insert_one(i, db);
      break;
    case TOKEN_FINDONE:
      interpret_db_find_one(i, db);
      break;
    case TOKEN_UPDATEONE:
      interpret_db_update_one(i, db);
      break;
    case TOKEN_UPDATEALL:
      interpret_db_update_all(i, db);
      break;
    case TOKEN_DELETEONE:
      interpret_db_delete_one(i, db);
      break;
    case TOKEN_DELETEALL:
      interpret_db_delete_all(i, db);
      break;
    default:
      break;
    }
  } else {
    printf("%s\n", i->db_in_use);
  }
}

void interpret(interpreter_t *i) {
  parse_tree_t tree = i->parser->tree;

  if (i->parser->status == PARSER_ERROR)
    return;

  switch (tree.kind.value) {
  case TOKEN_SHOW:
    interpret_show(i, &(tree.cmd.show));
    break;
  case TOKEN_HELP:
    interpret_help(i, &(tree.cmd.help));
    break;
  case TOKEN_USE:
    interpret_use(i, &(tree.cmd.use));
    break;
  case TOKEN_CREATE:
    interpret_create(i, &(tree.cmd.create_drop));
    break;
  case TOKEN_DROP:
    interpret_drop(i, &(tree.cmd.create_drop));
    break;
  case TOKEN_DB:
    interpret_db(i, &(tree.cmd.db));
    break;
  case TOKEN_EXIT:
    i->status = INTERPRETER_EXIT;
  default:
    break;
  }
}
