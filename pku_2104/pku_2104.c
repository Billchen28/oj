
#include<stdio.h>

typedef struct quest {
	int start;
	int end;
	int target;
}*quest_t, _quest;

typedef struct result_cache {
	int s;
	int e;
	int* sorted;
	struct result_cache* next;
}*result_cache_t, _result_cache;

void showArray_all(int* src, int size) {
	int i = 0;
	printf("{");
	for (i = 0; i < size; i++) {
		printf("%d,", src[i]);
	}
	printf("}");
}

void showArray(int* src, int s, int e) {
	int i = 0;
	printf("{");
	for (i = s; i < e; i++) {
		printf("%d,", src[i]);
	}
	printf("}\n");
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
	printf("left:");
	showArray_all(left, left_size);
	printf("right:");
	showArray_all(right, right_size);
	printf("\n");
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

void merge_sort_(int* src, int size) {
	int* tmp = (int*)malloc(sizeof(int) * size);
	int i = 0;
	int left_mini = 0;
	int left_max = 0;
	int right_mini = 0;
	int right_max = 0;
	int next = 0;
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
		}
	}
	free(tmp);
}

void select_sort(int* src, int stop_index, int size) {
	int i = 0;
	int j = 0;
	int mini = 0;
	for (i = 0; i < size - 1;i++) {
		mini = i;
		for (j = i + 1;j < size;j++) {
			if (src[mini] > src[j]) {
				mini = j;
			}
		}
		if (mini != i) {
			int temp = src[i];
			src[i] = src[mini];
			src[mini] = temp;
		}
		if (stop_index >= 0 && i == stop_index) {
			return;
		}
	}
}

void select_sort_rev(int* src, int stop_index, int size) {
	int i = 0;
	int j = 0;
	int max = 0;
	for (i = size - 1; i > 0 ;i--) {
		max = i;
		for (j = i - 1;j >= 0 ;j--) {
			if (src[max] < src[j]) {
				max = j;
			}
		}
		if (max != i) {
			int temp = src[i];
			src[i] = src[max];
			src[max] = temp;
		}
		if (stop_index >= 0 && i == stop_index) {
			return;
		}
	}
}

void addCache(int s, int e, int* result, result_cache_t header) {
	result_cache_t n = (result_cache_t)malloc(sizeof(_result_cache));
	memset(n, 0, sizeof(_result_cache));
	n->s = s;
	n->e = e;
	n->sorted = result;
	n->next = 0;
	result_cache_t next = header;
	do {
		if (next->next == 0) {
			next->next = n;
			break;
		}
		next = next->next;
	} while(next != 0);
}

result_cache_t findCache(int s, int e, result_cache_t header) {
	result_cache_t next = header;
	do {
		if (next != 0 && next->s == s && next->e == e) {
			return next;
		}
		next = next->next;
	} while(next != 0);
	return 0;
}

void cal(int* src, quest_t q, result_cache_t** cache) {
	int targetIndex = q->target - 1;
	result_cache_t c = findCache(q->start, q->end, cache);
	if(c != 0) {
		printf("%d\n", c->sorted[targetIndex]);
		return;
	}
	int* start_p = src;
	int sub_len = q->end - q->start + 1;
	int* temp = (int*)malloc(sizeof(int) * sub_len);
	start_p += q->start - 1;
	memcpy(temp, start_p, sizeof(int) * sub_len);
	int seg_len = sub_len / 3;
	if (seg_len > 0) {
		int mid1 = seg_len;
		int mid2 = seg_len * 2;
		if (targetIndex <= mid1) {
			select_sort(temp, targetIndex, sub_len);
			printf("%d\n", temp[targetIndex]);
			free(temp);
			return;
		} else if (mid1 < targetIndex && targetIndex <= mid2) {
		} else if (targetIndex > mid2) {
			select_sort_rev(temp, targetIndex, sub_len);
			printf("%d\n", temp[targetIndex]);
			free(temp);
			return;
		}
	}
	merge_sort_(temp, sub_len);
	printf("%d\n", temp[targetIndex]);
	addCache(q->start, q->end, temp, cache);
//	free(temp);
}

int main() {
	int array_size = 0;
	int q_num = 0;
	scanf("%d %d", &array_size, &q_num);
	int* src = (int*)malloc(sizeof(int) * array_size);
	memset(src, 0, array_size);
	int i = 0;
	for (i = 0;i < array_size;i++) {
		scanf("%d", &src[i]);
	}
	quest_t q_list = (quest_t)malloc(sizeof(_quest) * q_num);
	for (i = 0;i < q_num;i++) {
		scanf("%d %d %d", &(q_list[i].start), &(q_list[i].end), &(q_list[i].target));
	}
	result_cache_t header = (result_cache_t)malloc(sizeof(_result_cache));
	memset(header, 0, sizeof(_result_cache));
	header->s = -1;
	header->e = -1;
	header->next = 0;
	header->sorted = 0;
	merge_sort(src, 0, array_size);
	showArray_all(src, array_size);
//	for (i = 0;i < q_num;i++) {
//		cal(src, &q_list[i], header);
//	}
	free(src);
	free(q_list);
	result_cache_t next = header;
	do {
		result_cache_t temp = next;
		next = next->next;
		if (temp != 0) {
			if (temp->sorted != 0) {
				free(temp->sorted);
			}
			free(temp);
		}
	} while(next != 0);

	return 0;
}
