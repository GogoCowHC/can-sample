# can-sample


> git clone https://github.com/GogoCowHC/can-sample.git

> cmake can-sample

> cd can-sample

> make

> ./can-sample


#pre condition
1. Install can-utils: https://github.com/tolgakarakurt/CANBus-MCP2515-Raspi
2. Install WiringPi: https://github.com/WiringPi/WiringPi

    a. below command in instruction might not work:
       
    >mv debian-template/wiringpi-3.0-1.deb .
    
    >sudo apt install ./wiringpi-3.0-1.deb

    Due to package version is changed. After build "./build debian" run the below command: 

    > ls debian-template

    Then check the package name returned and use it instead of "wiringpi-3.0-1.deb"

    b. in GPS code "/dev/ttyAMA0" might not available in some device. Try
    
    > ls /dev

    then check which component is there. Else could try "/dev/serial0" or "/dev/tty0"

    c. Some case could not access ""/dev/ttyAMA0" due to permission denied. try to use "sudo" 

3. File might not be create or write due to permission: 

    > sudo chmod 777 folder_name




    