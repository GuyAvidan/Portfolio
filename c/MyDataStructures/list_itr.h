#ifndef __LIST_ITR_H__
#define __LIST_ITR_H__
#include "ListInternal.h"
#include "GenList.h"

typedef void* ListItr;

/** 
 * @brief Get itertator to the list's beginning
 *
 * @params _list : list to return begin iterator, pointing at first element
 *                 or at the end if list is empty
 * @return iterator pointing at the list's beginning
 * @return NULL if the list is NULL
 */
ListItr ListItrBegin(const List* _list);

/** 
 * @brief Get itertator to the list end
 *
 * @params _list : list to return end iterator
 * @return an iterator pointing at the list's end (tail)
 * @return NULL if the list is NULL
 */
ListItr ListItrEnd(const List* _list);

/** 
 * @brief retruns one if _a and _b iterators refer to same node, zero if _a and _b iterators not refer to same node and -1 if _a and _b iterators is NULL
 * @warning might be implemented as a macro
 */
int ListItrEquals(const ListItr _a, const ListItr _b);

/** 
 * @brief Get itertator to the next element from a given iterator
 * @warning if _itr is end iterator it will be returned
 * @return NULL if the list is NULL
 * @return tail if the _itr is tail
 */
ListItr ListItrNext(ListItr _itr);

/** 
 * @brief Get itertator to the previous element
 * @warning if _itr is begin iterator it will be returned
 * @return NULL if the list is NULL
 * @return head if the _itr is head
 */
ListItr ListItrPrev(ListItr _itr);

/** 
 * @brief Get data from the list node the iterator is pointing to
 *
 * @params _itr : A list iterator
 * @return the data the iterator is pointing at or NULL if pointing to the end
 * @return NULL if the list is NULL
 */
void* ListItrGet(ListItr _itr);

/** 
 * @brief Set data at the node where the iterator is pointing at
 * @return the data from the node to be changed
 * @return NULL if the list or elemnt is NULL
 */
void* ListItrSet(ListItr _itr, void* _element);

/** 
 * @brief Inserts a new node before node the iterator is pointing at
 * @return an iterator pointing at the element inserted or NULL on error
 */
ListItr ListItrInsertBefore(ListItr _itr, void* _element);

/** 
 * @brief Removes the node the iterator is pointing at
 *
 * @params _itr : A list iterator
 * @return the removed data
 * @return NULL if the list is NULL
 */
void* ListItrRemove(ListItr _itr);

#endif /* __LIST_ITR_H__ */