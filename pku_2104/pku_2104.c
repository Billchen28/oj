
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
	result_cache_t c = findCache(q->start, q->end, cache);
	if(c != 0) {
		printf("%d\n", c->sorted[q->target - 1]);
		return;
	}
	int* start_p = src;
	int sub_len = q->end - q->start + 1;
	int* temp = (int*)malloc(sizeof(int) * sub_len);
	start_p += q->start - 1;
	memcpy(temp, start_p, sizeof(int) * sub_len);
	merge_sort_(temp, sub_len);
	printf("%d\n", temp[q->target - 1]);
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
	for (i = 0;i < q_num;i++) {
		cal(src, &q_list[i], header);
	}
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
