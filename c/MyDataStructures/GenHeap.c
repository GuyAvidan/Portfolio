#include <stdio.h>
#include <stdlib.h> /* mealloc*/
#include "GenVector.h"
#include "GenHeap.h"
#define RC( i )  2*i+2
#define LC( i )  2*i+1
#define F( i )  (i+1)/2
#define LF( i )  i/2


struct Heap
{
	Vector* m_vec;
	size_t m_heapSize;
    LessThanComparator m_comp;
};

static void heapify(Heap* _heap, size_t _index);

Heap* HeapBuild(Vector* _vector, LessThanComparator _pfLess)
{
    Heap *dmnHeap;
    size_t i,n;
	if( _vector == NULL || _pfLess == NULL)
	{
		return NULL;
	}
	if((dmnHeap =(Heap*)malloc(sizeof(Heap))) == NULL)
	{
		return NULL;
	}
    n=VectorSize(_vector);
    dmnHeap->m_comp=_pfLess;
	dmnHeap->m_vec=_vector;
	dmnHeap->m_heapSize=n;
	for (i = F(n -1); i > 0; i--)
	{
		heapify(dmnHeap ,i);
	}
    heapify(dmnHeap ,0);
	return dmnHeap;
}


Vector* HeapDestroy(Heap** _heap)
{
    Vector *temp;
    if(_heap != NULL && *_heap != NULL)
	{
		temp=(*_heap)->m_vec;
        free(*_heap);
        *_heap=NULL;
        return temp;
	}
    return NULL;
}


HeapResultCode HeapInsert(Heap* _heap, void* _element)
{
    int i;
	if(_heap == NULL || _element == NULL)
	{
		return HEAP_NOT_INITIALIZED;
	}
	if(VectorAppend(_heap->m_vec,_element)==VECTOR_ALLOCATION_ERROR)
    {
        return HEAP_REALLOCATION_FAILED;
    }
	_heap->m_heapSize++;
	/**********bublll***********/
	for (i = _heap->m_heapSize / 2 - 1; i >= 0; i--)
	{
		heapify(_heap , i);
	}
	return HEAP_SUCCESS;
}


const void* HeapPeek(const Heap* _heap)
{
    void *val;
    if(_heap == NULL || _heap->m_heapSize == 0)
	{
		return NULL;
	}
    VectorGet(_heap->m_vec, 0, &val);
	return val;
}


void* HeapExtract(Heap* _heap)
{
    void *val, *setVal;
	if(_heap == NULL || _heap->m_heapSize == 0)
	{
		return NULL;
	}
    VectorGet(_heap->m_vec, 0, &val);
	_heap->m_heapSize--;
    if(VectorRemove(_heap->m_vec, &setVal) != VECTOR_SUCCESS)
	{
		return NULL;
	}
    VectorSet(_heap->m_vec, 0, &setVal);
    heapify(_heap, 0);
	return val;
}


size_t HeapSize(const Heap* _heap)
{
    if(_heap == NULL)
	{
		return 0;
	}
	return _heap->m_heapSize;
}

size_t HeapForEach(const Heap* _heap, ActionFunction _act, void* _context)
{
    size_t i;
    void* elem;
	if(_heap ==NULL ||  _act == NULL)
	{
		return -1;
	}
    for(i = 0; i < _heap->m_heapSize; ++i)
    {
        VectorGet(_heap->m_vec, i, &elem);
        if(_act(elem , _context) == 0)
        {
            break;
        }
        
    }
    return i;
}

static void heapify(Heap* _heap, size_t _index)
{
	size_t largest=_index, left=LC(_index), right=RC(_index);
    void *leftVal, *rightVal, *largestVal;
    VectorGet(_heap->m_vec, left, &leftVal);
    VectorGet(_heap->m_vec, right, &rightVal);
    VectorGet(_heap->m_vec, largest, &largestVal);
    
	if( _heap->m_heapSize > left && _heap->m_comp(leftVal, largestVal) )
	{
        largest=left;
		largestVal=leftVal;
	}
	if( _heap->m_heapSize > right && _heap->m_comp(rightVal, largestVal))
	{
        largest=right;
	}
     
	if (largest != _index)
	{	
        VectorSwap(_heap->m_vec, _index, largest);
		heapify(_heap ,largest);
	}
}

