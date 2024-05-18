
/* Author: Andrea Ongarini
 * C program that drives a HC-SR04 sensor 
 * to print the distance measurement (unit measure: cm)
 * TRIGGER PIN connected to GPIO 27
 * ECHO PIN connected to GPIO 17 using 2 resistor:
 * - 1kohm resistor between ECHO pin and jumper that goes to GPIO 17
 * - 2.2 kohm resistor between the same jumper to GND
 * Voltage divider to avoid "high" voltage to go straight into the RPI pin */
 
#include <bcm2835.h>
#include <stdio.h>

#define ECHO RPI_BPLUS_GPIO_J8_11 // GPIO17
#define TRIGGER RPI_BPLUS_GPIO_J8_13 //GPIO27

int main(int argc, char **argv){

    uint64_t timeSpan, start, end;
    double distance=0;
    
    if(!bcm2835_init())
      return 1;

    bcm2835_gpio_fsel(TRIGGER, BCM2835_GPIO_FSEL_OUTP);
    bcm2835_gpio_fsel(ECHO, BCM2835_GPIO_FSEL_INPT);
    
    while(1){
	distance = 0;
	start = 0;
	end = 0;
	
	bcm2835_gpio_write(TRIGGER, LOW);
	printf("Trigger low, ");
	
	bcm2835_gpio_write(TRIGGER, HIGH);
	printf("trigger high\n");
	bcm2835_delayMicroseconds(10);
	
	bcm2835_gpio_write(TRIGGER, LOW);
	
	while(bcm2835_gpio_lev(ECHO) == LOW){
	    start = bcm2835_st_read();
	}
	
	printf("Start time: %lu\n", start); 
	
	while(bcm2835_gpio_lev(ECHO) == HIGH){
	    end = bcm2835_st_read();
	    bcm2835_delayMicroseconds(1);
	}
	timeSpan = end - start;

	printf("End Time: %lu\n", end); 
	printf("Time span: %lu\n", timeSpan);
	
	distance = timeSpan / 58; // simple conversion (there is a longer formula, but this one does the same)
	
	if(timeSpan > 38000){
	    printf("Out Of Range\n");
	}
	else{	    
	    printf("--------------------------------\n");
	    printf("Distance %f\n", distance);
	    printf("--------------------------------\n");
	}
	
	bcm2835_delay(2000);
    }
    bcm2835_close();
    return 0;
}

