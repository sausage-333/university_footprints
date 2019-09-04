#include <iostream>
#include <string>

#include "double_list_iter.h"

using namespace std;

//////////////////////////////////////////////
// YOU CAN CHANGE INCLUDED HEADERS ^0^ //
//////////////////////////////////////////////

/* Our doubly linked lists have two header elements: the "head"
   just before the first element and the "tail" just after the
   last element. The "prev" link of the front header is null, as
   is the "next" link of the back header. Their other two links
   point toward each other via the interior elements of the list.

   An empty list looks like this:

                      +------+     +------+
                  <---| head |<--->| tail |--->
                      +------+     +------+

   A list with two elements in it looks like this:

        +------+     +-------+     +-------+     +------+
    <---| head |<--->|   1   |<--->|   2   |<--->| tail |<--->
        +------+     +-------+     +-------+     +------+

   The symmetry of this arrangement eliminates lots of special
   cases in list processing. That's a lot simpler than the code 
   would be without header elements.

   (Because only one of the pointers in each header element is used,
   we could in fact combine them into a single header element
   without sacrificing this simplicity.  But using two separate
   elements allows us to do a little bit of checking on some
   operations, which can be valuable.) 

   You SHOULD NOT change the name, input arguments, and
   input/output data types of existing functions. */

   // Used Double Linked List implementation in project 2a

   /* Initializes LIST as an empty list. "prev" of "head" and "next" of
   "tail" in LIST have null. "next" of "head" points "tail" and "prev"
   of "tail" points "head". */
double_list::double_list()
{
	/*** MODIFY HERE ***/
	head = new d_list_elem;
	tail = new d_list_elem;

	head->next = tail;
	tail->prev = head;
}

double_list::~double_list()
{
	/*** MODIFY HERE ***/
	// list가 empty할 때까지 front 원소를 계속 지움
	while (d_list_empty() != true) {
		d_list_remove(d_list_front());
	}
}

int
double_list::d_list_get_data1(d_list_elem *elem)
{
	/*** MODIFY HERE ***/
	return elem->data1;
}

int
double_list::d_list_get_data2(d_list_elem *elem)
{
	/*** MODIFY HERE ***/
	return elem->data2;
}

string
double_list::d_list_get_data3(d_list_elem *elem)
{
	/*** MODIFY HERE ***/
	return elem->data3;
}

/* Returns the element before ELEM in its list. If ELEM is the first
element in its list, returns the list head. Results are undefined
if ELEM is itself a list head. */
d_list_elem *
double_list::d_list_prev(d_list_elem *elem)
{
	/*** MODIFY HERE ***/
	if (elem == head) {
		cout << "We cannot return prev pointer of head." << endl;
		return NULL;
	}

	return elem->prev;
}

/* Returns the element after ELEM in its list. If ELEM is the last
element in its list, returns the list tail. Return NULL if ELEM is
itself a list tail. */
d_list_elem *
double_list::d_list_next(d_list_elem *elem)
{
	/*** MODIFY HERE ***/
	if (elem == tail) {
		cout << "We cannot return next pointer of tail." << endl;
		return NULL;
	}

	return elem->next;
}


/* Returns LIST's head. */
d_list_elem *
double_list::d_list_head(void)
{
	/*** MODIFY HERE ***/
	return head;
}

/* Returns LIST's tail. */
d_list_elem *
double_list::d_list_tail(void)
{
	/*** MODIFY HERE ***/
	return tail;
}

/* Returns the front element in LIST. Return NULL if LIST is empty. */
d_list_elem *
double_list::d_list_front(void)
{
	/*** MODIFY HERE ***/
	if (d_list_empty()) {
		return NULL;
	}

	else {
		return head->next;
	}
}

/* Returns the back element in LIST. Return NULL if LIST is empty. */
d_list_elem *
double_list::d_list_back(void)
{
	/*** MODIFY HERE ***/
	if (d_list_empty()) {
		return NULL;
	}

	else {
		return tail->prev;
	}
}


/* Insert ELEM at the beginning of LIST, so that it becomes the front
in LIST. */
void
double_list::d_list_insert_front(d_list_elem *elem)
{
	/*** MODIFY HERE ***/
	elem->prev = head;
	elem->next = head->next;

	head->next->prev = elem;
	head->next = elem;
	return;
}

/* Insert ELEM at the end of LIST, so that it becomes the back in LIST. */
void
double_list::d_list_insert_back(d_list_elem *elem)
{
	/*** MODIFY HERE ***/
	elem->prev = tail->prev;
	elem->next = tail;

	tail->prev->next = elem;
	tail->prev = elem;

	return;
}

/* Insert ELEM just before BEFORE, which may be either an interior
element or a tail. The latter case is equivalent to list_insert_back().
Results are undefined if BEFORE is itself a list head. */
void
double_list::d_list_insert_before(d_list_elem *before, d_list_elem *elem)
{
	/*** MODIFY HERE ***/
	// before = head이면 아무것도 하지 않는다.
	if (before == head) {
		return;
	}

	// before = tail인 경우
	else if (before == tail) {
		d_list_insert_back(elem);
		return;
	}

	// head, tail이 아닌 경우
	else {
		elem->prev = before->prev;
		elem->next = before;

		before->prev->next = elem;
		before->prev = elem;
		return;
	}
}

/* Insert ELEM just after AFTER, which may be either an interior
element or a head. The latter case is equivalent to list_insert_front().
Results are undefined if AFTER is itself a list tail. */
void
double_list::d_list_insert_after(d_list_elem *after, d_list_elem *elem)
{
	/*** MODIFY HERE ***/
	// after = tail이면 아무 것도 하지 않는다.
	if (after == tail) {
		return;
	}

	else if (after == head) {
		d_list_insert_front(elem);
		return;
	}

	else {
		elem->prev = after;
		elem->next = after->next;

		after->next->prev = elem;
		after->next = elem;
		return;
	}
}

/* Replace FROM with TO and deconstruct FROM*/
void
double_list::d_list_replace(d_list_elem *from, d_list_elem *to)
{
	/*** MODIFY HERE ***/
	// 리스트가 비어있거나, from = head or tail일 경우 아무것도 하지 않는다.
	if (d_list_empty() || from == head || from == tail) {
		return;
	}

	// 리스트가 비어있지 않고, from이 head나 tail이 아닌 list의 내부 원소일 때
	else {
		to->prev = from->prev;
		to->next = from->next;

		from->prev->next = to;
		from->next->prev = to;

		delete from;
		from = NULL;

		return;
	}
}


/* Removes ELEM from its list and deconstruct it.
Undefined behavior if ELEM is not in a list. Results are undefined
if ELEM is not an interior element of its list.
*/

void
double_list::d_list_remove(d_list_elem *elem)
{
	/*** MODIFY HERE ***/
	// 리스트가 비어있거나, elem = head or tail일 때 아무것도 하지 않음
	if (d_list_empty() || elem == head || elem == tail) {
		return;
	}

	// 리스트가 비어있지 않고, from이 head나 tail이 아닌 list의 내부 원소일 때
	else {
		elem->next->prev = elem->prev;
		elem->prev->next = elem->next;

		delete elem;
		elem = NULL;
		return;
	}

}

/* Returns true if LIST is empty, false otherwise. */
bool
double_list::d_list_empty(void)
{
	/*** MODIFY HERE ***/
	if ((head->next == tail) && (tail->prev == head)) {
		return true;
	}
	else {
		return false;
	}
}