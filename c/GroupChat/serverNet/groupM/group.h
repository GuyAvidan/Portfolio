
#ifndef __GROUP_H__
#define __GROUP_H__

typedef struct Group Group;

typedef enum GroupRes
{
    ADD_SUCCESS,
    ADD_FAIL,
    REMOVE_SUCCESS,
    REMOVE_FAIL,
    NULL_ERR,
    SUCCESS,
    IPSUCESS,
    DUP_USER,
    OK,
    GROUP_REMOVED
} GroupRes;

/**
 * @brief   create a new Group object of given _groupName and _ip
 * @param[in] _groupName
 * @param[in] _ip
 * @return NULL or pointer to Group
 * @retval pointer to Group struct - on success
 * @retval NULL on failure
 */
Group *CreateGroup(char *_groupName, char *_ip);

/**
 * @brief the DestroyUser finction destroys a given Group
 * @param _group - Group to be deallocated.
 * @return  x
 */
void DestroyGroup(Group **_group);

/**
 * @brief  adding user to group
 * @param _group
 * @param _username
 * @return  GroupRes
 * @retval ADD_FAIL
 * @retval DUP_USER
 * @retval ADD_SUCCESS
 */
GroupRes AddUserToGroup(Group *_group, char *_username);
GroupRes RemoveUserFromGroup(Group *_group, char *_username);
GroupRes GetGroupIp(Group *_group, char *_bufferIP);
GroupRes GetCounter(Group *_group, char *_bufferCounter);
GroupRes GetName(Group *_group, char *_bufferName);

#endif /* __GROUP_H__ */