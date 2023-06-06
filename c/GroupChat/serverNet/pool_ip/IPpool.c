/**********************************************************************************
                                include && define
**********************************************************************************/
#include <stdio.h>
#include <string.h>
#include "/home/guy/prog/GENDS/GenQueue.h"
#include "IPpool.h"
/* multicast ip addr (class d) 224.0.0.0 <=> 239.255.255.255
   pool ip: 224.0.0.0 <=> 224.0.0.100
   server give the same port for all groups
   when group closed the ip returns to pool ip*/

/* THE MAX LEN OF LAST CELL
   MAX VAL  => 100 (3 chars)  */
#define MAX_LEN 3
/* THE MAX LEN FULL IP ADR
   224.0.0.100 11 (11 chars) */
#define MAX_IP_LEN 12
#define QUEUE_SIZE 100
#define IP_PTR "224.0.0."

/**********************************************************************************
                                IpPool struct
**********************************************************************************/
struct IpPool
{
    Queue *m_ip;
};

/**********************************************************************************
                     Declaration of static Auxiliary Functions
**********************************************************************************/
static IpPoolRes InitQueue(Queue *_ipPool);
static void FreeQueueElement(void *_ip);

/**********************************************************************************
                                api Functions
**********************************************************************************/
IpPool *IpPoolCreate()
{
    IpPool *ip;

    if ((ip = (IpPool *)malloc(sizeof(IpPool))) == NULL)
    {
        return NULL;
    }

    if ((ip->m_ip = QueueCreate(QUEUE_SIZE)) == NULL)
    {
        free(ip);
        return NULL;
    }

    if ((InitQueue(ip->m_ip)) == INIT_QUE_FAIL)
    {
        DestroyIpQue(ip);
        printf("InitQueue failed\n");
        return NULL;
    }

    return ip;
}

void DestroyIpQue(IpPool *_ipQue)
{
    QueueDestroy(&(_ipQue->m_ip), FreeQueueElement);
    free(_ipQue);
    _ipQue = NULL;
}

/*  queInsert when group closed
    QueueRemove when group needs ip*/
IpPoolRes GetIp(IpPool *_ipQue, char *_bufferIp)
{
    void *retIp;
    QueueResult res;
    res = QueueRemove(_ipQue->m_ip, &retIp);

    if (res != QUEUE_SUCCESS)
    {
        return REMOVE_IP_FAIL;
    }
    strcpy(_bufferIp, (char *)retIp);
    return REMOVE_IP_SUCCESS;
}

IpPoolRes InsertIp(IpPool *_ipQue, char *_ipToInsert)
{
    if ((QueueInsert(_ipQue->m_ip, _ipToInsert) != QUEUE_SUCCESS))
    {
        return ADD_IP_FAIL;
    }

    return ADD_IP_SUCCESS;
}

/**********************************************************************************
                        static Auxiliary Functions
**********************************************************************************/
static IpPoolRes InitQueue(Queue *_ipPool)
{
    int ipCounter = 1;
    char latCellIp[MAX_LEN + 1];
    char *ip;
    int i;

    for (i = 0; i < QUEUE_SIZE; i++)
    {
        ip = (char *)malloc(MAX_IP_LEN);
        if (ip == NULL)
        {
            return INIT_QUE_FAIL;
        }
        else
        {
            strcpy(ip, IP_PTR);
            sprintf(latCellIp, "%d", ipCounter);
            strcat(ip, latCellIp);

            ipCounter++;

            /* check something?*/
            if ((QueueInsert(_ipPool, (void *)ip)) != QUEUE_SUCCESS)
            {
                return INIT_QUE_FAIL;
            }
        }
    }

    return INIT_QUE_SUCCESS;
}

static void FreeQueueElement(void *_ip)
{
    free(_ip);
}
