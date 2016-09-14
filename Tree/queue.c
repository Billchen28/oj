/*
 * queue.c
 *
 *  Created on: 2016年9月13日
 *      Author: Bill
 */

#include "queue.h"
#include "common.h"

node new_queue_node()
{
	node ret = (node)malloc(sizeof(node_t));
	ret->m_data = 0;
	ret->m_next = NULL;
	return ret;
}

void free_node(node n) {
	if (n != NULL) {
		free(n);
		n = NULL;
	}
}

queue new_queue() {
	queue ret = (queue)malloc(sizeof(queue_t));
	ret->m_head = NULL;
	ret->m_tail = NULL;
	return ret;
}

int queue_empty(queue q) {
	if (q == NULL || q->m_head == NULL) {
		return 1;
	} else {
		return 0;
	}
}

node queue_front(queue q)
{
	return q->m_head;
}

node queue_pop(queue q)
{
	node ret = q->m_head;
	if (ret != NULL) {
		q->m_head = ret->m_next;
		if (q->m_head == NULL) {
			q->m_tail = NULL;
		} else if (ret->m_next == ret) {
			q->m_head = NULL;
		}
	}
	return ret;
}

void queue_push(queue q, node n)
{
	if (q->m_tail != NULL) {
		n->m_next = NULL;
		q->m_tail->m_next = n;
		q->m_tail = n;
	} else {
		q->m_head = n;
		q->m_tail = n;
		n->m_next = NULL;
	}
}

