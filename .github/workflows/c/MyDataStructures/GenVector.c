#include <stdio.h>
#include <stdlib.h> /*realloc, mealloc*/
#include "GenVector.h"

struct Vector
{
	void **m_items;
	size_t m_originalSize; /* original allocated space for items */
	size_t m_size; /* actual allocated space for items*/
	size_t m_nItems; /* actual number of items */
	size_t m_blockSize; /* the chunk size to be allocated when no space*/

};

static VectorResult IncreaseVe(Vector* _vector);

Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize)
{
    Vector *dmnVector;
	if(_initialCapacity == 0 && _blockSize == 0)
	{
		return NULL;
	}
	if((dmnVector =(Vector*)malloc(sizeof(struct Vector))) == NULL)
	{
		return NULL;
	}
	if( (dmnVector->m_items = (void**)malloc( _initialCapacity*sizeof(void*))) == NULL)
	{
		free(dmnVector);
		return NULL;
	}
	dmnVector->m_originalSize=_initialCapacity;
	dmnVector->m_size=_initialCapacity;
	dmnVector->m_blockSize=_blockSize;
	dmnVector->m_nItems=0;
	return dmnVector;
}

void VectorDestroy(Vector ** _vector, void (*_elementDestroy)(void* _item))
{
    size_t i;
    if(_vector != NULL || *_vector != NULL )
	{
        if(_elementDestroy != NULL)
        {
            for (i=0; i< (*_vector)->m_nItems; i++)
            {
                _elementDestroy((*_vector)->m_items[i]);
            }
        }
		free((*_vector)->m_items);
		free(*_vector);
		*(_vector)=NULL;
	}
}

VectorResult VectorAppend(Vector* _vector, void* _item)
{
    VectorResult result;
	if(_vector ==NULL  || _item == NULL)
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
	if(_vector->m_nItems==_vector->m_size)
	{
		if ((result= IncreaseVe(_vector))!= VECTOR_SUCCESS)/*****/
		{
			return result;
		}
	}
	_vector->m_items[_vector->m_nItems]= _item;
	_vector->m_nItems++;
	return VECTOR_SUCCESS;
}   

VectorResult VectorRemove(Vector* _vector, void** _pValue)
{
    if(_vector ==NULL || _pValue ==NULL)/*in func*/
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
	if(_vector->m_nItems == 0)
	{
		return VECTOR_UNDERFLOW_ERROR;
	}
	(_vector->m_nItems)--;
	*_pValue = _vector->m_items[_vector->m_nItems];
	return VECTOR_SUCCESS;
}

VectorResult VectorGet(const Vector* _vector, size_t _index, void** _pValue)
{
    if(_vector ==NULL || _pValue ==NULL)/*in func*/
	{
		return VECTOR_SUCCESS;
	}
	if( _index>(_vector->m_nItems-1))
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}
	*_pValue = _vector->m_items[_index];
	return VECTOR_SUCCESS;
}

VectorResult VectorSet(Vector* _vector, size_t _index, void*  _value)
{
    if(_vector ==NULL)
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
	if(_value ==NULL)
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
	if(_index >= _vector->m_nItems)
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}
	_vector->m_items[_index]=_value;
	return VECTOR_SUCCESS;
}

size_t VectorSize(const Vector* _vector)
{
    if(_vector ==NULL )
	{
		return -1;
	}
	return _vector->m_nItems;
}

size_t VectorCapacity(const Vector* _vector)
{
    if(_vector ==NULL )
	{
		return -1;
	}
	return _vector->m_size;
}

size_t VectorForEach(const Vector* _vector, VectorElementAction _action, void* _context)
{
    size_t i;
    void* elem;
	if(_vector ==NULL ||  _action == NULL)
	{
		return -1;
	}
    for(i = 0; i < _vector->m_nItems; ++i)
    {
        VectorGet(_vector, i, &elem);
        if(_action(elem, i, _context) == 0)
        {
            break;
        }
        
    }
    return i;
}


VectorResult VectorSwap(Vector* _vector, size_t _firat,size_t _next)
{
	void *temp;
	temp= _vector->m_items[_firat];
	_vector->m_items[_firat]=_vector->m_items[_next];
	_vector->m_items[_next]=temp;
	return VECTOR_SUCCESS;
}

/*test func*/
void* GetM_items( Vector* _vector, size_t index)
{
	return _vector->m_items[index];
}

size_t GetM_originalSize(Vector* _vector)
{
	return _vector->m_originalSize;
}

size_t GetM_size(Vector* _vector)
{
	return _vector->m_size;
}

size_t GetM_nItems(Vector* _vector)
{
	return _vector->m_nItems;
}

size_t GetM_blockSize(Vector* _vector)
{
	return _vector->m_blockSize;
}


/*code func*/
static VectorResult IncreaseVe(Vector* _vector)
{
	size_t new_size;
    void **temp;
	if(_vector->m_blockSize==0)
	{
		return VECTOR_OVERFLOW_ERROR;
	}
	new_size=_vector->m_size+_vector->m_blockSize;
	if((temp=(void**)realloc(_vector->m_items,new_size*sizeof(void*)))==NULL)
	{
		return VECTOR_ALLOCATION_ERROR;
	}
	_vector->m_items = temp;
	_vector->m_size=new_size;
	return VECTOR_SUCCESS;
}

/*static VectorResult DecreaseVe(Vector* _vector)
{
	size_t new_size;
    void *temp;
	new_size=_vector->m_size-_vector->m_blockSize;
	if((temp=(void**)realloc(_vector->m_items,new_size*sizeof(void*)))==NULL)
	{
		return VECTOR_ALLOCATION_ERROR;
	}
	_vector->m_items = temp;
	_vector->m_size=new_size;
	return VECTOR_SUCCESS;
}*/
