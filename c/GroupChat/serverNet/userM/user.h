
#ifndef __USER_H__
#define __USER_H__

#define ACTIVE 1
#define NOT_ACTIVE 0

typedef struct User User;

typedef enum UserRes
{
    USER_SUCCESS,
    USER_EXIST,
    GROUP_NOT_FOUND,
    ERR = -1
} UserRes;

/**
 * @brief   create a new user object of given _userName and _password
 * @param[in] _userName
 * @param[in] _password
 * @return NULL or pointer to User
 * @retval pointer to User struct - on success
 * @retval NULL on failure
 */
User *CreateUser(char *_userName, char *_password);

/**
 * @brief the DestroyUser finction destroys a given User
 * @param _user - User to be deallocated.
 * @return  x
 */
void DestroyUser(User **_user);

/**
 * @brief The function copies the user's password to _buffer and returns a status
 * @param _user
 * @param _buffer - contains the user pass
 * @return  UserRes
 * @retval ERR
 * @retval USER_SUCCESS
 */
UserRes GetUserPassword(User *_user, char *_buffer);

/**
 * @brief The function copies the user's username to _buffer and returns a status
 * @param _user
 * @param _buffer  - contains the user username
 * @return  UserRes
 * @retval ERR
 * @retval USER_SUCCESS
 */
UserRes GetUserName(User *_user, char *_buffer);

/**
 * @brief The function attaches a user to a group
 * @param _user
 * @param _groupName - The name of the group the user wants to join
 * @return  UserRes
 * @retval ERR
 * @retval USER_EXIST
 * @retval USER_SUCCESS
 */
UserRes JoinGroup(User *_user, char *_groupName);

/**
 * @brief The function removes a user from a group
 * @param _user
 * @param _groupName - The name of the group the user wants to leave
 * @return  UserRes
 * @retval ERR
 * @retval GROUP_NOT_FOUND
 * @retval USER_SUCCESS
 */
UserRes LeaveGroup(User *_user, char *_groupName);

/**
 * @brief The function removes the user from all the group
 * @param _user
 * @return  UserRes
 * @retval ERR
 * @retval USER_SUCCESS
 */
UserRes LeaveAllGroups(User *_user);

/**
 * @brief The function changes the cativeFlag of the given user to the given _activeFlag
 * @param _user
 * @param _activeFlag - the new ativeFlag status
 * @return  void
 */
void setActiveFlag(User *_user, int _activeFlag);

/**
 * @brief getter func - the func returns the user scativeStatus
 * @param _user
 * @return  int
 * @retval ERR if the user not exist (equal to null)
 * @retval user ActiveFlag
 */
int GetActiveStatus(User *_user);
#endif /* __USER_H__ */