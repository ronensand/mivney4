/*
avl-test-helper.h
Copyright (c) Eromid (Olly) 2017
Friend of avltree class which contains functions only used in testing.
*/

#ifndef AVL_TEST_HELPER_H
#define AVL_TEST_HELPER_H

#include <algorithm>
#include <cmath>
#include <assert.h>

using std::max;

#include <iostream>
using std::cout;
using std::endl;

bool DBG = true;

class CompareInt{
public:
	bool operator()(const int obj, int i) {return obj == i;}
};

class LessInt{
public:
	bool operator()(const int obj, int i) {return obj < i;}
};

// A class template to test some of the internals of the AVL tree implementation.
// Is declared friend of avltree so has access to these.
template<typename K, typename V>
class test_helper
{
private:
	test_helper() {} // instantiation not needed (or allowed)
public:

	// Count the total number of nodes in the tree.
	static unsigned int count_nodes(const RankAVLTree<int, CompareInt, 
		LessInt>* tree)
	{
		if (tree)
			return count_descendants(tree->_root);
		else
			return 0u;
	}

	// Check the tree is AVL.
	static bool is_avl(const RankAVLTree<int, CompareInt, LessInt>* tree)
	{
		return is_avl(tree->_root);
	}

	// Check the tree's balance factors are correct.
	static bool valid_balance_factors(const RankAVLTree<int, CompareInt, LessInt>* tree)
	{
		return valid_balance_factors(tree->_root);
	}

	// Test the functions in this class.
	static void test_meta_functions()
	{
		{
			// Counting nodes
			RankAVLTree<int, CompareInt, LessInt> tree = RankAVLTree<int, 
			    CompareInt, LessInt>();
			assert(count_nodes(&tree) == 0);  // Empty tree should have 
			// 0 nodes.
			tree.insert(1,1);
			assert(count_nodes(&tree) == 1);  // one node inserted
			tree.insert(2,2);
			assert(count_nodes(&tree) == 2);  // second unique node inserted
			tree.remove(1);
			assert(count_nodes(&tree) == 1);  // one node removed
			tree.remove(2);
			assert(count_nodes(&tree) == 0);
		}
		{
			// subtree height
			RankAVLTree<int, CompareInt, LessInt> tree = RankAVLTree<int,
				CompareInt, LessInt>();
			assert(subtree_height(tree._root) == 0);  // root is null,
			// height
			// is 0.
			tree.insert(5,5);
			assert(subtree_height(tree._root) == 1);  // single node height should be 1.
			tree.insert(8,8);
			assert(subtree_height(tree._root) == 2);  // height should be 2; root has a single right child
			tree.insert(3,3);
			assert(subtree_height(tree._root) == 2);  // height should be 2; root has a left and right child
		}
	}

private:
	static bool is_avl(RankAVLTreeNode<int, CompareInt,
		LessInt>* node)
	{
		if (!node) return true;  // Base case; an empty tree is always AVL.
		bool left_is_avl, right_is_avl;
		unsigned int left_height, right_height;
		left_is_avl = is_avl(node->left);
		left_height = subtree_height(node->left);
		right_is_avl = is_avl(node->right);
		right_height = subtree_height(node->right);
		if (node->parent == nullptr)
		{
			if (DBG) { cout << "left subtree: " << left_height << " | right subtree: " << right_height << endl; }
			if (DBG) { cout << "left_is_avl: " << left_is_avl << " | right_is_avl: " << right_is_avl << endl; }
		}
		return left_is_avl && right_is_avl && (abs(left_height - right_height) <= 1u);
	}

	static bool valid_balance_factors(RankAVLTreeNode<int, CompareInt,
		LessInt>* node)
	{
		if (!node) return true;
		if (DBG) { cout << "left_height: " << subtree_height(node->left) << " | right_height: "
		                << subtree_height(node->right) << " | "
													"balance_factor: " << static_cast<int>(node->balance_factor()) << endl; }
		return (subtree_height(node->left) - subtree_height(node->right)
		== node->balance_factor())
		       && valid_balance_factors(node->left) && valid_balance_factors(node->right);
	}

	static unsigned int count_descendants(RankAVLTreeNode<int, CompareInt, 
		LessInt>* node)
	{
		if (!node) return 0;
		unsigned int left_count = node->left ? count_descendants(node->left) : 0;
		unsigned int right_count = node->right ? count_descendants(node->right) : 0;
		return 1u + left_count + right_count;
	}

	static unsigned int subtree_height(RankAVLTreeNode<int, CompareInt, 
		LessInt>* node)
	{
		if (!node) return 0u;  // no subtree root -> height = 0.
		unsigned int left_height, right_height;
		left_height = right_height = 0u;
		left_height = subtree_height(node->left);
		right_height = subtree_height(node->right);
		return 1 + max(left_height, right_height);
	}
};

#endif

