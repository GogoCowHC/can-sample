#ifndef generic_hpp
#define generic_hpp


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdbool>
#include <cstdint>





/* declare function here*/

extern "C" {
    int serialGetchar (const int fd);
    int serialDataAvail (const int fd);
    int serialOpen (const char *device, const int baud);
    int serialClose (const int fd);
   

}

extern "C" {   
    void test (void);}
#endif /* generic_hpp*/
// This file is part of the C Generic Library.