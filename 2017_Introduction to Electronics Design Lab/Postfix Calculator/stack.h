#ifndef _STACK_H_
#define _STACK_H_

/* struct StackItem should be defined in the client code.  
   The item itself is owned by the client. That is, the client is
   responsible for memory allocation and deallocation for the item.
   Stack_T will simply keep track of the pointer of the
   client-provided item. */
struct StackItem;

/* struct StackType is defined in stack.c */
struct StackType;

/* type definitions for StackItem and Stack */
typedef struct StackItem* StackItem_T;
typedef struct StackType* Stack_T;

/* initialize stack's own variables, allocate an array for items */
Stack_T Stack_Init(void);

/* call this when you're done with the stack */
void Stack_Release(Stack_T st);


/* pop the top element on the stack 
   return NULL if the stack is empty */
StackItem_T Stack_Pop(Stack_T st);

/* push an element on the top of the stack */
void Stack_Push(Stack_T st, StackItem_T item);

/* Observe the top element on the stack
   return NULL if the stack is empty */
StackItem_T Stack_Top(Stack_T st);

/* return TRUE (non-zero) if the stack is empty. 
   FALSE (zero) otherwise. */
int Stack_IsEmpty(Stack_T st);

#endif
