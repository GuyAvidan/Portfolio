#include <stdlib.h>
#include "group.h"
#include <string.h>
#include <stdio.h>
#include "/home/guy/prog/GENDS/GenList.h"
#include "/home/guy/prog/GENDS/ListInternal.h" 
#include "/home/guy/prog/GENDS/list_itr.h" 
#include "/home/guy/prog/GENDS/list_functions.h" 
#include "/home/guy/prog/GENDS/HashMap.h"

#define GROUP_NAME_LEN 24
#define MAX_IP_LEN 11
#define PORT_NUM 1990
#define TRUE 1
#define FALSE 0
#define MIN_GROUP_NAME 1
#define MAX_GROUP_NAME 24
#define MAX_USERS 100

struct Group
{
    List *m_users;
    char m_groupName[GROUP_NAME_LEN];
    char m_ipAddr[MAX_IP_LEN];
    int m_port;
    int m_numOfUsers;
};

static void ElementToDest(void *item);
static GroupRes FindUser(Group *_group, char *_username);
static int UserExist(void *_firstName, void *_secondName);
static ListItr FindUserToRmv(Group *_group, char *_username);

Group *CreateGroup(char *_groupName, char *_ip)
{
    Group *group;
    List *userList;

    if (_groupName == NULL || _ip == NULL)
    {
        return NULL;
    }

    if (strlen(_groupName) < MIN_GROUP_NAME || strlen(_groupName) > MAX_GROUP_NAME)
    {
        return NULL;
    }

    group = (Group *)malloc(sizeof(Group));
    if (NULL == group)
    {
        return NULL;
    }

    if ((userList = ListCreate()) == NULL)
    {
        return NULL;
    }

    group->m_users = userList;
    strcpy(group->m_ipAddr, _ip);
    strcpy(group->m_groupName, _groupName);
    group->m_port = PORT_NUM;
    group->m_numOfUsers = 0;

    return group;
}

void DestroyGroup(Group **_group)
{
    if (_group == NULL || *_group == NULL)
    {
        return;
    }

    ListDestroy(&(*_group)->m_users, ElementToDest);
    free(*_group);
    _group = NULL;
}

GroupRes AddUserToGroup(Group *_group, char *_username)
{
    if (_group == NULL || _username == NULL)
    {
        return ADD_FAIL;
    }

    if (_group->m_numOfUsers == MAX_USERS)
    {
        return ADD_FAIL;
    }

    if (FindUser(_group, _username) == DUP_USER)
    {
        return DUP_USER;
    }

    if (ListPushTail(_group->m_users, (void *)_username) != LIST_SUCCESS)
    {
        return ADD_FAIL;
    }

    _group->m_numOfUsers++;
    return ADD_SUCCESS;
}

GroupRes RemoveUserFromGroup(Group *_group, char *_username)
{
    ListItr begin, end;
    void *user;
    if (_group == NULL || _username == NULL || _group->m_numOfUsers == 0)
    {
        return REMOVE_FAIL;
    }
    begin = ListItrBegin(_group->m_users);
    end = ListItrEnd(_group->m_users);
    while (begin != end)
    {
        user = ListItrGet(begin);
        if (strcmp((char *)user, _username) != 0)
        {
            begin = ListItrNext(begin);
        }
        else
        {
            ListItrRemove(begin);
            _group->m_numOfUsers--;
            if (_group->m_numOfUsers == 0)
            {
                DestroyGroup(&_group);
                return GROUP_REMOVED;
            }
            return REMOVE_SUCCESS;
        }
    }
    return REMOVE_FAIL;
}

GroupRes GetGroupIp(Group *_group, char *_bufferIP)
{
    if (_group == NULL || _bufferIP == NULL)
    {
        return NULL_ERR;
    }
    strcpy(_bufferIP, _group->m_ipAddr);
    return SUCCESS;
}

GroupRes GetCounter(Group *_group, char *_bufferCounter)
{
    if (_group == NULL || _bufferCounter == NULL)
    {
        return NULL_ERR;
    }
    return _group->m_numOfUsers;
    return SUCCESS;
}

GroupRes GetName(Group *_group, char *_bufferName)
{
    if (_group == NULL || _bufferName == NULL)
    {
        return NULL_ERR;
    }
    strcpy(_bufferName, _group->m_groupName);
    return SUCCESS;
}

static void ElementToDest(void *item)
{
    free(item);
}

static ListItr FindUserToRmv(Group *_group, char *_username)
{
    ListItr begin, end, findItr;

    if (_group == NULL || _username == NULL)
    {
        return NULL;
    }

    begin = ListItrBegin(_group->m_users);
    end = ListItrEnd(_group->m_users);
    findItr = ListItrFindFirst(begin, end, UserExist, (void *)_username);

    if ((ListItrEquals(findItr, end)) == FALSE)
    {
        return findItr;
    }

    return NULL;
}

static GroupRes FindUser(Group *_group, char *_username)
{
    ListItr begin, end, findItr;
    void *data;

    if (_group == NULL || _username == NULL)
    {
        return NULL_ERR;
    }

    begin = ListItrBegin(_group->m_users);
    end = ListItrEnd(_group->m_users);

    while (begin != end)
    {
        data = ListItrGet(begin);
        if ((strcmp((char *)data, _username)) == 0)
            return DUP_USER;
        begin = ListItrNext(begin);
    }

    return OK;
}

static int UserExist(void *_firstName, void *_secondName)
{
    if (strcmp(_firstName, _secondName) == 0)
    {
        return TRUE;
    }
    return FALSE;
}
