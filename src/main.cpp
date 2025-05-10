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

int main(void)
{
    int i =100;
    demo_can_sent(0x123, 8, "12345678");
    while (i--)
    {
        demo_can_recv();
        std::cout << "CAN Sockets Demo\r\n";    
    }
    
    
    std::cout << std::endl << " This is end of code test!! \r\r " << std::endl;
	return 0;
}
