#include "generic.hpp"
#include <iostream>


#include <linux/can.h>

can_frame frame;
int main() {
    // Example usage of the generic functions
    test();
    std::cout << "Hello from main!" << std::endl;
    
    frame.can_id = 0x123;

    std::cout <<  frame.can_id << std::endl;
    return 0;
}