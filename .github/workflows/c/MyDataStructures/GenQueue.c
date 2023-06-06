#include <stdio.h>
#include <stdlib.h> /*mealloc*/
#include "GenQueue.h"


struct Queue
{
	void** m_que;
	size_t m_size;
	size_t m_head; /* Index of head in m_que. */
	size_t m_tail; /* Index of tail in m_que. */
	size_t m_nItems;
	int m_magicNumber;
};

Queue* QueueCreate (size_t _size)
{
	Queue *dmnQueue;
	if(_size == 0)
	{
		return NULL;
	}
	if((dmnQueue =(Queue*)malloc(sizeof(struct Queue))) == NULL)
	{
		return NULL;
	}
	if( (dmnQueue->m_que = (void**)malloc( _size*sizeof(void*))) == NULL)
	{
		free(dmnQueue);
		return NULL;
	}
	dmnQueue->m_size=_size;
	dmnQueue->m_head=0;
	dmnQueue->m_tail=0;
	dmnQueue->m_nItems=0;
	return dmnQueue;
}

void QueueDestroy(Queue** _queue, DestroyItem _itemDestroy)
{
    size_t i=0;
    if(_queue != NULL || *_queue != NULL )
	{
        if(_itemDestroy != NULL)
        {
            for (i=0; i< (*_queue)->m_nItems; i++)
            {
                _itemDestroy((*_queue)->m_que[i]);
            }
        }
		free((*_queue)->m_que);
		free(*_queue);
		*(_queue)=NULL;
	}
}


QueueResult QueueInsert(Queue* _queue,void* _item)
{
	if(_queue ==NULL)
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}
	if(_item == NULL)
	{
		return QUEUE_DATA_UNINITIALIZED_ERROR;
	}
	if(_queue->m_nItems==_queue->m_size)
	{
		return QUEUE_OVERFLOW_ERROR;
	}
	_queue->m_que[_queue->m_tail]= _item;
	_queue->m_tail=(_queue->m_tail+1)%_queue->m_size;
	_queue->m_nItems++;
	return QUEUE_SUCCESS;
}


QueueResult QueueRemove(Queue* _queue,void** _item)
{
    if(_queue ==NULL )
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}
    if(_item ==NULL)
	{
		return QUEUE_DATA_UNINITIALIZED_ERROR;
	}
	if(_queue->m_nItems == 0)
	{
		return QUEUE_UNDERFLOW_ERROR;
	}
	_queue->m_nItems--;
	*_item = _queue->m_que[_queue->m_head];
	_queue->m_head = (_queue->m_head + 1) % _queue->m_size;
	return QUEUE_SUCCESS;
}


size_t QueueIsEmpty(Queue* _queue)
{
    if(_queue == NULL)
	{
		return 0 ;
	}
	return _queue->m_nItems;
}

size_t QueueForEach(Queue* _queue, ActionFunction _action, void* _context)
{
    size_t i, locHead=_queue->m_head;
	if(_queue == NULL)
	{
		return -1;
	}
	for(i=0; i<_queue->m_nItems; i++)
	{
		_action(_queue->m_que[locHead],_context);
		locHead=(locHead + 1) % _queue->m_size;
	}
    return i;
}