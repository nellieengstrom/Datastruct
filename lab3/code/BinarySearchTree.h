#pragma once

#include <iostream>
#include <iomanip>
#include <cassert>  // used in node.h

#include "dsexceptions.h"

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree {
private:
	struct Node;  // nested class defined in node.h


public:
	class Iterator;  // Exercise 2: nested class to be defined in Iterator.h

	Iterator begin() { //The iterator begin at the smallest value
		if (isEmpty()) { return end(); }
		return Iterator(findMin(root->left));
	}

	Iterator end() { //The iterator end when reaching a nullptr
		return Iterator();
	}

	Iterator find(const Comparable& x) {
		Node* containsX = contains(x, root);
		if (containsX == nullptr) {
			return end();
		}
		return Iterator(containsX);
	}

	BinarySearchTree() : root{ nullptr } {
	}

	/**
	 * Copy constructor
	 */
	BinarySearchTree(const BinarySearchTree& rhs) : root{ clone(rhs.root) } {
	}

	/**
	 * Destructor for the tree
	 */
	~BinarySearchTree() {
		makeEmpty();
	}

	/**
	 * Copy assignment: copy and swap idiom
	 */
	BinarySearchTree& operator=(BinarySearchTree _copy) {
		std::swap(root, _copy.root);
		return *this;
	}

	/**
	* get parent of the node with value x
	* Throw UnderflowException if not found.
	*/
	const Comparable& get_parent(Comparable x) const {
		Node* ptr = contains(x, root);
		if (ptr != nullptr) { // value x is in the tree
			if (ptr->parent == nullptr) {
				return Comparable{};
			}
			else {
				return ptr->parent->element;
			}
		}
		else { // Value x is not in the tree
			return Comparable{};
		}
	}


	std::pair<Comparable, Comparable> find_pred_succ(const Comparable& x) const {
		Comparable pred; //the smaller
		Comparable succ; //the larger

		bool xIsSmaller = true;
		bool xIsBigger = true;

		Node* t = root;

		while (t != nullptr) {
			if (t->element > x) { // Node element bigger traverse left in tree
				succ = t->element;
				t = t->left;
				xIsBigger = false;
			}
			else if (t->element < x) { // Node element smaller traverse right in tree
				pred = t->element;
				t = t->right;
				xIsSmaller = false;
			}
			else { // t->element == x
				if (t->left != nullptr) {
					pred = (findMax(t->left)->element);
				}

				else if (xIsSmaller) {
					pred = t->element;
				}

				if (t->right != nullptr) {
					succ = (findMin(t->right)->element);
				}

				else if (xIsBigger) {
					succ = t->element;
				}
				break;
			} //case if x is smaller then tree
			if (t == nullptr && xIsSmaller) {
				pred = x;
			}//case if x is bigger then tree
			if (t == nullptr && xIsBigger) {
				succ = x;
			}

		}
		return std::pair<Comparable, Comparable>(pred, succ);
	}

	/**
	 * Find the smallest item in the tree.
	 * Throw UnderflowException if empty.
	 */
	const Comparable& findMin() const {
		if (isEmpty()) {
			throw UnderflowException{};
		}

		return findMin(root)->element;
	}

	/**
	 * Find the largest item in the tree.
	 * Throw UnderflowException if empty.
	 */
	const Comparable& findMax() const {
		if (isEmpty()) {
			throw UnderflowException{};
		}

		return findMax(root)->element;
	}

	/**
	 * Returns true if x is found in the tree.
	 */
	bool contains(const Comparable& x) const {
		return (contains(x, root) != nullptr);
	}

	/**
	 * Test if the tree is logically empty.
	 * Return true if empty, false otherwise.
	 */
	bool isEmpty() const {
		return root == nullptr;
	}

	/**
	 * Print the tree contents in sorted order.
	 */
	void printTree(std::ostream& out = std::cout) const {
		if (isEmpty()) {
			out << "Empty tree";
		}
		else {
			preorder(root, out);
		}
	}

	/**
	 * Make the tree logically empty.
	 */
	void makeEmpty() {
		root = makeEmpty(root);
	}

	/**
	 * Insert x into the tree; duplicates are ignored.
	 */
	void insert(const Comparable& x) {
		root = insert(x, root);
	}

	/**
	 * Remove x from the tree. Nothing is done if x is not found.
	 */
	void remove(const Comparable& x) {
		root = remove(x, root);
	}

	/** Return total number of existing nodes
	 *
	 * Used for debug purposes
	 */
	static int get_count_nodes() {
		return Node::count_nodes;
	}

private:
	Node* root;

	/**
	 * Private member function to insert into a subtree.
	 * x is the item to insert.
	 * t is the node that roots the subtree.
	 * Return a pointer to the node storing x.
	 */
	Node* insert(const Comparable& x, Node* t, Node* parent = nullptr) {
		if (t == nullptr) {
			t = new Node{ x, nullptr, nullptr, parent };
		}
		else if (x < t->element) {
			t->left = insert(x, t->left, t);
		}
		else if (t->element < x) {
			t->right = insert(x, t->right, t);
		}
		else {
			;  // Duplicate; do nothing
		}
		return t;
	}

	/**
	 * Private member function to remove from a subtree.
	 * x is the item to remove.
	 * t is the node that roots the subtree.
	 * Return a pointer to the new root of the subtree that had root x
	 */
	Node* remove(const Comparable& x, Node* t) {
		if (t == nullptr) {
			return t;  // Item not found
		}

		else if (x < t->element) {
			t->left = remove(x, t->left);
		}

		else if (t->element < x) {
			t->right = remove(x, t->right);
		}

		else if (t->left != nullptr && t->right != nullptr) {  // Two children
			t->element = findMin(t->right)->element;
			t->right = remove(t->element, t->right);
		}

		else {
			Node* oldNode = t; //Store the value t we want to delete to access its parent later when relinking
			t = (t->left != nullptr) ? t->left : t->right;
			if (t != nullptr) {
				t->parent = oldNode->parent;
			}
			delete oldNode; //If t has no children, it can be deleted without relink the parent
		}

		return t;
	}

	/**
	 * Private member function to find the smallest item in a subtree t.
	 * Return node containing the smallest item.
	 */
	Node* findMin(Node* t) const {
		if (t == nullptr) {
			return nullptr;
		}
		if (t->left == nullptr) {
			return t;
		}

		// Tail recursion can be easily replaced by a loop
		return findMin(t->left);  // recursive call
	}

	/**
	 * Private member function to find the largest item in a subtree t.
	 * Return node containing the largest item.
	 */
	Node* findMax(Node* t) const {
		if (t != nullptr) {
			while (t->right != nullptr) {
				t = t->right;
			}
		}
		return t;
	}

	/**
	 * Private member function to test if an item is in a subtree.
	 * x is item to search for.
	 * t is the node that roots the subtree.
	 * Return a pointer to the node storing x, if x is found
	 * Otherwise, return nullptr
	 */
	Node* contains(const Comparable& x, Node* t) const {
		if (t == nullptr) {
			return t;
		}
		else if (x < t->element) {
			return contains(x, t->left);
		}
		else if (t->element < x) {
			return contains(x, t->right);
		}
		else {
			return t;  // Match
		}
	}
	/****** NONRECURSIVE VERSION*************************
	Node *contains(const Comparable &x, Node *t) const {
		while (t != nullptr) {
			if (x < t->element) {
				t = t->left;
			} else if (t->element < x) {
				t = t->right;
			} else {
				return t;  // Match
			}
		}
		return t;  // No match
	}
	*****************************************************/

	/**
	 * Private member function to make subtree empty.
	 */
	Node* makeEmpty(Node* t) {
		if (t != nullptr) {
			makeEmpty(t->left);
			makeEmpty(t->right);
			delete t;
		}
		return nullptr;
	}

	/**
	 * Private member function to print a subtree rooted at t in sorted order.
	 * In-order traversal is used
	 */
	void inorder(Node* t, std::ostream& out) const {
		if (t != nullptr) {
			inorder(t->left, out);
			out << t->element << '\n';
			inorder(t->right, out);
		}
	}

	/**
	* Private member function to print a subtree rooted
	* pre-order traversal is used
	* Indetation is used showing the nodes depth in the tree
	*/
	void preorder(Node* t, std::ostream& out, int depth = 0) const {
		if (t != nullptr) {
			for (int i = 0; i < depth * 2; i++) {
				out << " ";
			}
			out << t->element << '\n';
			++depth;
			preorder(t->left, out, depth);
			preorder(t->right, out, depth);
		}
	}


	/**
	 * Private member function to clone subtree.
	 */
	Node* clone(Node* t, Node* parent = nullptr) const {
		if (t == nullptr) {
			return nullptr;
		}
		else {
			//Do not clone the parent because the parent has already been created in the previous step
			Node* temp = new Node(t->element);
			temp->parent = parent;
			temp->left = clone(t->left, temp);
			temp->right = clone(t->right, temp);

			return temp;
		}
	}

	/* Returns a pointer to the node storing the successor of the value stored in a given node t*/
	Node* find_successor(Node* t) const {
		Node* successor = t;

		if (t != nullptr) {
			if (t->right != nullptr) {
				successor = findMin(t->right);
			}

			else { //if t->right is nullptr
				while (successor->parent != nullptr && t->element >= successor->element) {
					successor = successor->parent;
				}

				if (successor->element < t->element) {
					successor = nullptr;
				}
			}
		}

		return successor;
	}


	/* Returns a pointer to the node storing the predecessor of the value stored in a given node t*/
	Node* find_predecesor(Node* t) const {
		Node* predecesor = t;

		if (t != nullptr) {
			if (t->left != nullptr) {
				predecesor = findMax(t->left);
			}

			else { //if t->left is nullptr
				while (predecesor->parent != nullptr && t->element <= predecesor->element) {
					predecesor = predecesor->parent;
				}

				if (predecesor->element > t->element) {
					predecesor = nullptr;
				}
			}
		}

		return predecesor;
	}
};

// Include definitions of the nested classes
#include "node.h"
#include "iterator.h"