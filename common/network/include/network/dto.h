/*
** EPITECH PROJECT, 2024
** network
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include "network/types.h"

// ------------------ REQUEST ------------------
/**
 * @brief Deserialize a request from a buffer
 * @param buffer the buffer to deserialize
 * @return the deserialized request
 */
request_t *deserialize_request(char *buffer);
/**
 * @brief Add a header to a request
 * @param req request to add the header to
 * @param key the key of the header
 * @param value the value of the header
 */
void request_add_header(request_t *req, char *key, char *value);
/**
 * @brief Add a param to a request
 * @param req request to add the param to
 * @param key the key of the param
 * @param value the value of the param
 */
void request_add_param(request_t *req, char *key, char *value);
/**
 * @brief Check whether a request has a header
 * @param req the request to check
 * @param key the key of the header
 * @return true if the request has the header, false otherwise
 */
bool request_has_header(request_t *req, char *key);
/**
 * @brief Check whether a request has a param
 * @param req the request to check
 * @param key the key of the param
 * @return true if the request has the param, false otherwise
 */
bool request_has_param(request_t *req, char *key);
/**
 * @brief Get a header from a request
 * @param req the request to get the header from
 * @param key the key of the header
 * @return the value of the header, or NULL if the header does not exist
 */
char *request_get_header(request_t *req, char *key);
/**
 * @brief Get a param from a request
 * @param req the request to get the param from
 * @param key the key of the param
 * @return the value of the param, or NULL if the param does not exist
 */
char *request_get_param(request_t *req, char *key);
/**
 * @brief Destroy a request
 * @param req the request to destroy
 */
void destroy_request(request_t *req);
/**
 * @brief Serialize a request to a buffer
 * @param request the request to serialize
 * @return the serialized buffer
 */
char *serialize_request(request_t request);
// ------------------ RESPONSE ------------------
/**
 * @brief Serialize a response to a buffer
 * @param response the response to serialize
 * @return the serialized buffer
 */
char *serialize_response(response_t response);
/**
 * @brief Destroy a response
 * @param res the response to destroy
 */
void destroy_response(response_t *res);
/**
 * @brief Deserialize a response from a buffer
 * @param buffer the buffer to deserialize
 * @return the deserialized response
 */
response_t *deserialize_response(char *buffer);
/**
 * @brief Add a header to a response
 * @param res response to add the header to
 * @param key the key of the header
 * @param value the value of the header
 */
void response_add_header(response_t *res, char *key, char *value);
