/*
 * binary_tree.c
 *
 *  Created on: 2016年9月13日
 *      Author: Bill
 */

#include "binary_tree.h"
#include "queue.h"
#include "common.h"

tree_node new_tree_node() {
	tree_node ret = (tree_node)malloc(sizeof(tree_node_t));
	ret->m_data = 0;
	ret->m_left = NULL;
	ret->m_right = NULL;
	return ret;
}

void free_tree_node(tree_node node) {
	if (node != NULL) {
		free(node);
		node = NULL;
	}
}

tree_node insert_node_not_recur(tree_node node, int data)
{
	tree_node new_node = NULL;
	tree_node pre = NULL;// 记录上一个结点
	tree_node t = node;
	while (t != NULL) {
		pre = t;
		if (t->m_data < data) {
			t = t->m_left;
		} else {
			t = t->m_right;
		}
	}
	new_node = new_tree_node();
	new_node->m_data = data;
	if (pre == NULL) {
		node = new_node;
		return node;
	} else {
		if (pre->m_data < data) {
			pre->m_left = new_node;
		} else {
			pre->m_right = new_node;
		}
	}
	return node;
}

tree_node insert_node(tree_node node, int data) {
	if (node == NULL) {
		node = new_tree_node();
		node->m_data = data;
		return node;
	}
	if (node->m_data < data) {
		node->m_left = insert_node(node->m_left, data);
	} else {
		node->m_right = insert_node(node->m_right, data);
	}
	return node;
}

tree_node create_tree(tree_node tree, int* data, int n)
{
	int i = 0;
	for (i = 0; i < n; i++) {
//		tree = insert_node(tree, data[i]);
		tree = insert_node_not_recur(tree, data[i]);
	}
	return tree;
}

void release_tree(tree_node node)
{
	post_traverse(node, free_tree_node);
}

int get_node_num(tree_node node) {
	if (node == NULL) {
		return 0;
	}
	return get_node_num(node->m_left) + get_node_num(node->m_right) + 1;
}

int get_depth(tree_node node)
{
	if (node == NULL) {
		return 0;
	}
	int l_depth = get_depth(node->m_left);
	int r_depth = get_depth(node->m_right);
	return l_depth > r_depth ? l_depth + 1 : r_depth + 1;
}

void pre_traverse(tree_node node, void (*func)(tree_node))
{
	if (node == NULL) {
		return;
	}
	func(node);
	pre_traverse(node->m_left, func);
	pre_traverse(node->m_right, func);
}

void in_traverse(tree_node node, void (*func)(tree_node))
{
	if (node == NULL) {
		return;
	}
	in_traverse(node->m_left, func);
	func(node);
	in_traverse(node->m_right, func);
}

void post_traverse(tree_node node, void (*func)(tree_node))
{
	if (node == NULL) {
		return;
	}
	post_traverse(node->m_left, func);
	post_traverse(node->m_right, func);
	func(node);
}

void bfs_traverse(tree_node t_node, void (*func)(tree_node))
{
	queue q = new_queue();
	node n = new_queue_node();
	n->m_data = t_node;
	queue_push(q, n);
	while (!queue_empty(q)) {
		n = queue_pop(q);
		tree_node t_n = n->m_data;
		func(t_n);
		free_node(n);
		if (t_n->m_left != NULL) {
			node nn = new_queue_node();
			nn->m_data = t_n->m_left;
			queue_push(q, nn);
		}
		if (t_n->m_right != NULL) {
			node nn = new_queue_node();
			nn->m_data = t_n->m_right;
			queue_push(q, nn);
		}
	}
	free(q);
}


