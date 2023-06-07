#include <stdio.h>
#include <stdlib.h> /*realloc, mealloc*/
#include "vector.h"
#include "ADTDefs.h"
#define MAGIC_NUMBER 654456


/*test func*/
int GetM_items( Vector* _vector, int index)
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

int GetM_magicNumber(Vector* _vector)
{
	return _vector->m_magicNumber;
}


/*code func*/
ADTErr IncreaseVe(Vector* _vector)
{
	int *temp, new_size;
	if(_vector->m_blockSize==0)
	{
		return ERR_OVERFLOW;
	}
	new_size=_vector->m_size+_vector->m_blockSize;
	if((temp=(int*)realloc(_vector->m_items,new_size*sizeof(int)))==NULL)
	{
		return ERR_REALLOCATION_FAILED;
	}
	_vector->m_items = temp;
	_vector->m_size=new_size;
	return ERR_OK;
}


Vector* VectorCreate(size_t _initialSize, size_t _extensionBlockSize)
{
	Vector *dmnVector;
	if(_initialSize == 0 && _extensionBlockSize == 0)
	{
		return NULL;
	}
	if((dmnVector =(Vector*)malloc(sizeof(struct Vector))) == NULL)
	{
		return NULL;
	}
	if( (dmnVector->m_items = (int*)malloc( _initialSize*sizeof(int))) == NULL)
	{
		free(dmnVector);
		return NULL;
	}
	dmnVector->m_originalSize=_initialSize;
	dmnVector->m_size=_initialSize;
	dmnVector->m_blockSize=_extensionBlockSize;
	dmnVector->m_nItems=0;
	dmnVector->m_magicNumber=MAGIC_NUMBER;
	return dmnVector;
}


void VectorDestroy(Vector* _vector)
{
	if(_vector != NULL && _vector->m_magicNumber == MAGIC_NUMBER)
	{
		_vector->m_magicNumber =0;
		free(_vector->m_items);
		free(_vector);
	}

}

ADTErr VectorAdd(Vector *_vector, int _item)
{
	ADTErr result;
	if(_vector ==NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_vector->m_nItems==_vector->m_size)
	{
		if ((result= IncreaseVe(_vector))!= ERR_OK)
		{
			return result;
		}
	}
	_vector->m_items[_vector->m_nItems]= _item;
	_vector->m_nItems++;
	return ERR_OK;
}

ADTErr VectorDelete (Vector *_vector, int* _item)
{
	if(_vector ==NULL || _item ==NULL)/*in func*/
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_vector->m_nItems == 0)
	{
		return ERR_UNDERFLOW;
	}
	(_vector->m_nItems)--;
	*_item = _vector->m_items[_vector->m_nItems];
	return ERR_OK;
}


ADTErr VectorGet(Vector *_vector, size_t _index, int *_item)
{
	if(_vector ==NULL || _item ==NULL)/*in func*/
	{
		return ERR_NOT_INITIALIZED;
	}
	if( _index>(_vector->m_nItems-1))
	{
		return ERR_WRONG_INDEX;
	}
	*_item = _vector->m_items[_index];
	return ERR_OK;
}

ADTErr VectorSet(Vector *_vector, size_t _index, int _item)
{
	if(_vector ==NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_index >= _vector->m_nItems)
	{
		return ERR_WRONG_INDEX;
	}
	_vector->m_items[_index]=_item;
	return ERR_OK;
}

ADTErr VectorItemsNum(Vector *_vector, size_t* _numOfItems)
{
	if(_vector ==NULL || _numOfItems ==NULL)
	{
		return ERR_NOT_INITIALIZED;
	}

	*_numOfItems=_vector->m_nItems;
	return ERR_OK;
}

void swap(Vector* _vec, int  x, int  y)
{
    int datax, datay;
	size_t n;
	if(_vec ==NULL )
	{
		return;
	}
	VectorItemsNum(_vec, &n);
	if( x>=n || y>=n || x<0 || y<0)
	{
		return;
	}

    VectorGet( _vec , x , &datax);
    VectorGet( _vec , y , &datay);
    VectorSet( _vec , x , datay);
    VectorSet( _vec , y , datax);
}


void VectorPrint(Vector *_vector)
{
	size_t i;
	if(_vector ==NULL)
	{
		return;
	}
	for(i=0; i<_vector->m_nItems; i++)
	{
		printf ("%d ",_vector->m_items[i]);
	}
	printf("\n");
}
