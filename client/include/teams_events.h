/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** teams_events
*/

#pragma once

#include "myclient.h"


// --------------------------- EVENTS STRUCTURES ---------------------------

/**
 * @brief Enum of all the possible events
 *
 * @param LOGGED_IN: User logged in
 * @param LOGGED_OUT: User logged out
 * @param DM_RECEIVED: Direct message received
 * @param TEAM_CREATED: Team created
 * @param CHANNEL_CREATED: Channel created
 * @param THREAD_CREATED: Thread created
 * @param THREAD_REPLIED: Thread replied
 * @param NONE: No event
 * @author @Marius-P1
 */
typedef enum client_event_e {
    LOGGED_IN,
    LOGGED_OUT,
    DM_RECEIVED,
    TEAM_CREATED,
    CHANNEL_CREATED,
    THREAD_CREATED,
    THREAD_REPLIED,
    NONE,
} client_event_t;

/**
 * @brief Structure that contains the event and the callback
 * to call when the event is received
 *
 * @param event The event type
 * @param callback The callback function to call
 * when the event is received
 * @author @Marius-P1
 */
typedef struct event_bindig_s {
    client_event_t event;
    void (*callback)(json_object_t *data, client_t *client);
} event_binding_t;

/**
 * @brief Array of all the events and their callbacks
 * to call when the event is received
 *
 * @author @Marius-P1
 */
extern const event_binding_t event_bindings[];


// --------------------------- EVENTS FUNCTIONS ----------------------------

/**
 * @brief Function that sends the request to get the events
 * to the server
 * This function is called again when the client receives an event
 *
 * @param client The client
 * @author @Marius-P1
 */
void send_events(client_t *client);

/**
 * @brief Function that handles the event logged in
 * It will call the client_event_logged_in function
 * from the libmyteams to print the message
 * when an user logs in on the server
 *
 * @param data The data of the event
 * @param client The client
 * @see client_event_logged_in in logging_client.h
 * @author @Marius-P1
 */
void logged_in_callback(json_object_t *data, client_t *client);

/**
 * @brief Function that handles the event logged out
 * It will call the client_event_logged_out function
 * from the libmyteams to print the message
 * when an user logs out on the server
 *
 * @param data The data of the event
 * @param client The client
 * @see client_event_logged_out in logging_client.h
 * @author @Marius-P1
 */
void logged_out_callback(json_object_t *data, client_t *client);

/**
 * @brief Function that handles the event direct message received
 * It will call the client_event_private_message_received
 * function from the libmyteams to print the message
 * when an user receives a direct message on the server
 *
 * @param data The data of the event
 * @param client The client
 * @see client_event_private_message_received
 * in logging_client.h
 * @author @Marius-P1
 */
void dm_received_callback(json_object_t *data, client_t *client);

/**
 * @brief Function that handles the event team created
 * It will call the client_event_team_created function
 * from the libmyteams to print the message
 * when a team is created on the server
 *
 * @param data The data of the event
 * @param client The client
 * @see client_event_team_created in logging_client.h
 * @author @Marius-P1
 */
void team_created_callback(json_object_t *data, client_t *client);

/**
 * @brief Function that handles the event channel created
 * It will call the client_event_channel_created function
 * from the libmyteams to print the message
 * when a channel is created on the server
 *
 * @param data The data of the event
 * @param client The client
 * @see client_event_channel_created in logging_client.h
 * @author @Marius-P1
 */
void channel_created_callback(json_object_t *data, client_t *client);

/**
 * @brief Function that handles the event thread created
 * It will call the client_event_thread_created function
 * from the libmyteams to print the message
 * when a thread is created on the server
 *
 * @param data The data of the event
 * @param client The client
 * @see client_event_thread_created in logging_client.h
 * @author @Marius-P1
 */
void thread_created_callback(json_object_t *data, client_t *client);

/**
 * @brief Function that handles the event thread replied
 * It will call the client_event_thread_reply_received
 * function from the libmyteams to print the message
 * when a thread is replied on the server
 *
 * @param data The data of the event
 * @param client The client
 * @see client_event_thread_reply_received
 * in logging_client.h
 * @author @Marius-P1
 */
void thread_replied_callback(json_object_t *data, client_t *client);

/**
 * @brief Function that handles the logout
 * when the client is leaving the program
 * It will do nearly the same thing as the logout command
 *
 * @param client The client
 * @see client_event_logged_out in logging_client.h
 * @author @Marius-P1
 */
void logout_when_leaving(client_t *client);
