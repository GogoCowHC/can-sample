

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <wiringPi.h>
#include <wiringSerial.h>

void test (void){
    // Test the print_dummy function
    printf("Hello, World!");
    printf("This is a test of the print_dummy function. \r\n");
}

void readUart (void)
{
    
 
    int fd;
    char c;
    printf("Raspberry's receiving : \n");
    
    while(1) {
        if((fd = serialOpen ("/dev/ttyAMA0", 9600)) < 0 ){
            printf( "Unable to open serial device: \n");
        }else{
            do{
                c = serialGetchar(fd);
                printf(" %c",c);
            }while(serialDataAvail(fd));
        }
    }

    


   printf("UART end \r\n");
    return ;
}