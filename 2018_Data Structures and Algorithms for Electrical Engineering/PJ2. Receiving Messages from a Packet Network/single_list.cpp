#include <iostream>
#include <string>

#include "single_list.h"

using namespace std;


//////////////////////////////////////////////
// CAUTION: DO NOT CHANGE INCLUDED HEADERS  //
//////////////////////////////////////////////


/* Our singly linked lists have one header elements: the "head" which
   points the first element. The "next" link of the back header is
   NULL. 
   An empty list looks like this:

                  
          HEAD ---> NULL 
                  

   A list with two elements in it looks like this:
   
                   +-------+    +-------+
          HEAD --->|   1   |--->|   2   |--->NULL
                   +-------+    +-------+

   You should not change the name, input arguments, and
   input/output data types of existing functions. */



/*** COMPLETE FUNCTIONS BELOW ***/

/* SINGLY LINKED LIST */

/* Initializes LIST as an empty list with a head. */
single_list::single_list()
{
  /*** MODIFY HERE ***/
	head = NULL;
}

single_list::~single_list()
{
  /*** MODIFY HERE ***/
	while (!list_empty()) {
		list_remove(head);
	}
}

int
single_list::list_get_data1(list_elem *elem)
{
  /*** MODIFY HERE ***/
	return elem->data1;
}

int
single_list::list_get_data2(list_elem *elem)
{
  /*** MODIFY HERE ***/
	return elem->data2;
}

string
single_list::list_get_data3(list_elem *elem)
{
  /*** MODIFY HERE ***/
	return elem->data3;
}


/* Returns the element after ELEM in its list. */
list_elem *
single_list::list_next(list_elem *elem)
{
  /*** MODIFY HERE ***/
	return elem->next;
}


/* Returns LIST's head. */
list_elem *
single_list::list_head(void)
{
  /*** MODIFY HERE ***/
	return head;
}

/* Insert ELEM at the beginning of LIST, so that it becomes the head 
   in LIST. */
void 
single_list::list_insert_front(list_elem *elem)
{
    /*** MODIFY HERE ***/
	elem->next = head;
	head = elem;
	return;

}

/* Insert ELEM just before BEFORE, which may be either an interior
 element or a head. */
void 
single_list::list_insert_before(list_elem *before, list_elem *elem)
{
  /*** MODIFY HERE ***/

	// list is empty, or before == head, insert elem as a head,
	if ((list_empty()) || (before == head)) {
		list_insert_front(elem);
		return;
	}
	
	// list is not empty, and before != head
	list_elem* traversal_ptr1 = list_head();
	list_elem* traversal_ptr2 = NULL;

	do {
		// traversal_ptr2 is tracing traversal_ptr1
		traversal_ptr2 = traversal_ptr1;
		traversal_ptr1 = list_next(traversal_ptr1);

		if (before == traversal_ptr1) {

			elem->next = traversal_ptr1;
			traversal_ptr2->next = elem;
			return;
		}
	  // traversal_ptr goes next until encounter list's tail
	} while (traversal_ptr1->next != NULL);

	// do nothing when there is no matching list element
	return;
}

/* Insert ELEM just after AFTER, which may be either an interior
 element or a head. */
void 
single_list::list_insert_after(list_elem *after, list_elem *elem)
{
  /*** MODIFY HERE ***/

	// If list is empty, insert elem as a head,
	if (list_empty()) {
		list_insert_front(elem);
		return;
	}

	// If list is not empty,
	list_elem* traversal_ptr1 = list_head();

	// DO until traversal_ptr1 encounters list's tail
	while (traversal_ptr1 != NULL) {
		if (after == traversal_ptr1) {

			elem->next = after->next;
			after->next = elem;
			return;
		}
		traversal_ptr1 = list_next(traversal_ptr1);
	}

	// do nothing when there is no matching list element
	return;
}

/* Replace FROM with TO and deconstruct FROM */
void 
single_list::list_replace(list_elem *from, list_elem *to)
{
  /*** MODIFY HERE ***/

	// If list is empty, do nothing
	if (list_empty()) {
		return;
	}

	// If list is not empty, and from == head
	if (from == head) {
		to->next = head->next;

		from = head;
		head = to;
		delete from;
		from = NULL;
		return;
	}

	// If list is not empty, and from != head
	list_elem* traversal_ptr1 = list_head();
	list_elem* traversal_ptr2 = NULL;

	do {
		// traversal_ptr2 is tracing traversal_ptr1
		traversal_ptr2 = traversal_ptr1;
		traversal_ptr1 = list_next(traversal_ptr1);

		if (from == traversal_ptr1) {

			to->next = from->next;
			traversal_ptr2->next = to;
			delete from;
			from = NULL;
			return;
		}
	} while (traversal_ptr1->next != NULL);

	// do nothing when there is no matching list element
	return;
}


/* Removes ELEM from its list and deconstructs it. */
void
single_list::list_remove (list_elem *elem)
{
  /*** MODIFY HERE ***/
    // If list is empty, do noting
	if (list_empty()) {
		return;
	}

	// If list is not empty, and elem == head
	if (elem == head) {
		list_elem* old = head;
		head = head->next;
		delete old;
		old = NULL;
		return;
	}

	// If list is not empty, and elem != head
	list_elem* traversal_ptr1 = list_head();
	list_elem* traversal_ptr2 = NULL;

	do {
		// traversal_ptr2 is tracing traversal_ptr1
		traversal_ptr2 = traversal_ptr1;
		traversal_ptr1 = list_next(traversal_ptr1);

		if (elem == traversal_ptr1) {

			traversal_ptr2->next = traversal_ptr1->next;
			delete elem;
			elem = NULL;
			return;
		}
	} while (traversal_ptr1->next != NULL);

	// do nothing when there is no matching list element
	return;
}

/* Returns true if LIST is empty, false otherwise. */
bool 
single_list::list_empty (void)
{
  /*** MODIFY HERE ***/
	return (head == NULL);

}


