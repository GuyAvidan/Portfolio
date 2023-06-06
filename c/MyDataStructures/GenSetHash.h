#ifndef __GENSETHASH_H__
#define __GENSETHASH_H__
#include <stddef.h>

typedef struct Hash Hash;

typedef size_t (*HashFunction)(void* _data);


typedef int (*EqualityFunction)(void* _firstData, void* _secondData);

typedef enum HashSet_Result 
{
    SET_SUCCESS = 0,
    SET_UNINITIALIZED, /** Uninitialized HasSeterror*/
    SET_KEY_DUPLICATE, /** Duplicate key error */
    SET_KEY_NOT_FOUND, /** Key not found */
    SET_OVERFLOW /**No more space in HashSe */
}HashSet_Result;


/**
 * @brief Create a new hash with a size of _size
 * @param[in] _size - The size of the hash (more then 0)
 * @param[in] _hashFunction - The function to determine the index of the data
 * @param[in] _equalityFunction - The function to determine equality of the data
 * @return Hash pointer - on success, NULL on failure
 */
Hash* HashCreate(size_t _size, size_t (*_hashFunction)(void*), int(*_equalityFunction)(void*, void*));


/**
 * @brief Unallocate a previously created hash
 * @param[in] _hash - the hash to unallocate
 * @param[in] _keyDestroy - Optional destrot function for item
 * @return void - no return value
  */
void HashDestroy(Hash** _hash, void (*_keyDestroy)(void* _data));


/**
 * @brief Add a new item to the hash
 * @param[in] _hash - The hash to add the item to
 * @param[in] _data - the item to add to the hash
 * @return HashSet_Result - 
 * @retval SET_SUCCESS - on seccess
 * @retval SET_UNINITIALIZED- if _hash is NULL
 * @retval SET_UNINITIALIZED- if _data is NULL
 * @retval SET_OVERFLOW - if there is no more room to add 
 * @retval SET_KEY_DUPLICATE- if _data is duplitace
 */
HashSet_Result HashInsert(Hash* _hash, void* _data);


/**
 * @brief Remove an item in the hash by key
 * @param[in] _hash - the hash to remove the information from
 * @param[in] _key - the information need to be removed
 * @param[in] _data - A pointer to the information removed
 * @return HashSet_Result - 
 * @retval SET_SUCCESS - on seccess
 * @retval SET_UNINITIALIZED- if _hash is NULL
 * @retval SET_UNINITIALIZED- if _item is NULL
 * @retval SET_KEY_NOT_FOUND- if  _item doesn't found
 *
 */
HashSet_Result HashRemove(Hash* _hash, void* _key, void** _data);


/**
 * @brief find an item in the hash by key
 * @param[in] _hash - the hash to find the information from
 * @param[in] _key - the information need to be found
 * @param[in] _data - A pointer to the information find
 * @return int- 
 * @retval not zero found
 * @retval 0 not found
 */
int HashIsFound(const Hash* _hash, void* _key);


/**
 * @brief give the number of items in the hash 
 * @param[in] _hash - the hash
 * @return size_t- number of items (0 if NULL)
 */
size_t HashNumOfItems(const Hash* _hash);


/**
 * @brief give the size in the hash 
 * @param[in] _hash - the hash
 * @return size_t- size (0 if NULL)
 */
size_t HashCapacity(const Hash* _hash);


/**
 * @brief give the average rehashes 
 * @param[in] _hash - the hash
 * @return double- average aehashes (0 if there is none)
 */
double HashAverageRehashes(const Hash* _hash);


/**
 * @brief give the Max ReHash 
 * @param[in] _hash - the hash
 * @return size_t- Max ReHash (0 if there is none)
 */
size_t HashMaxReHash(const Hash* _hash);


/**
 * @brief do function PrintKey all elements in hash 
 * @param[in] _hash - the hash
 * @param[in] PrintKey - action to do on data
 * @return void
 */
void HashPrint(const Hash* _hash, void (*PrintKey)(void*));

#endif /* #ifndef __GENSETHASH_H__ */