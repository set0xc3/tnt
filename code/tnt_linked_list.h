#ifndef TNT_LINKED_LIST_H
#define TNT_LINKED_LIST_H

#include <stddef.h>

#include "tnt_base_types.h"

typedef struct LinkedListNode LinkedListNode;
struct LinkedListNode {
  LinkedListNode *next;
  LinkedListNode *prev;
};

typedef struct LinkedListList {
  LinkedListNode *head;
  LinkedListNode *tail;
} LinkedListList;

void linked_list_push_front(LinkedListList *list, LinkedListNode *node);
void linked_list_push_back(LinkedListList *list, LinkedListNode *node);
LinkedListNode *linked_list_pop_front(LinkedListList *list);
LinkedListNode *linked_list_pop_back(LinkedListList *list);
void linked_list_remove(LinkedListList *list, LinkedListNode *node);
void linked_list_clear(LinkedListList *list);
b8 linked_list_is_empty(LinkedListList *list);

typedef struct LinkedListIterator {
  LinkedListNode *current;
  u64 offset;
} LinkedListIterator;

void *linked_list_iterate_next(LinkedListIterator *it);
void *linked_list_iterate_prev(LinkedListIterator *it);

#define linked_list_iterator_head(l, t, d) \
  ((LinkedList_Iterator){l.head, offsetof(t, d)})
#define linked_list_iterator_tail(l, t, d) \
  ((LinkedList_Iterator){l.tail, offsetof(t, d)})

#endif  // TNT_LINKED_LIST_H
