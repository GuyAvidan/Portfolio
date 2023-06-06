#include "serverNet.h"
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include "/home/guy/prog/GENDS/GenList.h"
#include "/home/guy/prog/GENDS/ListInternal.h" 
#include "/home/guy/prog/GENDS/list_itr.h" 
#include "/home/guy/prog/GENDS/list_functions.h" 


#define BUF_SIZE 4096
#define TRUE 1
#define MAX_CLIENTS 1024
#define N_CLIENTS 1000
#define MAX_PORT_N 65353
#define MIN_PORT_N 1024
struct Server
{
    WelcomeClient m_welcomefunc;
    ClosedClient m_closeFunc;
    Fail m_fail;
    GotMessage m_message;
    List *m_list;
    fd_set m_readfds;
    fd_set m_readfdsTemp;
    void *m_context;
    int m_counter;
    int m_listenSock;
    int m_flagPause;
    int m_activity;
    int m_portNum;
    int m_backLog;
};

static int InitListenSocket(Server *_server);
static int AddNewClient(Server *_server);
static void CheckCurClients(Server *_server);
static ServerResult ReceiveData(int _socket, Server *_server);

Server *ServerCreate(WelcomeClient _welcome, GotMessage _treatMessage, ClosedClient _closedClient, Fail _fail, int _serverPort, int _backLog, void *_context)
{
    Server *server = NULL;
    fd_set readfds, temp;
    if (_treatMessage == NULL || _backLog > MAX_CLIENTS || _backLog < 1 || _serverPort < MIN_PORT_N || _serverPort > MAX_PORT_N)
    {
        return NULL;
    }
    if ((server = (Server *)malloc(sizeof(Server))) == NULL)
    {
        return NULL;
    }

    server->m_list = ListCreate();
    if (server->m_list == NULL)
    {
        free(server);
        return NULL;
    }
    server->m_activity = 0;
    server->m_counter = 0;
    server->m_readfds = readfds;
    server->m_readfdsTemp = temp;
    server->m_context = _context;
    server->m_welcomefunc = _welcome;
    server->m_message = _treatMessage;
    server->m_closeFunc = _closedClient;
    server->m_fail = _fail;
    server->m_portNum = _serverPort;
    server->m_backLog = _backLog;
    server->m_flagPause = 0;
    server->m_listenSock = InitListenSocket(server);
    if (server->m_listenSock < 0)
    {
        free(server);
        return NULL;
    }
    return server;
}

ServerResult RunServer(Server *_server)
{
    int sockNum;
    FD_ZERO(&_server->m_readfds);
    FD_SET(_server->m_listenSock, &_server->m_readfds);
    while (_server->m_flagPause == 0)
    {
        _server->m_readfdsTemp = _server->m_readfds;

        _server->m_activity = select(MAX_CLIENTS, &_server->m_readfdsTemp, NULL, NULL, NULL);
        if (_server->m_activity < 0)
        {
            if (_server->m_fail != NULL)
            {
                _server->m_fail(_server, FAILED_SELECT);
            }
        }
        if (FD_ISSET(_server->m_listenSock, &_server->m_readfdsTemp))
        {
            if ((sockNum = AddNewClient(_server)) < 0) /*failed*/
            {
                if (_server->m_fail != NULL)
                {
                    _server->m_fail(_server, FAILED_CONNECTION);
                }
                else
                {
                    return FAILED_CONNECTION;
                }
            }
            else
            {
                if (_server->m_welcomefunc != NULL)
                {
                    _server->m_welcomefunc(sockNum);
                }
            }
        }
        if (_server->m_activity > 0)
        {
            CheckCurClients(_server);
        }
    }
    return SERVER_SUCCESS;
}

ServerResult SendMessage(Server *_server, int _clientId, void *_buffer, int _bufferSize)
{
    int sent_bytes;
    sent_bytes = send(_clientId, _buffer, _bufferSize, 0);
    if (sent_bytes < 0)
    {
        if (_server->m_fail != NULL)
        {
            _server->m_fail(_server, FAILED_SEND);
        }
        return FAILED_SEND;
    }
    if (sent_bytes <= _bufferSize)
    {
        return SERVER_SUCCESS;
    }
}

void StopRun(Server *_server)
{
    if (_server != NULL)
    {
        _server->m_flagPause = 1;
    }
}

void ServerDestroy(Server **_server)
{
    ListItr begin, end, data;
    int sock;
    if (_server == NULL || *_server == NULL)
    {
        return;
    }
    if ((*_server)->m_list != NULL)
    {
        begin = ListItrBegin((*_server)->m_list);
        end = ListItrEnd((*_server)->m_list);
        while (begin != end)
        {
            data = ListItrGet(begin);
            sock = *(int *)data;
            close(sock);
            free(data);
            begin = ListItrNext(begin);
        }
        ListDestroy(&(*_server)->m_list, NULL);
    }
    free(*_server);
    *_server = NULL;
}

static int AddNewClient(Server *_server)
{
    int new_socket;
    int *sock;
    struct sockaddr_in sin;
    socklen_t addr_len = sizeof(sin);
    if ((new_socket = accept(_server->m_listenSock, (struct sockaddr *)&sin, &addr_len)) < 0)
    {
        return FAILED_CONNECTION;
    }
    _server->m_activity--;
    if (new_socket > 0)
    {
        _server->m_counter++;
        if ((_server->m_counter) > N_CLIENTS)
        {
            close(new_socket);
            _server->m_counter--;
        }
        else
        {
            if ((sock = (int *)malloc(sizeof(int))) == NULL)
            {
                close(new_socket);
                return FAILED_CONNECTION;
            }
            *sock = new_socket;

            FD_SET(new_socket, &_server->m_readfds);
            if ((ListPushTail(_server->m_list, sock)) != LIST_SUCCESS)
            {
                perror("Failed in socket storage");
                _server->m_counter--;
                close(new_socket);
                free(sock);
                return FAILED_CONNECTION;
            }
        }
    }
    return new_socket;
}

static void CheckCurClients(Server *_server)
{
    ListItr begin, end, temp, data;
    int sock, statusRec, flagList = 0;
    begin = ListItrBegin(_server->m_list);
    end = ListItrEnd(_server->m_list);
    while (begin != end && _server->m_activity > 0)
    {
        flagList = 0;
        data = ListItrGet(begin);
        sock = *(int *)data;
        if (FD_ISSET(sock, &_server->m_readfdsTemp))
        {
            _server->m_activity--;
            statusRec = ReceiveData(sock, _server);
            if (statusRec != SERVER_SUCCESS)
            {
                close(sock);
                _server->m_counter--;
                FD_CLR(sock, &_server->m_readfds);
                free(data);
                temp = ListItrNext(begin);
                ListItrRemove(begin);
                begin = temp;
                flagList = 1;
            }
        }
        if (flagList != 1)
        {
            begin = ListItrNext(begin);
        }
    }
}

static ServerResult ReceiveData(int _socket, Server *_server)
{
    int read_bytes;
    char *buffer = malloc(BUF_SIZE);
    read_bytes = recv(_socket, buffer, BUF_SIZE, 0);
    if (read_bytes < 0)
    {
        if (_server->m_fail != NULL)
        {
            _server->m_fail(_server, FAILED_READ);
        }
        return FAILED_READ;
    }
    if (read_bytes == 0)
    {
        if (_server->m_closeFunc != NULL)
        {
            _server->m_closeFunc(_socket);
        }
        return SERVER_CLIENT_DISCONNECTED;
    }
    _server->m_message(buffer, read_bytes, _socket, _server, _server->m_context);
    return SERVER_SUCCESS;
}

static int InitListenSocket(Server *_server)
{
    struct sockaddr_in sin;
    int optval = 1;
    int listening_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (listening_sock < 0)
    {
        return -1;
    }
    if (setsockopt(listening_sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0)
    {
        perror("Reuse failed");
        close(listening_sock);
        return -1;
    }
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(_server->m_portNum);
    if (bind(listening_sock, (struct sockaddr *)&sin, sizeof(sin)) < 0)
    {
        perror("Bind failed");
        close(listening_sock);
        return -1;
    }
    if (listen(listening_sock, _server->m_backLog) < 0) /*~300 */
    {
        perror("listen failed");
        close(listening_sock);
        return -1;
    }
    return listening_sock;
}
