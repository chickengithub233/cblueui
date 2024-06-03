#ifndef _XORG_LINK_LIST_TOOL_BLXDY_INC_H_
#define _XORG_LINK_LIST_TOOL_BLXDY_INC_H_

template<typename ListType>
class LindList
{
  public:
	ListType* next;
	ListType* prev;
};

template<typename ListType>
void InitListHead(ListType* list)
{
	list->next = list->prev = list;
}

template<typename ListType>
void ListInsert(ListType* entry, ListType* prev, ListType* next)
{
	next->prev = entry;
	entry->next = next;
	entry->prev = prev;
	prev->next = entry;
}

/**
 * Insert a new element after the given list head. The new element does not
 * need to be initialised as empty list.
 * The list changes from:
 *
 * Example:
 * struct foo *newfoo = malloc(...);
 * ListAdd(&newfoo->entry, &bar->list_of_foos);
 *
 * @param entry The new element to prepend to the list.
 * @param head The existing list.
 */
template<typename ListType>
void ListAdd(ListType* entry, ListType* head)
{
	ListInsert(entry, head, head->next);
}

/**
 * Append a new element to the end of the list given with this list head.
 *
 *
 * Example:
 * struct foo *newfoo = malloc(...);
 * ListAddTail(&newfoo->entry, &bar->list_of_foos);
 *
 * @param entry The new element to prepend to the list.
 * @param head The existing list.
 */
template<typename ListType>
void ListAddTail(ListType* entry, ListType* head)
{
	ListInsert(entry, head->prev, head);
}

template<typename ListType>
void _ListDelete(ListType* prev, ListType* next)
{
	next->prev = prev;
	prev->next = next;
}

/**
 * Remove the element from the list it is in. Using this function will reset
 * the pointers to/from this element so it is removed from the list. It does
 * NOT free the element itself or manipulate it otherwise.
 *
 * Using ListDel on a pure list head (like in the example at the top of
 * this file) will NOT remove the first element from
 * the list but rather reset the list as empty list.
 *
 * Example:
 * ListDel(&foo->entry);
 *
 * @param entry The element to remove.
 */
template<typename ListType>
void ListDel(ListType* entry)
{
	_ListDelete(entry->prev, entry->next);
}

template<typename ListType>
void ListMoveTail(ListType* list, ListType* head)
{
	_ListDelete(list->prev, list->next);
	ListAddTail(list, head);
}

/**
 * Check if the list is empty.
 *
 * Example:
 * ListIsEmpty(&bar->list_of_foos);
 *
 * @return True if the list contains one or more elements or False otherwise.
 */
template<typename ListType>
int ListIsEmpty(ListType* head)
{
	return head->next == head ? 0 : 1;
}

#endif
