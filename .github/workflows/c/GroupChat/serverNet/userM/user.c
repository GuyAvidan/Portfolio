/**********************************************************************************
                                include && define
**********************************************************************************/
#include "/home/guy/prog/GENDS/GenList.h"
#include "/home/guy/prog/GENDS/ListInternal.h" 
#include "/home/guy/prog/GENDS/list_itr.h" 
#include "/home/guy/prog/GENDS/list_functions.h" 
#include "user.h"
#include <stdlib.h>
#include <string.h>

#define NAME_LEN 24
#define PASS_LEN 8
#define MAX_GROUP_NAME 24

/**********************************************************************************
                                User struct
**********************************************************************************/
struct User
{
    List *m_groups;
    char m_userName[NAME_LEN];
    char m_password[PASS_LEN];
    int m_activeFlag;
    int m_socket;
};

/**********************************************************************************
                     Declaration of static Auxiliary Function
**********************************************************************************/
static void FreeGroup(void *_name);

/**********************************************************************************
                                api Functions
**********************************************************************************/
User *CreateUser(char *_userName, char *_password)
{
    User *user;

    if (_userName == NULL || _password == NULL)
    {
        return NULL;
    }

    if ((user = (User *)malloc(sizeof(User))) == NULL)
    {
        return NULL;
    }

    user->m_groups = ListCreate();
    if (user->m_groups == NULL)
    {
        free(user);
        return NULL;
    }

    strcpy(user->m_userName, _userName);
    strcpy(user->m_password, _password);
    user->m_activeFlag = NOT_ACTIVE;
    user->m_socket = -1;

    return user;
}

void DestroyUser(User **_user)
{
    if (_user == NULL || *_user == NULL)
    {
        return;
    }

    ListDestroy(&(*_user)->m_groups, FreeGroup);

    free(*_user);
    *_user = NULL;
}

UserRes GetUserPassword(User *_user, char *_buffer)
{
    if (_user == NULL || _user->m_password == NULL)
    {
        return ERR;
    }
    strcpy(_buffer, _user->m_password);
    return USER_SUCCESS;
}

UserRes GetUserName(User *_user, char *_buffer)
{
    if (_user == NULL || _user->m_userName == NULL)
    {
        return ERR;
    }

    strcpy(_buffer, _user->m_userName);
    return USER_SUCCESS;
}

UserRes JoinGroup(User *_user, char *_groupName)
{
    ListItr begin, end;
    void *group;

    if (_user == NULL || _groupName == NULL)
    {
        return ERR;
    }

    begin = ListItrBegin(_user->m_groups);
    end = ListItrEnd(_user->m_groups);

    while (begin != end)
    {
        group = ListItrGet(begin);
        if (strcmp((char *)group, _groupName) != 0)
        {
            begin = ListItrNext(begin);
        }
        else
        {
            return USER_EXIST;
        }
    }

    ListPushTail(_user->m_groups, _groupName);
    return USER_SUCCESS;
}

UserRes LeaveGroup(User *_user, char *_groupName)
{
    ListItr begin, end;
    void *group;

    if (_user == NULL || _groupName == NULL)
    {
        return ERR;
    }

    begin = ListItrBegin(_user->m_groups);
    end = ListItrEnd(_user->m_groups);

    if (ListSize(_user->m_groups) == 1)
    {
        ListItrRemove(begin);
        return USER_SUCCESS;
    }

    while (begin != end)
    {
        group = ListItrGet(begin);
        if (strcmp((char *)group, _groupName) != 0)
        {
            begin = ListItrNext(begin);
        }
        else
        {
            ListItrRemove(begin);
            return USER_SUCCESS;
        }
    }
    return GROUP_NOT_FOUND;
}

UserRes LeaveAllGroups(User *_user)
{
    ListItr itr, end;
    void *itemToRem;

    if (_user == NULL)
    {
        return ERR;
    }

    itr = ListItrBegin(_user->m_groups);
    end = ListItrEnd(_user->m_groups);

    while (itr != end)
    {
        itr = ListItrNext(itr);
        ListPopHead(_user->m_groups, &itemToRem);
    }

    _user->m_activeFlag = NOT_ACTIVE;
    return USER_SUCCESS;
}

void setActiveFlag(User *_user, int _activeFlag)
{
    if (_user == NULL)
    {
        return;
    }

    _user->m_activeFlag = _activeFlag;
}

int GetActiveStatus(User *_user)
{
    if (_user == NULL)
    {
        return ERR;
    }

    return _user->m_activeFlag;
}

static void FreeGroup(void *_name)
{
    free(_name);
}
