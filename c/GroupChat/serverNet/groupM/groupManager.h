#ifndef __GROUP_MANAGER_H__
#define __GROUP_MANAGER_H__

typedef struct GroupManager GroupManager;

typedef enum GroupMRes
{
    GROUPM_SUCCESS,
    FOPEN_ERROR,
    WRONG_NAME_SIZE,
    WRONG_PASS_SIZE,
    DUPLICATE_GROUP,
    CREATE_GROUP_FAIL,
    HASH_INSERT_FAIL,
    HASH_REMOVE_FAIL,
    GROUP_ALLOCATION_FAIL,
    GROUP_NULL_ERR,
    OUT_OF_IP_ADDRS,
    GROUP_FOUND,
    GROUP_NOT_FOUND,
    DUPLICATE_USER

} GroupMRes;

/* Description: This function creates a group manager struct, containing data structure of all groups and a data strcture 
managing the available ip numbers for groups
    No input is required
    Output: GroupManager pointer*/
GroupManager *CreateGroupManager();

/* Description: this function frees the memory occupied by the groupManager struct 
    Input: pointer to group manager pointer
    No Output */
void DestroyGroupManager(GroupManager **_groupManager);

/* Description: This function adds a group to the data structure (Hash map) with all groups
    Input: Group manager pointer
            The name of the group
    Output: Result in GroupMRes enum: GROUPM_SUCCESS/HASH_INSERT_FAIL/CREATE_GROUP_FAIL/OUT_OF_IP_ADDRS/DUPLICATE_GROUP/GROUP_NULL_ERR*/
GroupMRes AddGroupToHash(GroupManager *_groupManager, char *_groupName);


/* Description: This function finds an IP address from the IP pool and saves it as the ip of _groupName
        Input: GroupManager pointer, groupname and buffer to store the new IP address
        Output: GROUP_NULL_ERR/GROUP_ALLOCATION_FAIL/GROUP_NOT_FOUND/GROUPM_SUCCESS*/
GroupMRes FindIP(GroupManager *_groupManager, char *_groupName, char *_bufferIP);

/* Description: This function adds a userName to a group in the hash map
            Input: GroupManager pointer, the group name and the user name to add
            Output: result in GroupMRes enum: GROUP_NULL_ERR/GROUPM_SUCCESS/DUPLICATE_USER/GROUP_NOT_FOUND*/
GroupMRes AddUser(GroupManager *_groupManager, char *_groupName, char *_userName);

/*Description: This function removes a userName from a group in the hash map
            Input: GroupManager pointer, the group name and the user name to remove
            Output: result in GroupMRes enum: GROUP_NULL_ERR/GROUPM_SUCCESS/GROUP_NOT_FOUND */
GroupMRes DelUserFromGroup( GroupManager *_groupManager, char *_groupName, char *_userName);

/* Description: This function creates a string of all group names in the hash, sapareted by a blank
    Input: GroupManager pointer, _bufferNames: buffer to store all group names
        Output:result in GroupMRes enum: GROUP_NULL_ERR/GROUPM_SUCCESS */
GroupMRes GetGroupNames(GroupManager *_groupManager, char *_bufferNames);

#endif /* __GROUP_MANAGER_H__ */