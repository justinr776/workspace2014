//
//  GVBinaryTree.hpp

#ifndef CS263_BinaryTree
#define CS263_BinaryTree
#include <stdexcept>
#include <ostream>
using namespace std;
namespace gvsu {
template<typename Z>
class BinaryTree {
private:
	class Node;
	/* instance variables */
	Node *root; /* pointer to the root node */
	/* inner class(es) */
	class Node {
	public:
		Z data;
		Node *left; /* pointer to the left child */
		Node *right; /* pointer to the right child */
	};
public:
	/* member functions */

	BinaryTree() {
		root = nullptr;
	}

	~BinaryTree() {
		if (root == nullptr)
			return;
		clearAll(root);
	}

	int numberOfNodes() const {
		return numberNodes(root);
		/* in your recursive private function, make sure to avoid duplicate recursive calls */

	}

	/* Definition: a leaf node has no children */
	int numberOfLeaves() const {

		/* in your recursive private function, make sure to avoid duplicate recursive calls */
		return 0;
	}

	/* Definition:  a full node has two children */
	int numberOfFullNodes() const {
		return numFullNodes(root);
		/* in your recursive private function, make sure to avoid duplicate recursive calls */
	}

	/* copy assignment */
	BinaryTree& operator=(const BinaryTree& rhs) {
		clearAll(root); /* required to avoid mem leak */
		root = duplicate(rhs.root);
		return *this;
	}

	/* move assignment */
	BinaryTree& operator=(BinaryTree&& rhs) {
		clearAll(root);
		this->root = rhs.root;
		rhs.root = nullptr;
		return *this;
	}

	bool contains(const Z& key) const {
		return is_element_of(root, key);
	}

	bool insert(const Z& key) {
		return insert_into(root, key);
	}

	void remove(const Z& key) {
		remove_from(root, key);
	}

	vector<Z> levelOrder() const {
		vector<Z> output;
		/* The returned string must be separated by commas */
		FAIL("I have to complete Question 4.40 by invoking a private function");
		return output;
	}

	/* Use the following print for debugging. To call this function,
	 * use one of the following invocations from your "main" function:
	 (fill in the blank with the name of you tree object)

	 ______.print();
	 ______.print(std::cout);
	 ______.print(your_own_output_stream);

	 The last example can be used, for instance, to save the output
	 to a file (by first creating an ofstream object)

	 */
	void print(ostream& os = std::cout) const {
		print_from(root, os, "");
	}

private:

	/* TODO: add as many as private functions as you wish */
	int numberNodes(Node* pos) const {
		int count = 0;
		if (pos) {
			if (pos->left != nullptr)
				count += numberNodes(pos->left);
			if (pos->right != nullptr)
				count += numberNodes(pos->right);
			return count;
		}
		return count;
	}

	int numFullNodes(Node* pos) const {
		int count = 0;
		if (pos) {
			if (pos->left != nullptr && pos->right != nullptr)
				count++;
			if (pos->left != nullptr)
				count += numberNodes(pos->left);
			if (pos->right != nullptr)
				count += numberNodes(pos->right);
			return count;
		}
		return count;
	}

	Node * duplicate_from(Node *theOtherNode) {
		if (theOtherNode->data == root->data)
			return root;
		FAIL("I have to complete duplicate");
		return nullptr;
	}

	bool is_element_of(Node *pos, const Z& key) const {
		if (pos) { //TODO: Fix the return false ahead of checking all points.
			if (pos->data == key)
				return true;
			if (pos->right != nullptr)
				is_element_of(pos->right, key);
			if (pos->left != nullptr)
				is_element_of(pos->left, key);
			if (pos->left == nullptr && pos->right == nullptr)
				return false;
		}
		return false;
	}

	bool insert_into(Node*& pos, const Z& key) const {
		if (pos) {
			if (pos->data == key)
				return false;
			if (pos->data > key) {
				if (pos->left != nullptr)
					return insert_into(pos->left, key);
				else {
					Node* in = new Node();
					in->data = key;
					in->left = nullptr;
					in->right = nullptr;
					pos->left = in;
					return true;
				}
			} else {
				if (pos->right != nullptr)
					return insert_into(pos->right, key);
				else {
					Node* in = new Node();
					in->data = key;
					in->left = nullptr;
					in->right = nullptr;
					pos->right = in;
					return true;
				}
			}
		} else {
			pos = new Node();
			pos->data = key;
			pos->left = nullptr;
			pos->right = nullptr;
			return true;
		}
		return false;
	}

	void remove_from(Node*& pos, const Z& key) const {
		if (pos) {
			if (pos->data == key) {
				//TODO: Remove Node and properly update for nodes below..

			}
			if (pos->left != nullptr)
				remove_from(pos->left, key);
			if (pos->right != nullptr)
				remove_from(pos->left, key);
		}

	}

	void clearAll(Node* & pos) {
		if (pos) {
			if (pos->left != nullptr) {
				clearAll(pos->left);
			}
			if (pos->right != nullptr) {
				clearAll(pos->right);
			}
			delete pos;
		}

	}

	void print_from(Node *pos, ostream& os, const string&& path) const {
		if (pos) {
			print_from(pos->left, os, path + "L");
			os << pos->data << " (" << path << ")" << endl;
			print_from(pos->right, os, path + "R");
		}
	}
}
;

template<typename Z>
ostream& operator<<(ostream& os, const BinaryTree<Z>& t) {
	t.print(os);
	return os;
}

}

#endif
