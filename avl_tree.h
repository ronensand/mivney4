#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <functional>

class ChildExistsException : public std::exception {
	const char* what() const noexcept override {
		return "AVLTreeNode already has a child there";
	}
};

class TreeNodeNotFoundException : public std::exception {
	const char* what() const noexcept override {
		return "TreeNode with the given value was not found";
	}
};

class AlreadyExistsException : public std::exception {
    const char* what() const noexcept override {
        return "Already exists";
    }
};

template <class T, class Pred, class Less>
class AVLTreeNode {
	int balance_factor() {
		int leftHeight = left != nullptr ? left->height : -1;
		int rightHeight = right != nullptr ? right->height : -1;
		return leftHeight - rightHeight;
	}

	void update_height() {
		int leftHeight = left != nullptr ? left->height : -1;
		int rightHeight = right != nullptr ? right->height : -1;
		int max = leftHeight > rightHeight ? leftHeight : rightHeight;
		height = max + 1;
	}

	void set_child(AVLTreeNode* tree) {
		if (less(tree->data, data) && left == nullptr) {
			set_left(tree);
		}
		else if (less(data, tree->data) && right == nullptr) {
			set_right(tree);
		} else {
			throw ChildExistsException();
		}
	}

	void set_left(AVLTreeNode* tree) {
		left = tree;
		if (nullptr != tree) tree->parent = this;
		update_height();
	}

	void set_right(AVLTreeNode* tree) {
		right = tree;
		if (nullptr != tree) tree->parent = this;
		update_height();
	}

	AVLTreeNode* roll_right() {
		AVLTreeNode* newRoot = left;
		set_left(newRoot->right);
		newRoot->set_right(nullptr);
		swap_with_child(newRoot);
		return newRoot;
	}

	AVLTreeNode* roll_left() {
		AVLTreeNode* newRoot = right;
		set_right(newRoot->left);
		newRoot->set_left(nullptr);
		swap_with_child(newRoot);
		return newRoot;
	}

	AVLTreeNode* balance() {
		int balanceFactor = balance_factor();
		if (balanceFactor * balanceFactor < 4) {
			update_height();
			return this;
		}

		if (2 == balanceFactor) { // LL + LR
			if (left->balance_factor() < 0) {
				left->roll_left(); // LR
			}
			return roll_right(); // Both
		} else { // RR + RL
			if (right->balance_factor() > 0) {
				right->roll_right(); // RL
			}
			return roll_left(); // Both
		}
	}

	AVLTreeNode* remove_node() {
		AVLTreeNode<T, Pred, Less>* toRemove = this;
		if (left != nullptr && right != nullptr) {
			AVLTreeNode* next = right;
			while (next->left != nullptr) {
				next = next->left;
			}

			T temp = data;
			data = next->data;
			next->data = temp;
			toRemove = next;
		}

		AVLTreeNode* newChild = toRemove->left == nullptr ?
		                    toRemove->right : toRemove->left;
		AVLTreeNode* oldParent = toRemove->parent;
		if (oldParent != nullptr) oldParent->change_child(toRemove, newChild);
		else if(nullptr != newChild) newChild->parent = nullptr;
		toRemove->right = nullptr;
		toRemove->left = nullptr;
		delete toRemove;
		return oldParent == nullptr ? newChild : oldParent;
	}

	void change_child(AVLTreeNode *currentChild, AVLTreeNode *newChild) {
		if (left == currentChild) {
			set_left(newChild);
		}

		if (right == currentChild) {
			set_right(newChild);
		}
	}

	void swap_with_child(AVLTreeNode* child) {
		if (parent != nullptr) {
			parent->change_child(this, child);
		} else {
			child->parent = nullptr;
		}

		child->set_child(this);
	}

    template <typename S>
	AVLTreeNode* search(const S& value) {
		if (pred(data, value)) {
			return this;
		}

		AVLTreeNode* next = nullptr;
		next = less(data, value) ? right : left;

		if (nullptr == next) {
			return this;
		}
		return next->search(value);
	}

public:
    T data;
    Pred pred;
    Less less;
    AVLTreeNode* parent;
    AVLTreeNode* left;
    AVLTreeNode* right;
    int height;

	AVLTreeNode(const T& data, Pred pred, Less less, AVLTreeNode* parent = nullptr, AVLTreeNode* left = nullptr, AVLTreeNode* right = nullptr) :
		data(data), pred(pred), less(less), parent(parent), left(left), right(right), height(0) {}

	virtual ~AVLTreeNode(){
	    if (right) delete right;
	    if (left) delete left;
	};

    template <typename S>
	AVLTreeNode* find(const S& value) {
		AVLTreeNode* tree = search(value);
		if (!pred(tree->data, value)){
			throw TreeNodeNotFoundException();
		}
		return tree;
	}

	AVLTreeNode* insert(const T& value) {
		AVLTreeNode *position = search(value);
		if (pred(position->data, value)) {
			throw AlreadyExistsException();
		}

		auto newTree = new AVLTreeNode(value, pred, less, position, nullptr, nullptr);
		position->set_child(newTree);

		while(nullptr != position->parent) {
			position = position->parent;
			// This only runs update_height() to every tree except the first
			position->balance();
		}

		return position;
	}

    template <typename S>
	AVLTreeNode* remove(const S& value) {
		AVLTreeNode* position = search(value);
		if (!pred(position->data,value)) {
			throw TreeNodeNotFoundException();
		}

		AVLTreeNode* tree = position->remove_node();
		AVLTreeNode* root = tree;

		while(nullptr != tree) {
			root = tree->balance();
			tree = root->parent;
		}

		return root;
	}

    template <typename Func>
    void inorder(Func func){
        if (left) left->inorder(func);
        func(data);
        if (right) right->inorder(func);
    }
};

template <class T, class Pred, class Less>
class AVLTree {
public:
    explicit AVLTree(Pred pred = Pred(), Less less = Less()) : _root(nullptr), _less(less), _pred(pred) {};
    ~AVLTree() {
        if (_root) delete _root;
    }

    void insert(const T& data) {
        if (nullptr == _root){
            _root = new AVLTreeNode<T, Pred, Less>(data, _pred, _less, nullptr, nullptr, nullptr);
        }
        else{
            _root = _root->insert(data);
        }
    }

    template <typename S>
    void remove(const S& data) {
        if (_root) {
            _root = _root->remove(data);
            return;
        }

        throw TreeNodeNotFoundException();
    }

    template <typename S>
    T& find(const S& data) {
        if (_root) {
            return _root->find(data)->data;
        }

        throw TreeNodeNotFoundException();
    }

    template <typename Func>
    void inorder(Func func){
        if (_root){
            _root->inorder(func);
        }
    }


private:
    AVLTreeNode<T, Pred, Less> * _root;
    Less _less;
    Pred _pred;
};

#endif //AVL_TREE_H

