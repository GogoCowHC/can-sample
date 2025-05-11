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


void getdemoCANData(string &canData)
{
    int s; 
    sockaddr_can addr;
    ifreq ifr;
    can_frame frame;

    cout << "CAN Sockets Demo\r\n";
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
    cout << "Writing to file: " << file << std::endl;

    while (1)
    {
        ofstream MyFile(file);
        if (!MyFile.is_open()) {
            std::cerr << "Error opening file: " << file << std::endl;
            return;
        }
        getdemoCANData(canData);       
        MyFile << canData;

        getdemoGPSData(&gpsData[0]);
        MyFile << gpsData;
        
        // Close the file
        MyFile.close();
        cout << "Close File: " << file << std::endl;
    }
    



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

