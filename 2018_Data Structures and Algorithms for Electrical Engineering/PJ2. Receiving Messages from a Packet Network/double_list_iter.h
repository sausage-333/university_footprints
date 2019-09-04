#ifndef __DOUBLE_LIST_H__
#define __DOUBLE_LIST_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include <string>

#include <iterator>

using namespace std;

///////////////////////////////////////
// YOU CAN CHANGE THIS FILE  ^0^ //
///////////////////////////////////////

/*
  Glossary of list terms:

  - "front": The first element in a list. Undefined in an empty list.
  Returned by list_front().

  - "back": The last element in a list. Undefined in an empty list.
  Returned by list_back().
  
  - "tail": The element figuratively just after the last element of
  a list. Well defined even in an empty list. Returned by list_end(). 
  Used as the end sentinel for an iteration from front to back.
  
  - "beginning": In a non-empty list, the front. In an empty list,
  the tail. Returned by list_begin(). Used as the starting point for 
  an iteration from front to back.
  
  - "head": The element figuratively just before the first element
  of a list. Well defined even in an empty list. Returned by list_rend(). 
  Used as the end sentinel for an iteration from back to front.
  
  - "interior element": An element that is not the head or tail, that is,
  a real list element. An empty list does not have any interior elements.
*/

/* List element. */
class d_list_elem{

 friend class double_list;

 private:

  int data1; /* Data of list element. */
  int data2; /* Data of list element. */
  string data3; /* Data of list element. */
  d_list_elem *next; /* Next list element. */
  d_list_elem *prev;   /* Previous list element. */    

 public:
  /* List element constructor. */
  d_list_elem (){
    next = NULL;
    prev = NULL;
  }
  d_list_elem (int _data1, int _data2, string _data3, d_list_elem *_next =NULL, d_list_elem *_prev = NULL){
    data1 = _data1;
    data2 = _data2;
    data3 = _data3;
    next = _next;
    prev = _prev;
  }
};


/* Doubly Linked List. */
class double_list{

 private:
	d_list_elem *head; /* List head. */
	d_list_elem *tail; /* List tail. */
  
 // Iterator Implementation
 public:

	  class Iter {
	  public:

		  // iterator traits
		  typedef Iter self_type;
		  typedef int value_type;
		  typedef int reference;
		  typedef d_list_elem* pointer;
		  typedef std::bidirectional_iterator_tag iterator_category;
		  typedef int difference_type;

		  // iterator initializaition by given d_list_elem v
		  Iter(pointer elem) : v(elem) {}

		  // iterator operator overloadings
		  
		  // Dereferecne data1 only
		  // We just need to check message number
		  reference operator*()
			{return v->data1;}

		  // check iterator is pointing same element
		  bool operator==(const Iter& it) const
			{return v == it.v;}
		  
		  // check iterator is pointins different element
		  bool operator!=(const Iter& it) const
			{return v != it.v;}
		  
		  // moves iterator to list's next element
		  self_type operator++() {
			  v = v->next;
			  return *this;
		  }

		  // moves iterator to list's prev element
		  self_type operator--() {
			  v = v->prev;
			  return *this;
		  }

		  friend class double_list;

	  private:
		  // iterator has pointer to list element
		  d_list_elem * v;
	  };


public:
	// Used Double Linked List interface implemented in project 2a

	/* List constructor. */
	double_list();

	/* List deconstructor. */
	~double_list();

	/* List data observation */
	int d_list_get_data1(d_list_elem *);
	int d_list_get_data2(d_list_elem *);
	string d_list_get_data3(d_list_elem *);

	/* List traversal. */
	d_list_elem *d_list_next(d_list_elem *);
	d_list_elem *d_list_prev(d_list_elem *);

	d_list_elem *d_list_head(void);
	d_list_elem *d_list_tail(void);

	d_list_elem *d_list_front(void);
	d_list_elem *d_list_back(void);

	/* List insertion. */
	void d_list_insert_front(d_list_elem *);
	void d_list_insert_back(d_list_elem *);
	void d_list_insert_before(d_list_elem *, d_list_elem *);
	void d_list_insert_after(d_list_elem *, d_list_elem *);

	/* List replacement. */
	void d_list_replace(d_list_elem*, d_list_elem *);

	/* List removal. */
	void d_list_remove(d_list_elem *);

	/* List properties. */
	bool d_list_empty(void);

	// To use find method, set begin() so iterator can point to front 
	Iter begin() {
		return Iter(head->next);
	}

	// To use find method, set end() so iterator can point to tail
	Iter end() {
		return Iter(tail);
	}
};

#endif /* __DOUBLE_LIST_H__ */