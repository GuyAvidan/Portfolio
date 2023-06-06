#include <stdio.h>
#include "Client_manager.h"
#include "../protocol/protocol.h"

int main ()
{
    ClientManager *myClientMan;
    ProtocolErr ressult;
    myClientMan=CreateClientManager(SER_IP,PORT_NUMBER);
    if(myClientMan == NULL)
    {
    		printf("error\n");
    }
    
    ressult=RunClientManager(myClientMan);
    printf("Out run error: %d\n",ressult);
    DestroyClientManager(&myClientMan);
    return 0;
}
