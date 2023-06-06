#include <stdio.h>
#include <string.h>
#define AC_BLACK "\x1b[30m"
#define AC_RED "\x1b[31m"
#define AC_GREEN "\x1b[32m"
#define AC_YELLOW "\x1b[33m"
#define AC_BLUE "\x1b[34m"
#define AC_MAGENTA "\x1b[35m"
#define AC_CYAN "\x1b[36m"
#define AC_WHITE "\x1b[37m"
#define AC_NORMAL "\x1b[m"

void FirstMenu()
{
    printf(AC_WHITE);
    printf("\n***********************\n");
    printf(AC_YELLOW);
    printf("Welcome to our chat!!\nPlease enter a choice\n1.Sign up\n2.Login\n3.Close the program\nChoice: ");
}

void EnterUserName()
{
    printf(AC_WHITE);
    printf("\n***********************\n");
    printf(AC_YELLOW);
    printf("Please enter UserName : ");
}

void EnterPass()
{
    printf(AC_YELLOW);
    printf("Please enter password: ");
}

void RegSuccess()
{
    printf(AC_WHITE);
    printf("\n***********************\n");
    printf(AC_GREEN);
    printf("Signed up Successfully\n ");
}

void RegFailUser()
{
    printf(AC_WHITE);
    printf("\n***********************\n");
    printf(AC_RED);
    printf("Invalid User Name\n ");
}

void RegFailPass()
{
    printf(AC_WHITE);
    printf("\n***********************\n");
    printf(AC_RED);
    printf("Invalid Password\n ");
}

void RegFail()
{
    printf(AC_WHITE);
    printf("\n***********************\n");
    printf(AC_RED);
    printf("Registration fail\n");
}

void LoginSuccess()
{
    printf(AC_WHITE);
    printf("\n***********************\n");
    printf(AC_GREEN);
    printf("Login Successfully\n");
}

void LoginFail()
{
    printf(AC_WHITE);
    printf("\n***********************\n");
    printf(AC_RED);
    printf("Login fail\n");
}

void GroupMenu()
{
    printf(AC_WHITE);
    printf("\n***********************\n");
    printf(AC_YELLOW);
    printf("Please enter a choice:\n1. Join group\n2. Leave group\n3. Create group\n4.Logout\n");
}

void CloseProg()
{
    printf(AC_WHITE);
    printf("\n***********************\n");
    printf(AC_RED);
    printf("close\n ");
}

void EnterGroupName()
{
    printf(AC_WHITE);
    printf("\n***********************\n");
    printf(AC_YELLOW);
    printf("Please enter group name (no more than one word):\n ");
}

void CreatGroupFail()
{
    printf(AC_WHITE);
    printf("\n***********************\n");
    printf(AC_RED);
    printf("Create group failed\n");
}

void CreateGroupSuccess()
{
    printf(AC_WHITE);
    printf("\n***********************\n");
    printf(AC_GREEN);
    printf("Created your group successfully\n");
    printf("\nYou are in!!\n");
}

void JoinGroupFail()
{
    printf(AC_WHITE);
    printf("\n***********************\n");
    printf(AC_RED);
    printf("Join group failed\n");
}

void JoinGroupSuccess()
{
    printf(AC_WHITE);
    printf("\n***********************\n");
    printf(AC_GREEN);
    printf("Join group successfully\n");
    printf("\nYou are in!!\n");
}

void InvalidGroupName()
{
    printf(AC_WHITE);
    printf("\n***********************\n");
    printf(AC_RED);
    printf("Invalid group name\n");
}

void LeaveGroupFailed()
{
    printf(AC_WHITE);
    printf("\n***********************\n");
    printf(AC_RED);
    printf("Leave group failed\n");
}

void LeaveGroupSuccess()
{
    printf(AC_WHITE);
    printf("\n***********************\n");
    printf(AC_GREEN);
    printf("Leave group successfully\n");
}

void LogOutFailed()
{
    printf(AC_WHITE);
    printf("\n***********************\n");
    printf(AC_RED);
    printf("LogOut failed\n");
}

void LogOutSuccess()
{
    printf(AC_WHITE);
    printf("\n***********************\n");
    printf(AC_GREEN);
    printf("LogOut successfully\n");
}

void ShowGroupsFail()
{
    printf(AC_WHITE);
    printf("\n***********************\n");
    printf(AC_RED);
    printf("No groups to show\n");
}

void UserAlreadyExist()
{
    printf(AC_WHITE);
    printf("\n***********************\n");
    printf(AC_RED);
    printf("User is already registered\n");
}

void PrintShowGroupsOK(char *_buffer)
{
    int i = 1;
    char *token = strtok(_buffer, " ");
    while (token != NULL)
    {
        printf("%d. %s\n", i, token);
        token = strtok(NULL, " ");
        i++;
    }
}
