struct Pac {
	uint8_t packet[1514];
	int size;
};

#define QUEUE 1000
struct queue {
	struct Pac data[QUEUE];

	int head;
	int tail;
};

void init(struct queue *);
void enqueue(struct queue *, struct Pac);
struct Pac dequeue(struct queue *);
