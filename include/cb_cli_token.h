/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifndef _CB_CLI_TOKEN_H
#define _CB_CLI_TOKEN_H

typedef enum  {
  /* Command */
  TOKEN_SHOW, 
  TOKEN_USE,
  TOKEN_CREATE,
  TOKEN_DROP,
  TOKEN_DB,
  TOKEN_DBS,
  TOKEN_COLLECTION,
  TOKEN_COLLECTIONS,
  TOKEN_HELP,
  TOKEN_EXIT,
  /* Opearations */
  TOKEN_INSERTONE,
  TOKEN_FINDONE,
  TOKEN_UPDATEONE,
  TOKEN_UPDATEALL,
  TOKEN_DELETEONE,
  TOKEN_DELETEALL,
  /* Property */
  TOKEN_DOT,
  /* Args */
  TOKEN_LPAREN,
  TOKEN_RPAREN,
  TOKEN_COMMA,
  TOKEN_IDENTIFIER,
  TOKEN_SIGN,
  TOKEN_NUMBER,
  TOKEN_WHITESPACE,
  TOKEN_END,
  TOKEN_ILLEGAL,
} token_value;

typedef struct {
  token_value value;
  char *start;
  char *end;
} token_t;

// Example token_t representation
//
//           0 
//           |                        
//           v___________________________________________________
//   Source: | d  b . u s e r s . i n s e r t O n e ( - 1 2 ) \n |
//           |________^_________^________________________________|
//                    |         |
//     Pointers:    start      end            
//     Value: IDENTIFIER
//     Length: end - start
//     String: "users"


token_t tokenizer(char *p, int p_len);

#endif // _CB_CLI_TOKEN_H
