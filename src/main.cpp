#include "generic.hpp"
#include <iostream>



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

#include "gps.h"


int readGps (void)
{
    loc_t coord;
    gps_init();
    gps_location(&coord);
    gps_off();

    printf("Latitude: %f, Longitude: %f, Altitude: %f, Speed: %f, Course: %f\n",
           coord.latitude, coord.longitude, coord.altitude, coord.speed, coord.course);

    return 0;
}

int main(void)
{
    int i =100000;
    // demo_can_sent(0x123, 8, "12345678");
    // while (i--)
    // {
    //     demo_can_recv();
    //     std::cout << "CAN Sockets Demo\r\n";    
    // }
    
    while (i--)
    {
        readGps();
        std::cout << "GPS Demo\r\n";    
    }
    std::cout << std::endl << " This is end of code test!! \r\r " << std::endl;
	return 0;
}

