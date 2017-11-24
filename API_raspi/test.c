#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <net/if.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <linux/can.h>
#include <linux/can/raw.h>

// to set a virtual socket on your pc : modprobe vcan, flexcan, mcp251x, can-raw, can-dev, can
// ip link set vcan0 up type vcan
// cansend vcan0 7DF#0201050000000000, 7df: id variable, le reste = valeur


// http://copperhilltech.com/what-is-socketcan/
int
main(void)
{
	int s;
	int nbytes;
	struct sockaddr_can addr;
	struct can_frame frame;
	struct ifreq ifr;

	const char *ifname = "vcan0";
	// opening socket CAN_RAW//SOCK_RAW or CAN_BCM // SOCK_DGRAM BCM = cyclique
	
	if((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Error while opening socket");
		return -1;
	}

	//finding dynamically the can0 interface (to bind to all can interface put 0 into the index)
	strcpy(ifr.ifr_name, ifname);
	ioctl(s, SIOCGIFINDEX, &ifr);
	
	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	printf("%s at index %d\n", ifname, ifr.ifr_ifindex);

	// bind the socket to a can interface
	if(bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Error in socket bind");
		return -2;
	}


	// defining filters for CAN :
	struct can_filter rfilter[2];
	rfilter[0].can_id   = 0x123;
	// both SFF frames with CAN ID 0x123 and EFF frames with 0xXXXXX123 can pass
	rfilter[0].can_mask = CAN_SFF_MASK;
	rfilter[1].can_id   = 0x200;
	rfilter[1].can_mask = 0x700;

	/*
	  pour recevoir les erreurs du bus can 
	  can_err_mask_t err_mask = ( CAN_ERR_TX_TIMEOUT | CAN_ERR_BUSOFF );
	  setsockopt(s, SOL_CAN_RAW, CAN_RAW_ERR_FILTER,
	  &err_mask, sizeof(err_mask));
	*/

	setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));


	// making a packet and sending it
	frame.can_id  = 0x21;
	frame.can_dlc = 2;
	frame.data[0] = 0x11;
	frame.data[1] = 0x22;

	nbytes = write(s, &frame, sizeof(struct can_frame));

	printf("Wrote %d bytes\n", nbytes);
	
	return 0;
}
