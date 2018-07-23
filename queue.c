#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "queue.h"

void
init(struct queue *q)
{
	q -> head = 0;
	q -> tail = 0;
}

void
enqueue(struct queue *q, struct Pac packet) 
{
	if (q->tail >= QUEUE) {
			printf("Queue is full\n");
	}
	else {
		q -> data[q -> tail] = packet;
		q -> tail++;
		if (q -> tail == QUEUE)
			q -> tail = 0;	
	}
}

struct Pac
dequeue(struct queue *q)
{
	struct Pac tmp;
	/* dummy */
	memset(&tmp.packet, 0, sizeof(tmp.packet));
	tmp.size = 0;

	if (q -> head == q -> tail) {
		return tmp;  // dummy
	}
	else {
		tmp = q -> data[q -> head];
		q -> head++;
		if (q -> head == QUEUE) {
			q -> head = 0;
		}
		return tmp;
	}
}
