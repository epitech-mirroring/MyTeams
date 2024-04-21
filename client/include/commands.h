/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** commands
*/

#pragma once

#include "myclient.h"

// --------------------------- COMMANDS STRUCTURE --------------------------

/**
 * @brief Structure that contains a command and its function
 * The command is a string that represents the command
 * The function is a pointer to the function that will be called
 * when the command is received
 * The commands structure is used to store all the commands
 * that the client can receive
 *
 * @param cmd The command
 * @param func The function to call when the command is received
 * @author @Marius-P1
 */
typedef struct command_s {
    char *cmd;
    void (*func)(char **parsed_cmd, client_t *client);
} command_t;

/**
 * @brief Array of all the commands and their functions
 * to call when the command is received
 * The commands array is used to store all the commands
 * that the client can receive
 *
 * @author @Marius-P1
 */
extern const command_t commands[];


// --------------------------- COMMANDS ------------------------------------

/**
 * @brief Function to call when a command is received
 * The function will parse the command and call the corresponding
 * function in the commands array
 * If the command is not found, the function will print "Unknown command"
 *
 * @param cmd The command to parse (given by the user)
 * @param client The client structure
 * @author @Marius-P1
 */
void on_command(char *cmd, client_t *client);

/**
 * @brief Command '/help' that will print all the available commands
 * The function will print all the commands in the commands array
 * The function will print the command and the description of the command
 *
 * @param parsed_cmd The parsed command
 * @param client The client structure
 * @author @Marius-P1
 */
void help(char **parsed_cmd);

/**
 * @brief Command '/login' that will log the user in
 * The function will send a request to the server to log the user in
 * The function will send the user_name given by the user
 * The function will print a message in case of success or error
 *
 * @param parsed_cmd The parsed command
 * @param client The client structure
 * @author @Marius-P1
 */
void login(char **parsed_cmd, client_t *client);

/**
 * @brief Command '/logout' that will log the user out
 * The function will send a request to the server to log the user out
 * The function will print a message in case of success or error
 *
 * @param parsed_cmd The parsed command
 * @param client The client structure
 * @author @Marius-P1
 */
void logout(char **parsed_cmd, client_t *client);

/**
 * @brief Command '/user' that will print the information of an user
 * The function will send a request to the server to
 * get the user information
 * The function will print the information of the user
 *
 * @param parsed_cmd The parsed command
 * @param client The client structure
 * @author @Marius-P1
 */
void user(char **parsed_cmd, client_t *client);

/**
 * @brief Command '/users' that will print all the users
 * The function will send a request to the server to get all the users
 * The function will print all the users and their information
 *
 * @param parsed_cmd The parsed command
 * @param client The client structure
 * @author @Marius-P1
 */
void users(char **parsed_cmd, client_t *client);

/**
 * @brief Command '/send' that will send a message to an user
 * The function will send a request to the server to send a message
 * to an user
 * The function will print a message in case of success or error
 *
 * @param parsed_cmd The parsed command
 * @param client The client structure
 * @author @Marius-P1
 */
void cmd_send(char **parsed_cmd, client_t *client);

/**
 * @brief Command '/messages' that will print all the messages
 * between the user and another user
 * The function will send a request to the server to get
 * all the messages between the user and another user
 * The function will print all the messages
 *
 * @param parsed_cmd The parsed command
 * @param client The client structure
 * @author @Marius-P1
 */
void messages(char **parsed_cmd, client_t *client);

/**
 * @brief Command '/subscribe' that will subscribe the user to a team
 * The function will send a request to the server to subscribe
 * the user to a team
 * The function will print a message in case of success or error
 *
 * @param parsed_cmd The parsed command
 * @param client The client structure
 * @author @Marius-P1
 */
void subscribe(char **parsed_cmd, client_t *client);

/**
 * @brief Command '/subscribed' that will print all the subscribed teams
 * or all the users subscribed to a team depending on the arguments
 * The function will send a request to the server to get all the
 * subscribed teams or all the users subscribed to a team
 * The function will print all the subscribed teams
 * or all the users subscribed to a team
 *
 * @param parsed_cmd The parsed command
 * @param client The client structure
 * @author @Marius-P1
 */
void subscribed(char **parsed_cmd, client_t *client);

/**
 * @brief Command '/unsubscribe' that will unsubscribe the user from a team
 * The function will send a request to the server to unsubscribe the user
 * from a team
 * The function will print a message in case of success or error
 *
 * @param parsed_cmd The parsed command
 * @param client The client structure
 * @author @Marius-P1
 */
void unsubscribe(char **parsed_cmd, client_t *client);

/**
 * @brief Command '/use' that will change the context of the client
 * The function will change the context of the client
 * The function will print a message in case of success or error
 *
 * @param parsed_cmd The parsed command
 * @param client The client structure
 * @author @Marius-P1
 */
void use(char **parsed_cmd, client_t *client);

// --------------------------- CREATE ---------------------------

/**
 * @brief Command '/create' that will create a team, a channel,
 * a thread or a reply
 * If the context is empty, the function will create a team
 * If the context is a team, the function will create a channel
 * If the context is a channel, the function will create a thread
 * If the context is a thread, the function will create a reply
 * The function will print a message in case of success or error
 *
 * @param parsed_cmd The parsed command
 * @param client The client structure
 * @author @Marius-P1
 */
void create(char **parsed_cmd, client_t *client);

/**
 * @brief Command '/create' that will create a team
 * The function will send a request to the server to create a team
 * The function will print a message in case of success or error
 *
 * @param parsed_cmd The parsed command
 * @param client The client structure
 * @author @Marius-P1
 */
void create_team(char **parsed_cmd, client_t *client);

/**
 * @brief Command '/create' that will create a channel
 * The function will send a request to the server to create a channel
 * The function will print a message in case of success or error
 *
 * @param parsed_cmd The parsed command
 * @param client The client structure
 * @author @Marius-P1
 */
void create_channel(char **parsed_cmd, client_t *client);

/**
 * @brief Command '/create' that will create a thread
 * The function will send a request to the server to create a thread
 * The function will print a message in case of success or error
 *
 * @param parsed_cmd The parsed command
 * @param client The client structure
 * @author @Marius-P1
 */
void create_thread(char **parsed_cmd, client_t *client);

/**
 * @brief Command '/create' that will create a reply
 * The function will send a request to the server to create a reply
 * The function will print a message in case of success or error
 *
 * @param parsed_cmd The parsed command
 * @param client The client structure
 * @author @Marius-P1
 */
void create_reply(char **parsed_cmd, client_t *client);


// --------------------------- INFO ---------------------------

/**
 * @brief Command '/info' that will print the information
 * of the context
 * If the context is empty, the function will print the
 * information of the user
 * If the context is a team, the function will print the
 * information of the team
 * If the context is a channel, the function will print
 * the information of the channel
 * If the context is a thread, the function will print
 * the information of the thread
 * The function will print a message in case of success or error
 *
 * @param parsed_cmd The parsed command
 * @param client The client structure
 * @author @Marius-P1
 */
void info(char **parsed_cmd, client_t *client);

/**
 * @brief Command '/info' that will print the information of the user
 * The function will send a request to the server to get the
 * information of the user
 * The function will print the information of the user
 *
 * @param client The client structure
 * @author @Marius-P1
 */
void info_user(client_t *client);

/**
 * @brief Command '/info' that will print the information of the team
 * The function will send a request to the server to get the
 * information of the team
 * The function will print the information of the team
 *
 * @param client The client structure
 * @author @Marius-P1
 */
void info_team(client_t *client);

/**
 * @brief Command '/info' that will print the information of the channel
 * The function will send a request to the server to get the
 * information of the channel
 * The function will print the information of the channel
 *
 * @param client The client structure
 * @author @Marius-P1
 */
void info_channel(client_t *client);

/**
 * @brief Command '/info' that will print the information of the thread
 * The function will send a request to the server to get the
 * information of the thread
 * The function will print the information of the thread
 *
 * @param client The client structure
 * @author @Marius-P1
 */
void info_thread(client_t *client);


// --------------------------- LIST ---------------------------

/**
 * @brief Command '/list' that will print all the teams, channels,
 * threads or replies
 * If the context is empty, the function will print all the teams
 * If the context is a team, the function will print all the channels
 * If the context is a channel, the function will print all the threads
 * If the context is a thread, the function will print all the replies
 * The function will print a message in case of success or error
 *
 * @param parsed_cmd The parsed command
 * @param client The client structure
 * @author @Marius-P1
 */
void list(char **parsed_cmd, client_t *client);

/**
 * @brief Command '/list' that will print all the teams of the server
 * The function will send a request to the server to get all the teams
 * The function will print all the teams
 *
 * @param client The client structure
 * @author @Marius-P1
 */
void list_teams(client_t *client);

/**
 * @brief Command '/list' that will print all the channels of a team
 * The function will send a request to the server to get all the channels
 * The function will print all the channels
 *
 * @param client The client structure
 * @author @Marius-P1
 */
void list_channels(client_t *client);

/**
 * @brief Command '/list' that will print all the threads of a channel
 * The function will send a request to the server to get all the threads
 * The function will print all the threads
 *
 * @param client The client structure
 * @author @Marius-P1
 */
void list_threads(client_t *client);

/**
 * @brief Command '/list' that will print all the replies of a thread
 * The function will send a request to the server to get all the replies
 * The function will print all the replies
 *
 * @param client The client structure
 * @author @Marius-P1
 */
void list_replies(client_t *client);
