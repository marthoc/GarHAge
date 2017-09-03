# GarHAge
## a Home-Automation-friendly ESP8266-based MQTT Garage Door Controller

GarHAge allows two "dumb" garage door openers to be controlled (open/close) and report garage door status (open/closed) via MQTT. 

GarHAge is almost completely compatible with Home Assistant's "MQTT Cover" platform. It responds to HASS's open and close commands and reports door status to keep HASS's GUI in sync with the door state. GarHAge does not implement HASS's "stop" command (as this functionality varies between garage door openers) or "tilt" functionality. Sample HASS configuration snippets are provided in this repository to get your garage door openers connected to HASS as quickly and painlessly as possible.

GarHAge should be controllable via any home automation software that can configure an MQTT cover, rollershutter, garage door, or send commands over MQTT, including OpenHAB.

GarHAge has both hardware and software components. The required hardware components include an ESP8266-based microcontroller (such as the NodeMCU or Wemos D1), a relay module, and reed/magnetic switches. The software component is found in this repo.

## Hardware

### Bill of Materials

Building GarHAge to control two garage door openers requires:

| No. | Qty | Part | Link | Approx Price |
| --- | --- | ---- | ---- | ------------ |
| 1. | 1 | ESP8266-based microcontroller (e.g. NodeMCU) | [Link](https://www.amazon.com/ESP8266-NodeMcu-development-Internet-HONG111/dp/B06XBSV95D/ref=sr_1_6?ie=UTF8&qid=1504449670&sr=8-6&keywords=nodemcu) | $7.00 |
| 2. | 1 | Dual-relay module with active-high inputs | [Link](http://www.robotshop.com/en/2-channel-5v-relay-module.html) | $3.50 |
| 3. | 2 | Reed/Magnetic door switches with normally-open contacts | [Link](http://www.robotshop.com/en/magnetic-door-switch-set.html) | $6.00 |
| 4. | 1 | 5v MicroUSB power supply | [Link](http://www.robotshop.com/en/wall-adapter-power-supply-5vdc-2a.html) | $6.00 |
| 5. | 1 | Mini solderless breadboard | [Link](http://www.robotshop.com/en/170-tie-point-mini-self-adhesive-solderless-breadboard-white.html) | $4.00 |
| 6. | | Bell/low voltage two-conductor wire | | |
| 7. | | Male-to-female breadboard jumper wires | | |
| 8. | | Project box or case | | |

### Detailed Bill of Materials

#### 1. ESP8266-based microcontroller

I recommend the NodeMCU as GarHAge was developed and is tested on it. Its advantages are: 
- it comes with header pins already soldered so that it can plug directly into a mini solderless breadboard;
- its VIN (or VU on the LoLin variant) port can power the 5v relay module;
- it can be powered and programmed via MicroUSB;
- it has Reset and Flash buttons, making programming easy.

But, Garhage should also work with the Adafruit HUZZAH, Wemos D1, or similar, though you may need to adjust the GPIO ports used by the sketch to match the ESP8266 ports that your microcontroller makes available.

#### 2. Dual-relay module with active-high inputs

A dual-relay module (as opposed to individual 5v relays) makes setup easy: just plug jumper wires from the module's VCC, CH1, CH2, and GND pins to the NodeMCU. These relay modules generally also include LEDs to ease troubleshooting. 

Most importantly, because the relay module is powered by 5v, its inputs can be triggered by the NodeMCU's GPIOs.

GarHAge will only work with relay modules that are active-high (meaning that the relay is triggered by a HIGH output from a GPIO pin). Note that many modules available on Amazon, eBay, or AliExpress are active-low, which is **not supported** by GarHAge.

3. Two reed / magnetic door switches with normally-open contacts (one per garage door); normally-closed switches will not currently work with GarHAge, though logic inversion is planned for a future update.
    - [This switch is the one I use for my doors](http://www.robotshop.com/en/magnetic-door-switch-set.html). If you use this switch, you will need to solder an additional length of wire to the short wires attached to the switch in order to reach from your garage door to your garage door opener, where GarHAge will likely be mounted.
    
4. Bell/low voltage two-conductor wire to make connections from the quad-relay module to your garage door openers.

5. A 5v micro USB power supply to power the NodeMCU.

6. Mini solderless breadboard (170 tie-point); the NodeMCU mounts to this type of breadboard nicely, leaving one row of female ports next to each NodeMCU port and making it simple to use male-to-female jumper wires to make connections from the NodeMCU to the quad-relay module. The bell wire attached to the reed switches will also plug into the breadboard ports, making for a clean installation.
    - e.g. [this breadboard](http://www.robotshop.com/en/170-tie-point-mini-solderless-breadboard-black.html).

7. Male-to-female breadboard jumper wires to connect the NodeMCU to the quad-relay module (6).

8. A project box or case to hold the NodeMCU and quad-relay module.

**Note:** If you are building GarHAge to control only one garage door, you will only require a dual-relay module ([e.g. this module](http://www.robotshop.com/en/2-channel-5v-relay-module.html), and a single reed switch.

### Building and Installing GarHAge

1. Attach your NodeMCU to the mini solderless breadboard, leaving one row of ports next to each NodeMCU pin.
2. Mount the mini solderless breadboard in your project box.
3. Mount the quad-relay module in your project box.
4. To be continued...

## Quick Start

0. Download, install, and setup the Arduino IDE with ESP8266 support.
1. Load the sketch in the Arduino IDE and modify the user parameters found at the top of the sketch.
2. Upload the sketch to your ESP8266 board.
3. Connect your ESP8266 board to your relays: one for open/close, and one for stop.
4. Connect your ESP8266 board to your reed switch. 
5. Connect the relays to your garage door opener's terminals.
6. Mount the reed switch to your garage door.
7. Add the configuration provided below to your Home Assistant's configuration.yaml.
8. Power up your ESP8266 board and enjoy!

## Setting up GarHAge

### 0. Setting up the Arduino IDE

You will modify the configuration parameters and upload the sketch to your ESP8266 board with the Arduino IDE. 

So, let's set it up.

1. Download the Arduino IDE for your platform from [here](https://www.arduino.cc/en/Main/Software) and install it.
2. Add support for the ESP8266 to the Arduino IDE by following the instructions under "Installing with Boards Manager" [here](https://github.com/esp8266/arduino).
3. Add the "PubSubClient" library to the Arduino IDE: follow the instructions for using the Library Manager [here](https://www.arduino.cc/en/Guide/Libraries#toc3), and search for and install the PubSubClient library.

### 1. Modifying the user parameters in the sketch

User-configurable parameters are found at the top of the sketch between the "Start of user-configurable parameters" and "End of user-configurable parameters" comments. You must modify these parameters to match your setup for the sketch to work!

#### Wifi details parameters

ssid = the wifi SSID you want GarHAge to join

password = the password for the wifi SSID you want GarHAge to join

#### Static IP details parameters

static_ip = set this to "static" to use the IP, Gateway, and Subnet parameters that follow; set to "dhcp" (or anything else) to obtain an IP address via DHCP (default "dhcp")

IPAddress ip(192,168,1,100) = the static IP you want to assign to GarHAge (default 192.168.1.100)

IPAddress gateway(192,168,1,1) = the gateway IP you want GarHAge to use (default 192.168.1.1) 

IPAddress subnet(255,255,255,0) = the subnet mask you want GarHAge to use (default 255.255.255.0)

NOTE: in the IPAddress parameters above, the octets are separated by commas (,) and not periods (.)!!!

#### MQTT Server details parameters

mqtt_server = the IP address/hostname of your MQTT broker

mqtt_clientId = the client ID by which GarHAge will identify itself to your MQTT broker; should be unique (default GarHAge)

mqtt_username = the username required to authenticate to your MQTT broker (for no authentication, use "")

mqtt_password = the password required to authenticate to your MQTT broker (for no authentication, use "")

#### MQTT Topic/Payload details parameters

mqtt_door1_action_topic = the topic GarHAge will subscribe to and listen for action commands for Door 1 (default "garage/door/1/action")

mqtt_door1_status_topic = the topic GarHAge will publish status messages to for Door 1 (default "garage/door/1/status")

mqtt_door2_action_topic = the topic GarHAge will subscribe to and listen for action commands for Door 2 (default "garage/door/2/action")

mqtt_door2_status_topic = the topic GarHAge will publish status messages to for Door 2 (default "garage/door/2/status")

#### GPIO pin details parameters

door1_openPin = the pin connected to the relay that controls Door 1 opening (default GPIO4)

door1_closePin = the pin connected to the relay that controls Door 1 closing (default GPIO4)

door1_stopPin = the pin connected to the relay that controls Door 1 stopping (default GPIO5)

door1_statusPin = the pin connected to the reed switch attached to Door 1 (default GPIO14)

door2_openPin = the pin connected to the relay that controls Door 2 opening (default GPIO2)

door2_closePin = the pin connected to the relay that controls Door 2 closing (default GPIO2)

door2_stopPin = the pin connected to the relay that controls Door 2 stopping (default GPIO12)

door2_statusPin = the pin connected to the reed switch attached to Door 2 (default GPIO13)

#### Miscellaneous parameters

door1_alias = the name to use for Door 1 in serial messages (default "Door 1")

door2_alias = the name to use for Door 2 in serial messages (default "Door 2")

mqtt_status_update_interval = publish a status message for each door every X seconds; use this parameter if you find your door status in HA becomes out of sync after HA or broker restarts (default 0 (disabled); any integer > 0 to enable; 60 is a reasonable value)

NOTE: mqtt_status_update_interval is currently NOT enabled in the sketch and changing this value will therefore currently do nothing (this feature is planned for a future update)

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
