/*
 * main.c
 *
 */

#include <stdio.h>
#include <math.h>

#include "sort.h"

#define TEST_SIZE 15

int bin_search(int* src, int size, int target) {
	int ret = -1;
	int start = 0;
	int end = size - 1;
	int mid = -1;
	while (start <= end) {
		mid = start + (end - start) / 2;
		int v = src[mid];
		if (v == target) {
			ret = mid;
			break;
		} else if (v < target) {
			start = mid + 1;
		} else {
			end = mid;
		}
	}
	return ret;
}

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
	printf("\n %d", bin_search(list, TEST_SIZE, 100));
	return 0;
}
