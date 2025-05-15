#include "generic.hpp"
#include <iostream>
#include <fstream>


#include <iomanip>
#include <random>
#include <thread>
#include <chrono>

#include "Utilities.h"
#include "RecordMngr.h"
#include "CANItem.h"

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
#include "Config.h"
#include "Utilities.h"
#include "RecordMngr.h"
#include "CANItem.h"

using namespace std;


string canData;
string gpsData;


int sub_demo_main()
{
    char gpsData[100];
    
    std::thread t_CAN(demo_can_recvWithTimestamp);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
    std::thread t_GPS(getdemoGPSData    , &gpsData[0]);
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    t_CAN.join();
    t_GPS.join();

    // while (recordMngr.isWritingFile())
    // {
    //     cout << "Wait for writing file..." << endl;
    //     std::this_thread::sleep_for(std::chrono::seconds(1));
    // }
    // cout << "Writing file done!" << endl;

    return 0;
}

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
    int i = 20;

    string file = "test/log.txt";
    cout << "Writing to file: " << file << std::endl;
    
    ofstream MyFile(file);

    if (!MyFile.is_open()) {
        std::cerr << "Error opening file: " << file << std::endl;
        return;
    }

    while (i--)
    {

        getdemoCANData(canData);       
        MyFile << canData;
        cout << canData;
        
        // getdemoGPSData(&gpsData[0]);
        // MyFile << gpsData;
        // cout << gpsData;
        // Close the file
        
    }
    
    MyFile.close();
    cout << "Close File: " << file << std::endl;
    return;
}

void setup_can_interface(const char *interface, int bitrate) {
    char command[100];

    // Construct the command string
    snprintf(command, sizeof(command), "ip link set %s up type can bitrate %d", interface, bitrate);

    // Execute the command
    int ret = system(command);
    if (ret == -1) {
        perror("Failed to execute command");
    } else {
        cout<<"CAN interface "<<interface<<" set up successfully with bitrate "<<bitrate<<endl;
    }
}

int main(void)
{
    setup_can_interface("can0", 500000);
    // int i =100000;
    // demo_can_sent(0x123, 8, "12345678");
    // while (i--)
    // {
    //     demo_can_recv();
    //     std::cout << "CAN Sockets Demo\r\n";    
    // }
    
    //std::cout << "GPS start \r\n";
    // readdemoUart();
//    writeToFile();

    // while (1)
    // {
    //     demo_can_recvWithTimestamp();
    // }
    

    while (1){
        sub_demo_main();
    }


    std::cout << std::endl << " This is end of code test!! \r\r " << std::endl;
	return 0;
}

