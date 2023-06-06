#include <stdlib.h>
#include "ListInternal.h"
#include "GenList.h"
#include "list_itr.h"

ListItr ListItrBegin(const List* _list)
{
    if(_list == NULL)
    {
        return NULL;
    }
    return (void*)_list->m_head.m_next;
}


ListItr ListItrEnd(const List* _list)
{
    if(_list == NULL)
    {
        return NULL;
    }
    return (void*)_list->m_tail.m_next;
}


int ListItrEquals(const ListItr _a, const ListItr _b)
{

    return (_a == _b);
}


ListItr ListItrNext(ListItr _itr)
{
    Node *temp;
    if(_itr == NULL)
    {
        return NULL;
    }
    temp=(Node*)_itr;
    return (void*)temp->m_next;
}


ListItr ListItrPrev(ListItr _itr)
{
    Node *temp;
    if(_itr == NULL)
    {
        return NULL;
    }
    temp=(Node*)_itr;
    return (void*)temp->m_prev;
}


void* ListItrGet(ListItr _itr)
{
    Node *temp;
    if(_itr == NULL)
    {
        return NULL;
    }
    temp=(Node*)_itr;
    return temp->m_data;
}


void* ListItrSet(ListItr _itr, void* _element)
{
    Node *temp;
    void *rtrnData;
    if(_itr == NULL || _element == NULL)
    {
        return NULL;
    }
    temp=(Node*)_itr;
    if(temp->m_next== temp || temp->m_prev== temp)
    {
        return NULL;
    }
    rtrnData=temp->m_data;
    temp->m_data=_element;
    return rtrnData;
}


ListItr ListItrInsertBefore(ListItr _itr, void* _element)
{
    Node *temp, *newNode;
    if(_itr == NULL || _element == NULL)
    {
        return NULL;
    }
    if( (newNode = (Node*)malloc( sizeof(Node))) == NULL)
	{
		return NULL;
	}
    temp=(Node*)_itr;
    newNode->m_data=_element;
    InsertNode(temp,newNode);
    return (void*)newNode;
}

void* ListItrRemove(ListItr _itr)
{
    void *data;
    Node *temp;
    if(_itr== NULL)
	{
		return NULL;
	}
    temp=(Node*)_itr;
    if(temp->m_next== temp || temp->m_prev== temp)
    {
        return NULL;
    }
	data=temp->m_data;
	RemoveNode(temp);
	return data;
}