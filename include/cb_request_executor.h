/**
 * Copyright (c) 2021-present Adil Benhlal <abenhlal@cborgdb.com>
 *
 */

#ifndef _CB_REQUEST_EXECUTOR_H
#define _CB_REQUEST_EXECUTOR_H

#include <stdint.h>
#include <stddef.h>

/**
 * create_db
 * payload :
 *  - string db_name;
 */
void cb_request_execute_create_db(uint8_t *msg_payload, response_t *res);

/**
 * drop_db
 * payload :
 *  - string db_name;
 */
void cb_request_execute_drop_db(uint8_t *msg_payload, response_t *res);

/**
 * create_collection
 * payload :
 *  - string db_name;
 *  - string collection_name;
 */
void cb_request_execute_create_collection(uint8_t *msg_payload, response_t *res);

/**
 * drop_collection
 * payload :
 *  - string db_name;
 *  - string collection_name;
 */
void cb_request_execute_drop_collection(uint8_t *msg_payload, response_t *res);

/**
 * insert_one
 * payload :
 *  - string db_name
 *  - string collection_name;
 *  - item
 */
void cb_request_execute_insert_one(uint8_t *msg_payload, response_t *res);

/**
 * find_one
 * payload :
 *  - string db_name
 *  - string collection_name;
 *  - item
 */
void cb_request_execute_find_one(uint8_t *msg_payload, response_t *res);

/**
 * update_one
 * payload :
 *  - string db_name
 *  - string collection_name;
 *  - old item
 *  - new item
 */
void cb_request_execute_update_one(uint8_t *msg_payload, response_t *res);

/**
 * update_all
 * payload :
 *  - string db_name
 *  - string collection_name;
 *  - old item
 *  - new item
 */
void cb_request_execute_update_all(uint8_t *msg_payload, response_t *res);

/**
 * delete_one
 * payload :
 *  - string db_name
 *  - string collection_name;
 *  - item
 */
void cb_request_execute_delete_one(uint8_t *msg_payload, response_t *res);

/**
 * delete_all
 * payload :
 *  - string db_name
 *  - string collection_name;
 *  - item
 */
void cb_request_execute_delete_all(uint8_t *msg_payload, response_t *res);

/**
 * list dbs
 */
void cb_request_execute_list_dbs(uint8_t *msg_payload, response_t *res);

/**
 * list collections
 * payload:
 *  - string db_name
 */
void cb_request_execute_list_collections(uint8_t *msg_payload, response_t *res);

void cb_request_executor(request_t *req, response_t *res);


#endif // _CB_REQUEST_EXECUTOR_H
