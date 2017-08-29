# GarHAge
## aka the Home-Assistant-friendly, ESP8266-based Garage Door Controller

This sketch, in combination with a dual-relay module and a reed switch, implements a garage door controller (almost) completely compatible with Home Assistant's "MQTT Cover" platform.

A detailed howto and bill of materials will follow shortly.

### Quick Start

0. Download, install, and setup the Arduino IDE with ESP8266 support.
1. Load the sketch in the Arduino IDE and modify the user parameters found at the top of the sketch.
2. Upload the sketch to your ESP8266 board.
3. Connect your ESP8266 board to your relays: one for open/close, and one for stop.
4. Connect your ESP8266 board to your reed switch. 
5. Connect the relays to your garage door opener's terminals.
6. Mount the reed switch to your garage door.
7. Add the configuration provided below to your Home Assistant's configuration.yaml.
8. Power up your ESP8266 board and enjoy!

### Setting up GarHAge

#### 0. Setting up the Arduino IDE

You will modify the configuration parameters and upload the sketch to your ESP8266 board with the Arduino IDE. So, let's set it up.

1. Download the Arduino IDE for your platform from [here](https://www.arduino.cc/en/Main/Software) and install it.

### Home Assistant configuration.yaml Parameters

This project supports both Home Assistant's "MQTT Cover" and "MQTT Binary Sensor" platforms.

#### MQTT Cover

    cover:
      - platform: mqtt
        name: "Garage Door"
        state_topic: "garage/status"
        command_topic: "garage/action"
        state_open: "open"
        state_closed: "closed"
        payload_open: "OPEN"
        payload_close: "CLOSE"
        payload_stop: "STOP"
        optimistic: false
        qos: 0
        retain: false

Note: many of the above parameters are Home Assistant's defaults and, as such, are not required in your configuration.yaml. However, I would add all of the parameters in the event that one of the defaults changes on a Home Assistant upgrade.

#### MQTT Binary Sensor

    binary_sensor:
      - platform: mqtt
        name: "Garage Door"
        state_topic: "garage/status"
        payload_on: "open"
        payload_off: "closed"
        device_class: opening
        qos: 0
