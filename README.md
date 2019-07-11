# cprogramming
-------
ARDUINO
-------
Starter kit Arduino projects in C
- sudo apt install avr-libc
- sudo apt install gcc-avr


----------------------------------------------------
SAMPLES CODE TO SEND AND RECEIVE ISOTP AND FD FRAMES
----------------------------------------------------

- sudo modprobe vcan
- sudo ip link add dev vcan0 type vcan
- sudo ip link set vcan0 mtu 72
- sudo ip link set up vcan0

CAN FD
- cd canfd/
- make

CAN ISOTP
- You need to load can-isotp kernel module and copy the header file
- howto -> https://github.com/hartkopp/can-isotp

- sudo cp isotp.h /usr/include/linux/can/
- cd canisotp/
- make


------
LOGGER
------
tiny logger


--------
CALLBACK
--------
sample code for a simple callback
