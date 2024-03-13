# Meteo station web server hosted by Raspberry pi

Attempt to create the most basic web server (using Apache2) hosting an html page containing info sent by some sensors.

I have a C program that continuously catches sensor readings after a delay of 2 seconds, convert them into useful data and write them on a .csv file (data.csv).

Then an html page (in my case hosted by apache2) fetch data from data.csv file (must be in the same directory of index.html). This page show the last row of the file, the reload itself every 2 seconds and repeat the same thing.

- [x] html page that read .csv file and display the last row
- [x] C program that write results in a .csv file (random generated value that simulates sensor reading)
- [ ] DHT11 temperature and humidity sensor that sends data to some Raspberry pi pins
