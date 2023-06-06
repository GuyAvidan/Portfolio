
#ifndef __POOL_IP_H__
#define __POOL_IP_H__

typedef struct IpPool IpPool;

typedef enum IpPoolRes
{
    IP_SUCESS,
    REMOVE_IP_FAIL,
    ADD_IP_SUCCESS,
    ADD_IP_FAIL,
    INIT_QUE_SUCCESS,
    INIT_QUE_FAIL,
    REMOVE_IP_SUCCESS = 6
} IpPoolRes;

/**
 * @brief   Creates ip pool.
 * @details create a queue of multicast ip addr (class d)
 *          Class D IP Address Range
 *          Range: 224.0.0.0 to 239.255.255.255
 *          The queue contains maximum 100 IP addresses
 *          queue IP Address Range
 *          Range: 224.0.0.0 <=> 224.0.0.100
 * @return NULL or pointer to ipPool
 * @retval pointer to ipPool struct - on success
 * @retval NULL on failure
 */
IpPool *IpPoolCreate();

/**
 * @brief Unallocated a previously created queue and & Frees ip pool struct.
 * @param[in] _ipQue - pointer to the ipPool struct
 * @return x
 */
void DestroyIpQue(IpPool *_ipQue);

/**
 * @brief   the func insert a ip to the queue
 * @param[in] _ipQue - pointer to the ipPool struct
 * @param[in] _ipToInsert - ip to insert
 * @return IpPoolRes
 * @retval ADD_IP_FAIL
 * @retval ADD_IP_SUCCESS
 */
IpPoolRes InsertIp(IpPool *_ipQue, char *_ipToInsert);

/**
 * @brief      the func removes ip from the queue
 * @param[in] _ipQue - pointer to the ipPool struct
 * @param[in] _bufferIp - ip to delete
 * @return IpPoolRes
 * @retval REMOVE_IP_FAIL if QueueRemove failed
 * @retval REMOVE_IP_SUCCESS
 */
IpPoolRes GetIp(IpPool *_ipQue, char *_bufferIp);

#endif /* __POOL_IP_H__ */