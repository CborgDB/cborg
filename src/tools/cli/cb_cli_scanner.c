/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include "tools/cli/cb_cli_scanner.h"

scanner_t scanner_init(char *p_start, int p_len) {
  return (scanner_t){
      .buf_start = p_start, .buf_current = p_start, .buf_end = p_start + p_len};
}

token_t scanner_next(scanner_t *s, int skip_space) {
  do {
    token_t t = tokenizer(s->buf_current, s->buf_end - s->buf_current);
    s->buf_current = t.end;
    s->last_token = t;
  } while (s->last_token.value == TOKEN_WHITESPACE && skip_space &&
           (s->buf_end - s->buf_current > 0));
  return s->last_token;
}

int scanner_has_finished(scanner_t *s) { return s->buf_current == s->buf_end; }

void scanner_update_identifier_to_keyword(token_t *t) {
  char *p = t->start;
  int p_len = (int)(t->end - t->start);
  if (2 <= p_len && p_len <= 11) {
    // clang-format off
    switch (*p) {
      ////////////
      //  show  //
      ////////////
      case 's':
      case 'S': 
        if((p_len == 4) &&
          (p[1] == 'h' || p[1] == 'H') &&
          (p[2] == 'o' || p[2] == 'O') &&
          (p[3] == 'w' || p[3] == 'W')){
            t->value = TOKEN_SHOW;
        }
        break;
      /////////////////////////////////
      //  use, updateOne, updateAll  //
      /////////////////////////////////
      case 'u':
      case 'U':
        if((p_len == 3) &&
          (p[1] == 's' || p[1] == 'S') &&
          (p[2] == 'e' || p[2] == 'E')){
            t->value = TOKEN_USE;
        }
        
        if((p_len == 9) &&
          (p[1] == 'p' || p[1] == 'P') &&
          (p[2] == 'd' || p[2] == 'D') &&
          (p[3] == 'a' || p[3] == 'A') &&
          (p[4] == 't' || p[4] == 'T') &&
          (p[5] == 'e' || p[5] == 'E')){
            if((p[6] == 'o' || p[6] == 'O') &&
              (p[7] == 'n' || p[7] == 'N') &&
              (p[8] == 'e' || p[8] == 'E')) {
                t->value = TOKEN_UPDATEONE;
            }

            if((p[6] == 'a' || p[6] == 'A') &&
              (p[7] == 'l' || p[7] == 'L') &&
              (p[8] == 'l' || p[8] == 'L')) {
                t->value = TOKEN_UPDATEALL;
            }
        }
        break;
      //////////////
      //  create  //
      //////////////
      case 'c': // create
      case 'C':
        if((p_len == 6) &&
          (p[1] == 'r' || p[1] == 'R') &&
          (p[2] == 'e' || p[2] == 'E') &&
          (p[3] == 'a' || p[3] == 'A') &&
          (p[4] == 't' || p[4] == 'T') &&
          (p[5] == 'e' || p[5] == 'E')){
            t->value = TOKEN_CREATE;
        }

        if((p_len >= 10) &&
          (p[1] == 'o' || p[1] == 'O') &&
          (p[2] == 'l' || p[2] == 'L') &&
          (p[3] == 'l' || p[3] == 'L') &&
          (p[4] == 'e' || p[4] == 'E') &&
          (p[5] == 'c' || p[5] == 'C') &&
          (p[6] == 't' || p[6] == 'T') &&
          (p[7] == 'i' || p[7] == 'I') &&
          (p[8] == 'o' || p[8] == 'O') &&
          (p[9] == 'n' || p[9] == 'N')){
            if(p_len == 11 && (p[10] == 's' || p[10] == 'S'))
              t->value = TOKEN_COLLECTIONS;
            else
              t->value = TOKEN_COLLECTION;
        }
        break;
      //////////////////////////////////////
      //  drop, db, dbs, deleteOne, deleteAll  //
      //////////////////////////////////////
      case 'd':
      case 'D':
        if((p_len == 4) &&
          (p[1] == 'r' || p[1] == 'R') &&
          (p[2] == 'o' || p[2] == 'O') &&
          (p[3] == 'p' || p[3] == 'P')){
            t->value = TOKEN_DROP;
        }

        if((p_len == 3) &&
          (p[1] == 'b' || p[1] == 'B') &&
          (p[2] == 's' || p[2] == 'S')){
            t->value = TOKEN_DBS;
        }

        if((p_len == 2) &&
          (p[1] == 'b' || p[1] == 'B')){
            t->value = TOKEN_DB;
        }

        if((p_len == 9) &&
          (p[1] == 'e' || p[1] == 'E') &&
          (p[2] == 'l' || p[2] == 'L') &&
          (p[3] == 'e' || p[3] == 'E') &&
          (p[4] == 't' || p[4] == 'T') &&
          (p[5] == 'e' || p[5] == 'E')){
            if((p[6] == 'o' || p[6] == 'O') &&
              (p[7] == 'n' || p[7] == 'N') &&
              (p[8] == 'e' || p[8] == 'E')) {
                t->value = TOKEN_DELETEONE;
            }

            if((p[6] == 'a' || p[6] == 'A') &&
              (p[7] == 'l' || p[7] == 'L') &&
              (p[8] == 'l' || p[8] == 'L')) {
                t->value = TOKEN_DELETEALL;
            }
        }
        break;
      ////////////
      //  help  //
      ////////////
      case 'h':
      case 'H':
        if((p_len == 4) &&
          (p[1] == 'e' || p[1] == 'E') &&
          (p[2] == 'l' || p[2] == 'L') &&
          (p[3] == 'p' || p[3] == 'P')){
            t->value = TOKEN_HELP;
        }
        break;
      /////////////////
      //  insertOne  //
      /////////////////
      case 'i':
      case 'I':
        if((p_len == 9) &&
          (p[1] == 'n' || p[1] == 'N') &&
          (p[2] == 's' || p[2] == 'S') &&
          (p[3] == 'e' || p[3] == 'E') &&
          (p[4] == 'r' || p[4] == 'R') &&
          (p[5] == 't' || p[5] == 'T') &&
          (p[6] == 'o' || p[6] == 'O') &&
          (p[7] == 'n' || p[7] == 'N') &&
          (p[8] == 'e' || p[8] == 'E')){
            t->value = TOKEN_INSERTONE;
        }
        break;
      ///////////////
      //  findOne  //
      ///////////////
      case 'f':
      case 'F':
        if((p_len == 7) &&
          (p[1] == 'i' || p[1] == 'I') &&
          (p[2] == 'n' || p[2] == 'N') &&
          (p[3] == 'd' || p[3] == 'D') &&
          (p[4] == 'o' || p[4] == 'O') &&
          (p[5] == 'n' || p[5] == 'N') &&
          (p[6] == 'e' || p[6] == 'E')){
            t->value = TOKEN_FINDONE;
        }
        break;
      ///////////////
      //  exit  //
      ///////////////
      case 'e':
      case 'E':
        if((p_len == 4) &&
          (p[1] == 'x' || p[1] == 'X') &&
          (p[2] == 'i' || p[2] == 'I') &&
          (p[3] == 't' || p[3] == 'T')){
            t->value = TOKEN_EXIT;
        }
        break;
    default:
      break;
    }
  }
}
