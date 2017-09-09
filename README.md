# GarHAge
## a Home-Automation-friendly ESP8266-based MQTT Garage Door Controller

GarHAge allows two "dumb" garage door openers to be controlled (open/close) and report garage door status (open/closed) via MQTT. 

GarHAge is almost completely compatible with Home Assistant's "MQTT Cover" platform. It responds to HASS's open and close commands and reports door status to keep HASS's GUI in sync with the door state. GarHAge does not implement HASS's "stop" command (as this functionality varies between garage door openers) or "tilt" functionality. Sample HASS configuration snippets are provided in this repository to get your garage door openers connected to HASS as quickly and painlessly as possible.

GarHAge should be controllable via any home automation software that can configure an MQTT cover, rollershutter, garage door, or send commands over MQTT, including OpenHAB.

GarHAge has both hardware and software components. The required hardware components include an ESP8266-based microcontroller (such as the NodeMCU), a relay module, and reed/magnetic switches. The software component is found in this repo.

Best of all, if you select the proper parts, building and installing a GarHAge requires **no soldering**! 


## How GarHAge works...

GarHAge subscribes to a configurable MQTT topic for each of two garage doors (by default, `garage/door/1/action` and `garage/door/2/action`). 

When the `OPEN` payload is received on either of these topics, GarHAge momentarily activates a relay connected to the relevant garage door opener to cause the door to open.

When the `CLOSE` payload is received on either of these topics, GarHAge momentarily activates a relay connected to the relevant garage door opener to cause the door to close. By default, GarHAge is configured to activate the same relay for the `OPEN` and `CLOSE` payloads.

When the `STATE` payload is received on either of these topics, GarHAge publishes the status (`open` or `closed`) of the relevant garage door to the configurable topic `garage/door/1/status` or `garage/door/2/status`. These messages are published with the "retain" flag set.

When the state of a garage door changes (because GarHAge has triggered the door to open or close, or because the door has been opened or closed via a remote, pushbutton switch, or manually), GarHAge publishes the status (`open` or `closed`) of the relevant garage door to `garage/door/1/status` or `garage/door/2/status`. These messages are published with the "retain" flag set.

_Note: To address a current issue in Home Assistant that may result in MQTT platforms not showing the correct garage door status (open/closed) after a HASS restart, GarHAge can also subscribe to Home Assistant's_ `birth_message` _topic (by default_ `hass/status`_) and listen for the_ `birth_message` _payload (by default_ `online`_). When this message is received, GarHAge will publish a status update for Door 1 and Door 2 (if enabled) to ensure that the garage door status (open/closed) is displayed in the HASS GUI for both the cover and binary sensor platforms._


## Hardware

### Bill of Materials

Building GarHAge to control two garage door openers requires:

| No. | Qty | Part | Link | Approx Price |
| --- | --- | ---- | ---- | ------------ |
| 1. | 1 | ESP8266-based microcontroller (e.g. NodeMCU) | [Link](https://www.amazon.com/ESP8266-NodeMcu-development-Internet-HONG111/dp/B06XBSV95D/ref=sr_1_6?ie=UTF8&qid=1504449670&sr=8-6&keywords=nodemcu) | $ 7.00 |
| 2. | 1 | Dual-relay module with active-high inputs | [Link](http://www.robotshop.com/en/2-channel-5v-relay-module.html) | $ 4.00 |
| 3. | 2 | Reed/Magnetic door switches | [Link](http://a.co/bEomwwP) | $ 12.00 |
| 4. | 1 | 5v MicroUSB power supply | [Link](http://www.robotshop.com/en/wall-adapter-power-supply-5vdc-2a.html) | $ 6.00 |
| 5. | 1 | Mini solderless breadboard (170 tie-point) | [Link](http://www.robotshop.com/en/170-tie-point-mini-self-adhesive-solderless-breadboard-white.html) | $ 4.00 |
| 6. | | Bell/low voltage two-conductor wire | | |
| 7. | | Male-to-female breadboard jumper wires | | |
| 8. | | Project box or case | | |

**Approximate total cost for major components:** $ 33.00, even less if you don't mind a long lead time and source your components from AliExpress/BangGood.

**Note:** If you are building GarHAge to control only one garage door opener, you will only require a single-relay module, and a single reed switch.


### Detailed Bill of Materials

#### 1. ESP8266-based microcontroller

I recommend the NodeMCU as GarHAge was developed and is tested on it. Its advantages are: 
- it comes with header pins already soldered so that it can plug directly into a mini solderless breadboard;
- its VIN (or VU on the LoLin variant) port can power the 5v relay module;
- it can be powered and programmed via MicroUSB;
- it has Reset and Flash buttons, making programming easy.

Accordingly, this guide is written with the NodeMCU in mind.

But, Garhage should also work with the Adafruit HUZZAH, Wemos D1, or similar, though you may need to adjust the GPIO ports used by the sketch to match the ESP8266 ports that your microcontroller makes available.

#### 2. Dual 5v relay module with active-high inputs

A dual 5v relay module (as opposed to individual 5v relays) makes setup easy: just plug jumper wires from the module's VCC, CH1, CH2, and GND pins to the NodeMCU. These relay modules generally also include LEDs to ease troubleshooting. 

Most importantly, because the relay module is powered by 5v, its inputs can be triggered by the NodeMCU's GPIOs.

GarHAge will only work with relay modules that are active-high (meaning that the relay is triggered by a HIGH output from a GPIO pin). Note that many modules available on Amazon, eBay, or AliExpress are active-low, which is **not supported** by GarHAge.

#### 3. Reed/magnetic door switches

GarHAge will work with both normally-open and normally-closed reed switches (be sure to set the relevant config parameter to match the type of switch in use). Many switches with screw terminals are available, making placement and wiring easy.

#### 4. 5v MicroUSB power supply

Power your NodeMCU via the same type of power supply used to charge Android phones or power a RaspberryPi. Powering the NodeMCU via MicroUSB is important since the relay module can then be powered via the NodeMCU VIN (or VU on the LoLin variant) port.

#### 5. Mini solderless breadboard (170 tie-point)

The NodeMCU mounts to this breadboard nicely, leaving one female port next to each NodeMCU port and making it easy to use male-to-female jumper wires to make connections from the NodeMCU to the relay module. The bell wire attached to the reed switches will also plug into the breadboard ports, making for a clean and solderless installation. Finally, these mini breadboards often also have an adhesive backing, making mounting in your project box easy.

#### 6. - 8. Miscellaneous parts

To install GarHAge, you will also require:
- Enough bell/low voltage two-conductor wire to make connections from each reed/magnetic switch at your garage doors to where GarHAge is mounted and to make connections from GarHAge to each garage door opener.
- Male-to-female breadboard jumper wires to make connections from the NodeMCU to the dual-relay module (4 jumper wires required).
- a project box to hold both the NodeMCU and dual-relay module.

### Building GarHAge

1. Attach your NodeMCU to the middle of the mini solderless breadboard, leaving one female port next to each NodeMCU port.
2. Mount the mini solderless breadboard in your project box.
3. Mount the dual-relay module in your project box.
4. Plug a jumper wire from VCC on the relay module to VIN / VU on the NodeMCU.
5. Plug a jumper wire from GND on the relay module to GND on the NodeMCU.
6. Plug a jumper wire from CH1 on the relay module to D2 on the NodeMCU (or Arduino/ESP8266 GPIO4).
7. Plug a jumper wire from CH2 on the relay module to D1 on the NodeMCU (or Arduino/ESP8266 GPIO5).

_Done!_


## Software

### 1. Set up the Arduino IDE

You will modify the configuration parameters and upload the sketch to the NodeMCU with the Arduino IDE.

1. Download the Arduino IDE for your platform from [here](https://www.arduino.cc/en/Main/Software) and install it.
2. Add support for the ESP8266 to the Arduino IDE by following the instructions under "Installing with Boards Manager" [here](https://github.com/esp8266/arduino).
3. Add the "PubSubClient" library to the Arduino IDE: follow the instructions for using the Library Manager [here](https://www.arduino.cc/en/Guide/Libraries#toc3), and search for and install the PubSubClient library.
4. You may need to install a driver for the NodeMCU for your OS - Google for instructions for your specific microcontroller and platform, install the driver if necessary, and restart the Arduino IDE.
5. Select your board from `Tools - Boards` in the Arduino IDE (e.g. "NodeMCU 1.0 (ESP-12E Module)").

### 2. Load the sketch in the Arduino IDE and modify the user parameters in config.h

GarHAge's configuration parameters are found in config.h. After loading GarHAge.ino, select the config.h tab in the Arduino IDE. This section describes the configuration parameters and their permitted values. 

_IMPORTANT: No modification of the sketch code in GarHAge.ino is necessary (or advised, unless you are confident you know what you are doing and are prepared for things to break unexpectedly)._

#### Wifi Parameters

`WIFI_SSID "your-wifi-ssid"` 

The wifi ssid GarHAge will connect to. Must be placed within quotation marks.

`WIFI_PASSWORD "your-wifi-password"` 

The wifi ssid's password. Must be placed within quotation marks.

#### Static IP Parameters

`STATIC_IP false` 

Set to `true` to use the IP / GATEWAY / SUBNET parameters that follow. Set to `false` to use DHCP. _(Default: false)_

`IP 192,168,1,100` 

The static IP you want to assign to GarHAge. _(Default: 192.168.1.100)_

`GATEWAY 192,168,1,1` 

The gateway you want GarHAge to use. _(Default: 192.168.1.1)_

`SUBNET 255,255,255,0` 

The subnet mask you want GarHAge to use. _(Default: 255.255.255.0)_

_Note: There are commas (,) not periods (.) in the IP / GATEWAY / SUBNET parameters above!_

#### MQTT Parameters

`MQTT_BROKER "w.x.y.z"` 

The IP address of your MQTT broker. Must be placed within quotation marks.

`MQTT_CLIENTID "GarHAge"` 

The Client ID you want GarHAge to use. Should be unique among all the devices connected to your broker. Must be placed within quotation marks. _(Default: Garhage)_

`MQTT_USERNAME "your-mqtt-username"` 

The username required to authenticate to your MQTT broker. Must be placed within quotation marks. Use "" (i.e. a pair of quotation marks) if your broker does not require authentication.

`MQTT_PASSWORD "your-mqtt-password"` 

The password required to authenticate to your MQTT broker. Must be placed within quotation marks. Use "" (i.e. a pair of quotation marks) if your broker does not require authentication.

#### Door 1 Parameters

`DOOR1_ALIAS "Door 1"` 

The alias to be used for Door 1 in serial messages. Must be placed within quotation marks. _(Default: Door 1)_

`MQTT_DOOR1_ACTION_TOPIC "garage/door/1/action"` 

The topic GarHAge will subscribe to for action commands for Door 1. Must be placed within quotation marks. _(Default: garage/door/1/action)_

`MQTT_DOOR1_STATUS_TOPIC "garage/door/1/status"` 

The topic GarHAge will publish Door 1's status to. Must be placed within quotation marks. _(Default: garage/door/1/status)_

`DOOR1_OPEN_PIN D2` 

The GPIO pin connected to the relay that is connected to Door 1's garage door opener's open terminals. _(Default: NodeMCU D2 / Arduino 4)_

`DOOR1_CLOSE_PIN D2` 

The GPIO pin connected to the relay that is connected to Door 1's garage door opener's close terminals. If your garage door opener is like most (all?), the same terminals control open and close via a momentary connection of the terminals. In this case, set DOOR1_CLOSE_PIN and DOOR1_OPEN_PIN to the same pin. _(Default: NodeMCU D2 / Arduino 4)_

`DOOR1_STATUS_PIN D5` 

The GPIO pin connected to the reed/magnetic switch attached to Door 1. _(Default: NodeMCU D5 / Arduino 14)_

`DOOR1_STATUS_SWITCH_LOGIC "NO"` 

The type of reed/magnetic switch used for Door 1. Must be placed within quotation marks. Set to `"NO` for normally-open. Set to `"NC"` for normally-closed. _(Default: NO)_

#### Door 2 Parameters

`DOOR2_ENABLED false`

Set to `true` to enable GarHAge to control/monitor Door 2. Set to `false` to disable Door 2. _(Default: false)_

`DOOR2_ALIAS "Door 2"` 

The alias to be used for Door 2 in serial messages. Must be placed within quotation marks. _(Default: Door 2)_

`MQTT_DOOR2_ACTION_TOPIC "garage/door/2/action"` 

The topic GarHAge will subscribe to for action commands for Door 2. Must be placed within quotation marks. _(Default: garage/door/2/action)_

`MQTT_DOOR2_STATUS_TOPIC "garage/door/2/status"` 

The topic GarHAge will publish Door 2's status to. Must be placed within quotation marks. _(Default: garage/door/2/status)_

`DOOR2_OPEN_PIN D1` 

The GPIO pin connected to the relay that is connected to Door 2's garage door opener's open terminals. _(Default: NodeMCU D1 / Arduino 5)_

`DOOR2_CLOSE_PIN D1` 

The GPIO pin connected to the relay that is connected to Door 2's garage door opener's close terminals. If your garage door opener is like most (all?), the same terminals control open and close via a momentary connection of the terminals. In this case, set DOOR2_CLOSE_PIN and DOOR2_OPEN_PIN to the same pin. _(Default: NodeMCU D1 / Arduino 5)_

`DOOR2_STATUS_PIN D6` 

The GPIO pin connected to the reed/magnetic switch attached to Door 2. _(Default: NodeMCU D6 / Arduino 12)_

`DOOR2_STATUS_SWITCH_LOGIC "NO"` 

The type of reed/magnetic switch used for Door 2. Must be placed within quotation marks. Set to `"NO` for normally-open. Set to `"NC"` for normally-closed. _(Default: NO)_

#### Home Assistant Workaround Parameters

_Note: These parameters are temporary until a bug in HASS (and perhaps the underlying Paho MQTT library that HASS relies on for MQTT communication) is resolved. It appears that, on restart, HASS does not properly resubscribe to topics it was previously subscribed to, such that it does not receive retained messages on the MQTT broker when it resubscribes. GarHAge addresses this problem by listening for a "birth message" that HASS can send when it connects to the MQTT broker. When GarHAge receives this message, it publishes the status of Door 1 and Door 2 (if enabled) on MQTT_DOOR1_STATUS_TOPIC and MQTT_DOOR2_STATUS_TOPIC, ensuring that HASS will receive these messages. Until the HASS/Paho bug is resolved, if you are using HASS I recommend using the below parameters; otherwise, if HASS is stopped and restarted the cover platform will show an "unknown" state and the binary sensor platform will show "closed", regardless the actual state of the door, until the first time the door state changes.

`HOMEASSISTANT true`

Set to `true` if using Home Assistant. Set to `false` if not using Home Assistant. Note that `true` will also require you to configure HASS's configuration.yaml to enable the birth_message (set out below). _(Default: true)_

`HASS_BIRTH_TOPIC "hass/status"`

The topic GarHAge will subscribe to to listen for HASS's birth message. Must be placed within quotation marks. _(Default: hass/status)_

`HASS_BIRTH_PAYLOAD "online"`

The payload HASS will send on the `HASS_BIRTH_TOPIC` when it connects to the MQTT broker. Must be placed within quotation marks. _(Default: online)_

### 3. Upload the sketch to your NodeMCU / microcontroller

If using the NodeMCU, connect it to your computer via MicroUSB; press and hold the reset button on the NodeMCU, press and hold the Flash button on the NodeMCU, then release the Reset button. Select `Sketch - Upload` in the Arduino IDE.

If using a different ESP8266 microcontroller, follow that device's instructions for putting it into flashing/programming mode.

### 4. Check the Arduino IDE Serial Monitor

Open the Serial Monitor via `Tools - Serial Monitor`. Reset your microcontroller. If all is working correctly, you should see something similar to the following messages:

```
Starting GarHAge...

Connecting to your-wifi-ssid
..
WiFi connected
IP address: 192.168.1.100
Attempting MQTT connection...Connected!
Subscribing to garage/door/1/action...
Subscribing to garage/door/2/action...
Door 1 closed! Publishing to garage/door/1/status...
Door 2 closed! Publishing to garage/door/2/status...
```

If you receive these (or similar) messages, all appears to be working correctly. Disconnect GarHAge from your computer and prepare to install in your garage.

## Installing GarHAge

1. Mount GarHAge in your garage.
2. Mount the reed switch for Door 1.
3. Run bell/low voltage wire from Door 1's reed switch to the NodeMCU; strip the wires and plug into D5 and GND.
4. Mount the reed switch for Door 2.
5. Run bell/low voltage wire from Door 2's reed switch to the NodeMCU; strip the wires and plug into D6 and GND.
6. Connect bell/low voltage wire to the NO and COMMON terminals of relay 1 on your relay module; run the wire to the garage door opener for Door 1 and connect to the opener's terminals (the same terminals that the pushbutton switch for your door is attached to).
7. Connect bell/low voltage wire to the NO and COMMON terminals of relay 2 on your relay module; run the wire to the garage door opener for Door 2 and connect to the opener's terminals (the same terminals that the pushbutton switch for your door is attached to).

_Done!_


## Configuring Home Assistant

GarHAGE supports both Home Assistant's "MQTT Cover" and "MQTT Binary Sensor" platforms. Add the following configuration snippets to your `configuration.yaml` to enable either or both platforms.

### HASS's Birth Message

To be used in conjunction with the "Home Assistant Workaround Parameters" in config.h. These must be set to take advantage of the GarHAge functionality described along with those parameters that addresses a current bug in HASS.

Add the `birth_message` parameters to the `mqtt` stanza in configuration.yaml:

```
mqtt:
  broker: your.broker.ip.address
  birth_message:
    topic: "hass/status"
    payload: "online"
```

### MQTT Cover: Basic configuration

```
cover:
  - platform: mqtt
    name: "Garage Door 1"
    state_topic: "garage/door/1/status"
    command_topic: "garage/door/1/action"
    
  - platform: mqtt
    name: "Garage Door 2"
    state_topic: "garage/door/2/status"
    command_topic: "garage/door/2/action"
```

_Note: GarHAge's default parameters match Home Assistant's defaults and, as such, the above minimal configuration will work._

### MQTT Cover: Complete configuration

_Note: If you want to guard against your GarHAge configuration breaking if a Home Assistant update changes one of its defaults, the complete configuration below can be added._

```
cover:
  - platform: mqtt
    name: "Garage Door 1"
    state_topic: "garage/door/1/status"
    command_topic: "garage/door/1/action"
    qos: 0
    optimistic: false
    retain: false
    payload_open: "OPEN"
    payload_close: "CLOSE"
    payload_stop: "STATE"
    state_open: "open"
    state_closed: "closed"
    
  - platform: mqtt
    name: "Garage Door 2"
    state_topic: "garage/door/2/status"
    command_topic: "garage/door/2/action"
    qos: 0
    optimistic: false
    retain: false
    payload_open: "OPEN"
    payload_close: "CLOSE"
    payload_stop: "STATE"
    state_open: "open"
    state_closed: "closed"
```

_Note: Setting_ `payload_stop` _to_ `STATE` _allows you to trigger a status update from GarHAge for a Door by pressing the stop button for that door in the HASS GUI. The stop button in the HASS GUI is otherwise unused and the `STATE` payload is otherwise uncalled._

### MQTT Binary Sensor

```
binary_sensor:
  - platform: mqtt
    name: "Garage Door 1"
    state_topic: "garage/door/1/status"
    payload_on: "open"
    payload_off: "closed"
    device_class: opening
    qos: 0
    
  - platform: mqtt
    name: "Garage Door 2"
    state_topic: "garage/door/2/status"
    payload_on: "open"
    payload_off: "closed"
    device_class: opening
    qos: 0  
```


## Configuring OpenHAB

_Forthcoming. Please submit a pull request with a working OpenHAB configuration if you can assist!_


## Contributing

Fork this repository and submit a pull request.


## Issues/Bug Reports/Feature Requests

Please open an issue in this repository and describe your issue in as much detail as possible with the steps necessary to replicate the bug. It will also be helpful to include the content of your config.h in code tags and indicate whether (and how) you modified GarHAge.ino.

Please also request new features via issues!
