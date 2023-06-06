#include <stdlib.h>
#include <stdio.h>
#include "ListInternal.h"
#include "list_itr.h"
#include "list_functions.h"



typedef int (*FuncInter)(void * _element, void* _context);

typedef struct Info
{
	void* m_context;
    FuncInter m_func;
    size_t m_count;
    ListItr m_stop;
    int m_type;  
} Info;

static void LoopForEach(ListItr _begin, ListItr _end, Info *_info);

ListItr ListItrFindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
    Info myInfo;
    ListItr stop;
    if(_begin== NULL  || _end== NULL  || _predicate == NULL)
	{
		return NULL;
	}
    myInfo.m_context=_context;
    myInfo.m_func=_predicate;
    myInfo.m_count=0;
    myInfo.m_stop=&stop;
    myInfo.m_type=FIND;
    LoopForEach(_begin, _end, &myInfo);
    return myInfo.m_stop;
}

size_t ListItrCountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
    Info myInfo;
    if(_begin== NULL  || _end== NULL  || _predicate == NULL)
	{
		return 0;
	}
    myInfo.m_context=_context;
    myInfo.m_func=_predicate;
    myInfo.m_count=0;
    myInfo.m_stop=NULL;
    myInfo.m_type=COUNT_IF;
    LoopForEach(_begin, _end, &myInfo);
    return myInfo.m_count;

}

ListItr ListItrForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context)
{
    Info myInfo;
    ListItr stop;
    if(_begin== NULL  || _end== NULL  || _action == NULL)
	{
		return NULL;
	}
    myInfo.m_context=_context;
    myInfo.m_func=_action;
    myInfo.m_count=0;
    myInfo.m_stop=&stop;
    myInfo.m_type=EACH;
    LoopForEach(_begin, _end, &myInfo);
    return myInfo.m_stop;
}

static void LoopForEach(ListItr _begin, ListItr _end, Info *_info)
{
    Node *newNode,*newNode1;
    int stat;
	newNode=(Node*)_begin;  
	while(newNode != (Node*)_end)
	{
		newNode1=newNode->m_next;
        stat=(*_info).m_func(newNode, _info->m_context);
        if(stat != 0  && _info->m_type == COUNT_IF)
        {
            _info->m_count++;
        }
        if(stat != 0  && _info->m_type == FIND)
        {
            break;
        }
        if(stat == 0  && _info->m_type == EACH)
        {
            break;
        }
		newNode=newNode1;
	}
    _info->m_stop=(void*)newNode;
}