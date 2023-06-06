#include <stdio.h>
#include <stdlib.h> /*calloc, malloc*/
#include "HashMap.h"
#include "GenList.h"
#include "list_functions.h"
#include "list_itr.h"
#define LIST_SIZE 10
#define TRUE 1
#define FALSE 0

typedef struct KeyVal KeyVal;

struct HashMap
{
    List** m_list;
    HashFunction m_hashFunction;
    EqualityFunction m_equalityFunction;
    size_t m_hashSize; /*original size given by the client*/
    size_t m_capacity; /*real hash size */
    size_t m_numOfItems; /*number of occupied places in the table*/
    size_t m_counterOfInsertions; /*total amount of insertions into the table*/
};

struct KeyVal
{
    void* m_key;
    void* m_value;
};

static int IsPrime(size_t _n);
static size_t NextPrime(size_t _n);
static KeyVal* CreateKeyVal(const void* _key,const void* _value);
static int IsFound(const HashMap* _map, const void* _key, size_t _index, ListItr *_finding);
static Map_Result InsertToLisr(const HashMap* _map ,size_t _index, const void* _key,const void* _value);



HashMap* HashMap_Create(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
    HashMap *dmnHash;
    size_t i;
    if(_capacity < MIN_HASH_SIZE || _hashFunc == NULL  ||  _keysEqualFunc == NULL)
    {
        return NULL;
    }
    if((dmnHash =(HashMap*)malloc(sizeof(HashMap))) == NULL)
	{
		return NULL;
	}
    dmnHash->m_capacity=NextPrime(_capacity);
	if( (dmnHash->m_list = (List**)malloc( dmnHash->m_capacity*sizeof(List*))) == NULL)
	{
		free(dmnHash);
		return NULL;
	}
    for(i=0; i<dmnHash->m_capacity;i++)
    {
        dmnHash->m_list[i]=NULL;
    }
    dmnHash->m_hashFunction=_hashFunc;
    dmnHash->m_equalityFunction=_keysEqualFunc;
    dmnHash->m_hashSize=_capacity;
    dmnHash->m_numOfItems=0;
    dmnHash->m_counterOfInsertions=0;
    return dmnHash;
}


void HashMap_Destroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
    size_t i;
    ListItr findingIn, start, end;
    KeyVal* data;
    if(_map ==NULL || *_map ==NULL)
	{
		return;
	}
    for(i=0 ; i< (*_map)->m_capacity; i++)
    {
        if ((*_map)->m_list[i] != NULL)
        {
            start=ListItrBegin((*_map)->m_list[i]);
            end=ListItrEnd((*_map)->m_list[i]);
            findingIn=start;
            while (!ListItrEquals(findingIn,end))
            {
                data=(KeyVal*)ListItrGet(findingIn);
                if(_keyDestroy != NULL)
                {
                    _keyDestroy(data->m_key);
                }
                if(_valDestroy !=NULL)
                {
                    _valDestroy(data->m_value);
                }
                free(data);
                findingIn=ListItrNext(findingIn);
            }   
            ListDestroy(&((*_map)->m_list[i]), NULL);
        }
    }
    free((*_map)->m_list);
    free(*_map);
    *_map=NULL;
}


Map_Result HashMap_Insert(HashMap* _map, const void* _key, const void* _value)
{
    size_t index;
    Map_Result stat;
    ListItr findItr;
    if(_map ==NULL  || _value == NULL)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
    index=(_map->m_hashFunction(_key))%_map->m_capacity;
    if (_map->m_list[index] != NULL)
    {
        if(IsFound(_map,_key,index, &findItr) == TRUE)
        {
            return MAP_KEY_DUPLICATE_ERROR;
        }
    }
    stat=InsertToLisr(_map, index,_key, _value);
    if(stat != MAP_SUCCESS)
    {
        return stat;
    }
    _map->m_counterOfInsertions++;
    _map->m_numOfItems++;
	return stat;
}


Map_Result HashMap_Remove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
    size_t index;
    KeyVal *deleted;
    ListItr firstItr;
    if(_map ==NULL  || _searchKey == NULL || _pKey == NULL  || _pValue==NULL)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
    index=(_map->m_hashFunction(_searchKey))%_map->m_capacity;
    if (_map->m_list[index] != NULL)
    {
        if(IsFound(_map,_searchKey,index, &firstItr) == TRUE)
        {
            deleted = (KeyVal*)ListItrRemove(firstItr);
            *_pKey=deleted->m_key;
            *_pValue=deleted->m_value;
            return MAP_SUCCESS;
        }
    }
    return MAP_KEY_NOT_FOUND_ERROR;
}


Map_Result HashMap_Find(const HashMap* _map, const void* _key, void** _pValue)
{
    size_t index;
    KeyVal *deleted;
    ListItr firstItr;
    if(_map ==NULL  || _key == NULL  || _pValue==NULL)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
    index=(_map->m_hashFunction(_key))%_map->m_capacity;
    if (_map->m_list[index] != NULL)
    {
        if(IsFound(_map,_key,index, &firstItr) == TRUE)
        {
            
            deleted= (KeyVal*)ListItrGet(firstItr);
            *_pValue=deleted->m_value;
            return MAP_SUCCESS;
        }
    }
    return MAP_KEY_NOT_FOUND_ERROR;
}


size_t HashMap_Size(const HashMap* _map)
{
    if(_map ==NULL)
	{
		return 0;
	}
    return _map->m_hashSize;
}

size_t HashMap_ForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
    size_t i, count=0;
    ListItr findingIn, start, end;
    KeyVal* data;
    if(_map ==NULL || _action == NULL)
	{
		return 0;
	}
    for(i=0 ; i< _map->m_capacity; i++)
    {
        if (_map->m_list[i] != NULL)
        {
            
            start=ListItrBegin(_map->m_list[i]);
            end=ListItrEnd(_map->m_list[i]);
            findingIn=start;
            while (!ListItrEquals(findingIn,end))
            {
                data=(KeyVal*)ListItrGet(findingIn);
                if(!_action(data->m_key,data->m_value, _context ))
                {
                    break;
                }
                count++;
                findingIn=ListItrNext(findingIn);
                
            }
            
        }
    }
    return count;
}

static size_t NextPrime(size_t _n)
{
    size_t i;
    int found=0;
    for(i=_n; found == 0; i++)
    {
        found=IsPrime(i);
    }
    return i;
}

static int IsPrime(size_t _n)
{
    size_t i;
    if (_n == 1)
    {
        return 1;
    }
    for (i = 2; i <= _n / 2; ++i) 
    {
        if (_n % i == 0) 
        {
            return 1;
        }
    }
    return 0;
}

static int IsFound(const HashMap* _map, const void* _key, size_t _index, ListItr *_finding)
{
    ListItr findingIn, start, end;
    void* data;
    start=ListItrBegin(_map->m_list[_index]);
    end=ListItrEnd(_map->m_list[_index]);
    findingIn=start;
    while (!ListItrEquals(findingIn,end))
    {
        data=ListItrGet(findingIn);
        if(_map->m_equalityFunction(((KeyVal*)data)->m_key, (void*)_key)==TRUE)
        {
            *_finding=findingIn;
            return TRUE;
        };
        findingIn=ListItrNext(findingIn);
    }
    return FALSE;
}

static Map_Result InsertToLisr(const HashMap* _map ,size_t _index, const void* _key,const void* _value)
{
    List *newList;
    KeyVal *newKeyVal;
    ListItr *newListItr, *end;
    if(_map->m_list[_index] == NULL)
    {
        if((newList=ListCreate()) == NULL)
        {
            return MAP_ALLOCATION_ERROR;
        }
        _map->m_list[_index]=newList;
    }
    end=ListItrEnd(_map->m_list[_index]);
    newKeyVal=CreateKeyVal(_key,_value);
    if(newKeyVal == NULL)
    {
        return MAP_ALLOCATION_ERROR;
    }
    newListItr=ListItrInsertBefore(end,newKeyVal);
    if(newListItr == NULL)
    {
        return MAP_ALLOCATION_ERROR;
    }
    return MAP_SUCCESS;
}

static KeyVal* CreateKeyVal(const void* _key,const void* _value)
{
    KeyVal *new;
    if((new =(KeyVal*)malloc(sizeof(KeyVal))) == NULL)
	{
		return NULL;
	}
    new->m_key=(void*)_key;
    new->m_value=(void*)_value;
    return new;
}
