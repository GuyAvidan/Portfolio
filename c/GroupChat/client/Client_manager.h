#ifndef __CLIENT_MANAGER_H__
#define __CLIENT_MANAGER_H__
#include "../protocol/protocol.h"

typedef enum ClientManErr
{
    CLIENT_MAN_SUCCESS=1,
    CLIENT_PACKING_ERROR,
    CLIENT_UNPACKING_ERROR,
    CLIENT_REG_ERROR,
    CLIENT_LOGIN_ERROR,
    CLIENT_CONNECTION_ERROR,
    CLIENT_LEAVE_GROUP_FAIL,
    CLIENT_LOG_OUT_FAIL,
    CLIENT_NULL,
    EMPTY_GROUP_LIST
} ClientManErr;

typedef struct ClientManager ClientManager;


/**  
 * @brief Dynamically create a new ClientManager object of given IP and server port 
 * @param _serverIP - the server IP
 * @param _portServer - the server port 
 * @return ClientManager * - on success / NULL on fail 
 */
ClientManager *CreateClientManager(char *_serverIP, int _portServer);


/**  
 * @brief Runs the ClientManager
 * @param _clientManager - clientManager
 * @return ClientManErr: CLIENT_MAN_SUCCESS on success or error
 * @errors CLIENT_PACKING_ERROR, CLIENT_UNPACKING_ERROR,CLIENT_REG_ERROR,CLIENT_LOGIN_ERROR
 */
ClientManErr RunClientManager(ClientManager *_clientManager);


/**  
 * @brief ClientManager
 * @param myClientMan - ClientNet to be deallocated. 
 * @return 
 */
void DestroyClientManager(ClientManager **myClientMan);

#endif /*__CLIENT_MANAGER_H__*/
