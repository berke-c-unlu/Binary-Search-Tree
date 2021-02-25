#ifndef NODE_H

#define NODE_H

template <class T>
class Node {

public:
	Node() { // constructor
		val = 0;
		right = nullptr;
		left = nullptr;
	}
	Node(const T& val) { // constructor with value
		this->val = val;
		right = nullptr;
		left = nullptr;
	}
	Node(const T& val, Node<T>* left, Node<T>* right) { // constructor with every value
		this->val = val;
		this->right = right;
		this->left = left;
	}
	T val; // data
	Node<T>* right; // right child
	Node<T>* left; // left child
};


#endif // !NODE_H

