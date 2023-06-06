#include <stdio.h>
#include <stdlib.h> /*realloc, mealloc*/
#include "GenList.h"
#include "list_itr.h"
#include "ListInternal.h"



List* ListCreate(void)
{
	List *dmnList;
	if((dmnList =(List*)malloc(sizeof(struct List))) == NULL)
	{
		return NULL;
	}
	dmnList->m_head.m_next= &dmnList->m_tail;
	dmnList->m_head.m_prev= &dmnList->m_head;
	dmnList->m_tail.m_next= &dmnList->m_tail;
	dmnList->m_tail.m_prev= &dmnList->m_head;
	return dmnList;
}

void ListDestroy(List** _pList, void (*_elementDestroy)(void* _item))
{
    Node *newNode,*newNode1;
	if(_pList== NULL  || *_pList== NULL)
	{
		return;
	}
	
	newNode=(*_pList)->m_head.m_next;
	while(newNode != &(*_pList)->m_tail)
	{
		newNode1=newNode->m_next;
        if(_elementDestroy != NULL)
        {
            _elementDestroy( newNode1->m_data );
        }
		free(newNode);
		newNode=newNode1;
	}
	free(*_pList);
    *_pList=NULL;
}


ListResult ListPushHead(List* _list, void* _item)
{
    Node *newNode;
	if(_list== NULL)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
    if(_item== NULL)
	{
		return LIST_UNINITIALIZED_POINTER_ERROR;
	}
	if( (newNode = (Node*)malloc( sizeof(Node))) == NULL)
	{
		return LIST_ALLOCATION_ERROR;
	}
	newNode->m_data=_item;
	InsertNode(_list->m_head.m_next,newNode);
	return LIST_SUCCESS;
}

ListResult ListPushTail(List* _list, void* _item)
{
    Node *newNode;
	if(_list== NULL)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
    if(_item== NULL)
	{
		return LIST_UNINITIALIZED_POINTER_ERROR;
	}
	if( (newNode = (Node*)malloc( sizeof(Node))) == NULL)
	{
		return LIST_ALLOCATION_ERROR;
	}
	newNode->m_data=_item;
	InsertNode(&_list->m_tail,newNode);
	return LIST_SUCCESS;
}


ListResult ListPopHead(List* _list, void** _pItem)
{
    if(_list== NULL)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
    if(_pItem== NULL)
	{
		return LIST_UNINITIALIZED_POINTER_ERROR;
	}
	if(_list->m_head.m_next == &_list->m_tail)
	{
		return LIST_IS_EMPTY_ERROR;
	}
	*_pItem=_list->m_head.m_next->m_data;
	RemoveNode(_list->m_head.m_next);
	return LIST_SUCCESS;	
}


ListResult ListPopTail(List* _list, void** _pItem)
{
    if(_list== NULL)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
    if(_pItem== NULL)
	{
		return LIST_UNINITIALIZED_POINTER_ERROR;
	}
	if(_list->m_head.m_next == &_list->m_tail)
	{
		return LIST_IS_EMPTY_ERROR;
	}
	*_pItem=_list->m_tail.m_prev->m_data;
	RemoveNode(_list->m_tail.m_prev);
	return LIST_SUCCESS;
}

size_t ListSize(const List* _list)
{
    Node *newNode;
	int count=0;
    if(_list== NULL)
	{
		return 0;
	}
	newNode=_list->m_head.m_next;
	while(newNode != &_list->m_tail)
	{
		newNode=newNode->m_next;
		count++;
	}
	return count;
}

void* GetM_tailData(List* _list)
{
	return _list->m_tail.m_prev->m_data;
}

void* GetM_headData(List* _list)
{
	return _list->m_head.m_next->m_data;
}

void InsertNode( Node *_befor, Node *_insert)
{
	_insert-> m_prev = _befor->m_prev;
	_insert-> m_next = _befor ;
	if(_befor-> m_prev != NULL)
	{
		_befor-> m_prev->m_next = _insert;
	}
	_befor->m_prev = _insert;
}

void RemoveNode( Node *_remove)
{
	_remove->m_next-> m_prev=_remove-> m_prev;
	_remove-> m_prev->m_next = _remove->m_next;
	free(_remove);
	_remove=NULL;
}