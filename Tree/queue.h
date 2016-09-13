/*
 * queue.h
 *
 *  Created on: 2016年9月13日
 *      Author: Bill
 */

#ifndef QUEUE_H_
#define QUEUE_H_

typedef struct _node_t {
	void* m_data;
	struct _node_t* m_next;
}*node, node_t;

typedef struct _queue_t {
	node m_head;
	node m_tail;
}*queue, queue_t;

node new_queue_node();

void free_node(node n);

queue new_queue();

node queue_front(queue q);

node queue_pop(queue q);

void queue_push(queue q, node n);

int queue_empty(queue q);

#endif /* QUEUE_H_ */
