#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include "GenList.h"
#include "ListInternal.h" 
#include "list_itr.h"
#include "list_functions.h"
/*gcc -ansi -pedantic -g MainGroupWin.c GenList.c list_itr.c list_functions.c -o Main.out*/

typedef struct GroupPID
{
    char m_IP[14];
    int m_port;
    char m_ClientName[24];
    char m_groupName[24];
    int m_listenPID;
    int m_SenderPID;
}GroupPID;

int OpenGroupWin(GroupPID *_groupPID)
{
    char command1[100],command2[100],add[100], sPort[20];
    FILE *ListenPID_FILE;
    FILE *SenderPID_FILE;
    snprintf(sPort,100, "%d" ,_groupPID->m_port);
    strcpy( command1, "gnome-terminal --geometry=50x20+550+10 --title=Group:_" );
    strcat( command1, _groupPID->m_groupName);
    strcat( command1, " -- ./Listen.out  ");
    strcpy( add, _groupPID->m_IP);
    strcat( add, " ");
    strcat( add, sPort);
    strcat( add, " ");
    strcat( add, _groupPID->m_ClientName);
    strcat( command1, add);
    system(command1);
    strcpy( command2, "gnome-terminal --geometry=50x20+1050+500 --title=User:_" );
    strcat( command2, _groupPID->m_groupName);
    strcat( command2, " -- ./Sender.out ");
    strcat( command2, add);
    system(command2);
    sleep(1);
    ListenPID_FILE = fopen("Listen.txt", "r");
    SenderPID_FILE = fopen("Sender.txt", "r");
    fscanf(ListenPID_FILE, "%d", &_groupPID->m_listenPID);
    fscanf(SenderPID_FILE, "%d", &_groupPID->m_SenderPID);
    fclose(ListenPID_FILE);
    fclose(SenderPID_FILE);
}

static int CloseGroupWin(GroupPID *_groupPID)
{
    if(kill(_groupPID->m_listenPID,SIGKILL) != 0)
    {
        printf("Failed");
        return 1;
    }
    if(kill(_groupPID->m_SenderPID,SIGKILL) != 0)
    {
        printf("Failed");
        return 1;
    }
    return 0;
}

GroupPID* CreateGroupPID(char* _clientName,char* _groupName )
{
    GroupPID *dnmGroupPID= NULL;
    if ((dnmGroupPID = (GroupPID *)malloc(sizeof(GroupPID))) == NULL)
    {
        return NULL;
    }
    strcpy(dnmGroupPID->m_ClientName, _clientName);
    strcpy(dnmGroupPID->m_groupName, _groupName);
    return dnmGroupPID;
}

static int FindGroupName(void * _element, void* _context)
{
    Node *new;
	new=(Node*)_element;
	if(strcmp(((GroupPID*)(new->m_data))->m_groupName, (char*)_context)== 0)
	{
        return 1;
	} else
	{
		return 0;
	}
}

static ListItr* FindGroupPIDByName(char* _groupName, List *listGID)
{
    
    ListItr itr;
    itr=ListItrFindFirst(ListItrBegin(listGID), ListItrEnd(listGID), FindGroupName, (void*) _groupName);
    if(itr == ListItrEnd(listGID))
    {
        return NULL;
    }
    return itr;
}

int main()
{
    char buffer[100],buffer2[100];
    int doKill;
    List *listGID;
    void* GGG;
    ListItr itr;
    GroupPID *dnmGroupPID= NULL;
    printf("Enter user name:\n");
    scanf("%s", buffer);
    printf("Enter group name:\n");
    scanf("%s", buffer2);
    dnmGroupPID=CreateGroupPID( buffer,buffer2);
    listGID=ListCreate();
    ListPushHead( listGID, (void*)dnmGroupPID);
    strcpy(dnmGroupPID->m_IP ,"224.0.0.2");
    dnmGroupPID->m_port = 1200;
    OpenGroupWin(dnmGroupPID);
    itr=ListItrFindFirst(ListItrBegin(listGID), ListItrEnd(listGID), FindGroupName, (void*) dnmGroupPID->m_groupName);
    if(itr == ListItrEnd(listGID))
    {
        printf("not\n");
    }
    printf("Do Kill:\n");
    scanf("%d", &doKill);
    CloseGroupWin((GroupPID*)ListItrGet(itr));
}