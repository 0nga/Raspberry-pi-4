#include <wiringPi.h>
#include <stdio.h>

int main (void)
{
  wiringPiSetupGpio() ;
  
  int potPin = 21;
  int ledPin = 20;
  
  pinMode(potPin, INPUT) ;
  pinMode(ledPin, OUTPUT) ;
  digitalWrite(ledPin,LOW);

  int statoLed = 0;
  
  for(;;){
  
    if(digitalRead(potPin)==HIGH && statoLed == 1 ){
      
      digitalWrite(ledPin,LOW);
      statoLed = 0;
      delay(1000);
    } 
    
    if(digitalRead(potPin)==HIGH && statoLed == 0 ){
      
      digitalWrite(ledPin,HIGH);
      statoLed = 1;

      delay(1000);
    }
  }
  return 0 ;
}

