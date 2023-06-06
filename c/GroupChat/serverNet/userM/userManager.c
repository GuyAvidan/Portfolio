/**********************************************************************************
                                include && define
**********************************************************************************/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "user.h"
#include "userManager.h"
#include "/home/guy/prog/GENDS/GenList.h"
#include "/home/guy/prog/GENDS/ListInternal.h" 
#include "/home/guy/prog/GENDS/list_itr.h" 
#include "/home/guy/prog/GENDS/list_functions.h" 
#include "/home/guy/prog/GENDS/HashMap.h"

#define NAME_LEN 24
#define PASS_LEN 8
#define HASH_SIZE 255

/* prime numbers for hashFunction */
#define PRIME_NUM_A 3
#define PRIME_NUM_B 7

/**********************************************************************************
                                UserManager struct
**********************************************************************************/
struct UserManager
{
    HashMap *m_users;
};

/**********************************************************************************
                     Declaration of static Auxiliary Functions
**********************************************************************************/
static size_t UserHashFunc(const void *_userName);
static int UserEqualFunc(void *_userName1, void *_userName2);
static void UserValToDestroy(void *_User);
static void UserKeyToDestroy(void *_keyUserName);
static void InsertClientToHash(HashMap *_users, FILE *_regUsers);

/**********************************************************************************
                                api Functions
**********************************************************************************/
UserManager *UserManagerCreate()
{
    UserManager *user;

    if ((user = (UserManager *)malloc(sizeof(UserManager))) == NULL)
    {
        return NULL;
    }

    user->m_users = HashMap_Create(HASH_SIZE, UserHashFunc, UserEqualFunc);
    if (user->m_users == NULL)
    {
        free(user);
        return NULL;
    }

    InitHashFromFile(user);
    return user;
}

UserManagerRes AddToUsersMap(char *_keyUserName, char *_password, UserManager *_manager)
{
    User *user;
    FILE *registeredUsers = fopen("users.txt", "a");
    char strName[NAME_LEN];
    char strPass[PASS_LEN];
    char *key;
    if (_keyUserName == NULL || _password == NULL || _manager == NULL)
    {
        return FAIL;
    }
    if (registeredUsers == NULL)
    {
        return FOPEN_ERR;
    }

    if (strlen(_keyUserName) < 3 || strlen(_keyUserName) > 24)
    {
        return NAME_SIZE_ERR;
    }

    if (strlen(_password) < 3 || strlen(_password) > 8)
    {
        return PASS_SIZE_ERR;
    }

    if ((key = (char *)malloc(strlen(_keyUserName) + 1)) == NULL)
    {
        return ALLOCATION_ERR;
    }
    strcpy(key, _keyUserName);

    if (GetUserDetails(_manager, _keyUserName, strName, strPass) == FOUND)
    {
        return DUPLICATE_USER_ERR;
    }

    if ((user = CreateUser(key, _password)) == NULL)
    {
        return CREATE_USER_ERR;
    }

    if ((HashMap_Insert(_manager->m_users, key, user)) != MAP_SUCCESS)
    {
        return HASH_INSERT_ERR;
    }

    fprintf(registeredUsers, "%s %s\n", key, _password);
    fclose(registeredUsers);

    return USER_MNG_SUCCESS;
}

UserManagerRes RemoveUser(char *_keyUserName, UserManager *_manager)
{
    void *key = NULL, *value = NULL;
    char *res;
    char strName[NAME_LEN];
    char strPass[PASS_LEN];

    if (_keyUserName == NULL || _manager == NULL)
    {
        return HASH_REMOVE_ERR;
    }

    if (GetUserDetails(_manager, _keyUserName, strName, strPass) == FOUND)
    {
        if ((HashMap_Remove(_manager->m_users, _keyUserName, &key, &value)) == MAP_SUCCESS)
        {
            return REMOVE_USER_SUCCESS;
        }
        return HASH_REMOVE_ERR;
    }

    return USER_NOT_FOUND_ERR;
}

UserManagerRes UserLogOut(UserManager *_manager, char *_keyUserName)
{
    void *user;
    if (_manager == NULL || _keyUserName == NULL)
    {
        return USER_NOT_FOUND_ERR;
    }
    if ((HashMap_Find(_manager->m_users, _keyUserName, &user)) == MAP_SUCCESS)
    {
        LeaveAllGroups((User *)user);
        setActiveFlag((User *)user, NOT_ACTIVE);
        return USER_MNG_SUCCESS;
    }
    return USER_NOT_FOUND_ERR;
}

UserManagerRes UserExit(UserManager *_manager, char *_keyUserName)
{
    void *user;
    User *userToDesroy;

    if (_manager == NULL || _keyUserName == NULL)
    {
        return USER_NOT_FOUND_ERR;
    }

    if ((HashMap_Find(_manager->m_users, _keyUserName, &user)) == MAP_SUCCESS)
    {
        userToDesroy = (User *)user;
        DestroyUser(&(userToDesroy));
        return USER_MNG_SUCCESS;
    }

    return USER_NOT_FOUND_ERR;
}

UserManagerRes LogInUser(UserManager *_manager, char *_keyUserName, char *_password)
{
    void *user;
    char password[PASS_LEN];

    if (_manager == NULL || _manager->m_users == NULL || _keyUserName == NULL || _password == NULL)
    {
        return FAIL;
    }

    if ((HashMap_Find(_manager->m_users, (void *)_keyUserName, &user)) == MAP_SUCCESS)
    {
        if (GetUserPassword((User *)user, password) == USER_SUCCESS)
        {
            if (strcmp(_password, password) == 0)
            {
                if ((GetActiveStatus((User *)user)) == NOT_ACTIVE)
                {
                    setActiveFlag((User *)user, ACTIVE);
                    return USER_MNG_SUCCESS;
                }
                return USER_LOGED_IN;
            }
            return INVALID_PASS_ERR;
        }

        return INVALID_PASS_ERR;
    }

    return USER_NOT_FOUND_ERR;
}

UserManagerRes UserLeaveGroup(UserManager *_manager, char *_username, char *_groupName)
{
    void *user;
    void *keyUserName, *groupBuf;

    if (_manager == NULL || _username == NULL || _groupName == NULL)
    {
        return FAIL;
    }

    if ((keyUserName = (char *)malloc(strlen(_username) + 1)) == NULL)
    {
        return FAIL;
    }

    strcpy(keyUserName, _username);
    if ((groupBuf = (char *)malloc(strlen(_groupName) + 1)) == NULL)
    {
        return FAIL;
    }

    strcpy(groupBuf, _groupName);
    if ((HashMap_Find(_manager->m_users, keyUserName, &user)) == MAP_SUCCESS)
    {
        LeaveGroup((User *)user, groupBuf);
        return USER_MNG_SUCCESS;
    }
    else
    {
        return USER_NOT_FOUND_ERR;
    }
}

UserManagerRes UserJoinGroup(UserManager *_manager, char *_username, char *_groupName)
{
    void *user;
    char *groupBuf;
    char *userBuf;
    if (_username == NULL || _groupName == NULL || _manager == NULL)
    {
        return FAIL;
    }
    if ((groupBuf = (char *)malloc(strlen(_groupName) + 1)) == NULL)
    {
        return FAIL;
    }
    strcpy(groupBuf, _groupName);
    if ((userBuf = (char *)malloc(strlen(_username) + 1)) == NULL)
    {
        free(groupBuf);
        return FAIL;
    }
    strcpy(userBuf, _username);
    if ((HashMap_Find(_manager->m_users, userBuf, &user)) == MAP_SUCCESS)
    {
        if ((JoinGroup((User *)user, groupBuf)) == USER_SUCCESS)
        {
            return USER_MNG_SUCCESS;
        }
        else
        {
            return USER_ALREADY_EXIST_ERR;
        }
    }
    else
    {
        return USER_NOT_FOUND_ERR;
    }
}

UserManagerRes GetUserDetails(UserManager *_manager, char *_keyUserName, char *_bufferName, char *_bufferPass)
{
    void *value;

    if (_keyUserName == NULL || _manager == NULL || _bufferName == NULL || _bufferPass == NULL)
    {
        return NOT_FOUND;
    }

    if ((HashMap_Find(_manager->m_users, (void *)_keyUserName, &value)) == MAP_SUCCESS)
    {
        if (GetUserName((User *)value, _bufferName) == 1)
        {
            if (GetUserPassword((User *)value, _bufferPass) == 1)
            {
                setActiveFlag((User *)value, ACTIVE);
                return FOUND;
            }
        }
    }

    return NOT_FOUND;
}

void DestroyUserHash(UserManager *_user)
{
    if (_user != NULL)
    {
        HashMap_Destroy(&(_user->m_users), UserKeyToDestroy, UserValToDestroy);
    }
}

UserManagerRes InitHashFromFile(UserManager *_manager)
{
    FILE *registeredUsers = fopen("users.txt", "r");

    if (registeredUsers == NULL || _manager == NULL || _manager->m_users == NULL)
    {
        return FOPEN_ERR;
    }
    InsertClientToHash(_manager->m_users, registeredUsers);
    while (!feof(registeredUsers))
    {
        InsertClientToHash(_manager->m_users, registeredUsers);
    }

    fclose(registeredUsers);

    return USER_MNG_SUCCESS;
}

/**********************************************************************************
                        static Auxiliary Functions
**********************************************************************************/
static void UserKeyToDestroy(void *_keyUserName)
{
    free(_keyUserName);
}

static void UserValToDestroy(void *_User)
{
    free(_User);
}

static size_t UserHashFunc(const void *_userName)
{
    int hash = 0, i;
    char *userName;
    userName = (char *)_userName;

    for (i = 0; userName[i] != '\0'; ++i)
    {
        hash += PRIME_NUM_A + (userName[i] % PRIME_NUM_B);
    }

    return hash;
}

static int UserEqualFunc(void *_userName1, void *_userName2)
{
    if (strcmp((char *)_userName1, (char *)_userName2) == 0)
    {
        return 1;
    }

    return 0;
}

static void InsertClientToHash(HashMap *_users, FILE *_regUsers)
{
    User *user;
    char userBuff[NAME_LEN], password[PASS_LEN];
    char *userName;
    int sock;

    fscanf(_regUsers, "%s %s\n", userBuff, password);

    if ((userName = malloc(strlen(userBuff) + 1)) == NULL)
    {
        return;
    }

    strcpy(userName, userBuff);
    user = CreateUser(userName, password);
    HashMap_Insert(_users, userName, user);
}
