#include "generic.hpp"
#include <iostream>
#include <fstream>



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

#include <sys/types.h>
#include <sys/stat.h>

#include "candemo.hpp"


using namespace std;


string canData;
string gpsData;

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
void  
getCANData(string &canData)
{
    int s; 
    sockaddr_can addr;
    ifreq ifr;
    can_frame frame;

    if ((s = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0) {
        perror("Socket");
        return;
    }

    strcpy(ifr.ifr_name, "can0" );
    ioctl(s, SIOCGIFINDEX, &ifr);

    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if (bind(s, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("Bind");
        return;
    }

    int nbytes = read(s, &frame, sizeof(struct can_frame));
    if (nbytes < 0) {
        perror("Read");
        return;
    }

    canData = "Received CAN frame: ID=0x" + to_string(frame.can_id) + " DLC=" + to_string(frame.can_dlc) + " Data=";
    for (int i = 0; i < frame.can_dlc; i++) {
        canData += " " + to_string(frame.data[i]);
    }
    
    canData += "\n";

    if (close(s) < 0) {
        perror("Close");
        return;
    }
}

void writeToFile(void) {

    // std::ios::sync_with_stdio(false);
    string file = "test/log.txt";

    ofstream MyFile(file);

    while (1)
    {
        getCANData(canData);       
        MyFile << canData;

        getGPSData(gpsData);
        MyFile << gpsData;
    }
    

    // Close the file
    MyFile.close();

    return;
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
    
    //std::cout << "GPS start \r\n";
   // readUart();
   writeToFile();

    std::cout << std::endl << " This is end of code test!! \r\r " << std::endl;
	return 0;
}

