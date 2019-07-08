#!/usr/bin/python3
from sense_hat import SenseHat
sense = SenseHat()

# Sense Hat

## Show message
sense.clear()
sense.show_message("HKG ELEC3542")



## Sensors

### Humidity
sense.get_humidity()

### Pressure
sense.get_pressure()

### Temperature
sense.get_temperature() # from HTS221 humidity and temperature sensor
sense.get_temperature_from_humidity() # from HTS221 humidity and temperature sensor
sense.get_temperature_from_pressure() # From LPS25H pressure and temperature sensor



## Movement
### Roll, Pitch, Yaw
sense.get_orientation_degrees()
sense.get_orientation_radians()

### individual elements
orientation = sense.get_orientation_degrees()
pitch = orientation ['pitch']
yaw = orientation ['yaw']
roll = orientation ['roll']



## Print
print(time.time())



## Sleep
import time
time.sleep(10) # 10 sec



## Time
import datetime
datetime.datetime.now() # 2017-02-27 23:16:08.960965



## Write file
# Logging function with the temperature value as argument
# https://docs.python.org/release/3.1.5/library/stdtypes.html#old-string-formatting-operations
def log_temperature_to_file(temperature, currentTime):

	# Open (or create if not exists) the file named "temperature.txt"
	# in "append" mode
	temp_log = open("temperature.txt", "a")

	# Write the line to the given file
	temp_log.write("[%s] "% currentTime) 
	temp_log.write("T: %.2f \n"% temperature)

	# Close the file after writing
	temp_log.close()



# ThingSpeak
import requests

api_key = "NITHMFTX0I0XSC93"
temperature = 25.5
humidity = 60.0
pressure = 1013.0

data = { "api_key": api_key, "field1": temperature, "field2": humidity, "field3": pressure }
req = requests.post("https://api.thingspeak.com/update", data=data)
# https://www.mathworks.com/help/thingspeak/update-channel-feed.html



# MQTT
# $ sudo pip3 install paho-mqtt
