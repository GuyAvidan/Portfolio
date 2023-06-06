#ifndef __USER_MANAGER_H__
#define __USER_MANAGER_H__

typedef enum UserManagerRes
{
    USER_MNG_SUCCESS,
    REMOVE_USER_SUCCESS,
    FOPEN_ERR,
    NAME_SIZE_ERR,
    PASS_SIZE_ERR,
    ALLOCATION_ERR,
    DUPLICATE_USER_ERR,
    CREATE_USER_ERR,
    HASH_INSERT_ERR,
    HASH_REMOVE_ERR,
    USER_ALREADY_EXIST_ERR,
    USER_NOT_FOUND_ERR,
    INVALID_PASS_ERR,
    FOUND,
    NOT_FOUND,
    FAIL,
    USER_LOGED_IN
} UserManagerRes;

typedef struct UserManager UserManager;

/**
 * @brief   create a new UserManager object
 * @return NULL or pointer to UserManager
 * @retval pointer to UserManager struct - on success
 * @retval NULL on failure
 */
UserManager *UserManagerCreate();

/**
 * @brief  removes user from the hash
 * @param _keyUserName - a user key to hash
 * @param _manager
 * @return UserManagerRes
 * @retval HASH_REMOVE_ERR
 * @retval USER_NOT_FOUND_ERR
 * @retval REMOVE_USER_SUCCESS
 */
UserManagerRes RemoveUser(char *_keyUserName, UserManager *_manager);

/**
 * @brief  add user from to the hash
 * @param _keyUserName - a user key to hash
 * @param _password
 * @param _manager
 * @return UserManagerRes
 * @retval FAIL
 * @retval FOPEN_ERR
 * @retval NAME_SIZE_ERR
 * @retval PASS_SIZE_ERR
 * @retval ALLOCATION_ERR
 * @retval DUPLICATE_USER_ERR
 * @retval CREATE_USER_ERR
 * @retval HASH_INSERT_ERR
 * @retval USER_MNG_SUCCESS
 */
UserManagerRes AddToUsersMap(char *_keyUserName, char *_password, UserManager *_manager);

/**
 * @brief  find user and returns her details
 * @param _keyUserName - a user key to hash
 * @param _bufferName
 * @param _bufferPass
 * @param _manager
 * @return UserManagerRes
 * @retval NOT_FOUND
 * @retval FOUND
 */
UserManagerRes GetUserDetails(UserManager *_manager, char *_keyUserName, char *_bufferName, char *_bufferPass);

/**
 * @brief  removes the user from all groups and change the activityFlag
 * @param _keyUserName - a user key to hash
 * @param _manager
 * @return UserManagerRes
 * @retval USER_NOT_FOUND_ERR
 * @retval USER_MNG_SUCCESS
 */
UserManagerRes UserLogOut(UserManager *_manager, char *_keyUserName);

/**
 * @brief  login user to chat
 * @param _keyUserName
 * @param _manager
 * @return UserManagerRes
 * @retval USER_NOT_FOUND_ERR
 * @retval INVALID_PASS_ERR
 * @retval USER_LOGED_IN
 * @retval USER_MNG_SUCCESS
 */
UserManagerRes LogInUser(UserManager *_manager, char *_keyUserName, char *_password);

/**
 * @brief  removes the group from the user
 * @param _keyUserName
 * @param _username
 * @param _groupName
 * @return UserManagerRes
 * @retval USER_NOT_FOUND_ERR
 * @retval FAIL
 * @retval USER_MNG_SUCCESS
 */
UserManagerRes UserLeaveGroup(UserManager *_manager, char *_username, char *_groupName);

/**
 * @brief  Connects a user to a given group
 * @param _keyUserName
 * @param _username
 * @param _groupName
 * @return UserManagerRes
 * @retval USER_NOT_FOUND_ERR
 * @retval FAIL
 * @retval USER_ALREADY_EXIST_ERR
 * @retval USER_MNG_SUCCESS
 */
UserManagerRes UserJoinGroup(UserManager *_manager, char *_username, char *_groupName);

/**
 * @brief  initialized the hash with users from a file
 * @param _keyUserName
 * @return UserManagerRes
 * @retval FOPEN_ERR
 * @retval USER_MNG_SUCCESS
 */
UserManagerRes InitHashFromFile(UserManager *_manager);

/**
 * @brief  find user and destroy him
 * @param _keyUserName
 * @return UserManagerRes
 * @retval USER_NOT_FOUND_ERR
 * @retval USER_MNG_SUCCESS
 */
UserManagerRes UserExit(UserManager *_manager, char *_keyUserName);

#endif /* __USER_MANAGER_H__ */