#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#define NAME_LEN_MAX 24
#define PASS_LEN_MAX 8
#define PASS_LEN_MIN 6
#define PORT_NUMBER 1990
#define PACKET_SIZE 200
#define SER_IP "127.0.0.1"

typedef enum Tags
{
    TAG_FAIL = -1,
    REG_REQUEST = 1,
    REG_REP,
    LOGIN_REQUEST,
    LOGIN_REP,
    CLIENT_DISCONNECTED,
    REQUEST_CREATE_GROUP,
    CREATE_GROUP_OK,
    CREATE_GROUP_FAILED,
    REQUEST_JOIN_GROUP,
    JOIN_GROUP_OK,
    JOIN_GROUP_FAILED,
    REQUEST_LEAVE_GROUP,
    LEAVE_REP,
    LEAVE_OK,
    LEAVE_FAIL,
    REQUEST_LOG_OUT,
    LOG_OUT_REP,
    LOG_OUT_OK,
    LOG_OUT_FAIL,
    EXIT_REQUEST,
    SHOW_GROUPS_REQUEST,
    SHOW_GROUPS_OK,
    SHOW_GROUPS_FAIL
} Tags;

typedef enum ProtocolErr
{
    SUCCESS,
    INVALID_MSG = 2,
    INVALID_USERNAME,
    INVALID_PASSWORD,
    INVALID_GROUP_NAME,
    OUT_OF_IP_ADDRESSES,
    SENT_ERROR,
    RECV_ERROR,
    PACKING_ERROR,
    UNPACKING_ERROR,
    PROGRAM_CLOSED,
    REG_ERROR,
    LOGIN_ERROR,
    DUPLICATE_USER_ERROR,
    LOGED_IN_ERR
} ProtocolErr;


/* Description: This function deals with messages of registration & login requests. 
 (stores user data in the _userName and _password buffer)
 Input: _buf: the message in TLV format
        _reaBytes: the length of the message received
        _userName: buffer to store userName
        _password: buffer to store password
Output: status (SUCCESS or INVALID_MSG if input is invalid) */
int UnPackRegLogRequests(char *_buf, int _readBytes, char *_userName, char *_password); /* unpack puts values in username and password buffers*/

/* Description: this function prepares the message of registration request
    Input: _userName: name inserted by user
            _password: the user's password
    Output: full length of message(TLV format) in bytes */
int PackRegRequest(char *_userName, char *_password, char *_bufferPacket);


/* Description: This function deals with messages of registration/login reply- puts errorCode in the buffer
 Input: _message: the message in TLV format
        _msgLen: the length of the message received
        _errCode: buffer to store the error/success info
Output: status (SUCCESS or INVALID_MSG if input is invalid) */
int UnPackRegLogAns(char *_message, char *_errCode, int _msgLen);

/* Description: this function prepares the message of login request
    Input: _userName: name inserted by user
            _password: the user's password
    Output: full length of message(TLV format) in bytes */
int PackLogRequest(char *_userName, char *_password, char *_bufferPacket);


/* Description: this function gets the error code (success or fail errors), and stores it in _bufferPacket
    Input: _errorCode: result of registration status
            _bufferPacket: buffer to store message in TLV format
        
    Output:full length of message(TLV format) in bytes */
int PackRegAns(char _errorCode, char *_bufferPacket);

/* Description: This function packs an answer about login request
    Input: _errorCode: result of login 
            _bufferPacket: buffer to store message in TLV format
     Output:full length of message(TLV format) in bytes         */
int PackLogAns(char _errorCode,char* _bufferPacket );

/*Description: this function packs request for create group 
    Input: _groupName- name for group, inserted by user
            _bufferPacket: buffer to store message 
    Output: full length of message(TLV format) in bytes */
int PackGroupRequest(char *_groupName, char* _userName, char *_bufferPacket);


/* Description: this function deals with requests of creating, joining and leaving groups
    Input:_message: the message in TLV format
           _msgLen: the length of the message received
           _groupName: buffer to store the groupname
           _userName: buffer to store the user name
    Output: status ( SUCCESS or INVALID_MSG )  */
int UnPackGroupRequest(char* _message, int _msgLen, char* _groupName, char* _userName);


/* Description: this function packs answer on create group in cases of failure
    Input: _errorCode: result of create group
            _bufferPacket: buffer to store message in TLV format
     Output:full length of message(TLV format) in bytes */
int PackCreateAnsFail( char _errorCode, char* _bufferPacket);


/* Description: this function packs answer on create group in cases of succcess
    if created group successfully - ip address is stored in the buffer
and tag is CREATE_OK
    Input: _ip: ip address
            bufferPacket: buffer to store message in TLV format
    Output:full length of message(TLV format) in bytes  */
int PackCreateAnsOK( char* _ip, char* _bufferPacket);

/* Description: Answer from server on create&join group requests.
    _answer can be errorCode(if tag = CREATE_GROUP_FAIL / JOIN_GROUP_FAILED) 
    or IP address(if tag = CREATE_GROUP_OK/JOIN_GROUP_OK )*/
int UnPackCreateJoinAns(char *_message, char *_answer, int _msgLen);

/*Description: This function gets groupname and username, and saves them in _bufferPacket
    Output:full length of message(TLV format) in bytes   */
int PackJoinGroupRequest(char *_groupName, char* _userName, char *_bufferPacket);

/* Description: this function packs answer on join group in cases of failure
    Input: _errorCode: result of join group
            _bufferPacket: buffer to store message in TLV format
     Output:full length of message(TLV format) in bytes*/
int PackJoinAnsFail( char _errorCode, char* _bufferPacket);

/* Description: this function packs answer on join group in cases of succcess
    Input: _ip: ip address of group
            bufferPacket: buffer to store message in TLV format
    Output:full length of message(TLV format) in bytes */
int PackJoinAnsOK(char* _ip, char* _bufferPacket);

/*Description: this function packs request to leave group 
    Input: _groupName- name for group, inserted by user
            _userName: username that wants to leave
            _bufferPacket: buffer to store message 
    Output: full length of message(TLV format) in bytes */
int PackLeaveGroupRequest( char *_groupName, char* _userName, char *_bufferPacket);


/*Description: this function packs answer on leave group
    Input: _errorCode: result of leave group (LEAVE_OK or LEAVE_FAIL )
            _bufferPacket: buffer to store message in TLV format
     Output:full length of message(TLV format) in bytes */
int PackLeaveAns(char _errorCode, char* _bufferPacket);


/*/*Description: this function packs answer on leave group
    Input: _errorCode: buffer to store result of leave group (LEAVE_OK or LEAVE_FAIL )
           _message: the message in TLV format
           _msgLen: the length of the message received
    Output: status SUCCESS or INVALID_MSG
      */
int UnPackLeaveAns(char *_message, char *_errCode, int _msgLen );

/* This function returns the tag of _msg
    input: _msg: the message in TLV format
    Output: the tag (enum of message type )*/
int getTag(char *_msg);

/*Description: this function prepares the message of logout request
    Input: _userName: name inserted by user
            _password: the user's password
            _bufferPacket: buffer to store message in TLV format
    Output: full length of message(TLV format) in bytes  */
int PackLogOutRequest(char* _userName, char *_bufferPacket);

/* Description: This function deals with messages of logout requests. 
 Input: _message: the message in TLV format
        _msgLen: the length of the message received
        _userName: buffer to store userName
        _password: buffer to store password
Output: status (SUCCESS or INVALID_MSG if input is invalid)*/
int UnPackLogOutRequest( char* _message, int _msgLen, char* _userName);

/* Description: This function packs an answer about logout request
    Input: _errorCode: result of logout 
            _bufferPacket: buffer to store message in TLV format
     Output:full length of message(TLV format) in bytes  */
int PackLogOutAns(char _errorCode, char* _bufferPacket);

/*Description: This function deals with messages of lougout reply- puts errorCode in the buffer
 Input: _message: the message in TLV format
        _msgLen: the length of the message received
        _errCode: buffer to store the error/success info
Output: status (SUCCESS or INVALID_MSG if input is invalid) */
int UnPackLogOutAns(char *_message, char *_errCode, int _msgLen );

/* Description: this function packs the request to show all groups
    Input:  _bufferPacket: buffer to store message in TLV format
     Output:full length of message(TLV format) in bytes */
int PackShowGroupsRequest( char* _bufferPacket);

/* Description: This function packs an answer on show groups request 
    Input: _groups: string of all group names, sapareted by ' ' 
            _bufferPacket: buffer to store message in TLV format
    Output: full length of message(TLV format) in bytes*/
int PackShowGroupsOK(char* _groups, char* _bufferPacket);

/* Description: if the treat of show  group request failed, this function packs the answer
    Input: _errCode: the error info
            _bufferPacket: buffer to store message in TLV format
    Output: full length of message(TLV format) in bytes */
int PackShowGroupsFail( char _errorCode, char* _bufferPacket);


/* Description: This function deals with unpack of show groups request
    Input: _message :  the message in TLV format
        _msgLen: the length of the message received
        _answer:buffer to store anser-  can be errorCode or the string of group names
    Output: status (SUCCESS or INVALID_MSG if input is invalid)*/
int UnPackShowGroupsAns(char *_message, char *_answer, int _msgLen);

#endif /*__PROTOCOL_H__*/
