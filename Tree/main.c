/*
 * main.c
 *
 *  Created on: 2016年9月13日
 *      Author: jiubi_000
 */

#include <stdio.h>
#include "binary_tree.h"

#define TEST_SIZE 15
//#define TEST_SIZE 3

void printf_node(tree_node node)
{
	if (node != NULL) {
		printf("%d ", node->m_data);
	}
}

int main()
{
	int list[TEST_SIZE] = {3, 44, 38, 5, 47, 15, 36, 26, 27, 2, 46, 4, 19, 50, 48};
//	int list[TEST_SIZE] = {3, 44, 38};
	tree_node root = create_tree(NULL, list, TEST_SIZE);
	printf("tree_node_num:%d\n", get_node_num(root));
	printf("tree_depth:%d\n", get_depth(root));
	pre_traverse(root, printf_node);
	printf("\n");
	bfs_traverse(root, printf_node);
	release_tree(root);
	return 0;
}
