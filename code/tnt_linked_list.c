#include "tnt_linked_list.h"

void linked_list_push_front(LinkedListList *list, LinkedListNode *node) {
  if (list->head != 0) {
    list->head->prev = node;
    node->next = list->head;
    node->prev = 0;
    list->head = node;
  } else {
    list->head = node;
    list->tail = node;
    node->next = 0;
    node->prev = 0;
  }
}

void linked_list_push_back(LinkedListList *list, LinkedListNode *node) {
  if (list->tail != 0) {
    list->tail->next = node;
    node->next = 0;
    node->prev = list->tail;
    list->tail = node;
  } else {
    list->head = node;
    list->tail = node;
    node->next = 0;
    node->prev = 0;
  }
}

LinkedListNode *linked_list_pop_front(LinkedListList *list) {
  LinkedListNode *link = list->head;
  if (link == 0) {
    return 0;
  }
  if (link->next != 0) {
    link->next->prev = link->prev;
  }
  if (link->prev != 0) {
    link->prev->next = link->next;
  }
  if (link == list->head) {
    list->head = link->next;
  }
  if (link == list->tail) {
    list->tail = link->prev;
  }
  return link;
}

LinkedListNode *linked_list_pop_back(LinkedListList *list) {
  LinkedListNode *link = list->tail;
  if (link == 0) {
    return 0;
  }
  if (link->next != 0) {
    link->next->prev = link->prev;
  }
  if (link->prev != 0) {
    link->prev->next = link->next;
  }
  if (link == list->head) {
    list->head = link->next;
  }
  if (link == list->tail) {
    list->tail = link->prev;
  }
  return link;
}

void linked_list_remove(LinkedListList *list, LinkedListNode *node) {
  if (node != 0) {
    if (node->next != 0) {
      node->next->prev = node->prev;
    }
    if (node->prev != 0) {
      node->prev->next = node->next;
    }
    if (list->head == node) {
      list->head = node->next;
    }
    if (list->tail == node) {
      list->tail = node->prev;
    }
  }
}

void linked_list_clear(LinkedListList *list) {
  for (LinkedListNode *node = list->head; node != 0; node = node->next) {
    if (node->next != 0) {
      node->next->prev = node->prev;
    }
    if (node->prev != 0) {
      node->prev->next = node->next;
    }
    if (list->head == node) {
      list->head = node->next;
    }
    if (list->tail == node) {
      list->tail = node->prev;
    }
  }
}

b8 linked_list_is_empty(LinkedListList *list) { return list->head == 0; }

void *linked_list_iterate_next(LinkedList_Iterator *it) {
  LinkedListNode *node = it->current;
  if (node == 0) {
    return 0;
  }
  it->current = node->next;
  return (void *)(u64)node - it->offset;
}

void *linked_list_iterate_prev(LinkedList_Iterator *it) {
  LinkedListNode *node = it->current;
  if (node == 0) {
    return 0;
  }
  it->current = node->prev;
  return (void *)(u64)node - it->offset;
}
