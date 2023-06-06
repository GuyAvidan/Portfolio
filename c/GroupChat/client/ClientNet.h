#ifndef __CLIENTNET_H__
#define __CLIENTNET_H__
#define NAME_LEN_MAX 24
#define PASS_LEN_MAX 8

typedef struct ClientNet ClientNet;

typedef enum ClientErr
{
    CLIENT_SUCCESS = 1,
    CLIENT_SENT_ERROR = 7
} ClientErr;

/**
 * @brief Dynamically create a new ClientNet object of given IP and server port
 * @param _serverIP - the server IP
 * @param _portServer - the server port
 * @return ClientNet * - on success / NULL on fail
 */
ClientNet *CreateClient(char *_serverIP, int _portServer);

/**
 * @brief Destroy ClientNet
 * @param _clientNet - ClientNet to be deallocated.
 * @return
 */
void DestroyClient(ClientNet **_clientNet);

/**
 * @brief ClientNet to server
 * @param _clientNet - ClientNet to connect
 * @return 1- on success / 0 on fail
 */
int ConnectClient(ClientNet *_clientNet);

/**
 * @brief ClientNet sending message the server
 * @param _clientNet - ClientNet sending the message
 * @param _buffer - the message
 * @return ClientEr:r CLIENT_SUCCESS on success / CLIENT_SENT_ERROR on fail
 */
ClientErr SendFunc(ClientNet *_clientNet, char *_buffer);

/**
 * @brief ClientNet receives message from server
 * @param _clientNet - ClientNet receives the message
 * @param _packet - the message
 * @return 1- on success / -1 on fail
 */
int RecvFunc(ClientNet *_clientNet, char *_packet);

/**
 * @brief Sets the username of the ClientNet
 * @param _clientNet - ClientNet
 * @param _name - the name
 * @return
 */
void SetName(ClientNet *_clientNet, char *_name);

/**
 * @brief Sets the password of the ClientNet
 * @param _clientNet - ClientNet
 * @param _name - the password
 * @return
 */
void SetPassword(ClientNet *_clientNet, char *_pass);

/**
 * @brief Gets the username of the ClientNet
 * @param _clientNet - ClientNet
 * @param _name - the buffer for the name
 * @return 1 on sucsses or -1 on fail
 */
int GetName(ClientNet *_clientNet, char *_buffer);

/**
 * @brief Gets the sockt of the ClientNet
 * @param _clientNet - ClientNet
 * @return the client socket or -1 on fail
 */
int GetSocket(ClientNet *_clientNet);

#endif /*__CLIENTNET_H__*/
