
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include "candemo.hpp"
#include <iostream>

using namespace std;

void format_can_timestamp(struct timeval tv) {
    struct tm *tm_info;
    char buffer[20];

    // Convert seconds to HH:MM:SS format
    tm_info = localtime(&tv.tv_sec);
    strftime(buffer, 20, "%H:%M:%S", tm_info);

    // Append milliseconds
    printf("\nCAN Frame Timestamp: %s:%03ld   ::   ", buffer, tv.tv_usec / 1000);
}

int demo_can_sent(int can_id, int can_dlc, const char* can_data)
{
    int s; 
     sockaddr_can addr;
     ifreq ifr;
     can_frame frame;

    printf("CAN Sockets Demo\r\n");

    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("Socket");
        return 1;
    }

    strcpy(ifr.ifr_name, "can0" );
    ioctl(s, SIOCGIFINDEX, &ifr);

    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Bind");
        return 1;
    }

    frame.can_id = can_id;
    frame.can_dlc = can_dlc;
    memcpy(frame.data, can_data, can_dlc);

    if (write(s, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
        perror("Write");
        return 1;
    }

    if (close(s) < 0) {
        perror("Close");
        return 1;
    }

    return 0;
}

    // Note: The timestamp is in seconds and microseconds since the epoch.
    // You can format it as needed.
    // For example, you can convert it to a human-readable format using strftime.
    // You can also use the timestamp to calculate the time difference between frames.
    // This is just a basic example to show how to receive CAN frames with timestamps.
    // You can extend this code to handle multiple frames, filter frames, etc.
    // Make sure to handle errors and edge cases as needed.
    // Also, remember to close the socket when done.
    // This code is just a starting point and may need to be adapted to your specific use case.
    // You can also use the timestamp to synchronize with other events or systems.
int demo_can_recvWithTimestamp(void)
{
    int s;
    sockaddr_can addr;
    ifreq ifr;
    can_frame frame;
    msghdr msg;
    iovec iov;
    char ctrlmsg[CMSG_SPACE(sizeof(struct timeval))];

    // Open CAN socket
    s = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if (s < 0) {
        perror("Socket");
        return 1;
    }

    // Set socket options for timestamp
    int timestamp_on = 1;
    if (setsockopt(s, SOL_SOCKET, SO_TIMESTAMP, &timestamp_on, sizeof(timestamp_on)) < 0) {
        perror("setsockopt");
        std::cout << "Error setting socket options" << std::endl;
        
    }
    // Specify CAN interface
    strcpy(ifr.ifr_name, "can0");
    ioctl(s, SIOCGIFINDEX, &ifr);

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    // Bind socket
    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Bind");
        std::cout << "Error binding CAN socket" << std::endl;
            
    }

    // Prepare message structure
    iov.iov_base = &frame;
    iov.iov_len = sizeof(frame);
    msg.msg_name = &addr;
    msg.msg_namelen = sizeof(addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    msg.msg_control = ctrlmsg;
    msg.msg_controllen = sizeof(ctrlmsg);

    // Receive CAN frame
    if (recvmsg(s, &msg, 0) < 0) {
        perror("recvmsg");
        std::cout << "Error receiving CAN frame" << std::endl;
        
    }

    // Extract timestamp
    timeval tv;
    struct cmsghdr *cmsg = CMSG_FIRSTHDR(&msg);
    if (cmsg && cmsg->cmsg_level == SOL_SOCKET && cmsg->cmsg_type == SO_TIMESTAMP) {
        memcpy(&tv, CMSG_DATA(cmsg), sizeof(tv));
        format_can_timestamp(tv);
        // printf("\nTimestamp: %ld.%06ld\n", tv.tv_sec, tv.tv_usec);
    }

    printf("Received CAN ID: %X, DLC: %d\n", frame.can_id, frame.can_dlc);
    for (int i = 0; i < frame.can_dlc; i++) {
        printf(" %02X", frame.data[i]);
    }
    close(s);

    return 0;

}

int demo_can_recv(void)
{
    int s; 
     sockaddr_can addr;
     ifreq ifr;
     can_frame frame;

    printf("CAN Sockets Demo\r\n");

    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("Socket");
        return 1;
    }

    strcpy(ifr.ifr_name, "can0" );
    ioctl(s, SIOCGIFINDEX, &ifr);

    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Bind");
        return 1;
    }

    /*while (1)*/ {
        int nbytes = read(s, &frame, sizeof(struct can_frame));
        if (nbytes < 0) {
            perror("Read");
            return 1;
        }

        printf("Received CAN frame: ID=0x%X DLC=%d Data=", frame.can_id, frame.can_dlc);
        for (int i = 0; i < frame.can_dlc; i++) {
            printf(" %02X", frame.data[i]);
        }
        printf("\n");
    }

    if (close(s) < 0) {
        perror("Close");
        return 1;
    }

    return 0;
}

int demo_can_filter(int argc, char **argv)
{
	int s, i; 
	int nbytes;
	 sockaddr_can addr;
	 ifreq ifr;
	 can_frame frame;

	printf("CAN Sockets Receive Filter Demo\r\n");

	if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
		perror("Socket");
		return 1;
	}

	strcpy(ifr.ifr_name, "can0" );
	ioctl(s, SIOCGIFINDEX, &ifr);

	memset(&addr, 0, sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
		perror("Bind");
		return 1;
	}

	struct can_filter rfilter[1];

	rfilter[0].can_id   = 0x550;
	rfilter[0].can_mask = 0xFF0;


	setsockopt(s, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));

	nbytes = read(s, &frame, sizeof(struct can_frame));

	if (nbytes < 0) {
		perror("Read");
		return 1;
	}

	printf("0x%03X [%d] ",frame.can_id, frame.can_dlc);

	for (i = 0; i < frame.can_dlc; i++)
		printf("%02X ",frame.data[i]);

	printf("\r\n");

	if (close(s) < 0) {
		perror("Close");
		return 1;
	}

	return 0;
}