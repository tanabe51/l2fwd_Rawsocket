#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <linux/if.h>
#include <signal.h>
#include <errno.h>
#include <net/ethernet.h>
#include <netpacket/packet.h>
#include <netinet/if_ether.h>
#include <pthread.h>

#include "ether.h"
#include "queue.h"
#include "packetAnalyze.h"

static bool force_quit;
int driver;

struct status {
	int recv_sum;
	int send_sum;
};
struct status status = {0, 0};

void 
sigHandler()
{
	printf("\nEND\n");
	printf("recv sum: %d\n",status.recv_sum);
	printf("send sum: %d\n",status.send_sum);
	force_quit = true;
	exit(0);
}

void
*l2fwd(void *queue)
{
	struct Pac send;
	struct packetInformation info;

	
	while (!force_quit) {
		send = dequeue(&*(struct queue *)queue);
		if (send.size <= 0)
			;
		else {
			Analyze(send.packet, send.size, &info);
			write(driver, send.packet, send.size);
			status.send_sum++;
		}
	}
	return 0;
}

int 
main(int argc,char *argv[]) 
{
	struct queue queue;
	struct Pac recv;  //受信バッファ
	int size;
	pthread_t pthread;

	if (argc < 2) {
		printf("Require dev\n" "Error\n");
		exit(1);
	}
	
	init(&queue);
	force_quit = false;
	signal(SIGINT, sigHandler);
	pthread_create(&pthread, NULL, &l2fwd, &queue);

	driver = DriverUp(argv[1],0,0);

	/* 受信->queueに追加 */ 
	while (!force_quit) {
		if ((size = read(driver, recv.packet, sizeof(recv.packet))) <= 0)
			perror("read");
		else {
			recv.size = size;
			status.recv_sum++;
			/* queueに挿入 */
			enqueue(&queue, recv);
		}
	}
	return 0;
}
