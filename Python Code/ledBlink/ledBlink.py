import RPi.GPIO as GPIO    # Import Raspberry Pi GPIO library
from time import sleep     # Import the sleep function from the time module

ledPin = 21

#GPIO.setmode(GPIO.BCM)   # Use LOGICAL pin numbering

GPIO.setmode(GPIO.BOARD)   # Use PHYSICAL pin numbering

GPIO.setwarnings(False)    # Ignore warning for now

GPIO.setup(ledPin, GPIO.OUT)   # Set pin 8 to be an output pin



while True:
    GPIO.output(ledPin, GPIO.HIGH) # Turn on
    print("LED ON")
    sleep(1)                  # Sleep for 1 second
    
    GPIO.output(ledPin, GPIO.LOW)  # Turn off
    print("LED OFF")
    sleep(1)                  # Sleep for 1 secondß
