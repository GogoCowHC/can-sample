#ifndef generic_hpp
#define generic_hpp


#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdbool>
#include <cstdint>

extern void format_can_timestamp(struct timeval tv);

extern "C" {
    #include <wiringPi.h>
    #include <wiringSerial.h>
    }

/* declare function here*/


extern "C" {   
    void getdemoGPSData(char gpsData[]);
    void readdemoUart (void);
    void test (void);}


#endif /* generic_hpp*/
// This file is part of the C Generic Library.