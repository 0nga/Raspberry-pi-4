# Meteo station web server hosted by Raspberry pi

Attempt to create the most basic web server (using Apache2) hosting a static html page containing info sent by some sensors.

I have a C program that continuously catches sensor readings after a delay of 2 seconds, convert them into useful data and write them on a .txt file (data.txt).

I also have an html static page (that will be hosted by apache2) that reloads itself every 2 seconds and fetch data from data.txt file (must be in the same directory of index.html)

- [x] html static page that read .txt file and autoreload itself 
- [x] C program that write results in a .txt file
- [ ] DHT11 temperature and humidity sensor that sends data to some Raspberry pi pins
