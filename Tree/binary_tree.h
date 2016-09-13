/*
 * binary_tree.h
 *
 *  Created on: 2016年9月13日
 *      Author: Bill
 */

#ifndef BINARY_TREE_H_
#define BINARY_TREE_H_

typedef struct _tree_node_t {
	int m_data;
	struct _tree_node_t* m_left;
	struct _tree_node_t* m_right;
}*tree_node, tree_node_t;

tree_node create_tree(tree_node node, int* data, int n);

void release_tree(tree_node node);

int get_node_num(tree_node node);

int get_depth(tree_node node);

void pre_traverse(tree_node node, void (*func)(tree_node));

void in_traverse(tree_node node, void (*func)(tree_node));

void post_traverse(tree_node node, void (*func)(tree_node));

#endif /* BINARY_TREE_H_ */
