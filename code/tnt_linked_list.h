#ifndef TNT_LINKED_LIST_H
#define TNT_LINKED_LIST_H

#include <stddef.h>

typedef struct LinkedList_Node LinkedList_Node;
struct LinkedList_Node {
    LinkedList_Node* next;
    LinkedList_Node* prev;
};

typedef struct LinkedList_List LinkedList_List;
struct LinkedList_List {
    LinkedList_Node* head;
    LinkedList_Node* tail;
};

internal void 		      linked_list_push_front(LinkedList_List* list, LinkedList_Node* node);
internal void 		      linked_list_push_back(LinkedList_List* list, LinkedList_Node* node);
internal LinkedList_Node* linked_list_pop_front(LinkedList_List* list);
internal LinkedList_Node* linked_list_pop_back(LinkedList_List* list);
internal void		      linked_list_remove(LinkedList_List* list, LinkedList_Node* node);
internal void		      linked_list_clear(LinkedList_List* list);
internal b8			      linked_list_is_empty(LinkedList_List* list);

typedef struct LinkedList_Iterator LinkedList_Iterator;
struct LinkedList_Iterator
{
    LinkedList_Node* current;
	u64 offset;
};

internal void* linked_list_iterate_next(LinkedList_Iterator* it);
internal void* linked_list_iterate_prev(LinkedList_Iterator* it);

#define linked_list_iterator_head(l, t, d) \
	((LinkedList_Iterator){l.head, offsetof(t, d)})

#define linked_list_iterator_tail(l, t, d) \
	((LinkedList_Iterator){l.tail, offsetof(t, d)})

#endif //TNT_LINKED_LIST_H