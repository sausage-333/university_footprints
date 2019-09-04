/*
* Skeleton code for project 3 in EE205 2018 Fall KAIST
* Created by Yoonpyo Koo.
*/

#include "avl_tree.h"
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

/* Return the height of the tree. Remember external nodes are valid nodes. 
* Suppose we have a tree as follows. * means an external node.
*           a
*         /   \
*        b     c
*       / \   / \
*      d   * *   *
*     / \
*    *   *
* Then this tree has the height of 3
*
* ### Already implemented.
*/
template <class T>
int AVLTree<T>::height(AVLNode<T> *n) {
	return n->height;
}

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
template <class T>
void AVLTree<T>::update_height(AVLNode<T> *n) {
	if (is_external(n)) {
		n->height = 0;
	}
	else {
		int lh = height(n->leftChild);
		int rh = height(n->rightChild);

		n->height = (lh >= rh ? lh : rh) + 1;
	}
}

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
void AVLTree<T>::inorder_print(AVLNode<T> *n) {

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
void AVLTree<T>::preorder_print(AVLNode<T> *n) {

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

/* Refer to the supplementary PPT file. */
template <class T>
void AVLTree<T>::balance(AVLNode<T> *n) {
	// Tree가 비었을 때
	if (is_external(root)) {
		cout << "Tree is empty." << endl;
		return;
	}

	// n이 root의 위까지 가서 더 이상 할 것이 없을 때
	if (n == NULL) {
		return;
	}

	// 시작하기 전에 node의 height을 update하고 시작하자
	update_height(n);

	// n의 Left child와 right child의 높이 차이를 구하자
	// 각 rotation 작업이 끝난 이후에는 새 n의 부모에서도 balance 함수 호출

	// n의 right child가 더 클 때
	if (height(n->leftChild) - height(n->rightChild) <= -2) {

		AVLNode<T> *nrc = n->rightChild;
		AVLNode<T> *new_n;

		// right - right
		// nrc의 child들의 높이가 서로 같으면 right - right의 경우와 같다.
		if (height(nrc->leftChild) <= height(nrc->rightChild)) {
			new_n = rotate_left(n);

			// Update root to new node
			if (is_root(new_n)) {
				root = new_n;
			}

			balance(new_n->parent);
		}
		// right - left
		else {
			rotate_right(nrc);
			new_n = rotate_left(n);

			if (is_root(new_n)) {
				root = new_n;
			}

			balance(new_n->parent);
		}
	}
	// n의 left child가 더 클 때
	else if (height(n->leftChild) - height(n->rightChild) >= 2) {
		AVLNode<T> *nlc = n->leftChild;
		AVLNode<T> *new_n;

		// left - left
		if (height(nlc->leftChild) > height(n->rightChild)) {
			new_n = rotate_right(n);

			if (is_root(new_n)) {
				root = new_n;
			}

			balance(new_n->parent);
		}
		// left - right
		// nlc의 child들의 높이가 서로 같으면 left - right의 경우와 같다.
		else {
			rotate_left(nlc);
			new_n = rotate_right(n);

			if (is_root(new_n)) {
				root = new_n;
			}

			balance(new_n->parent);
		}
	}
	// node n에 대해서 balance할 때 n의 부모에 대해서도 balance 호출
	else {
		balance(n->parent);
	}
}

/* For your reference, the function has already been implemented. */
template <class T>
AVLNode<T>* AVLTree<T>::rotate_right(AVLNode<T> *n) {
	AVLNode<T> *x = n->leftChild;

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
	n->parent = x;

	/* the order of updates is important */
	update_height(n);
	update_height(x);

	return x;
}

/* Refer to the supplementary PPT file. And right above ↑↑↑ */
template <class T>
AVLNode<T>* AVLTree<T>::rotate_left(AVLNode<T> *n) {
	AVLNode<T> *x = n->rightChild;

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
	n->parent = x;

	/* the order of updates is important */
	update_height(n);
	update_height(x);

	return x;
}

/* 
* Refer to page 6 of the lecture note 'SearchTrees-BST_AVL'.
* CAUTION: You HAVE TO implement this function the way described in the lecture note.
* Use string::compare function for comparison between two keys.
*/
template <class T>
AVLNode<T>* AVLTree<T>::search(string key) {
	AVLNode<T> *compare_node = root;

	while (is_external(compare_node) == false) {
		
		// 대소문자에 구애받지 않는 key 비교
		string upper_key = key;
		string upper_cmp_node_key = compare_node->key;

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

/*
* I have also implemented this function for your reference and convenience. 
* 조교 자비 오지고 지리고 렛잇고 아리랑 고개를 넘ㅇ...
*/
template <class T>
bool AVLTree<T>::insert(string key) {

	AVLNode<T> *n = search(key);

	if (is_external(n)) {

		n->key = key;
		n->leftChild = new AVLNode<T>("", n);
		n->rightChild = new AVLNode<T>("", n);

		balance(n);

		return true;
	}
	else
		return false; // the key already exists
}

/* 
* Remove a node. Return true if successful(if the key exists), false otherwise. 
* Refer to page 8~9, 22~23 of the lecture note 'SearchTrees-BST_AVL'.
* CAUTION: You HAVE TO implement this function the way described in the lecture note.
*/
template <class T>
bool AVLTree<T>::remove(string key) {

	AVLNode<T> *n = search(key);
	AVLNode<T> *d;	// Node to delete.
	AVLNode<T> *de;  // External node to delete. (Usually left node)
	AVLNode<T> *r;   // Node to replace.

	// If root is empty or found node is external
	// there's no such node that matches with given key.
	if (is_external(n)) {
		return false;
	}

	// TASK 1: Find node to delete and replace.
	// CASE 1: n has only external children
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

			delete de;
			delete d;

			return true;
		}
	}

	// From now on, d cannot be root

	// CASE 1: Normal case
	if (d->parent->leftChild == d) {
		d->parent->leftChild = r;
	}
	else {
		d->parent->rightChild = r;
	}
	r->parent = d->parent;

	delete de;
	delete d;

	balance(r->parent);

	return true;
}
	
/* 
* You need to explicitly instantiate the template to use it in the main function.
* Instantiate here if you need to.
* e.g., 
* template class AVLTree<Your_linkedlist_class>;
*/
template class AVLTree<list<int>>;

/* You can do it! */

/* Additional Function for AVLTree<T> search Fucntion. */