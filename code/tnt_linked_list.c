
//#define DLL_PUSH_BACK(f, l, n, next, prev) 

internal void sll_push(void *list_ptr, void *node_ptr)
{
	SLL_List *list = (SLL_List *)list_ptr;
	SLL_Node *node = (SLL_Node *)node_ptr;
	
	if (!list->first && !list->last) 
	{
		list->first = list->last = node;
	} 
	else if (list->last != node)
	{
		list->last->next = node;
		list->last = node;
	}
}

internal void sll_pop(void *list_ptr, void *node_ptr)
{
	SLL_List *list = (SLL_List *)list_ptr;
	SLL_Node *node = (SLL_Node *)node_ptr;
	
	if (list->last != node) 
	{
		list->first = list->first->next;
	} else 
	{
		list->first = list->last = 0;
	}
}

internal void dll_push(void *list_ptr, void *node_ptr)
{
	DLL_List *list = (DLL_List *)list_ptr;
	DLL_Node *node = (DLL_Node *)node_ptr;
	
	if (!list->first && !list->last) 
	{
		list->first = list->last = node;
	} 
	else if (list->last != node)
	{
		list->last->next = node;
		node->prev = list->last;
		list->last = node;
	}
}

internal void dll_pop(void *list_ptr, void *node_ptr)
{
	DLL_List *list = (DLL_List *)list_ptr;
	DLL_Node *node = (DLL_Node *)node_ptr;
	
	if (list->last != node) 
	{
		list->first = node->next;
	} 
	else 
	{
		list->first = list->last = 0;
	}
}

internal void dll_remove(void *list_ptr, void *node_ptr)
{
	DLL_List *list = (DLL_List *)list_ptr;
	DLL_Node *node = (DLL_Node *)node_ptr;
	
	if (list->first != node && list->last != node) 
	{
		node->prev->next = node->next;
		node->next->prev = node->prev;
	} 
	else if (list->first == node && list->last != node) 
	{
		list->first = node->next;
		list->first->prev = 0;
	} 
	else if (list->last == node && list->first != node) 
	{
		list->last = node->prev;
		list->last->next = 0;
	} 
	else if (list->first == node && list->last == node) 
	{
		list->first = list->last = 0;
	}
}