#ifndef __GENLIST_H__
#define __GENLIST_H__
#include <stddef.h>  /* size_t */
#include "ListInternal.h"


typedef struct List List;

typedef enum ListResult {
	LIST_SUCCESS,
	LIST_UNINITIALIZED_ERROR,			/**< Uninitialized list 					 	*/
	LIST_ALLOCATION_ERROR,				/**< Node allocation failed due to heap error   */
	LIST_UNINITIALIZED_POINTER_ERROR,
	LIST_IS_EMPTY_ERROR
	/* Add more as needed by your implementation */
	
} ListResult;

/** 
 * @brief Create a list
 * 
 * @returns a pointer to the created list.
 * @retval NULL on failure due to allocation failure
 */
List* ListCreate(void);

/** 
 * @brief Destroy list
 * @details Destroys the list completely 
 *          optionally destroys elements using user provided function
 *
 * @params[in] _pList : A pointer to previously created List returned via ListCreate
 *					   on completion *_pList will be null
 * @params[in] _elementDestroy : A function pointer to be used to destroy elements inserted into the list
 *             or a null if no such destroy is required
 */
void ListDestroy(List** _pList, void (*_elementDestroy)(void* _item));

/** 
 * @brief Add element to head of list
 * @details time complexity: O(1).
 *
 * @params _list A previously created List ADT returned via ListCreate
 * @params _item An item to add to the list
 * @returns error code
 * @retval LIST_SUCCESS on success
 * @retval LIST_UNINITIALIZED_ERROR if the list is not initialized
 * @retval LIST_UNINITIALIZED_POINTER_ERROR  if _item is NULL
 * @retval LIST_ALLOCATION_ERROR on memory allocation failure
 */
ListResult ListPushHead(List* _list, void* _item);

/** 
 * @brief Add element to the list's tail
 * @details time complexity O(1).
 *
 * @params _list A previously created List ADT returned via ListCreate 
 * @params _item An item to add to the list
 * @returns error code
 * @retval LIST_SUCCESS on success
 * @retval LIST_UNINITIALIZED_ERROR if the list is not initialized
 * @retval LIST_UNINITIALIZED_POINTER_ERROR- if _item is NULL
 * @retval LIST_ALLOCATION_ERROR on memory allocation failure
 */
ListResult ListPushTail(List* _list, void* _item);

/** @brief Remove element from list's head
 *  @details if successfull, stores a pointer to the removed item in _item
 *  time complexity O(1).
 *
 * @params _list : A previously created List ADT returned via ListCreate
 * @params _pItem: To store a pointer to the removed item in
 * @returns error code
 * @retval LIST_SUCCESS on success
 * @retval LIST_UNINITIALIZED_ERROR if the list is not initialized
 * @retval LIST_UNINITIALIZED_POINTER_ERROR- if _pItem is NULL
 */
ListResult ListPopHead(List* _list, void** _pItem);

/** @brief Remove element from list's tail
 *  @details time complexity O(1).
 *
 * @params _list : A previously created List ADT returned via ListCreate
 * @params _pItem: To store a pointer to the removed item in 
 * @returns error code
 * @retval LIST_SUCCESS on success
 * @retval LIST_UNINITIALIZED_ERROR if the list is not initialized
 * @retval LIST_UNINITIALIZED_POINTER_ERROR- if _pItem is NULL 
 */
ListResult ListPopTail(List* _list, void** _pItem);

/** @brief Get number of elements in the list
 * Average time complexity O(n).
 *
 * @params _list : A previously created List ADT returned via ListCreate
 * @returns size of list, 0 if it's NULL
 */
size_t ListSize(const List* _list);

void* GetM_tailData(List* _list);/*test func*/
void* GetM_headData(List* _list);/*test func*/

#endif /* __LIST_H__ */
