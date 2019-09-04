/*
* Skeleton code for project 3 in EE205 2018 Fall KAIST
* Created by Wan Ju Kang.
*/

#include "rb_tree.h"
#include <iostream>
#include <string>

/*
* Include your linked list here
* e.g., #include "your_linked_list_header.h"
*/
#include <list>
#include <cctype>
#include <iterator>
#include <algorithm>

using namespace std;
/*
* You can do this! Feel free to ask to TA if you have anything unclear.
* I'm here to help you!
*/


/*
* Assign proper height value after operations on nodes.
* You will need this function in some functions.
* such as rotate_right(), rotate_left(), balance(), etc.
*
* Make sure all children have proper heights before you execute
* this function on a node.
*
* ### Already implemented.
*/

/* Print keys along inorder traversal. Separate each key by a single space.
* Do not print external node's key, which is an empty string. The input is
* the root node of the tree you want to tarverse.
* e.g.,
*           a
*         /   \
*        b     c
*       / \   / \
*      d   * *   *
*     / \
*    *   *
* Then this function should print "d b a c " (with no newline character).
*
*/
template <class T>
void RBTree<T>::inorder_print(RBNode<T> *n) {

	if (is_external(root)) {
		cout << "Tree is empty." << endl;
		return;
	}

	// external node에 접근했을 때
	if (is_external(n)) {
		return;
	}

	inorder_print(n->leftChild);

	cout << n->key << " ";

	inorder_print(n->rightChild);
}

/*
* Print keys along preorder traversal.
* The rule is the same as inorder_print(), except the order.
*/
template <class T>
void RBTree<T>::preorder_print(RBNode<T> *n) {

	if (is_external(root)) {
		cout << "Tree is empty." << endl;
		return;
	}

	// external node에 접근했을 때
	if (is_external(n) == true)  return;

	cout << n->key << " ";

	preorder_print(n->leftChild);

	preorder_print(n->rightChild);

}


template<class T>
RBNode<T>* RBTree<T>::find_uncle(RBNode<T>* n)
{
	// There's no uncle for root and root's children
	if (n != root && n != root->rightChild && n != root->leftChild) {
		// Find uncle for given node
		if (is_rightChild(n->parent)) {
			return n->parent->parent->leftChild;
		}

		else {
			return n->parent->parent->rightChild;
		}
	}

	else {
		cout << "There's no uncle for given node." << endl;
		return nullptr;
	}
}

template<class T>
RBNode<T>* RBTree<T>::find_sibling(RBNode<T>* n)
{
	// There's no sibling for root
	if (n != root) {
		// Find sibling for given node
		if (is_rightChild(n)) {
			return n->parent->leftChild;
		}

		else {
			return n->parent->rightChild;
		}
	}

	else {
		cout << "There's no sibling for given node." << endl;
		return nullptr;
	}
}

// Return false if n is root or leftChild.
// Following operation should not be called if n is root.
template<class T>
bool RBTree<T>::is_rightChild(RBNode<T>* n)
{
	if (n == root || n->parent->leftChild == n) {
		return false;
	}

	return true;
}

// Return false if n is root or rightChild.
// Following operation should not be called if n is root.
template<class T>
bool RBTree<T>::is_leftChild(RBNode<T>* n)
{
	if (n == root || n->parent->rightChild == n) {
		return false;
	}

	return true;
}

// Remedey for double red.
// This method should be only called when insertion is executed.
template <class T>
void RBTree<T>::remedey_double_red(RBNode<T> *n) {

	// Assume that this method is called from only red node.

	// CASE 0-1: n is root
	if (n == root) {
		root->color = BLACK;
		return;
	}

	// CASE 0-2: n is black or n's parent is black
	if (n->color == BLACK || n->parent->color == BLACK) {
		return;
	}

	// Children of root cannot reach here, because their parents is black.
	// From now on, both n and n's parent are red.
	
	// CASE 1: n's uncle is red
	if (find_uncle(n)->color == RED) {
		n->parent->color = BLACK;
		find_uncle(n)->color = BLACK;
		n->parent->parent->color = RED;

		// Call this funtion for n's grandparent
		remedey_double_red(n->parent->parent);
		return;
	}

	// CASE 2: n's uncle is black
	// CASE 2-1: (n's parent, n) = (left, left)
	if (is_leftChild(n->parent) && is_leftChild(n)) {
		rotate_right(n->parent->parent);
		
		n->parent->color = BLACK;
		n->parent->rightChild->color = RED;
	}

	// CASE 2-2: (n's parent, n) = (left, right)
	else if (is_leftChild(n->parent) && is_rightChild(n)) {
		rotate_left(n->parent);
		rotate_right(n->parent);

		n->color = BLACK;
		n->rightChild->color = RED;
	}

	// CASE 2-3: (n's parent, n) = (right, right)
	else if (is_rightChild(n->parent) && is_rightChild(n)) {
		rotate_left(n->parent->parent);

		n->parent->color = BLACK;
		n->parent->leftChild->color = RED;
	}

	// CASE 2-4: (n's parent, n) = (right, left)
	else {
		rotate_right(n->parent);
		rotate_left(n->parent);

		n->color = BLACK;
		n->leftChild->color = RED;
	}

	return;
}

// Remedey for double black.
// This method should be called in remove method.
template<class T>
void RBTree<T>::remedey_double_black(RBNode<T>* n)
{
	// Assume that this method is called from only double black node.

	// CASE 0: n is root.
	if (n == root) {
		n->color = BLACK;
		return;
	}

	// From now on, n cannot be root.

	RBNode<T>* s = find_sibling(n); // s, Sibling of double black node.

	// CASE 1: n's sibling is black, and at least one of sibling's children is red.
	if (s->color == BLACK &&
		s->rightChild->color == RED || s->leftChild->color == RED) {

		// CASE 1-1: (s, s' red child) = (right, right)
		// s' left child can be red node.
		if (is_rightChild(s) && s->rightChild->color == RED) {

			rotate_left(s->parent);

			s->rightChild->color = BLACK;
			s->color = s->leftChild->color;
			s->leftChild->color = BLACK;
			n->color = BLACK;

			return;
		}

		// CASE 1-2: (s, s' red child) = (right, left)
		else if (is_rightChild(s) && s->leftChild->color == RED) {

			rotate_right(s);
			rotate_left(s->parent->parent);

			s->parent->color = find_sibling(s)->color;
			find_sibling(s)->color = BLACK;
			n->color = BLACK;

			return;
		}

		// CASE 1-3: (s, s's red child) = (left, left)
		// s' right child can be red node.
		else if (is_leftChild(s) && s->leftChild->color == RED) {

			rotate_right(s->parent);

			s->leftChild->color = BLACK;
			s->color = s->rightChild->color;
			s->rightChild->color = BLACK;
			n->color = BLACK;

			return;
		}

		// CASE 1-4: (s, s' red child) = (left, right)
		else {

			rotate_left(s);
			rotate_right(s->parent->parent);

			s->parent->color = find_sibling(s)->color;
			find_sibling(s)->color = BLACK;
			n->color = BLACK;

			return;
		}

	}

	// CASE 2: n's sibling is black and sibling's both children are black.
	else if (s->color == BLACK &&
		     s->rightChild->color == BLACK && s->leftChild->color == BLACK) {

		s->color = RED;
		n->color = BLACK;

		if (s->parent->color == RED) {
			s->parent->color = BLACK;

			return;
		}

		s->parent->color = DOUBLE_BLACK;

		remedey_double_black(s->parent);

		return;
	}

	// CASE 3: n's sibling is red
	else {

		// CASE 3-1: s is left child.
		if (is_leftChild(s)) {
			rotate_right(s->parent);
			
			s->color = BLACK;
			s->rightChild->color = RED;

			// Now n's sibling becomes Black.
			// Let's call this function recursively.
			remedey_double_black(n);

			return;
		}

		// CASE 3-2: s is right child.
		else {
			rotate_left(s->parent);

			s->color = BLACK;
			s->leftChild->color = RED;

			// Now n's sibling becomes Black.
			// Let's call this function recursively.
			remedey_double_black(n);

			return;
		}

	}

}


/* For your reference, the function has already been implemented. */
template <class T>
RBNode<T>* RBTree<T>::rotate_right(RBNode<T> *n) {

	RBNode<T> *x = n->leftChild;

	n->leftChild = x->rightChild;
	n->leftChild->parent = n;

	x->rightChild = n;
	x->parent = n->parent;

	if (!is_root(n)) {
		if (n->parent->leftChild == n)
			n->parent->leftChild = x;
		else
			n->parent->rightChild = x;
	}
	// If n is root, we need to change root.
	else {
		root = x;
	}

	n->parent = x;

	return x;
}

/* Refer to the supplementary PPT file. And right above ↑↑↑ */
template <class T>
RBNode<T>* RBTree<T>::rotate_left(RBNode<T> *n) {

	RBNode<T> *x = n->rightChild;

	n->rightChild = x->leftChild;
	n->rightChild->parent = n;

	x->leftChild = n;
	x->parent = n->parent;

	if (!is_root(n)) {
		if (n->parent->leftChild == n)
			n->parent->leftChild = x;
		else
			n->parent->rightChild = x;
	}
	// If n is root, we need to change root.
	else {
		root = x;
	}

	n->parent = x;

	return x;
}

/*
* Refer to page 6 of the lecture note 'SearchTrees-BST_AVL'.
* CAUTION: You HAVE TO implement this function the way described in the lecture note.
* Use string::compare function for comparison between two keys.
*/
template <class T>
RBNode<T>* RBTree<T>::search(string key) {
	RBNode<T> *compare_node = root;

	while (is_external(compare_node) == false) {

		// 대소문자에 구애받지 않는 key 비교
		string upper_key(key);
		string upper_cmp_node_key(compare_node->key);
		
		// 비교하는 두 문자를 모두 대문자로 바꿈
		transform(upper_key.begin(), upper_key.end(), upper_key.begin(), ::toupper);
		transform(upper_cmp_node_key.begin(), upper_cmp_node_key.end(), upper_cmp_node_key.begin(), ::toupper);

		// compare_node의 key가 입력 key보다 작을 때
		if (upper_cmp_node_key.compare(upper_key) < 0) {
			compare_node = compare_node->rightChild;
		}
		// compare_node의 key가 입력 key와 같을 때
		else if (upper_cmp_node_key.compare(upper_key) == 0) {
			return compare_node;
		}
		// compare_node의 key가 입력 key보다 클 때
		else {
			compare_node = compare_node->leftChild;
		}
	}
	// compare_node가 주어진 key를 가지는 node를 찾지 못한 경우
	return compare_node;
}


// Insert 내부에서 Breaking rule을 처리할 지,
// 혹은 Balance 함수를 호출하는 것이 편한지 생각해봐야 함.

/*
* I have also implemented this function for your reference and convenience.
* 조교 자비 오지고 지리고 렛잇고 아리랑 고개를 넘ㅇ...
*/
template <class T>
bool RBTree<T>::insert(string key) {

	RBNode<T> *n = search(key);
	// If tree is empty, n will be the root

	if (is_external(n)) {

		n->key = key;
		n->leftChild = new RBNode<T>("", n);
		n->rightChild = new RBNode<T>("", n);

		// 삽입 시에 root 자리에 삽입되면 black으로 칠해야 함.
		if (n == root) {
			n->color = BLACK;

			// No need to remedey double red
			return true;
		}

		n->color = RED;

		remedey_double_red(n);

		return true;
	}
	// Given key already exists
	else
		return false;
}

/*
* Remove a node. Return true if successful(if the key exists), false otherwise.
* Refer to page 8~9, 22~23 of the lecture note 'SearchTrees-BST_AVL'.
* CAUTION: You HAVE TO implement this function the way described in the lecture note.
*/

template<class T>
bool RBTree<T>::remove(string key)
{
	RBNode<T> *n = search(key);
	RBNode<T> *d;	// Node to delete.
	RBNode<T> *de;  // External node to delete. (Usually left node)
	RBNode<T> *r;   // Node to replace.

	// If root is empty or found node is external
	// there's no such node that matches with given key.
	if (is_external(n)) {
		return false;
	}

	// TASK 1: Find node to delete and replace.
	// CASE 1: n has only external children.
	if (is_external(n->leftChild) && is_external(n->rightChild)) {
		d = n;
		de = n->leftChild;
		r = n->rightChild;

		// Cannot know whether d is right child or left child
	}

	// CASE 2: n has only 1 external child.
	else if (is_external(n->leftChild) || is_external(n->rightChild)) {
		
		d = n;

		if (is_external(n->rightChild)) {
			de = n->rightChild;
			r = n->leftChild;
		}
		else {
			de = n->leftChild;
			r = n->rightChild;
		}

		// Cannot know whether d is right child or left child
	}

	// CASE 3: n has only internal nodes.
	// We need to find inorder successor
	else {
		// CASE 3-1: Right child of n has external left child.
		if (is_external(n->rightChild->leftChild)) {
			d = n->rightChild;
			de = n->rightChild->leftChild;
			r = n->rightChild->rightChild;

			// d is right child
		}

		// CASE 3-2: Richt child of n has internal left child.
		// Starts from right child of n,
		// go only left path until it encounters external node.
		else {
			d = n->rightChild;

			while (!is_external(d->leftChild)) {
				d = d->leftChild;
			}
			de = d->leftChild;
			r = d->rightChild;

			// d is left child

			// Copy inorder successor's contents.
			n->key = d->key;
			/// Copy contents, not pointer.
			*(n->value) = *(d->value);
		}
	}

	// TASK 2: With combination of node's color, do something.
	// d: Deleting non-external node
	// de: Deleting external node
	// r: Replacing node
	
	// Assume that we don't know anything
	// about left or right information of d, de, r.

	// CASE 0: Special case that root is directly deleted.
	if (is_root(d)) {

		// CASE 0-1: Root is the only node that exists in the tree
		// Instead of deleting node, just make node contents initial state.
		if (is_external(r)) {
			d->key = "";
			delete d->value;
			d->value = new T;

			return true;
		}

		// CASE 0-2: There is another internal node.
		// This node must be red node and unique.
		// Make this node root, and color black.
		else {
			root = r;
			r->color = BLACK;
			
			delete de;
			delete d;

			return true;
		}
	}

	// From now on, d cannot be root.

	// CASE 1: r or d is red.
	// Delete d, and color r black.
	if (d->color == RED || r->color == RED) {

		if (is_leftChild(d)) {
			d->parent->leftChild = r;
		}
		else {
			d->parent->rightChild = r;
		}
		r->parent = d->parent;

		delete de;
		delete d;

		r->color = BLACK;

		return true;
	}

	// CASE 2: r and d both are black.
	// Delete d, and color r double black. And then, remedey this node.
	else {

		if (is_leftChild(d)) {
			d->parent->leftChild = r;
		}
		else {
			d->parent->rightChild = r;
		}
		r->parent = d->parent;

		delete de;
		delete d;

		r->color = DOUBLE_BLACK;
		remedey_double_black(r);

		return true;
	}
}

/*
* You need to explicitly instantiate the template to use it in the main function.
* Instantiate here if you need to.
* e.g.,
* template class AVLTree<Your_linkedlist_class>;
*/
template class RBTree<list<int>>;

/* You can do it! */

/* Additional Function for AVLTree<T> search Fucntion. */