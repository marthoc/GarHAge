## GarHAge Software

GarHAge must be configured and compiled in the Arduino IDE. This section details the prerequisites and steps needed to configure, compile, and flash GarHAge to your ESP8266.

### Configuring Arduino IDE

You will modify GarHAGe's configuration parameters, compile the sketch, and upload to the NodeMCU with the Arduino IDE.

#### Download and Install

Download the Arduino IDE for your platform from [here](https://www.arduino.cc/en/Main/Software) and install it.

#### Add ESP8266 Support

Add support for the ESP8266 to the Arduino IDE by following the instructions under "Installing with Boards Manager" [here](https://github.com/esp8266/arduino).

#### Libraries

All of the following libraries must be added to the Arduino IDE in order to compile GarHAge, even if you are not planning to use DHT sensor support, due to the way that the IDE handles (or does not correctly handle) conditional includes. Follow the instructions for using the Library Manager [here](https://www.arduino.cc/en/Guide/Libraries#toc3), and search for and install the most up-to-date versions of the following libraries (some may already be installed):

1. PubSubClient
1. ESP8266mDNS
1. ArduinoOTA
1. ArduinoJSON
1. DHT sensor library
1. Adafruit Unified Sensor

#### Selecting the NodeMCU / ESP8266

You may need to install a driver for the NodeMCU for your OS - Google for instructions for your specific microcontroller and platform, install the driver if necessary, and restart the Arduino IDE. (Other ESP8266-based microcontrollers may also require os-specific drivers.)

Select your board from **Tools -> Boards** in the Arduino IDE (e.g. "NodeMCU 1.0 (ESP-12E Module)").

#### Loading the Sketch and Modifying `config.h` Parameters

GarHAge's configuration parameters are found in `config.h`. After loading GarHAge.ino, select the `config.h` tab in the Arduino IDE. 

[This section](configparameters.md) describes the configuration parameters and their permitted values.

_At a minimum, you must modify the Wifi and MQTT Parameters in `config.h`, or GarHAge will not connect to your Wifi network and MQTT broker._

_IMPORTANT: No modification of the sketch code in GarHAge.ino is necessary (or advised, unless you are confident you know what you are doing and are prepared for things to break unexpectedly)._

#### Uploading the Sketch to your NodeMCU / ESP8266

If using the NodeMCU, connect it to your computer via MicroUSB; press and hold the reset button on the NodeMCU, press and hold the Flash button on the NodeMCU, then release the Reset button. Select **Sketch -> Upload** in the Arduino IDE.

If using a different ESP8266 microcontroller, follow that device's instructions for putting it into flashing/programming mode.

#### Check the Arduino IDE Serial Monitor

Open the Serial Monitor via **Tools -> Serial Monitor**. Reset your microcontroller. If all is working correctly, you should see something similar to the following messages:

```
Starting GarHAge...
Relay mode: Active-High

Connecting to your-wifi-ssid.. WiFi connected - IP address: 192.168.1.100
Attempting MQTT connection...Connected!
Publishing birth message "online" to GarHAge/availability...
Subscribing to garage/door/1/action...
Subscribing to garage/door/2/action...
Door 1 closed! Publishing to garage/door/1/status...
Door 2 closed! Publishing to garage/door/2/status...
```

If you receive these (or similar) messages, all appears to be working correctly. Disconnect GarHAge from your computer and prepare to install in your garage.