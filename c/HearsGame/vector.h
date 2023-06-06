#ifndef __VECTOR_H__
#define __VECTOR_H__
#include "ADTDefs.h"

typedef struct Vector Vector;

struct Vector
{
	int *m_items; /* A dynamic array of integers*/
	size_t m_originalSize; /* original allocated space for items */
	size_t m_size; /* actual allocated space for items*/
	size_t m_nItems; /* actual number of items */
	size_t m_blockSize; /* the chunk size to be allocated when no space*/
	int m_magicNumber;

};


/*
Description: The function creates a dynamic structure according to the settings
Input: _initialSize-The size of the dynamic array, _extensionBlockSize-block propertis of the struct
Output:struct DynamicArray
Errors: NA
*/
Vector* VectorCreate(size_t _initialSize, size_t _extensionBlockSize);


/* 
Description: The function destroys a dynamic structure
Input: *_vector- struct to destroy
Output:NA
Errors: NA
*/
void VectorDestroy(Vector* _vector);


/* 
Description: The function inserts a number in the last place in the dynamic array
Input: *_vector- struct to insert to, _item- the data to put in the end
Output:ERR_OK or Errors
Errors: ERR_NOT_INITIALIZED, ERR_OVERFLOW, ERR_REALLOCATION_FAILED
*/
ADTErr VectorAdd(Vector *_vector, int _item);


/* 
Description: The function delets the last place in the dynamic array
Input: *DynaminArrayPtr- struct to insert to, data- the data deleted from the end
Output:ERR_OK or Errors
Errors: ERR_NOT_INITIALIZED, ERR_UNDERFLOW
*/
ADTErr VectorDelete (Vector *_vector, int* _item);/* Delete item from the end. */


/* 
Description: The function puts in a pointer the int in the index of the dynamic array
Input: *_vector- struct , _index-index of the int, _item- the poinet to put the data in it
Output:OK or Errors
Errors: ERR_NOT_INITIALIZED, ERR_WRONG_INDEX
*/
ADTErr VectorGet(Vector *_vector, size_t _index, int *_item);


/* 
Description: The function replace a int in the index of the dynamic array
Input: *_vector- struct , _index-index of the int, _item- the data to put in it
Output:OK or Errors
Errors: ERR_NOT_INITIALIZED, ERR_WRONG_INDEX
*/
ADTErr VectorSet(Vector *_vector, size_t _index, int _item);


/* 
Description: The function puts in a pointer the number of elements
Input: *_vector- struct ,  _numOfItems-the number of elements
Output:OK or Error
Errors: ERR_NOT_INITIALIZED
*/
ADTErr VectorItemsNum(Vector *_vector, size_t* _numOfItems);

/* 
Description: The function swaps 2 indexs of elements
Input: *_vector- struct , x,y-idex to swap
Output:NA
Errors: If vector is NULL or x/y out of range, don't do swap
*/
void swap(Vector* _vec, int  x, int  y);


/* 
Description: The function prints all the elements
Input: *_vector- struct
Output:OK or Error
Errors: ERR_NOT_INITIALIZED
*/
void VectorPrint(Vector *_vector);

#endif /* #ifndef __VECTOR_H__ */
