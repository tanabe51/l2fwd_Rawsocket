#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <linux/if.h>
#include <netinet/ether.h>
#include <netpacket/packet.h>

#include "packetAnalyze.h"

void
Analyze(u_char *data,int size,struct packetInformation *packInfo)
{
	u_char *ptr;
	struct ether_header *eh;
	char *dst = "";  //fwd dst MACaddr
	char *src = "";  //fwd src MACaddr

	ptr = data;

	eh = (struct ether_header *)ptr;
	ptr += sizeof(struct ether_header);

	ether_ntoa_r((struct ether_addr *)eh->ether_shost, packInfo->hsrc);
	ether_ntoa_r((struct ether_addr *)eh->ether_dhost, packInfo->hdst);

	memcpy(eh->ether_shost, ether_aton(src), 6);
	memcpy(eh->ether_dhost, ether_aton(dst), 6);
}
