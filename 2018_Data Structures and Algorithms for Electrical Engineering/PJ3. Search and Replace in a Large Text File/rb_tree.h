/*
* Skeleton code for project 3 in EE205 2018 Fall KAIST
* Created by Wan Ju Kang.
*/

#ifndef __RB_TREE_H__
#define __RB_TREE_H__

#include <string>
#include <iostream>

using namespace std;

/* 
* ############################CAUTION!!!############################
* You can define any additional features for your debugging purpose,
* but make sure you remove all of them before you submit this.
* ##################################################################
*/

enum Color {RED, BLACK, DOUBLE_BLACK};

template <class T>
class RBNode {
public:
	string key;
	T* value;
	Color color;

	class RBNode<T>* leftChild;
	class RBNode<T>* rightChild;
	class RBNode<T>* parent;

	RBNode(string k, RBNode<T> *p) {
		key = k;
		leftChild = NULL;
		rightChild = NULL;
		parent = p;
		value = new T;
		color = BLACK;
	}

	~RBNode() {
		// Explicit memory free for dynamic allocation
		delete value;
		value = NULL;
	}

	// I will handle dynamic allocation my self
	// rather than making copy constructor

};

template <class T>
class RBTree {
public:
	RBTree();
	~RBTree();
	void display();

	bool insert(string key);
	bool remove(string key);
	RBNode<T>* search(string key);

	bool is_external(RBNode<T> *n);
	bool is_root(RBNode<T> *n);

private:
	RBNode<T> *root;

	void remedey_double_red(RBNode<T> *n);
	void remedey_double_black(RBNode<T> *n);

	RBNode<T>* rotate_right(RBNode<T> *n);
	RBNode<T>* rotate_left(RBNode<T> *n);

	void inorder_print(RBNode<T> *n);
	void preorder_print(RBNode<T> *n);

	// Not available for root and root's chiledren
	RBNode<T>* find_uncle(RBNode<T> *n);

	// Not available for root
	RBNode<T>* find_sibling(RBNode<T> *n);
	bool is_rightChild(RBNode<T> *n);  
	bool is_leftChild(RBNode<T>* n);

};

template <class T>
RBTree<T>::RBTree() {
	root = new RBNode<T>("", NULL);   
}

template <class T>
RBTree<T>::~RBTree() {
	// Explicit memory free for dynamic allocation
	delete root;
}

template <class T>
void RBTree<T>::display() {
	if (is_external(root)) {
		cout << "Tree is empty." << endl;
		return;
	}
	cout << "root: " << root->key << endl;;
	inorder_print(root);
	cout << endl;
	preorder_print(root);
	cout << endl;
}

template <class T>
bool RBTree<T>::is_external(RBNode<T> *n) {

	return (n->leftChild == NULL && n->rightChild == NULL);
}

template <class T>
bool RBTree<T>::is_root(RBNode<T> *n) {

	// Root가 바뀌는 경우에는 root를 재설정 해줘야 함.
	return n->parent == NULL;
}

#endif /* __RB_TREE_H__ */