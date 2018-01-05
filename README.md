# plant-watering-system  

This project is created to play with Arduino and IoT solutions.  
It should help in watering plants at home to keep them full of life.  
Current implmentation checks soil moisture once every 4 hours and show it's level using 3 LED diods.  


## CHANGE LOG  

### Resolving sensor problem 05.01.2018

Moisture sensor is repleaced with different one.  
The sensor VCC is now powered by digital pin 9.  
After 4 hours of sleep the sensor is turned on, then it waits 3 seconds to stabilize power and read analog value of moisture.  
I'll see if it resolves the problem.

### Sensor problem 10.07.2017

Current implementation was working for 5 days. 
After that time one leg of the moisture sensor had destroyed because of continued work.
Probalby because of the electrolysis?

Possible solution:
Power should be turned on only for measurment purposes, and measurment should be prepared once a while (eg. 1 hour).

### Project Started 05.07.2017
