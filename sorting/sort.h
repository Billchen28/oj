/*
 * sort.h
 *
 */

#ifndef SORT_H_
#define SORT_H_

void showArray(int* src, int size);

void bubble_sort(int* src, int size);

void select_sort(int* src, int size);

void insert_sort(int* src, int size);

void merge_sort(int* src, int start, int end);

void quick_sort(int* src, int start, int end);

#endif /* SORT_H_ */
