/*
 * sort.c
 */

#include "sort.h"

void showArray(int* src, int size) {
	int i = 0;
	printf("{");
	for (i = 0; i < size; i++) {
		printf("%d,", src[i]);
	}
	printf("}");
}

void bubble_sort(int* src, int size) {
	int i = 0;
	int swap = 0;
	int count = 0;
	do {
		swap = 0;
		for (i = 0;i < size - 1; i++) {
			count++;
			if (src[i] > src[i+1]) {
				int temp = src[i+1];
				src[i+1] = src[i];
				src[i] = temp;
				swap = 1;
			}
		}
	} while(swap);
	printf("\nbubble_sort count:%d", count);
}

void select_sort(int* src, int size) {
	int i = 0;
	int j = 0;
	int mini = 0;
	int count = 0;
	for (i = 0; i < size - 1;i++) {
		mini = i;//
		for (j = i + 1;j < size;j++) {
			count++;
			if (src[mini] > src[j]) {
				mini = j;
			}
		}
		if (mini != i) {
			int temp = src[i];
			src[i] = src[mini];
			src[mini] = temp;
		}
	}
	printf("\nselect_sort count:%d", count);
}

void insert_sort(int* src, int size) {
	int i= 0;
	int j = 0;
	int temp = 0;
	int count = 0;
	for (i = 1; i < size; i++) {
		temp = src[i];
		for (j = i; j > 0 && temp < src[j - 1];j--) {
			src[j] = src[j - 1];
			count++;
		}
		src[j] = temp;
	}
	printf("\ninsert_sort count:%d", count);
}

void merge(int* src, int start, int mid, int end) {
	int left_size = mid - start + 1;
	int right_size = end - mid;
	if (left_size <= 0 || right_size <= 0) {
		return;
	}
	int* left = (int*)malloc(sizeof(int) * left_size);
	int* right = (int*)malloc(sizeof(int) * right_size);
	int i = 0;
	for (i = 0; i < left_size; i++) {
		left[i] = src[start + i];
	}
	int j = 0;
	for (j = 0; j < right_size; j++) {
		right[j] = src[mid + 1 + j];
	}
	i = j = 0;
	int k = start;
	while (i < left_size && j < right_size) {
		if (left[i] > right[j]) {
			src[k++] = right[j++];
		} else {
			src[k++] = left[i++];
		}
	}
	while (i < left_size) {
		src[k++] = left[i++];
	}
	while (j < right_size) {
		src[k++] = right[j++];
	}
	free(left);
	left = 0;
	free(right);
	right = 0;
}

void merge_sort(int* src, int start, int end) {
	if (end > start) {
		int mid = (end + start) / 2;
		merge_sort(src, start, mid);
		merge_sort(src, mid + 1, end);
		merge(src, start, mid, end);
	}
}

void merge_sort_v2(int* src, int size) {
	int* tmp = (int*)malloc(sizeof(int) * size);
	int i = 0;
	int left_mini = 0;
	int left_max = 0;
	int right_mini = 0;
	int right_max = 0;
	int next = 0;
	int count = 0;
	for (i = 1; i < size; i *= 2) {
		for (left_mini = 0; left_mini < size - i; left_mini = right_max) {
			right_mini = left_max = left_mini + i;
			right_max = left_max + i;
			if (right_max > size) {
				right_max = size;
			}
			next = 0;
			while (left_mini < left_max && right_mini < right_max) {
				tmp[next++] = src[left_mini] > src[right_mini] ? src[right_mini++] : src[left_mini++];
			}
			while (left_mini < left_max) {
				src[--right_mini] = src[--left_max];
			}
			while (next > 0) {
				src[--right_mini] = tmp[--next];
			}
			count++;
		}
	}
	free(tmp);
	printf("\nmerge_sort_v2 count:%d", count);
}

void quick_sort(int* src, int start, int end) {
	if (start >= end) {
		return;
	}
	int i = start;
	int j = end;
	int key = src[start];
	while (i < j) {
		while (i < j && key < src[j]) {
			j--;
		}
		src[i] = src[j];
		while (i < j && key >= src[i]) {
			i++;
		}
		src[j] = src[i];
	}
	src[i] = key;
	quick_sort(src, start, i - 1);
	quick_sort(src, i + 1, end);
}


