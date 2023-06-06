#include "serverNet.h"
#include "../protocol/protocol.h"
#include "userM/userManager.h"
#include "groupM/groupManager.h"
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>

#define PORT_NUM 1990
#define BACK_LOG 300
#define BUF_SEND 255
#define BUF_NAME 24
#define BUF_PASS 9
#define IP_LEN 11

typedef struct ServerManager
{
    Server *m_server;
    UserManager *m_userMng;
    GroupManager *m_groupMng;

} ServerManager;

void TreatRegistration(char *_userName, char *_password, void *_context, int _clientId)
{
    char bufferSend[BUF_SEND];
    char tag;
    int totalLen, status;
    status = AddToUsersMap(_userName, _password, ((ServerManager *)_context)->m_userMng);
    if (status == USER_MNG_SUCCESS)
    {
        totalLen = PackRegAns(SUCCESS, bufferSend);
    }
    else
    {
        totalLen = PackRegAns(DUPLICATE_USER_ERROR, bufferSend);
    }

    if (totalLen == 3)
    {
        SendMessage(((ServerManager *)_context)->m_server, _clientId, (void *)bufferSend, totalLen);
    }
}

void TreatLogin(char *_userName, char *_password, void *_context, int _clientId)
{
    char bufferSend[BUF_SEND];

    int totalLen, status;

    status = LogInUser(((ServerManager *)_context)->m_userMng, _userName, _password);
    if (status == USER_MNG_SUCCESS)
    {
        totalLen = PackLogAns(SUCCESS, bufferSend);
    }
    if (status == INVALID_PASS_ERR)
    {
        totalLen = PackLogAns(INVALID_PASSWORD, bufferSend);
    }
    if (status == USER_NOT_FOUND_ERR)
    {
        totalLen = PackLogAns(INVALID_USERNAME, bufferSend);
    }
    if(status == USER_LOGED_IN)
    {
        totalLen = PackLogAns(LOGED_IN_ERR, bufferSend);
    }
    if (totalLen == 3)
    {
        SendMessage(((ServerManager *)_context)->m_server, _clientId, (void *)bufferSend, totalLen);
        return;
    }
}

void TreatCreateGroup(char *_groupName, char *_userName, void *_context, int _clientId)
{
    int status = 0, totalLen, resAddToGroup, resAddToUser;
    char bufferSend[BUF_SEND];
    char bufferIp[IP_LEN];
    status = AddGroupToHash(((ServerManager *)_context)->m_groupMng, _groupName);
    if (status == GROUPM_SUCCESS)
    {
        resAddToGroup = AddUser(((ServerManager *)_context)->m_groupMng, _groupName, _userName);
        resAddToUser = UserJoinGroup(((ServerManager *)_context)->m_userMng, _userName, _groupName);
        if (resAddToGroup == GROUPM_SUCCESS && resAddToUser == USER_MNG_SUCCESS)
        {
            status = FindIP(((ServerManager *)_context)->m_groupMng, _groupName, bufferIp);
            totalLen = PackCreateAnsOK(bufferIp, bufferSend);

            if (totalLen >= 11)
            {
                SendMessage(((ServerManager *)_context)->m_server, _clientId, (void *)bufferSend, totalLen);
                return;
            }
        }
        if (resAddToGroup == DUPLICATE_USER || resAddToUser == USER_ALREADY_EXIST_ERR)
        {
            totalLen = PackCreateAnsFail(DUPLICATE_USER, bufferSend);
            SendMessage(((ServerManager *)_context)->m_server, _clientId, (void *)bufferSend, totalLen);
            return;
        }
    }
    totalLen = PackCreateAnsFail(CREATE_GROUP_FAILED, bufferSend);
    SendMessage(((ServerManager *)_context)->m_server, _clientId, (void *)bufferSend, totalLen);
}

void TreatJoinGroup(char *_groupName, char *_userName, void *_context, int _clientId)
{
    int status, totalLen, resAddToGroup, resAddToUser;
    char bufferSend[BUF_SEND];
    char bufferIp[IP_LEN];

    resAddToGroup = AddUser(((ServerManager *)_context)->m_groupMng, _groupName, _userName);
    resAddToUser = UserJoinGroup(((ServerManager *)_context)->m_userMng, _userName, _groupName);
    if (resAddToGroup == GROUPM_SUCCESS && resAddToUser == USER_MNG_SUCCESS)
    {
        FindIP(((ServerManager *)_context)->m_groupMng, _groupName, bufferIp);
        totalLen = PackJoinAnsOK(bufferIp, bufferSend);

        if (totalLen >= 11)
        {
            SendMessage(((ServerManager *)_context)->m_server, _clientId, (void *)bufferSend, totalLen);
            return;
        }
    }
    if (resAddToGroup == DUPLICATE_USER || resAddToUser == USER_ALREADY_EXIST_ERR)
    {
        totalLen = PackJoinAnsFail(DUPLICATE_USER, bufferSend);
        SendMessage(((ServerManager *)_context)->m_server, _clientId, (void *)bufferSend, totalLen);
        return;
    }
    totalLen = PackJoinAnsFail(JOIN_GROUP_FAILED, bufferSend);
    SendMessage(((ServerManager *)_context)->m_server, _clientId, (void *)bufferSend, totalLen);
}

void TreatLeaveGroup(char *_groupName, char *_userName, void *_context, int _clientId)
{
    int statusUser, statusGroup, totalLen;
    char bufferSend[BUF_SEND];
    char bufferIp[IP_LEN];
    statusUser = UserLeaveGroup(((ServerManager *)_context)->m_userMng, _userName, _groupName);
    statusGroup = DelUserFromGroup(((ServerManager *)_context)->m_groupMng, _groupName, _userName);
    if (statusGroup == GROUPM_SUCCESS && statusUser == USER_MNG_SUCCESS)
    {
        totalLen = PackLeaveAns(LEAVE_OK, bufferSend);
    }
    else
    {
        totalLen = PackLeaveAns(LEAVE_FAIL, bufferSend);
    }
    SendMessage(((ServerManager *)_context)->m_server, _clientId, (void *)bufferSend, totalLen);
}

void TreatLogOut(char *_userName, void *_context, int _clientId)
{
    int statusUser, statusGroup, totalLen;
    char bufferSend[BUF_SEND];
    statusUser = UserLogOut(((ServerManager *)_context)->m_userMng, _userName);
    if (statusUser == USER_MNG_SUCCESS)
    {
        totalLen = PackLogOutAns(LOG_OUT_OK, bufferSend);
    }
    else
    {
        totalLen = PackLogOutAns(LOG_OUT_FAIL, bufferSend);
    }
    SendMessage(((ServerManager *)_context)->m_server, _clientId, (void *)bufferSend, totalLen);
}

void TreatGroupsRequest(void *_context, int _clientId)
{
    char bufferSend[BUF_SEND], bufferGroups[BUF_SEND];
    int status, totalLen;
    status = GetGroupNames(((ServerManager *)_context)->m_groupMng, bufferGroups);
    if (status == GROUPM_SUCCESS)
    {
        totalLen = PackShowGroupsOK(bufferGroups, bufferSend);
    }
    else
    {
        totalLen = PackShowGroupsFail(SHOW_GROUPS_FAIL, bufferSend);
    }
    SendMessage(((ServerManager *)_context)->m_server, _clientId, (void *)bufferSend, totalLen);
}

void GotMessageFunc(char *_buf, int _readBytes, int _clientId, Server *_server, void *_context)
{
    int status;
    char tag;
    char messageBuf[BUF_SEND];
    char messageFail[BUF_SEND], userName[BUF_NAME], password[BUF_PASS], groupName[BUF_NAME];
    snprintf(messageFail, BUF_SEND, "Unvalid message from client %d", _clientId);

    if (_buf == NULL || _readBytes < 1)
    {
        SendMessage(_server, _clientId, (void *)messageFail, strlen(messageFail));
        return;
    }

    tag = getTag(_buf);
    switch (tag)
    {
    case REG_REQUEST:
        status = UnPackRegLogRequests(_buf, _readBytes, userName, password); /* unpack puts values in username and password buffers*/
        if (status == SUCCESS)
        {
            TreatRegistration(userName, password, _context, _clientId);
        }
        break;
    case LOGIN_REQUEST:
        status = UnPackRegLogRequests(_buf, _readBytes, userName, password);
        if (status == SUCCESS)
        {
            TreatLogin(userName, password, _context, _clientId);
        }
        break;

    case REQUEST_CREATE_GROUP:
        status = UnPackGroupRequest(_buf, _readBytes, groupName, userName);
        if (status == SUCCESS)
        {
            TreatCreateGroup(groupName, userName, _context, _clientId);
        }
        break;
    case REQUEST_JOIN_GROUP:
        status = UnPackGroupRequest(_buf, _readBytes, groupName, userName);
        if (status == SUCCESS)
        {
            TreatJoinGroup(groupName, userName, _context, _clientId);
        }
        break;
    case REQUEST_LEAVE_GROUP:
        status = UnPackGroupRequest(_buf, _readBytes, groupName, userName);
        if (status == SUCCESS)
        {
            TreatLeaveGroup(groupName, userName, _context, _clientId);
        }
        break;
    case REQUEST_LOG_OUT:
        status = UnPackLogOutRequest(_buf, _readBytes, userName);
        if (status == SUCCESS)
        {
            TreatLogOut(userName, _context, _clientId);
        }
        break;
    case SHOW_GROUPS_REQUEST:
        TreatGroupsRequest(_context, _clientId);
        break;

    default:
        break;
    }
}

ServerManager *CreateServerManager()
{
    ServerManager *mng = NULL;
    if ((mng = (ServerManager *)malloc(sizeof(ServerManager))) == NULL)
    {
        return NULL;
    }

    mng->m_userMng = UserManagerCreate();
    if (mng->m_userMng == NULL)
    {
        return NULL;
    }
    mng->m_groupMng = CreateGroupManager();
    if (mng->m_groupMng == NULL)
    {
        return NULL;
    }
    mng->m_server = ServerCreate(NULL, GotMessageFunc, NULL, NULL, PORT_NUM, BACK_LOG, (void *)mng);
    if (mng->m_server == NULL)
    {
        return NULL;
    }
    return mng;
}

int main()
{
    ServerResult res;
    ServerManager *serverMng = CreateServerManager();

    if (serverMng == NULL)
    {
        printf("Failed creating the server\n");
    }
    else
    {
        res = RunServer(serverMng->m_server);
        if (res == FAILED_CONNECTION || res == FAILED_SELECT)
        {
            ServerDestroy(&serverMng->m_server);
/*             ReloadServer(NULL, GotMessageFunc, NULL, NULL, PORT_NUM, BACK_LOG);
 */        }
    }

    return 0;
}