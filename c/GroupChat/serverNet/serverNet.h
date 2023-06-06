#ifndef __SERVER_H__
#define __SERVER_H__

typedef struct Server Server;

typedef enum ServerResult
{
    SERVER_SUCCESS = -6,
    FAILED_CONNECTION,
    FAILED_SELECT,
    SERVER_CLIENT_DISCONNECTED,
    FAILED_SEND,
    FAILED_READ
} ServerResult;

/* WelcomeClient: the action taken when new client connects. can be set to NULL if no action is required*/
typedef int (*WelcomeClient)(int _clientId);

/*GotMessage: action/s to do after the server received message from client. cannot be NULL
the server returns the message, socket number(_clientId) and its size to the app */
typedef void (*GotMessage)(char *_buf, int _bufSize, int _clientId, Server *_server, void *_context);
/* ClosedClient: the action taken when client disconnects. can be set as NULL */
typedef int (*ClosedClient)(int _clientId);

/*Fail: The function informs the app about failure in the run process. can be set as NULL   */
typedef int (*Fail)(Server *_server, ServerResult _error);

/**
 * @brief Creates server struct and initializes server
 * @details
 *
 * @params _welcome : action taken when new client connects. can be set to NULL
 * @params _treatMessage: function called when message is received. cannot be NULL
 * @params _closedclient: the action taken when client disconnects. can be set as NULL
 * @params _fail: function that informs the app about failure in the run process. can be set as NULL
 * @params _serverPort: port number of the server
 * @params _backLog: the max number of queued sockets for new connections (for listen)
 * @returns Server* or NULL on failure or parameters are not valid.

 */
Server *ServerCreate(WelcomeClient _welcome, GotMessage _treatMessage, ClosedClient _closedclient, Fail _fail, int _serverPort, int _backLog, void *_context);

void ServerDestroy(Server **_server);

ServerResult RunServer(Server *_server);

/* This function lets the app send a message for specific client */
ServerResult SendMessage(Server *_server, int _clientId, void *_buffer, int _bufferSize);

void StopRun(Server *_server);

#endif