/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifndef _CB_MSG_H
#define _CB_MSG_H

typedef enum {
  OP_CREATE_DB = 1,
  OP_DROP_DB = 2,
  OP_CREATE_COLLECTION = 3,
  OP_DROP_COLLECTION = 4,
  OP_INSERT_ONE = 5,
  OP_FIND_ONE = 6,
  OP_UPDATE_ONE = 7,
  OP_UPDATE_ALL = 8,
  OP_DELETE_ONE = 9,
  OP_DELETE_ALL = 10,
  OP_LIST_DBS = 20,
  OP_LIST_COLLECTIONS = 21,
  OP_REPLY = 666,
} OP_CODE;

#endif // _CB_MSG_H
