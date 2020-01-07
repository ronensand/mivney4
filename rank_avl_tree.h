#ifndef RANK_AVL_TREE_H
#define RANK_AVL_TREE_H

#include <functional>

class ChildExistsException : public std::exception {
	const char* what() const noexcept override {
		return "RankAVLTreeNode already has a child there";
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
class RankAVLTreeNode {

	void update_height() {
		int leftHeight = left != nullptr ? left->height : -1;
		int rightHeight = right != nullptr ? right->height : -1;
		int max = leftHeight > rightHeight ? leftHeight : rightHeight;
		height = max + 1;
	}

	void update_ranks(){
		int left_rank = this->left ? this->left->rank : 0;
		int right_rank = this->right ? this->right->rank : 0;
		rank = left_rank + right_rank + 1;

		int left_score_rank = this->left ? this->left->score_rank : 0;
		int right_score_rank = this->right ? this->right->score_rank : 0;
		score_rank = left_score_rank + right_score_rank + score;
	}

	void set_child(RankAVLTreeNode* tree) {
		if (less(tree->data, data) && left == nullptr) {
			set_left(tree);
		}
		else if (less(data, tree->data) && right == nullptr) {
			set_right(tree);
		} else {
			throw ChildExistsException();
		}
	}

	void virtual set_left(RankAVLTreeNode* tree) {
		left = tree;
		if (nullptr != tree) tree->parent = this;
		update_height();
		update_ranks();
	}

	void virtual set_right(RankAVLTreeNode* tree) {
		right = tree;
		if (nullptr != tree) tree->parent = this;
		update_height();
		update_ranks();
	}

	RankAVLTreeNode* roll_right() {
		RankAVLTreeNode* newRoot = left;
		set_left(newRoot->right);
		newRoot->set_right(nullptr);
		swap_with_child(newRoot);
		return newRoot;
	}

	RankAVLTreeNode* roll_left() {
		RankAVLTreeNode* newRoot = right;
		set_right(newRoot->left);
		newRoot->set_left(nullptr);
		swap_with_child(newRoot);
		return newRoot;
	}

	RankAVLTreeNode* balance() {
		int balanceFactor = balance_factor();
		if (balanceFactor * balanceFactor < 4) {
			update_height();
			update_ranks();
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

	RankAVLTreeNode* remove_node() {
		RankAVLTreeNode<T, Pred, Less>* toRemove = this;
		if (left != nullptr && right != nullptr) {
			RankAVLTreeNode* next = right;
			while (next->left != nullptr) {
				next = next->left;
			}

			T temp = data;
			data = next->data;
			next->data = temp;
			toRemove = next;
		}

		RankAVLTreeNode* newChild = toRemove->left == nullptr ?
		                    toRemove->right : toRemove->left;
		RankAVLTreeNode* oldParent = toRemove->parent;
		if (oldParent != nullptr) oldParent->change_child(toRemove, newChild);
		else if(nullptr != newChild) newChild->parent = nullptr;
		toRemove->right = nullptr;
		toRemove->left = nullptr;
		delete toRemove;
		return oldParent == nullptr ? newChild : oldParent;
	}

	void change_child(RankAVLTreeNode *currentChild, RankAVLTreeNode *newChild) {
		if (left == currentChild) {
			set_left(newChild);
		}

		if (right == currentChild) {
			set_right(newChild);
		}
	}

	void swap_with_child(RankAVLTreeNode* child) {
		if (parent != nullptr) {
			parent->change_child(this, child);
		} else {
			child->parent = nullptr;
		}

		child->set_child(this);
	}

    template <typename S>
	RankAVLTreeNode* search(const S& value) {
		if (pred(data, value)) {
			return this;
		}

		RankAVLTreeNode* next = nullptr;
		next = less(data, value) ? right : left;

		if (nullptr == next) {
			return this;
		}
		return next->search(value);
	}

public:
    T data;
    int score;
    int rank;
    int score_rank;
    Pred pred;
    Less less;
    RankAVLTreeNode* parent;
    RankAVLTreeNode* left;
    RankAVLTreeNode* right;
    int height;

	RankAVLTreeNode(const T& data, int score, Pred pred, Less less,
		RankAVLTreeNode* parent = nullptr, RankAVLTreeNode* left = nullptr, RankAVLTreeNode* right = nullptr) :
		data(data), score(score), rank(1), score_rank(score), pred(pred),
		less(less), parent(parent), left(left), right(right), height(0) {}

	virtual ~RankAVLTreeNode(){
	    if (right) delete right;
	    if (left) delete left;
	};

    template <typename S>
	RankAVLTreeNode* find(const S& value) {
		RankAVLTreeNode* tree = search(value);
		if (!pred(tree->data, value)){
			throw TreeNodeNotFoundException();
		}
		return tree;
	}

	RankAVLTreeNode* insert(const T& value, int score) {
		RankAVLTreeNode *position = search(value);
		if (pred(position->data, value)) {
			throw AlreadyExistsException();
		}

		auto newTree = new RankAVLTreeNode(value, score, pred, less,
			position, nullptr, nullptr);
		position->set_child(newTree);

		while(nullptr != position->parent) {
			position = position->parent;
			// This only runs update_height() and updateRanks() to every
			// tree except the first
			position->balance();
		}

		return position;
	}

    template <typename S>
	RankAVLTreeNode* remove(const S& value) {
		RankAVLTreeNode* position = search(value);
		if (!pred(position->data,value)) {
			throw TreeNodeNotFoundException();
		}

		RankAVLTreeNode* tree = position->remove_node();
		RankAVLTreeNode* root = tree;

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


	int get_score_by_rank(int index) {
		int i = left ? left->rank + 1 : 1;
		int left_score_rank = this->left ? this->left->score_rank : 0;
		if (i > index) return left->get_score_by_rank(index);
		if (i < index)
			return right ? left_score_rank + score +
			right->get_score_by_rank(index - i) : left_score_rank + score;
		return left_score_rank + score; // i == index
	}


	int balance_factor() {
		int leftHeight = left != nullptr ? left->height : -1;
		int rightHeight = right != nullptr ? right->height : -1;
		return leftHeight - rightHeight;
	}
};

template <class T, class Pred, class Less>
class RankAVLTree {
public:
    explicit RankAVLTree(Pred pred = Pred(), Less less = Less()) : _root(nullptr), _less(less), _pred(pred) {};
    RankAVLTree(RankAVLTree& tree1, RankAVLTree& tree2, Pred pred = Pred(), Less less = Less());
    ~RankAVLTree() {
        if (_root) delete _root;
    }

    void insert(const T& data, int score) {
        if (nullptr == _root){
            _root = new RankAVLTreeNode<T, Pred, Less>(data, score, _pred,
            	_less, nullptr, nullptr, nullptr);
        }
        else{
            _root = _root->insert(data, score);
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

	int get_score_by_rank(int rank){
    	if (_root) {
			return _root->get_score_by_rank(rank);
		}

		throw TreeNodeNotFoundException();
	}

private:
    RankAVLTreeNode<T, Pred, Less> * _root;
    Less _less;
    Pred _pred;
};

#endif //RANK_AVL_TREE_H

