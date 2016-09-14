/*
 * main.c
 *
 */

#include <stdio.h>
#include <math.h>

#include "sort.h"

#define TEST_SIZE 10

int main() {
	int i, n;
	int list[TEST_SIZE] = {3, 44, 38, 5, 47, 15, 36, 26, 27, 2, 46, 4, 19, 50, 48};
	n = TEST_SIZE;
//	for (i = 0; i < n; i++){    /* randomly generate numbers */
//		list[i] = rand();
//	}
	showArray(list, TEST_SIZE);
//	insert_sort(list, TEST_SIZE);
//	merge_sort(list, 0, TEST_SIZE - 1);
//	merge_sort_v2(list, TEST_SIZE);
	quick_sort(list, 0, TEST_SIZE);
	printf("\n");
	showArray(list, TEST_SIZE);
	return 0;
}
