
#include "protocol.h"
#include <string.h>
#include <stdio.h>

int UnPackRegLogRequests(char *_msg, int _totalLen, char *_userName, char *_password)
{
    int nameLen, passLen;
    if (_msg == NULL || _totalLen < 3 || _userName == NULL || _password == NULL)
    {
        return INVALID_MSG;
    }
    nameLen = _msg[2];
    passLen = _msg[3 + nameLen];
    strncpy(_userName, (const char *)&_msg[3], nameLen);

    _userName[nameLen] = '\0';
    strncpy(_password, (const char *)&_msg[4 + nameLen], passLen);

    _password[passLen] = '\0';

    return SUCCESS;
}



int PackRegRequest(char *_userName, char *_password, char *_bufferPacket)
{
    int nameLen, passLen;
    int msgLen;
    if (_userName == NULL || _password == NULL || _bufferPacket == NULL)
    {
        return INVALID_MSG;
    }
    nameLen = strlen(_userName);
    passLen = strlen(_password);
    msgLen = nameLen + passLen + 2;
    _bufferPacket[0] = REG_REQUEST;
    _bufferPacket[1] = msgLen; /* name len + password len*/
    _bufferPacket[2] = nameLen;
    strncpy(&_bufferPacket[3], _userName, nameLen);
    _bufferPacket[3 + nameLen] = passLen;
    strncpy(&_bufferPacket[4 + nameLen], _password, passLen);

    return (2 + msgLen);
}




int PackRegAns(char _errorCode, char *_bufferPacket)
{
    if( _bufferPacket == NULL)
    {
        return INVALID_MSG;
    }
    _bufferPacket[0] = REG_REP;
    _bufferPacket[1] = 1; /* len of message in bytes */
    _bufferPacket[2] = _errorCode;
    return 3;
}

int UnPackRegLogAns(char *_message, char *_errCode, int _msgLen)
{
    if (_message == NULL || _msgLen < 3 || _errCode == NULL)
    {
        return INVALID_MSG;
    }

    *_errCode = _message[2];

    return SUCCESS;
}


int PackLogAns(char _errorCode,char* _bufferPacket )
{
    if( _bufferPacket == NULL)
    {
        return INVALID_MSG;
    }
    _bufferPacket[0] = LOGIN_REP;
    _bufferPacket[1] = 1; /* len of message in bytes */
    _bufferPacket[2] = _errorCode;
    return 3;
}

int PackLogRequest(char *_userName, char *_password, char *_bufferPacket)
{
    int nameLen, passLen;
    int msgLen;
    if (_userName == NULL || _password == NULL || _bufferPacket == NULL)
    {
        return INVALID_MSG;
    }
    nameLen = strlen(_userName);
    passLen = strlen(_password);
    msgLen = nameLen + passLen + 2;
    _bufferPacket[0] = LOGIN_REQUEST; /* 3*/
    _bufferPacket[1] = msgLen; 
    _bufferPacket[2] = nameLen;
    strncpy(&_bufferPacket[3], _userName, nameLen);
    _bufferPacket[3 + nameLen] = passLen;
    strncpy(&_bufferPacket[4 + nameLen], _password, passLen);

    return (2 + msgLen); /* total length of message*/
}

int PackGroupRequest(char *_groupName, char* _userName, char *_bufferPacket)
{
    int nameLen, userLen, msgLen;
    if( _groupName == NULL|| _userName == NULL || _bufferPacket == NULL)
    {
        return INVALID_MSG;
    }
    nameLen = strlen(_groupName);
    userLen = strlen(_userName);
    _bufferPacket[0] = REQUEST_CREATE_GROUP;
    msgLen = nameLen+userLen+2;
    _bufferPacket[1] = msgLen; 
    _bufferPacket[2] = nameLen;
    strncpy(&_bufferPacket[3], _groupName, nameLen);
    _bufferPacket[3 + nameLen] = userLen;
    strncpy(&_bufferPacket[4 + nameLen], _userName, userLen);
    return (2 + msgLen);
}

int PackJoinGroupRequest(char *_groupName, char* _userName, char *_bufferPacket)
{
    int nameLen, userLen, msgLen;
    if( _groupName == NULL|| _userName == NULL || _bufferPacket == NULL)
    {
        return INVALID_MSG;
    }
    nameLen = strlen(_groupName);
    userLen = strlen(_userName);
    _bufferPacket[0] = REQUEST_JOIN_GROUP;
    msgLen = nameLen+userLen+2;
    _bufferPacket[1] = msgLen; 
    _bufferPacket[2] = nameLen;
    strncpy(&_bufferPacket[3], _groupName, nameLen);
    _bufferPacket[3 + nameLen] = userLen;
    strncpy(&_bufferPacket[4 + nameLen], _userName, userLen);
    return (2 + msgLen);
}




int UnPackGroupRequest(char* _message, int _msgLen, char* _groupName, char* _userName)
{
    int nameLen, userLen;
    if (_message == NULL || _msgLen < 3 || _groupName == NULL|| _userName==NULL)
    {
        return INVALID_MSG;
    }
     nameLen = _message[2];
     userLen = _message[3+nameLen];
    strncpy(_groupName, (const char *)&_message[3], nameLen);
    _groupName[nameLen] = '\0';
    strncpy(_userName, (const char*)&_message[4+nameLen], userLen);
    _userName[userLen]='\0';

    return SUCCESS;
}


int PackCreateAnsFail( char _errorCode, char* _bufferPacket)
{
    if( _bufferPacket == NULL)
    {
        return INVALID_MSG;
    }
    _bufferPacket[0] = CREATE_GROUP_FAILED;
    _bufferPacket[1] = 1; /* len of message in bytes */
    _bufferPacket[2] = _errorCode;
    return 3;
}

int PackCreateAnsOK( char* _ip, char* _bufferPacket)
{
    int ipLen, msgLen;
    if( _ip == NULL || _bufferPacket ==NULL)
    {
        return INVALID_MSG;
    }
    ipLen = strlen(_ip);
    _bufferPacket[0] = CREATE_GROUP_OK;
    msgLen = ipLen+1;
    _bufferPacket[1] = msgLen; 
    _bufferPacket[2] = ipLen;
    strncpy(&_bufferPacket[3], _ip, ipLen);
    return (2 + msgLen);
}


int PackJoinAnsFail( char _errorCode, char* _bufferPacket)
{
    if( _bufferPacket == NULL)
    {
        return INVALID_MSG;
    }
    _bufferPacket[0] = JOIN_GROUP_FAILED;
    _bufferPacket[1] = 1; /* len of message in bytes */
    _bufferPacket[2] = _errorCode;
    return 3;
}


int PackJoinAnsOK(char* _ip, char* _bufferPacket)
{
    int ipLen, msgLen;
    if( _ip == NULL || _bufferPacket ==NULL)
    {
        return INVALID_MSG;
    }
    ipLen = strlen(_ip);
    _bufferPacket[0] = JOIN_GROUP_OK;
    msgLen = ipLen+1;
    _bufferPacket[1] = msgLen; 
    _bufferPacket[2] = ipLen;
    strncpy(&_bufferPacket[3], _ip, ipLen);
    return (2 + msgLen);
}

int UnPackCreateJoinAns(char *_message, char *_answer, int _msgLen)
{
    int lenIp;
    if (_message == NULL || _msgLen < 3 || _answer == NULL)
    {
        return INVALID_MSG;
    }
    if(_message[1] == 1 )
    {
        *_answer = _message[2];
        return SUCCESS;
    }
     lenIp = _message[2];
    strncpy(_answer, (const char *)&_message[3], lenIp);

    _answer[lenIp] = '\0';
    return SUCCESS;
}

int PackLeaveGroupRequest( char *_groupName, char* _userName, char *_bufferPacket)
{
    int nameLen, userLen, msgLen;
    if( _groupName == NULL|| _userName == NULL || _bufferPacket == NULL)
    {
        return INVALID_MSG;
    }
    nameLen = strlen(_groupName);
    userLen = strlen(_userName);
    _bufferPacket[0] = REQUEST_LEAVE_GROUP;
    msgLen = nameLen+userLen+2;
    _bufferPacket[1] = msgLen; 
    _bufferPacket[2] = nameLen;
    strncpy(&_bufferPacket[3], _groupName, nameLen);
    _bufferPacket[3 + nameLen] = userLen;
    strncpy(&_bufferPacket[4 + nameLen], _userName, userLen);
    return (2 + msgLen);
}

int PackLeaveAns(char _errorCode, char* _bufferPacket)
{
    if( _bufferPacket == NULL)
    {
        return INVALID_MSG;
    }
    _bufferPacket[0] = LEAVE_REP;
    _bufferPacket[1] = 1; /* len of message in bytes */
    _bufferPacket[2] = _errorCode;
    return 3;
}

int UnPackLeaveAns(char *_message, char *_errCode, int _msgLen )
{
    if (_message == NULL || _msgLen < 3 || _errCode == NULL)
    {
        return INVALID_MSG;
    }

    *_errCode = _message[2];

    return SUCCESS;
}

int PackLogOutRequest(char* _userName, char *_bufferPacket)
{
    int nameLen, msgLen;
    if( _userName == NULL || _bufferPacket == NULL)
    {
        return INVALID_MSG;
    }
    nameLen = strlen(_userName);
    _bufferPacket[0] = REQUEST_LOG_OUT;
    msgLen = nameLen+1;
    _bufferPacket[1] = msgLen; 
    _bufferPacket[2] = nameLen;
    strncpy(&_bufferPacket[3], _userName, nameLen);
    return (2 + msgLen);
}

int UnPackLogOutRequest( char* _message, int _msgLen, char* _userName)
{
    int lenName;
    if (_message == NULL || _msgLen < 3 || _userName == NULL)
    {
        return INVALID_MSG;
    }
    
    lenName = _message[2];
    strncpy(_userName, (const char *)&_message[3], lenName);

    _userName[lenName] = '\0';
    return SUCCESS;
}

int PackLogOutAns(char _errorCode, char* _bufferPacket)
{
    if( _bufferPacket == NULL)
    {
        return INVALID_MSG;
    }
    _bufferPacket[0] = LOG_OUT_REP;
    _bufferPacket[1] = 1; /* len of message in bytes */
    _bufferPacket[2] = _errorCode;
    return 3;
}

int UnPackLogOutAns(char *_message, char *_errCode, int _msgLen )
{
    if (_message == NULL || _msgLen < 3 || _errCode == NULL)
    {
        return INVALID_MSG;
    }

    *_errCode = _message[2];

    return SUCCESS;
}

int PackExitRequest(char* _userName, char *_bufferPacket)
{
    int nameLen, msgLen;
    if( _userName == NULL || _bufferPacket == NULL)
    {
        return INVALID_MSG;
    }
    nameLen = strlen(_userName);
    _bufferPacket[0] = EXIT_REQUEST;
    msgLen = nameLen+1;
    _bufferPacket[1] = msgLen; 
    _bufferPacket[2] = nameLen;
    strncpy(&_bufferPacket[3], _userName, nameLen);
    return (2 + msgLen);
}

int PackShowGroupsRequest( char* _bufferPacket)
{
    if( _bufferPacket == NULL)
    {
        return INVALID_MSG;
    }
    _bufferPacket[0] = SHOW_GROUPS_REQUEST;
    return 1;
}

int PackShowGroupsOK(char* _groups, char* _bufferPacket)
{
    int groupsLen, msgLen;
    if( _groups == NULL || _bufferPacket == NULL)
    {
        return INVALID_MSG;
    }
    groupsLen = strlen(_groups);
    _bufferPacket[0] = SHOW_GROUPS_OK;
    msgLen = groupsLen+1;
    _bufferPacket[1] = msgLen;
    _bufferPacket[2] = groupsLen;
    strncpy(&_bufferPacket[3], _groups, groupsLen);
    return (2+msgLen);
}

int PackShowGroupsFail( char _errorCode, char* _bufferPacket)
{
    if( _bufferPacket == NULL)
    {
        return INVALID_MSG;
    }
    _bufferPacket[0] = SHOW_GROUPS_FAIL;
    _bufferPacket[1] = 1;  
    _bufferPacket[2] = _errorCode;
    return 3;
}

int UnPackShowGroupsAns(char *_message, char *_answer, int _msgLen)
{
    int groupsLen;
    if (_message == NULL || _msgLen < 3 || _answer == NULL)
    {
        return INVALID_MSG;
    }
    if(_message[1] == 1 )
    {
        *_answer = _message[2];
        return SUCCESS;
    }
    groupsLen = _message[2];
    strncpy(_answer, (const char *)&_message[3], groupsLen);
    _answer[groupsLen] = '\0';
    return SUCCESS;
}

int getTag(char *_msg)
{
    if (_msg == NULL)
    {
        return TAG_FAIL;
    }

    return _msg[0];
}