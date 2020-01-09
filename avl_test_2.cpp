/*
optional.h
Copyright (c) Eromid (Olly) 2017
Unit tests for AVL tree implementation in RankAVLTree.h.
*/

#include <assert.h>
#include "rank_avl_tree.h"
#include "avltree-test-helper.h"

#include <iostream>
using std::cout;
using std::endl;
using std::left;
using std::right;

#include <iomanip>
using std::setw;
using std::setfill;

using tests = test_helper<int, double>;

#define TEST_CASE(fn)\
cout << "================================================================================" << endl;\
cout << "    Running " << #fn << "...";                                                            \
fn();                                                                                              \
cout << " Complete. " << endl;                                                                     \
cout << "================================================================================" << endl;


// Run the tests inside the test-helper class template
void test_meta_functions()
{
	tests::test_meta_functions();
}

// Test empty tree behaves correctly
void test_empty_tree()
{
	RankAVLTree<int, CompareInt, LessInt> tree = RankAVLTree<int, CompareInt, LessInt>();
	assert(tests::is_avl(&tree));            // Tree should be an AVL tree
	assert(tests::count_nodes(&tree) == 0);  // Empty tree should have 0 nodes.
	assert(tests::count_nodes(&tree) == 0);  // Empty tree should still have 0 nodes.
	assert(tests::is_avl(&tree));            // Tree should be an AVL tree still
	assert(tests::valid_balance_factors(&tree)); // Are all balance factors correct (none)
}

// Test tree with only one node behaves correctly
void test_single_node()
{
	const int key = 1;
	RankAVLTree<int, CompareInt, LessInt> tree = RankAVLTree<int, CompareInt, LessInt>();
	tree.insert(key, key);

	// After insertion of single node:
	assert(tests::count_nodes(&tree) == 1);      // Empty tree should have 0 nodes.
	assert(tests::is_avl(&tree));                // Tree should be an AVL tree still
	assert(tests::count_nodes(&tree) == 1);      // Tree should now have one node
	assert(tests::is_avl(&tree));                // Tree should be an AVL tree still
	assert(tests::valid_balance_factors(&tree)); // Are all balance factors correct

	// after removing single node:
	tree.remove(key);
	assert(tests::count_nodes(&tree) == 0);      // Empty tree should still have 0 nodes.
	assert(tests::is_avl(&tree));
	assert(tests::valid_balance_factors(&tree)); // Are all balance factors correct

}

// Test repeated right insertions don't imbalance the tree
void test_multiple_right_insertions()
{
	RankAVLTree<int, CompareInt, LessInt> tree = RankAVLTree<int, CompareInt, LessInt>();
	const static int n_insertions = 100;
	for (unsigned int i = 1; i <= n_insertions; ++i)
	{
		tree.insert(i, i);   // insert increasing numbers
		assert(tests::is_avl(&tree));              // check tree remains AVL
		assert(tests::count_nodes(&tree) == i);          // Check the node made is in
		assert(tests::valid_balance_factors(&tree)); // Are all balance factors correct
	}
	for (int i = 1; i < n_insertions; ++i)
	{
		assert(tree.find(i) == i);  // query should return a
	}
	cout << tree.get_score_by_rank(50) << "\n";
}

// Test repeated left insertions don't imbalance the tree
void test_multiple_left_insertions()
{
	RankAVLTree<int, CompareInt, LessInt> tree = RankAVLTree<int, CompareInt, LessInt>();
	const static int n_insertions = 100;
	for (unsigned int i = n_insertions; i >= 1; --i)
	{
		tree.insert(i,i);   // insert increasing numbers
		assert(tests::is_avl(&tree));              // check tree remains AVL
		assert(tests::count_nodes(&tree) == n_insertions - (i -1));          // Check the node made is in
		assert(tests::valid_balance_factors(&tree)); // Are all balance factors correct
	}
	for (int i = 1; i < n_insertions; ++i)
	{
		assert(tree.find(i)== i); 
	}
}

// Test that a right-left rotation correctly balances the tree
void test_right_left_rotation()
{
	RankAVLTree<int, CompareInt, LessInt> tree = RankAVLTree<int, CompareInt, LessInt>();
	tree.insert(10, 10);      // Root
	tree.insert(20, 20);      // Right child of root
	tree.insert(15,15);      // left child of right child of root ->
	// triggers RL rotation
	assert(tests::is_avl(&tree));
	assert(tests::valid_balance_factors(&tree));

}

// Test that a left-right rotation correctly balances the tree
void test_left_right_rotation()
{
	RankAVLTree<int, CompareInt, LessInt> tree = RankAVLTree<int, CompareInt, LessInt>();
	tree.insert(20,20);        // Root node
	tree.insert(10,10);        // Left child
	tree.insert(15,15);        // Right child of left child -> triggers LR
	// rotation
	assert(tests::is_avl(&tree));
	assert(tests::valid_balance_factors(&tree));
	cout << tree.get_score_by_rank(1) << "\n";
}

void test_merge() {
	RankAVLTree<int, CompareInt, LessInt> tree1 = RankAVLTree<int, CompareInt, LessInt>();
	tree1.insert(1,1);
	tree1.insert(3,3);
	tree1.insert(5,5);

	RankAVLTree<int, CompareInt, LessInt> tree2 = RankAVLTree<int, CompareInt, LessInt>();
	tree2.insert(2,2);
	tree2.insert(4,4);
	tree2.insert(6,6);

	tree1._root = merge(tree1._root, tree2._root);
	tree2._root = nullptr; // to avoid deleting the nodes we merged
	assert(tests::is_avl(&tree1));
}

// Call all the above cases
int main()
{
	TEST_CASE(test_meta_functions);
	TEST_CASE(test_empty_tree);
	TEST_CASE(test_single_node);
	TEST_CASE(test_multiple_right_insertions);
	TEST_CASE(test_multiple_left_insertions);
	TEST_CASE(test_right_left_rotation);
	TEST_CASE(test_left_right_rotation);
	TEST_CASE(test_merge);
	return 0;
}
