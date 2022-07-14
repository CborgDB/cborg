/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#include "cb_cli_token.h"

token_t tokenizer(char *p, int p_len) {
  if (p_len > 0) {
    // clang-format off
    switch (*p) {
      ///////////
      //  DOT  //
      ///////////
      case '.':
        return (token_t){.value=TOKEN_DOT, .start=p, .end=p+1 };
        break;
      //////////////////
      //  WHITESPACE  //
      //////////////////
      case ' ':
      case '\r':
      case '\t':
        return (token_t){.value=TOKEN_WHITESPACE, .start=p, .end=p+1 };
        break;
      ///////////
      //  END  //
      ///////////
      case '\n':
        return (token_t){.value=TOKEN_END, .start=p, .end=p+1 };
      /////////////
      //  COMMA  //
      /////////////
      case ',':
        return (token_t){.value=TOKEN_COMMA, .start=p, .end=p+1 };
        break;
      //////////////
      //  LPAREN  //
      //////////////
      case '(':
        return (token_t){.value=TOKEN_LPAREN, .start=p, .end=p+1 };
        break;
      //////////////
      //  RPAREN  //
      //////////////
      case ')':
        return (token_t){.value=TOKEN_RPAREN, .start=p, .end=p+1 };
        break;
      ////////////
      //  SIGN  //
      ////////////
      case '+':
      case '-':
        return (token_t){.value=TOKEN_SIGN, .start=p, .end=p+1 };
    default:
      break;
    }
    //////////////////
    //  IDENTIFIER  //
    //////////////////
    // clang-format on
    if (('A' <= *p && *p <= 'Z') || ('a' <= *p && *p <= 'z')) {
      token_t id = {.value = TOKEN_IDENTIFIER, .start = p, .end = p + 1};
      while (('0' <= *(id.end) && *(id.end) <= '9') ||
             ('A' <= *(id.end) && *(id.end) <= 'Z') ||
             ('a' <= *(id.end) && *(id.end) <= 'z')) {
        id.end++;
      }
      return id;
    }
    //////////////
    //  NUMBER  //
    //////////////
    if (('1' <= *p && *p <= '9')) {
      token_t num = {.value = TOKEN_NUMBER, .start = p, .end = p + 1};
      while (('0' <= *(num.end) && *(num.end) <= '9'))
        num.end++;
      return num;
    }
  }
  return (token_t){.value = TOKEN_ILLEGAL, .start = p, .end = p + 1};
}
