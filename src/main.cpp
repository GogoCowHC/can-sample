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

#include <wiringPi.h>
#include <wiringSerial.h>

// int readGps (void)
// {
//     loc_t coord;
//     int i =100000;

//     gps_init();
//     while (i--)
//     {
//         gps_location(&coord);
        
//         std::cout <<"Latitude: "<<coord.latitude<<"Longitude: "<<coord.longitude<< "Altitude: "<< coord.altitude << "Speed: "<<coord.speed << "Course: " << coord.course << "\r\n";
//     }
//     gps_off();
//     std::cout << "GPS end \r\n";
//     return 0;
// }



void readuart (void)
{
    char buffer[256];
    int i = 100000;
    int fd;

    setupUart();
    if((fd = serialOpen ("/dev/ttyAMA0", 9600)) < 0 ){
        fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno));
    }

    while (i--)
    {
        if((fd = serialOpen ("/dev/ttyAMA0", 9600)) < 0 ){
			fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
		}else{
			do{
				c = serialGetchar(fd);
				printf("%c",c);
				fflush (stdout);
			}while(serialDataAvail(fd));
        
    }

        std::cout << buffer << "\r\n";
    }
    std::cout << "UART end \r\n";
}
int main(void)
{
    // int i =100000;
    // demo_can_sent(0x123, 8, "12345678");
    // while (i--)
    // {
    //     demo_can_recv();
    //     std::cout << "CAN Sockets Demo\r\n";    
    // }
    
    std::cout << "GPS start \r\n";
    readuart();
            

    std::cout << std::endl << " This is end of code test!! \r\r " << std::endl;
	return 0;
}

