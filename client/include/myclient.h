/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** myclient
*/

#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include "uuid/uuid.h"
#include "network/api_client.h"
#include "network/dto.h"
#include "json/json.h"
#include "teams_defines.h"

#define _GNU_SOURCE


// --------------------------- CLIENT CONTEXT ------------------------------
/**
 * @brief Structure that contains the context of the client
 * It contains the team_uuid, channel_uuid and thread_uuid
 * If the client is not in a team, channel or thread, the
 * corresponding uuid is NULL
 * The context is used to know in which team, channel or
 * thread the client is when he uses commands like /list,
 * /info or /create
 * It will be updated when the client uses the /use command
 *
 * @param team_uuid The uuid of the team
 * @param channel_uuid The uuid of the channel
 * @param thread_uuid The uuid of the thread
 * @author @Marius-P1
 */
typedef struct context_s {
    char const *team_uuid;
    char const *channel_uuid;
    char const *thread_uuid;
} context_t;


// --------------------------- CLIENT STRUCTURE ----------------------------

/**
 * @brief Structure that contains the client and its information
 * It contains the context of the client, the user_uuid,
 * the user_name, the status of the client (is_logged,
 * waiting_for_response, running, is_event), the buffer
 * of the client, the api_handler
 * The client is used to store the information of the client
 * and to know if the client is logged, waiting for a response,
 * running or if it is an event
 *
 * @param context The context of the client
 * @param user_uuid The uuid of the user
 * @param user_name The name of the user
 * @param is_logged The status of the client
 * (true if the client is logged else false)
 * @param waiting_for_response The status of the client
 * (true if the client is waiting for a response else false)
 * @param running The status of the client
 * (true if the client is running else false)
 * @param is_event The status of the client
 * (true if the client is waiting for an event else false)
 * @param buffer The buffer for the command of the client
 * @param instance_nb The number of the instance
 * @param api_handler The api_handler
 * (to send requests to the server)
 * @author @Marius-P1
 */
typedef struct client_s {
    context_t *context;
    char const *user_uuid;
    char const *user_name;
    bool is_logged;
    bool waiting_for_response;
    bool running;
    bool is_event;
    char *buffer;
    size_t instance_id;
    api_client_t *api_handler;
} client_t;


// --------------------------- CLIENT METHODS ------------------------------

/**
 * @brief Launch the client
 * It will initialize the client and the api_handler
 * Then it will read the input of the user and send
 * the command to the server, and handle the response
 *
 * @param ac number of arguments
 * @param av given arguments
 * @return int 0 if the client worked successfully
 * else 84 if an error occured
 * @author @Marius-P1
 */
int client(int ac, char **av);


// --------------------------- ERROR HANDLING ------------------------------

/**
 * @brief Check if the arguments given to the client are valid
 * We need to have 3 arguments: the name of the program,
 * the ip of the server and the port of the server
 * The ip must be at the format "xxx.xxx.xxx.xxx"
 * The port must be a positive number
 * If the arguments are not valid, we print the help
 *
 * @param ac number of arguments
 * @param av given arguments
 * @return int 0 if the arguments are valid else 84
 * @author @Marius-P1
 */
int is_valid_args(int ac, char **av);

/**
 * @brief Print the help of the client
 * It will print the usage of the client and the
 * description of the arguments
 * The help is printed when the user gives the argument
 * "-help" to the client or when the arguments are not valid
 * @author @Marius-P1
 */
void print_help(void);

/**
 * @brief Parse the command given by the user
 * It will split the command into an array of strings
 * The command is split by the space character
 * The first element of the array is the command
 * The other elements are the arguments of the command
 * The arguments should be quoted with double quotes
 * or it will be considered as an error
 *
 * @param cmd The command string given by the user
 * @return char** The array of strings of the command
 * @author @Marius-P1
 */
char **parse_command(char *cmd);


// --------------------------- UTILS METHODS ------------------------------

/**
 * @brief Get the length of a tab of strings
 * It will return the number of strings in the tab
 * The tab should be NULL terminated
 *
 * @param tab The tab of strings
 * @return size_t The number of strings in the tab
 * @author @Marius-P1
 */
size_t tab_len(char **tab);

/**
 * @brief Create the bearer token for the client
 * It will create the bearer token with the uuid
 * of the client
 * The bearer token is used to authenticate the client
 * when he sends requests to the server
 * The bearer token is created by adding "Bearer " before
 * the uuid of the client and the instance_id of the client
 * The bearer token is used in the header of the request
 * to authenticate the client
 *
 * @param uuid The uuid of the client
 * @param instance_id The instance_id of the client
 * @return char* The bearer token of the client
 * @author @Marius-P1
 */
char *add_bearer(const char *uuid, size_t instance_id);
