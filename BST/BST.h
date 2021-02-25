#ifndef BST_H

#define BST_H

#include "Node.h"
#include <iostream>
#include <vector>

template <class T>
class BST {
public:
	BST();
	
	~BST();

	Node<T>* getRoot();

	T find(const T& val);

	std::vector<T> findRange(const T& low, const T& up);

	void add(const T& val);

	void remove(const T& val);

	bool isEmpty();

	void removeAll(Node<T>* node);
	
	std::vector<Node<T>*> preorder();
	std::vector<Node<T>*> inorder();
	std::vector<Node<T>*> postorder();

	void printValues();

private:
	Node<T>* root;
	int nodeCount;

	void helperForRange(Node<T>* node, const T& low, const T& up, std::vector<T> & out);

	Node<T>* helperAdd(Node<T>* node, const T& val);

	void helperForPre(Node<T>* node, std::vector<Node<T>*>& v);
	void helperForIn(Node<T>* node, std::vector<Node<T>*>& v);
	void helperForPost(Node<T>* node, std::vector<Node<T>*>& v);

	Node<T>* Successor(Node<T>* node);

	Node<T>* findHelper(Node<T>* node, const T& val);

	Node<T>* removeHelper(Node<T>* node, const T& val);
};


template <class T>
BST<T>::BST() {
	root = nullptr;
	nodeCount = 0;
}

template <class T>
BST<T>::~BST() {
	removeAll(root);
	root = nullptr;
	nodeCount = 0;
}

template <class T>
Node<T>* BST<T>::getRoot() {
	return root;
}

template <class T>
T BST<T>::find(const T& val) {
	Node<T>* found = findHelper(root, val);
	if (!found) {//if not found
		return -1;
	}
	return found->val;
}

template <class T>
Node<T>* BST<T>::findHelper(Node<T>* node, const T& val) {
	if (!node || node->val == val) //if does not exist or found
		return node;

	else if (node->val >= val) { // go left
		return findHelper(node->left, val);
	}

	else if (node->val < val) { // go right
		return findHelper(node->right, val);
	}
}

template <class T>
std::vector<T> BST<T>::findRange(const T& low, const T& up) {
	std::vector<T> output;
	helperForRange(root,low, up, output);
	return output;
}

template <class T>
void BST<T>::helperForRange(Node<T>* node,const T& low, const T& up, std::vector<T>& out) {
	if (!node) return;
	// works like inorder
	if (node->val >= low) { // go left 
		helperForRange(node->left, low, up, out);
	}

	if(node->val >= low && node->val <= up) // if given node lies in range
		out.push_back(node->val);

	if (node->val <= up) { // go right 
		helperForRange(node->right, low, up, out);
	}
}


template <class T>
void BST<T>::add(const T& val) {
	root = helperAdd(root, val);
	nodeCount++;
}

template <class T>
Node<T>* BST<T>::helperAdd(Node<T>* node, const T& val) {
	if (!node) {//if suitable place has founded
		Node<T>* add = new Node<T>(val, nullptr, nullptr);
		node = add;
		return node;
	}
	else if (node->val >= val) { // go left
		node->left = helperAdd(node->left, val);
	}
	else if (node->val < val) { // go right
		node->right = helperAdd(node->right, val);
	}

	return node;
}

template <class T>
void BST<T>::remove(const T& val) {
	root = removeHelper(root,val);
}


template <class T>
Node<T>* BST<T>::removeHelper(Node<T>* node, const T& val) {
	if (!node) return nullptr;

	if (node->val > val) { // go to left
		node->left = removeHelper(node->left, val);
	}
	else if (node->val < val) { // go to right
		node->right = removeHelper(node->right, val);
	}
	else if(node->val == val) { // found
		if (!node->left && !node->right) { // no children / leaf node
			delete node;
			node = nullptr;
			return node;
		}
		else if (!node->left) { //  right child exists
			Node<T>* tmp = node->right;
			delete node;
			return tmp;
		}
		else if (!node->right) { // left child exists
			Node<T>* tmp = node->left;
			delete node;
			return tmp;
		}
		else { // two children case 
			Node<T>* tmp = Successor(node->right); // find inorder successor
			node->val = tmp->val; // change datas
			root->right = removeHelper(root->right, tmp->val); // find and remove inorder successor
		}
	}
	return node;
}

//finds inorder successor
template <class T>
Node<T>* BST<T>::Successor(Node<T>* node){
	Node<T>* curr = node;

	while (curr && curr->left != nullptr) {
		curr = curr->left;
	}
	return curr;
}

//checks whether or not given tree is empty
template <class T>
bool BST<T>::isEmpty() {
	return root == nullptr;
}

// removes all nodes with postorder traversal
template <class T>
void BST<T>::removeAll(Node<T>* node) {
	if (!node) return;
	removeAll(node->left);
	removeAll(node->right);
	delete node;
	node = nullptr;
}

template <class T>
std::vector<Node<T>*> BST<T>::preorder() {
	std::vector<Node<T>*> v;
	helperForPre(root, v);
	return v;
}

template <class T>
void BST<T>::helperForPre(Node<T>* node, std::vector<Node<T>*>& v) {
	if (!node) return;

	v.push_back(node);

	helperForPre(node->left, v);

	helperForPre(node->right, v);
}

template <class T>
std::vector<Node<T>*> BST<T>::inorder() {
	std::vector<Node<T>*> v;
	helperForIn(root, v);
	return v;
}

template <class T>
void BST<T>::helperForIn(Node<T>* node, std::vector<Node<T>*>& v) {
	if (!node) return;

	helperForIn(node->left, v);

	v.push_back(node);

	helperForIn(node->right, v);
}

template <class T>
std::vector<Node<T>*> BST<T>::postorder() {
	std::vector<Node<T>*> v;
	helperForPost(root, v);
	return v;
}

template <class T>
void BST<T>::helperForPost(Node<T>* node, std::vector<Node<T>*>& v) {
	if (!node) return;

	helperForIn(node->left, v);

	helperForIn(node->right, v);

	v.push_back(node);
}
template <class T>
void BST<T>::printValues() {
	std::vector<Node<T>*> v;
	v = inorder();
	for (int i = 0; i < v.size(); i++) {
		std::cout << v[i]->val << ' ';
	}
	std::cout << std::endl;
}
#endif // !BST_H

