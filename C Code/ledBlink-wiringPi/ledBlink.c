#include <wiringPi.h>
#include <stdio.h>

int main (void)
{
  wiringPiSetupGpio() ;
  
  int ledPin = 12;
  
  pinMode(ledPin, OUTPUT) ;
  

  for(;;){
    digitalWrite (ledPin, HIGH) ; 
    delay (1000) ;
    printf("ON");
    
    digitalWrite (ledPin,  LOW) ; 
    delay (1000) ;
    printf("OFF");

  }
  return 0 ;
}

