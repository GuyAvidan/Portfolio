#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../pool_ip/IPpool.h"

#include "groupManager.h"
#include "group.h"

#include "/home/guy/prog/GENDS/GenList.h"
#include "/home/guy/prog/GENDS/ListInternal.h" 
#include "/home/guy/prog/GENDS/list_itr.h" 
#include "/home/guy/prog/GENDS/list_functions.h" 
#include "/home/guy/prog/GENDS/HashMap.h"

#define HASH_SIZE 100
/* prime numbers for hashFunction */
#define PRIME_NUM_A 3
#define PRIME_NUM_B 7
#define MIN_GROUP_NAME 1
#define MAX_GROUP_NAME 24
#define IP_LEN 11
struct GroupManager
{
    HashMap *m_groups;
    IpPool *m_pool;
};

static size_t GroupHashFunc(const void *_groupName);
static int GroupEqualFunc(void *_name1, void *_name2);
static int ActionCatGroups(const void *_key, void *_value, void *_context);


GroupManager *CreateGroupManager()
{
    GroupManager *manager;

    if ((manager = (GroupManager *)malloc(sizeof(GroupManager))) == NULL)
    {
        return NULL;
    }

    manager->m_groups = HashMap_Create(HASH_SIZE, GroupHashFunc, GroupEqualFunc);
    if (manager->m_groups == NULL)
    {
        free(manager);
        return NULL;
    }
    manager->m_pool = IpPoolCreate();
    if (manager->m_pool == NULL)
    {
        free(manager);
        return NULL;
    }
    return manager;
}

GroupMRes AddGroupToHash(GroupManager *_groupManager, char *_groupName)
{
    int status;
    Group *group;
    char *keyName, bufferIP[IP_LEN];
    void *value;
    char *key;
    
    if (_groupManager == NULL || _groupName == NULL)
    {
        return GROUP_NULL_ERR;
    }
    if ((key = (char *)malloc(strlen(_groupName) + 1)) == NULL)
    {
        return GROUP_ALLOCATION_FAIL;
    }
    strcpy(key, _groupName);
    if ((HashMap_Find(_groupManager->m_groups, (void *)key, &value)) == MAP_SUCCESS)
    {
        return DUPLICATE_GROUP;
    }

    status = GetIp(_groupManager->m_pool, bufferIP);
    if (status == IPSUCESS) /* need to match enum of IPPool*/
    {
        group = CreateGroup(_groupName, bufferIP);
        if (group != NULL)
        {
            if ((HashMap_Insert(_groupManager->m_groups, key, group)) != MAP_SUCCESS)
            {
                return HASH_INSERT_FAIL;
            }
            return GROUPM_SUCCESS;
        }
        return CREATE_GROUP_FAIL;
    }
    return OUT_OF_IP_ADDRS;
}

GroupMRes FindIP(GroupManager *_groupManager, char *_groupName, char *_bufferIP)
{
    char *key;
    void *value;
    if (_groupManager == NULL || _groupName == NULL || _bufferIP == NULL)
    {
        return GROUP_NULL_ERR;
    }
    if ((key = (char *)malloc(strlen(_groupName) + 1)) == NULL)
    {
        return GROUP_ALLOCATION_FAIL;
    }

    strcpy(key, _groupName);
    if ((HashMap_Find(_groupManager->m_groups, (void *)key, &value)) == MAP_SUCCESS)
    {
        GetGroupIp((Group *)value, _bufferIP);
        return GROUPM_SUCCESS;
    }
    return GROUP_NOT_FOUND;
}

GroupMRes AddUser(GroupManager *_groupManager, char *_groupName, char *_userName)
{
    char *key;
    char *userBuf;
    void *value;
    int res;
    if (_groupManager == NULL || _groupName == NULL || _userName == NULL)
    {
        return GROUP_NULL_ERR;
    }
    if ((key = (char *)malloc(strlen(_groupName) + 1)) == NULL)
    {
        return GROUP_ALLOCATION_FAIL;
    }
    strcpy(key, _groupName);
    if ((userBuf = (char *)malloc(strlen(_userName) + 1)) == NULL)
    {
        return GROUP_ALLOCATION_FAIL;
    }
    strcpy(userBuf, _userName);
    if ((HashMap_Find(_groupManager->m_groups, (void *)key, &value)) == MAP_SUCCESS)
    {
        res = AddUserToGroup((Group *)value, userBuf);
        if (res == ADD_SUCCESS)
        {
            return GROUPM_SUCCESS;
        }
        if (res == DUP_USER)
        {
            return DUPLICATE_USER;
        }
    }

    return GROUP_NOT_FOUND;
}

GroupMRes DelUserFromGroup(GroupManager *_groupManager, char *_groupName, char *_userName)
{
    char *key;
    char *userBuf;
    void *value, *pKey, *pValue;
    int res;
    if (_groupManager == NULL || _groupName == NULL || _userName == NULL)
    {
        return GROUP_NULL_ERR;
    }
    if ((key = (char *)malloc(strlen(_groupName) + 1)) == NULL)
    {
        return GROUP_ALLOCATION_FAIL;
    }
    strcpy(key, _groupName);
    if ((userBuf = (char *)malloc(strlen(_userName) + 1)) == NULL)
    {
        return GROUP_ALLOCATION_FAIL;
    }
    strcpy(userBuf, _userName);
    if ((HashMap_Find(_groupManager->m_groups, (void *)key, &value)) == MAP_SUCCESS)
    {
        res = RemoveUserFromGroup((Group *)value, userBuf);
        if (res == REMOVE_SUCCESS)
        {
            return GROUPM_SUCCESS;
        }
        if (res == GROUP_REMOVED)
        {
            HashMap_Remove(_groupManager->m_groups, (void *)key, &pKey, &pValue);
            return GROUPM_SUCCESS;
        }
    }

    return GROUP_NOT_FOUND;
}



GroupMRes GetGroupNames(GroupManager *_groupManager, char *_bufferNames)
{
    int counter;
    char tab = ' ';

    if (_groupManager == NULL || _bufferNames == NULL)
    {
        return GROUP_NULL_ERR;
    }
    strcpy(_bufferNames, " ");
    counter = HashMap_ForEach(_groupManager->m_groups, ActionCatGroups, (void *)_bufferNames);
    return GROUPM_SUCCESS;
}

void DestroyGroupManager(GroupManager **_groupManager)
{
    if (_groupManager == NULL || *_groupManager == NULL)
    {
        return;
    }
    DestroyIpQue((*_groupManager)->m_pool);
    HashMap_Destroy(&(*_groupManager)->m_groups, NULL, (void (*)(void *))DestroyGroup);
    free(*_groupManager);
    *_groupManager = NULL;
    return;
}


static int ActionCatGroups(const void *_key, void *_value, void *_context)
{
    char tab = ' ';

    if (_key != NULL && _value != NULL && _context != NULL)
    {
        strcat((char *)_context, (char *)_key);
        strcat((char *)_context, &tab);
        return 1;
    }
    return 0;
}

static size_t GroupHashFunc(const void *_groupName)
{
    int hash = 0, i;
    char *groupName = (char *)_groupName;

    for (i = 0; groupName[i] != '\0'; ++i)
    {
        hash += PRIME_NUM_A + (groupName[i] % PRIME_NUM_B);
    }

    return hash;
}

static int GroupEqualFunc(void *_name1, void *_name2)
{
    if (strcmp((char *)_name1, (char *)_name2) == 0)
    {
        return 1;
    }

    return 0;
}
