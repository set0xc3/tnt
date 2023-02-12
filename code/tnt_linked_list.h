#ifndef TNT_LINKED_LIST_H
#define TNT_LINKED_LIST_H

typedef struct SLL_Node SLL_Node;
struct SLL_Node {
	SLL_Node *next;
};

typedef struct SLL_List SLL_List;
struct SLL_List {
	SLL_Node *first, *last;
};

typedef struct DLL_Node DLL_Node;
struct DLL_Node {
	DLL_Node *next, *prev;
};

typedef struct DLL_List DLL_List;
struct DLL_List {
	DLL_Node *first, *last;
};

internal void sll_push(void *list_ptr, void *node_ptr);
internal void sll_pop(void *list_ptr, void *node_ptr);

internal void dll_push(void *list_ptr, void *node_ptr);
internal void dll_pop(void *list_ptr, void *node_ptr);
internal void dll_remove(void *list_ptr, void *node_ptr);

#endif //TNT_LINKED_LIST_H