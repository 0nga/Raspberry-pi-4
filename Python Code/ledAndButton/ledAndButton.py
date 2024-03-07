import RPi.GPIO as GPIO    # Import Raspberry Pi GPIO library
from time import sleep     # Import the sleep function from the time module

ledPin = 21
buttonPin = 20

statoLed = GPIO.LOW

GPIO.setmode(GPIO.BCM)   # Use LOGICAL pin numbering

#GPIO.setmode(GPIO.BOARD)   # Use PHYSICAL pin numbering

GPIO.setwarnings(False)    # Ignore warning for now

GPIO.setup(ledPin, GPIO.OUT) # Set pin 21 to be an output pin
GPIO.setup(buttonPin, GPIO.IN, pull_up_down = GPIO.PUD_UP) # Set pin 20 to be an input pin and with pull down
GPIO.output(ledPin, GPIO.LOW)

while True:
    if((statoLed == GPIO.LOW) & (GPIO.input(buttonPin) == GPIO.LOW)):
        statoLed = GPIO.HIGH
        GPIO.output(ledPin, GPIO.HIGH) # Turn on
        print("LED ON")
        sleep(1)                  # Sleep for 1 second
    
    if((statoLed == GPIO.HIGH) & (GPIO.input(buttonPin) == GPIO.LOW)):
        statoLed = GPIO.LOW
        GPIO.output(ledPin, GPIO.LOW)  # Turn off
        print("LED OFF")
        sleep(1)                  # Sleep for 1 second
