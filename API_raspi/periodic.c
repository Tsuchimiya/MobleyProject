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

	//finding dynamically the can0 interface (to bind to all can interface put 0 into the index)
	strcpy(ifr.ifr_name, ifname);
	ioctl(s, SIOCGIFINDEX, &ifr);
	
	addr.can_family  = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	printf("%s at index %d\n", ifname, ifr.ifr_ifindex);

	// opening socket CAN_RAW//SOCK_RAW or CAN_BCM // SOCK_DGRAM BCM = cyclique
	
	if((s = socket(PF_CAN, SOCK_DGRAM, CAN_BCM)) < 0) {
		perror("Error while opening socket");
		return -1;
	}


	if((s = connect(s, (struct sockaddr*)&addr, sizeof(addr))) < 0) {
		perror("Error while connecting socket");
		return -1;
	}


	// defining struct to set up a sequence of 2 CAN frames

	struct{
	  struct bcm_msg_head msg_head;
	  struct can_frame frame[2];
	}msgs;
	
	struct msgs M;
	M.msg_head.nframes=2




	// making a packet and sending it
	frame.can_id  = 0x21;
	frame.can_dlc = 2;
	frame.data[0] = 0x11;
	frame.data[1] = 0x22;

	nbytes = write(s, &frame, sizeof(struct can_frame));

	printf("Wrote %d bytes\n", nbytes);
	
	return 0;
}
