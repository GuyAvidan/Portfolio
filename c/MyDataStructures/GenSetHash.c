#include <stdio.h>
#include <stdlib.h> /*calloc, malloc*/
#include "GenSetHash.h"
#define MULTI 1.3
#define TRUE 1
#define FALSE 0


struct Hash
{
    void** m_data;
    char* m_state;
    size_t (*m_hashFunction)(void* _data);
    int (*m_equalityFunction)(void* _firstData, void* _secondData);
    size_t m_hashSize; /*original size given by the client*/
    size_t m_capacity; /*real hash size */
    size_t m_numOfItems; /*number of occupied places in the table*/
    size_t m_maxOfRehashOperations; /*maximum amount of rehash operations
    which have been done over one insertion*/
    size_t m_counterOfInsertions; /*total amount of insertions into the table*/
    size_t m_allRehashOperations; /*all rehash operations mutual counter*/
};

static int IsPrime(size_t _n);
static size_t NextPrime(size_t _n);
static int IsFound(const Hash* _hash, void* _key, size_t* _index);


Hash* HashCreate(size_t _size, size_t (*_hashFunction)(void*), int(*_equalityFunction)(void*, void*))
{
    Hash *dmnHash;
    if(_size < 1 || _hashFunction == NULL  ||  _equalityFunction == NULL)
    {
        return NULL;
    }
    if((dmnHash =(Hash*)malloc(sizeof(Hash))) == NULL)
	{
		return NULL;
	}
    dmnHash->m_capacity=NextPrime((size_t)_size*MULTI);
	if( (dmnHash->m_data = (void**)malloc( dmnHash->m_capacity*sizeof(void*))) == NULL)
	{
		free(dmnHash);
		return NULL;
	}
    if( (dmnHash->m_state = (char*)calloc( dmnHash->m_capacity,sizeof(char))) == NULL)
	{
		free(dmnHash->m_data);
        free(dmnHash);
		return NULL;
	}
    dmnHash->m_hashFunction=_hashFunction;
    dmnHash->m_equalityFunction=_equalityFunction;
    dmnHash->m_hashSize=_size;
    dmnHash->m_numOfItems=0;
    dmnHash->m_maxOfRehashOperations=0;
    dmnHash->m_counterOfInsertions=0;
    dmnHash->m_allRehashOperations=0;
    return dmnHash;
}


void HashDestroy(Hash** _hash, void (*_keyDestroy)(void* _data))
{
    size_t i;
    if(_hash == NULL || *_hash == NULL )
	{
        return;
	}
    if(_keyDestroy != NULL)
    {
        for (i=0; i< (*_hash)->m_numOfItems; i++)
        {
            if((*_hash)->m_state[i]==2)
            {
                _keyDestroy((*_hash)->m_data[i]);
            }
        }
    }
    free((*_hash)->m_data);
    free((*_hash)->m_state);
    free(*_hash);
    *_hash=NULL;
}


HashSet_Result HashInsert(Hash* _hash, void* _data)
{
	size_t index, countRehash=0;
    if(_hash ==NULL  || _data == NULL)
	{
		return SET_UNINITIALIZED;
	}
	if(_hash->m_numOfItems ==_hash->m_hashSize)
	{
		return SET_OVERFLOW;
	}
    if(IsFound(_hash,_data,&index) == TRUE)
    {
        return SET_KEY_DUPLICATE;
    }
    index=(_hash->m_hashFunction(_data))%_hash->m_capacity;
    while (_hash->m_state[index] == 2)
    {
        index=(index+1)%_hash->m_capacity;
        countRehash++;
    }
    if(_hash->m_maxOfRehashOperations < countRehash)
    {
        _hash->m_maxOfRehashOperations = countRehash;
    }
    _hash->m_data[index]=_data;
    _hash->m_state[index]=2;
    _hash->m_allRehashOperations+= countRehash;
    _hash->m_counterOfInsertions++;
    _hash->m_numOfItems++;
	return SET_SUCCESS;
}

HashSet_Result HashRemove(Hash* _hash, void* _key, void** _data)
{
    size_t index;
    if(_hash ==NULL  || _key == NULL || _data== NULL)
	{
		return SET_UNINITIALIZED;
	}
    if(!IsFound(_hash,_key, &index))
    {
        return SET_KEY_NOT_FOUND;
    }
    *_data= _hash->m_data[index];
    _hash->m_numOfItems--;
    _hash->m_state[index]=1;
    return SET_SUCCESS;
}

int HashIsFound(const Hash* _hash, void* _key)
{
    size_t index;
    if(_hash ==NULL  || _key == NULL)
	{
		return 0;
	}
    if(IsFound(_hash,_key, &index))
    {
        return 1;
    }
    return 0;
}

size_t HashNumOfItems(const Hash* _hash)
{
    if(_hash == NULL)
    {
        return 0;
    }
    return _hash->m_numOfItems;
}

size_t HashCapacity(const Hash* _hash)
{
    if(_hash == NULL)
    {
        return 0;
    }
    return _hash->m_hashSize;
}

double HashAverageRehashes(const Hash* _hash)
{
    if(_hash == NULL)
    {
        return 0;
    }
    if(_hash->m_counterOfInsertions == 0)
    {
        return 0;
    }
    return _hash->m_allRehashOperations/_hash->m_counterOfInsertions;
}

size_t HashMaxReHash(const Hash* _hash)
{
    if(_hash == NULL)
    {
        return 0;
    }
    return _hash->m_maxOfRehashOperations;
}

void HashPrint(const Hash* _hash, void (*PrintKey)(void*))
{
    size_t i;
	if(_hash ==NULL)
	{
		return;
	}
    for(i = 0; i < _hash->m_capacity; ++i)
    {
        if(_hash->m_state[i] == 2)
        {
            PrintKey(_hash->m_data[i]);
        }
    }
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

static int IsFound(const Hash* _hash, void* _key, size_t* _index)
{
    size_t index, maxRe=_hash->m_maxOfRehashOperations, count=0;
    index= _hash->m_hashFunction(_key)%_hash->m_capacity;
    while (_hash->m_state[index] >0  && count <= maxRe )
    {
        if(_hash->m_state[index]== 2 && _hash->m_equalityFunction(_key,_hash->m_data[index]))
        {
            *_index=index;
            return TRUE;
        }
        index= (index+1)% _hash->m_capacity;
        count++;
    }
    return FALSE;
}
