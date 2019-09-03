#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

#define ALLOC_UNIT 64


/* 
   Stack structure definition: 
   - we define the structure here not to share its definition and
   implementation with the client. That is, the client does not need
   to know what elements Stack_T has nor how its API is implemented.

*/
struct StackType 
{
	StackItem_T *pitem;   /* StackItem_T array: 
                             note: StackItem is defined by the client */
	int max_items;        /* number of maximum elements */
	int num_items;              /* number of items in the stack */
};

/*---------------------------------------------------------------------------*/
static int
AllocateItems(Stack_T st)
{
	StackItem_T *p;
	int new_count;

	new_count = st->max_items + ALLOC_UNIT;
	p = realloc(st->pitem, sizeof(StackItem_T) * new_count);
	if (p) {
		st->pitem = p;
		st->max_items = new_count;
	}
	return (p != NULL);
}
/*---------------------------------------------------------------------------*/
Stack_T 
Stack_Init(void)
{
	Stack_T st = malloc(sizeof(struct StackType));

	if (st == NULL)
		return NULL;

	st->num_items = 0;
	st->pitem     = NULL;
	st->max_items = 0;
	if (!AllocateItems(st)) {
		free(st);
		return NULL;
	}
	return st;
}
/*---------------------------------------------------------------------------*/
void
Stack_Release(Stack_T st)
{
	free(st->pitem);
	free(st);
}
/*---------------------------------------------------------------------------*/
int
Stack_IsEmpty(Stack_T st)
{
	assert(st->num_items >= 0);
	return (st->num_items == 0);
}
/*---------------------------------------------------------------------------*/
StackItem_T
Stack_Top(Stack_T st)
{
	if (Stack_IsEmpty(st))
		return NULL;
	return st->pitem[st->num_items -1];
}
/*---------------------------------------------------------------------------*/
StackItem_T
Stack_Pop(Stack_T st)
{
	if (Stack_IsEmpty(st))
		return NULL;
	st->num_items--;
	return st->pitem[st->num_items];
}
/*---------------------------------------------------------------------------*/
void 
Stack_Push(Stack_T st, StackItem_T item)
{
	if (st->num_items >= st->max_items) {
		if (!AllocateItems(st)) {
			fprintf(stderr, "Error: stack overflow\n");
			exit(-1);
		}
	}
	st->pitem[st->num_items++] = item;
}
