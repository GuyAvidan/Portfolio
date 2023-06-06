#include <stdio.h>
#include "Client_manager.h"
#include "../protocol/protocol.h"

int main ()
{
    ClientManager *myClientMan;
    ClientManErr ressult = CLIENT_MAN_SUCCESS;
    myClientMan=CreateClientManager(SER_IP,PORT_NUMBER);
    if(myClientMan == NULL)
    {
        printf("error\n");
        return 0;
    }
    while (ressult == CLIENT_MAN_SUCCESS)
    {
        ressult=RunClientManager(myClientMan);
    }
    if(ressult != PROGRAM_CLOSED)
    {
        printf("Out run error: %d\n",ressult);
    }
    DestroyClientManager(&myClientMan);
    return 0;
}
