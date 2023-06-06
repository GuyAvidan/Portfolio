#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "/home/guy/prog/GENDS/GenList.h"
#include "/home/guy/prog/GENDS/ListInternal.h"
#include "/home/guy/prog/GENDS/list_itr.h"
#include "/home/guy/prog/GENDS/list_functions.h" 
/*#include "../../../advc/genDoubleList/genDoubleList.h"
#include "../../../advc/genDoubleList/list_itr.h"
#include "../../../advc/genDoubleList/list_functions.h" */

#include "../protocol/protocol.h"
#include "ClientNet.h"
#include "UI.h"
#include "Client_manager.h"
#define NAME_LEN 24
#define PASS_LEN 8
#define NOT_FOUND 0
#define FOUND 1
#define FAIL 1
#define ACTIVE 1
#define NOT_ACTIVE 0

struct ClientManager
{
    ClientNet *m_clientNet;
    List *m_groupsPID;
    int m_flagStop;
};

typedef struct GroupPID
{
    char m_IP[14];
    int m_port;
    char m_ClientName[24];
    char m_groupName[24];
    int m_listenPID;
    int m_SenderPID;
} GroupPID;

static ClientManErr recvMsg(char *_msg, ClientManager *_myClientMan, char *_context);
static ClientManErr makeMsg(ClientManager *_myClientMan, char _tag, char *_context);
static void OpenGroupWin(GroupPID *_groupPID);
static GroupPID *CreateGroupPID(char *_clientName, char *_groupName);
static int CloseGroupWin(GroupPID *_groupPID);
static ListItr *FindGroupPIDByName(char *_groupName, ClientManager *_myClientMan);
static void DestroyGroupPID(void *_groupPID);
static ClientManErr resetManeger(ClientManager *_myClientMan);
static ClientManErr PrintGroupsName(ClientManager *_myClientMan);

ClientManager *CreateClientManager(char *_serverIP, int _portServer)
{
    ClientManager *myClientMan;
    if(_serverIP == NULL)
    {
        return NULL;
    }
    if ((myClientMan = (ClientManager *)malloc(sizeof(struct ClientManager))) == NULL)
    {
        return NULL;
    }
    if ((myClientMan->m_clientNet = CreateClient(_serverIP, _portServer)) == NULL)
    {
        free(myClientMan);
        return NULL;
    }
    myClientMan->m_groupsPID = ListCreate();
    if (myClientMan->m_groupsPID == NULL)
    {
        DestroyClient(&myClientMan->m_clientNet);
        free(myClientMan);
        return NULL;
    }
    myClientMan->m_flagStop = NOT_ACTIVE;
    return myClientMan;
}

ClientManErr RunClientManager(ClientManager *_clientManager)
{
    int choise = 0;
    ClientManErr ressult;
    char tag;
    char *buffer;
    int status;
    char context[NAME_LEN];
    if(_clientManager == NULL)
    {
        return CLIENT_NULL;
    }
    if (!ConnectClient(_clientManager->m_clientNet))
    {
        return CLIENT_CONNECTION_ERROR;
    }
    _clientManager->m_flagStop = ACTIVE;
    while (choise < 1 || choise > 3)
    {
        FirstMenu();
        scanf("%d", &choise);
        switch (choise)
        {
        case 1:
        {
            tag = REG_REQUEST;
            status = makeMsg(_clientManager, tag, context);
            recvMsg(buffer, _clientManager, context);
            choise = 4;
            break;
        }
        case 2:
        {
            tag = LOGIN_REQUEST;
            status = makeMsg(_clientManager, tag, context);
            if (recvMsg(buffer, _clientManager, context) != CLIENT_MAN_SUCCESS)
            {
                choise = 4;
            }
            break;
        }
        case 3:
        {
            close(GetSocket(_clientManager->m_clientNet));
            CloseProg();
            return PROGRAM_CLOSED;
        }
        default:
        {
            break;
        }
        }
    }

    choise = 0;
    while (choise < 1 || choise > 4)
    {
        GroupMenu(); /*1.join 2.leave 3.create 4.logout*/
        scanf("%d", &choise);
        switch (choise)
        {
        case 1:
        {
            tag = SHOW_GROUPS_REQUEST;
            status = makeMsg(_clientManager, tag, context);
            recvMsg(buffer, _clientManager, context);
            tag = REQUEST_JOIN_GROUP;
            status = makeMsg(_clientManager, tag, context);
            recvMsg(buffer, _clientManager, context);
            choise = 5;
            break;
        }
        case 2:
        {
            tag = REQUEST_LEAVE_GROUP;
            status = makeMsg(_clientManager, tag, context);
            recvMsg(buffer, _clientManager, context);
            choise = 5;
            break;
        }
        case 3:
        {
            tag = REQUEST_CREATE_GROUP;
            status = makeMsg(_clientManager, tag, context);
            recvMsg(buffer, _clientManager, context);
            choise = 5;
            break;
        }
        case 4:
        {
            tag = REQUEST_LOG_OUT;
            status = makeMsg(_clientManager, tag, context);
            if (recvMsg(buffer, _clientManager, context) != CLIENT_MAN_SUCCESS)
            {
                choise = 5;
            }
            else
            {

                return CLIENT_MAN_SUCCESS;
            }
            break;
        }
        default:
        {
            break;
        }
        }
    }
    return 1;
}

void DestroyClientManager(ClientManager **_myClientMan)
{
    if (_myClientMan != NULL || *_myClientMan != NULL)
    {
        DestroyClient(&((*_myClientMan)->m_clientNet));
        ListDestroy(&((*_myClientMan)->m_groupsPID), DestroyGroupPID);
        free(*_myClientMan);
        *(_myClientMan) = NULL;
    }
}

static ClientManErr makeMsg(ClientManager *_myClientMan, char _tag, char *_context)
{
    int sent_bytes;
    char buffer1[NAME_LEN], buffer2[PASS_LEN];
    char Packet[PACKET_SIZE], bufferGroup[NAME_LEN];
    ListItr itr;
    void *data;
    if(_myClientMan == NULL)
    {
        return CLIENT_NULL;
    }
    switch (_tag) /*1.join 2.leave 3.create 4.logout*/
    {
    case REG_REQUEST:
    {
        EnterUserName();
        scanf("%s", buffer1);
        SetName(_myClientMan->m_clientNet, buffer1);
        EnterPass();
        scanf("%s", buffer2);
        SetPassword(_myClientMan->m_clientNet, buffer2);
        if ((PackRegRequest(buffer1, buffer2, Packet)) == INVALID_MSG)
        {
            return CLIENT_PACKING_ERROR;
        }
        SendFunc(_myClientMan->m_clientNet, Packet);

        break;
    }
    case LOGIN_REQUEST:
    {
        EnterUserName();
        scanf("%s", buffer1);
        SetName(_myClientMan->m_clientNet, buffer1);
        EnterPass();
        scanf("%s", buffer2);
        SetPassword(_myClientMan->m_clientNet, buffer2);
        if ((PackLogRequest(buffer1, buffer2, Packet)) == INVALID_MSG)
        {
            return CLIENT_PACKING_ERROR;
        }
        SendFunc(_myClientMan->m_clientNet, Packet);
        break;
    }
    case REQUEST_JOIN_GROUP:
    {
        EnterGroupName();
        scanf("%s", buffer1);
        GetName(_myClientMan->m_clientNet, buffer2);

        strcpy(_context, buffer1);
        if ((PackJoinGroupRequest(buffer1, buffer2, Packet)) == INVALID_MSG)
        {
            return CLIENT_PACKING_ERROR;
        }
        SendFunc(_myClientMan->m_clientNet, Packet);
        break;
    }
    case REQUEST_LEAVE_GROUP:
    {
        if (PrintGroupsName(_myClientMan) == CLIENT_MAN_SUCCESS)
        {
            EnterGroupName();
            scanf("%s", buffer1);
            strcpy(bufferGroup, buffer1);
            strcpy(_context, bufferGroup);
            GetName(_myClientMan->m_clientNet, buffer2);
        }
        else
        {
            ShowGroupsFail();
            strcpy(bufferGroup, "000000000");
            strcpy(_context, bufferGroup);
            GetName(_myClientMan->m_clientNet, buffer2);
        }
        if ((PackLeaveGroupRequest(bufferGroup, buffer2, Packet)) == INVALID_MSG)
        {
            return CLIENT_PACKING_ERROR;
        }
        SendFunc(_myClientMan->m_clientNet, Packet);
        break;
    }
    case REQUEST_CREATE_GROUP:
    {
        EnterGroupName();
        scanf("%s", buffer1);
        strcpy(bufferGroup, buffer1);
        strcpy(_context, bufferGroup);
        GetName(_myClientMan->m_clientNet, buffer2);
        if ((PackGroupRequest(bufferGroup, buffer2, Packet)) == INVALID_MSG)
        {
            return CLIENT_PACKING_ERROR;
        }
        SendFunc(_myClientMan->m_clientNet, Packet);
        break;
    }
    case REQUEST_LOG_OUT:
    {
        GetName(_myClientMan->m_clientNet, buffer2);
        if ((PackLogOutRequest(buffer2, Packet)) == INVALID_MSG)
        {
            return CLIENT_PACKING_ERROR;
        }
        SendFunc(_myClientMan->m_clientNet, Packet);
        break;
    }
    case SHOW_GROUPS_REQUEST:
    {
        if ((PackShowGroupsRequest(Packet)) == INVALID_MSG)
        {
            return CLIENT_PACKING_ERROR;
        }
        SendFunc(_myClientMan->m_clientNet, Packet);
        break;
    }
    default:
    {
        break;
    }
    }
    return CLIENT_MAN_SUCCESS;
}

static ClientManErr recvMsg(char *_msg, ClientManager *_myClientMan, char *_context)
{
    char tag;
    char bufferName[PACKET_SIZE];
    char packet[PACKET_SIZE], buffer[PACKET_SIZE];
    int msgLen;
    GroupPID *dnmGroupPID;
    void *data;
    ListItr itr;
    msgLen = RecvFunc(_myClientMan->m_clientNet, packet);
    tag = getTag(packet);
    if(_myClientMan == NULL)
    {
        return CLIENT_NULL;
    }
    switch (tag)
    {
    case REG_REP:
    {
        if (UnPackRegLogAns(packet, buffer, msgLen) == INVALID_MSG)
        {
            return CLIENT_UNPACKING_ERROR;
        }
        if (buffer[0] == SUCCESS)
        {
            RegSuccess();
        }
        else if (buffer[0] == DUPLICATE_USER_ERROR)
        {
            UserAlreadyExist();
            return INVALID_USERNAME;
        }
        else
        {
            RegFail();
            return INVALID_PASSWORD;
        }
        break;
    }
    case LOGIN_REP:
    {
        if (UnPackRegLogAns(packet, buffer, msgLen) == INVALID_MSG)
        {
            return CLIENT_UNPACKING_ERROR;
        }
        if (buffer[0] == SUCCESS)
        {
            LoginSuccess();
        }
        else if (buffer[0] == INVALID_USERNAME)
        {
            RegFailUser();
            return INVALID_USERNAME;
        }
        else if (buffer[0] == INVALID_PASSWORD)
        {
            RegFailPass();
            return INVALID_PASSWORD;
        }else if (buffer[0] ==  LOGED_IN_ERR)
        {
            LoginFail();
            return LOGED_IN_ERR;
        }
        else
        {
            LoginFail();
            return CLIENT_LOGIN_ERROR;
        }
        break;
    }
    case CREATE_GROUP_FAILED:
    {
        if (UnPackCreateJoinAns(packet, buffer, msgLen) == INVALID_MSG)
        {
            return CLIENT_UNPACKING_ERROR;
        }
        CreatGroupFail();
        return CREATE_GROUP_FAILED;
        break;
    }
    case CREATE_GROUP_OK:
    {
        CreateGroupSuccess();
        if (UnPackCreateJoinAns(packet, buffer, msgLen) == INVALID_MSG)
        {
            return CLIENT_UNPACKING_ERROR;
        }
        GetName(_myClientMan->m_clientNet, bufferName);

        dnmGroupPID = CreateGroupPID(bufferName, _context);
        ListPushTail(_myClientMan->m_groupsPID, (void *)dnmGroupPID);
        strcpy(dnmGroupPID->m_IP, buffer);
        dnmGroupPID->m_port = PORT_NUMBER;
        OpenGroupWin(dnmGroupPID);
        break;
    }
    case JOIN_GROUP_FAILED:
    {
        if (UnPackCreateJoinAns(packet, buffer, msgLen) == INVALID_MSG)
        {
            return CLIENT_UNPACKING_ERROR;
        }
        JoinGroupFail();
        return JOIN_GROUP_FAILED;
    }
    case JOIN_GROUP_OK:
    {
        JoinGroupSuccess();
        if (UnPackCreateJoinAns(packet, buffer, msgLen) == INVALID_MSG)
        {
            return CLIENT_UNPACKING_ERROR;
        }
        GetName(_myClientMan->m_clientNet, bufferName);
        dnmGroupPID = CreateGroupPID(bufferName, _context); 
        ListPushTail(_myClientMan->m_groupsPID, (void *)dnmGroupPID);
        strcpy(dnmGroupPID->m_IP, buffer);
        dnmGroupPID->m_port = PORT_NUMBER;
        OpenGroupWin(dnmGroupPID);
        break;
    }
    case LEAVE_REP:
    {
        if (UnPackLeaveAns(packet, buffer, msgLen) == INVALID_MSG)
        {
            return CLIENT_UNPACKING_ERROR;
        }
        if (*buffer == LEAVE_FAIL)
        {
            LeaveGroupFailed();
            return JOIN_GROUP_FAILED;
        }
        itr = FindGroupPIDByName(_context, _myClientMan);
        if (itr == NULL)
        {
            InvalidGroupName();
            return INVALID_GROUP_NAME;
        }
        data = ListItrRemove(itr);
        if (data == NULL)
        {
            LeaveGroupFailed();
            return CLIENT_LEAVE_GROUP_FAIL;
        }
        if (CloseGroupWin((GroupPID *)data) == FAIL)
        {
            LeaveGroupFailed();
            return CLIENT_LEAVE_GROUP_FAIL;
        }
        free(data);
        LeaveGroupSuccess();
        break;
    }
    case LOG_OUT_REP:
    {
        if (UnPackLogOutAns(packet, buffer, msgLen) == INVALID_MSG)
        {
            return CLIENT_UNPACKING_ERROR;
        }
        if (*buffer == LOG_OUT_FAIL)
        {
            LogOutFailed();
            return CLIENT_LOG_OUT_FAIL;
        }
        LogOutSuccess();
        resetManeger(_myClientMan);
        break;
    }
    case SHOW_GROUPS_FAIL:
    {
        if (UnPackShowGroupsAns(packet, buffer, msgLen) == INVALID_MSG)
        {
            return CLIENT_UNPACKING_ERROR;
        }
        ShowGroupsFail();
        break;
    }
    case SHOW_GROUPS_OK:
    {
        if (UnPackShowGroupsAns(packet, buffer, msgLen) == INVALID_MSG)
        {
            return CLIENT_UNPACKING_ERROR;
        }
        PrintShowGroupsOK(buffer);
        break;
    }
    }
    return CLIENT_MAN_SUCCESS;
}

static void OpenGroupWin(GroupPID *_groupPID)
{
    char command1[PACKET_SIZE], command2[PACKET_SIZE], add[PACKET_SIZE], sPort[PACKET_SIZE], iStr[PACKET_SIZE];
    FILE *ListenPID_FILE;
    FILE *SenderPID_FILE;
    static int i = 1;
    if(_groupPID == NULL)
    {
        return;
    }
    snprintf(iStr, PACKET_SIZE, "%d", i);
    snprintf(sPort, PACKET_SIZE, "%d", _groupPID->m_port);
    strcpy(command1, "gnome-terminal --geometry=50x20+");
    strcat(command1, iStr);
    strcat(command1, "+10 --title=Group:_");
    strcat(command1, _groupPID->m_groupName);
    strcat(command1, " -- ./Listen.out  ");
    strcpy(add, _groupPID->m_IP);
    strcat(add, " ");
    strcat(add, sPort);
    strcat(add, " ");
    strcat(add, _groupPID->m_ClientName);
    strcat(command1, add);
    system(command1);
    strcpy(command2, "gnome-terminal --geometry=50x20+");
    strcat(command2, iStr);
    strcat(command2, "+500 --title=User:_");
    strcat(command2, _groupPID->m_groupName);
    strcat(command2, " -- ./Sender.out ");
    strcat(command2, add);
    system(command2);
    i = (i + 550) % 2200;
    sleep(1);
    ListenPID_FILE = fopen("Listen.txt", "r");
    SenderPID_FILE = fopen("Sender.txt", "r");
    fscanf(ListenPID_FILE, "%d", &_groupPID->m_listenPID);
    fscanf(SenderPID_FILE, "%d", &_groupPID->m_SenderPID);
    fclose(ListenPID_FILE);
    fclose(SenderPID_FILE);
}

static GroupPID *CreateGroupPID(char *_clientName, char *_groupName)
{
    GroupPID *dnmGroupPID = NULL;
    if(_clientName == NULL || _groupName == NULL)
    {
        return NULL;
    }
    if ((dnmGroupPID = (GroupPID *)malloc(sizeof(GroupPID))) == NULL)
    {
        return NULL;
    }
    strcpy(dnmGroupPID->m_ClientName, _clientName);
    strcpy(dnmGroupPID->m_groupName, _groupName);
    return dnmGroupPID;
}

static void DestroyGroupPID(void *_groupPID)
{
    if(_groupPID == NULL)
    {
        return;
    }
    free((GroupPID *)_groupPID);
}

static int CloseGroupWin(GroupPID *_groupPID)
{
    if(_groupPID == NULL)
    {
        return FAIL;
    }
    if (kill(_groupPID->m_listenPID, SIGKILL) != 0)
    {
        return FAIL;
    }
    if (kill(_groupPID->m_SenderPID, SIGKILL) != 0)
    {
        return FAIL;
    }
    return SUCCESS;
}

static ListItr *FindGroupPIDByName(char *_groupName, ClientManager *_myClientMan)
{
    ListItr begin, end;
    void *data;
    if(_myClientMan == NULL || _groupName == NULL)
    {
        return NULL;
    }
    begin = ListItrBegin(_myClientMan->m_groupsPID);
    end = ListItrEnd(_myClientMan->m_groupsPID);

    while (begin != end)
    {
        data = ListItrGet(begin);
        if (strcmp(((GroupPID *)data)->m_groupName, _groupName) != 0)
        {
            begin = ListItrNext(begin);
        }
        else
        {
            return begin;
        }
    }

    return NULL;
}

static ClientManErr PrintGroupsName(ClientManager *_myClientMan)
{
    ListItr begin, end;
    void *data;
    int i = 1;
    if(_myClientMan == NULL )
    {
        return CLIENT_NULL;
    }

    begin = ListItrBegin(_myClientMan->m_groupsPID);
    end = ListItrEnd(_myClientMan->m_groupsPID);

    while (begin != end)
    {
        data = ListItrGet(begin);
        printf("%d. %s\n", i, ((GroupPID *)data)->m_groupName);
        begin = ListItrNext(begin);
        i++;
    }

    if (i == 1)
    {
        return EMPTY_GROUP_LIST;
    }

    return CLIENT_MAN_SUCCESS;
}

static ClientManErr resetManeger(ClientManager *_myClientMan)
{
    ListItr itr, end;
    void *itemToRem;
    itr = ListItrBegin(_myClientMan->m_groupsPID);
    end = ListItrEnd(_myClientMan->m_groupsPID);
    if(_myClientMan == NULL )
    {
        return CLIENT_NULL;
    }
    while (itr != end)
    {
        itr = ListItrNext(itr);
        ListPopHead(_myClientMan->m_groupsPID, &itemToRem);
        CloseGroupWin((GroupPID *)itemToRem);
        DestroyGroupPID(itemToRem);
    }

    _myClientMan->m_flagStop = NOT_ACTIVE;
    return SUCCESS;
}
