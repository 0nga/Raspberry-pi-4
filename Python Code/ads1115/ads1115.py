
import time
import board
import busio
import adafruit_ads1x15.ads1115 as ADS
from adafruit_ads1x15.analog_in import AnalogIn

# Create the I2C bus
i2c = busio.I2C(board.SCL, board.SDA)

# Create the ADC object using the I2C bus
ads = ADS.ADS1115(i2c)

# Choose a gain (1, 2/3, 1, 2, 4, 8, or 16) for +/- 4.096V input
ads.gain = 2/3

# Create an analog input channel on pin 0
chan = AnalogIn(ads, ADS.P0)

# Main loop
while True:
    # Read the raw ADC value
    raw_value = chan.value

    # Convert the raw ADC value to voltage
    voltage = chan.voltage

    # Print the results
    print(f"Raw Value: {raw_value}, Voltage: {voltage}V")

    # Wait for a short time before the next reading
    time.sleep(1)