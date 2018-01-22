# GarHAge
## a Home-Automation-friendly ESP8266-based MQTT Garage Door Controller

GarHAge allows:

- two "dumb" garage door openers to be controlled (open/close) and report garage door status (open/closed) via MQTT;

- two auxiliary doors (e.g. a garage side-door and house-door) to report their status (open/closed) via MQTT;

- garage temperature and humidity readings (via a DHT11 or 22) to be reported over MQTT.

GarHAge is compatible with the following Home Assistant platforms: 

- "MQTT Cover", responding to HA's open and close commands and reporting door status to keep HA's GUI in sync with the garage door state; 

- "MQTT Binary Sensor", reporting door status to keep HA binary sensors for the auxiliary doors in sync with the door state; 

- "MQTT Sensor", reporting temperature and humidity readings to keep HA sensors up-to-date.

- "Template Cover", providing for control of garage door open/close only, and allowing the user to rely on a different means of reporting the door state in HA (e.g. a Zwave/ZigBee tilt sensor or similar).

Complete HA configuration snippets and sample automations are provided to get your garage connected to HA as quickly and painlessly as possible, but GarHAge should also be compatible with any home automation software that can configure an MQTT cover, rollershutter, garage door, switch, or send commands over MQTT, including OpenHAB.

GarHAge has both hardware and software components. The required hardware components include an ESP8266-based microcontroller (such as the NodeMCU), a relay module, and reed/magnetic switches. The software component is found in this repo.

Best of all, if you select the proper parts, building and installing GarHAge requires **no soldering**!

### Table of Contents

1. [Hardware](hardware.md)
1. [Software](software.md)
1. [Installing GarHAge](installing.md)
1. [GarHAge MQTT "API"](api.md)
1. [Configuring Home Assistant](configuringHA.md)

### Contributing

Fork this repository, create a feature branch, and submit a Pull Request. For more complex features or changes, it may be best to open an Issue with the proposed changes first. Similarly, simple changes may also be best accomplished via an Issue rather than a Pull Request.

### Issues / Feature Requests

Please open an Issue and describe your problem in as much detail as possible along with the steps necessary to replicate the problem. It will also be helpful to include the content of your `config.h` in code tags and indicate whether (and how) you modified `GarHAge.ino`.
