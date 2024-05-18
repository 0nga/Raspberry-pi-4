# HC-SR04 with Raspberry pi 4 (BCM2835.h)

### Install BCM2835 Library
First of all u need to install BCM2835.h library (guide @ https://github.com/0nga/Bcm2835)

### Connect the components
Download the .c source file, connect all the components as shown in the figure below

![Circuit](RPi-HCSR04.png)


Make sure to run the .exe as a root, otherwise u won't have acces to the system timer and the st_read() function will fail silently giving 0 as output.








