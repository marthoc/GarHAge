
## Table of Contents

* [GarHAge](#garhage)
  * [a Home\-Automation\-friendly ESP8266\-based MQTT Garage Door Controller](#a-home-automation-friendly-esp8266-based-mqtt-garage-door-controller)
  * [How GarHAge works\.\.\.](#how-garhage-works)
  * [Hardware](#hardware)
    * [Bill of Materials](#bill-of-materials)
    * [Detailed Bill of Materials](#detailed-bill-of-materials)
      * [1\. ESP8266\-based microcontroller](#1-esp8266-based-microcontroller)
      * [2\. Dual 5v relay module with active\-high inputs](#2-dual-5v-relay-module-with-active-high-inputs)
      * [3\. Reed/magnetic door switches](#3-reedmagnetic-door-switches)
      * [4\. 5v MicroUSB power supply](#4-5v-microusb-power-supply)
      * [5\. Mini solderless breadboard (170 tie\-point)](#5-mini-solderless-breadboard-170-tie-point)
      * [6\. \- 8\. Miscellaneous parts](#6---8-miscellaneous-parts)
    * [Building GarHAge](#building-garhage)
  * [Software](#software)
    * [1\. Set up the Arduino IDE](#1-set-up-the-arduino-ide)
    * [2\. Load the sketch in the Arduino IDE and modify the user parameters in config\.h](#2-load-the-sketch-in-the-arduino-ide-and-modify-the-user-parameters-in-configh)
      * [Wifi Parameters](#wifi-parameters)
      * [Static IP Parameters](#static-ip-parameters)
      * [MQTT Parameters](#mqtt-parameters)
      * [Door 1 Parameters](#door-1-parameters)
      * [Door 2 Parameters](#door-2-parameters)
    * [3\. Upload the sketch to your NodeMCU / microcontroller](#3-upload-the-sketch-to-your-nodemcu--microcontroller)
    * [4\. Check the Arduino IDE Serial Monitor](#4-check-the-arduino-ide-serial-monitor)
  * [Installing GarHAge](#installing-garhage)
  * [Configuring Home Assistant](#configuring-home-assistant)
    * [HASS Automation Workaround](#hass-automation-workaround)
    * [MQTT Cover: Basic configuration](#mqtt-cover-basic-configuration)
    * [MQTT Cover: Complete configuration](#mqtt-cover-complete-configuration)
    * [MQTT Binary Sensor](#mqtt-binary-sensor)
    * [HASS Example Automations](#hass-example-automations)
  * [Configuring OpenHAB](#configuring-openhab)
  * [Contributing](#contributing)
  * [Issues/Bug Reports/Feature Requests](#issuesbug-reportsfeature-requests)


## Hardware


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

The Client ID you want GarHAge to use. Should be unique among all the devices connected to your broker. Must be placed within quotation marks. _(Default: GarHAge)_

`MQTT_USERNAME "your-mqtt-username"`

The username required to authenticate to your MQTT broker. Must be placed within quotation marks. Use "" (i.e. a pair of quotation marks) if your broker does not require authentication.

`MQTT_PASSWORD "your-mqtt-password"`

The password required to authenticate to your MQTT broker. Must be placed within quotation marks. Use "" (i.e. a pair of quotation marks) if your broker does not require authentication.

#### Relay Parameters

`ACTIVE_HIGH_RELAY true`

Set to `false` if using an active-low relay module. Set to `true` if using an active-high relay module. _(Default: true)_

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

### 3. Upload the sketch to your NodeMCU / microcontroller

If using the NodeMCU, connect it to your computer via MicroUSB; press and hold the reset button on the NodeMCU, press and hold the Flash button on the NodeMCU, then release the Reset button. Select `Sketch - Upload` in the Arduino IDE.

If using a different ESP8266 microcontroller, follow that device's instructions for putting it into flashing/programming mode.

### 4. Check the Arduino IDE Serial Monitor

Open the Serial Monitor via `Tools - Serial Monitor`. Reset your microcontroller. If all is working correctly, you should see something similar to the following messages:

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

GarHAGE supports both Home Assistant's "MQTT Cover" and "MQTT Binary Sensor" platforms.

### HASS Automation Workaround

_Testing has shown that the MQTT platform in Home Assistant sometimes does not update the status of an entity (such as the cover or binary sensor) in accordance with a retained message on the status topic on HASS start or restart. This can leave the cover entity in an "unknown" state, and the binary sensor may show "closed" even if the door is open._

_The entities will, however, update to show the correct state when the door next changes state and GarHAge publishes the state to the door's status topic._ 

_A temporary workaround (until this issue is resolved in HASS, or possibly in the underlying Paho MQTT library used in HASS) is to use an automation to send the "STATE" payload to the doors' action topics on Home Assistant start. This will ensure that the cover and binary sensor show the correct door state on HASS start and restart._

Place the following in your `automations.yaml` (adjusting if you have only one door controlled by GarHAge); replace `id: xyz` with the next sequential automation number according to your own `automations.yaml`.

```
- id: xyz
  alias: Update garage door state on startup
  trigger:
    - platform: homeassistant
      event: start
  action:
    - service: mqtt.publish
      data:
        topic: "garage/door/1/action"
        payload: "STATE"
    - service: mqtt.publish
      data:
        topic: "garage/door/2/action"
        payload: "STATE"
```

### MQTT Cover: Basic configuration

```
cover:
  - platform: mqtt
    name: "Garage Door 1"
    state_topic: "garage/door/1/status"
    command_topic: "garage/door/1/action"
    availability_topic: "GarHAge/availability"

  - platform: mqtt
    name: "Garage Door 2"
    state_topic: "garage/door/2/status"
    command_topic: "garage/door/2/action"
    availability_topic: "GarHAge/availability"
```

_Note: GarHAge's default parameters match Home Assistant's defaults and, as such, the above minimal configuration will work._

_Note: the "availability_topic" configuration parameter will be available in Home Assistant as of version 0.55; it allows Home Assistant to display the cover as "unavailable" if GarHAge goes offline unexpectedly. When GarHAge reconnects to your broker, the cover controls will again be available in Home Assistant. GarHAge forms its availability topic by suffixing "/availability" to the MQTT_CLIENTID parameter in config.h, and publishes "online" to that topic when connecting or reconnecting to the broker and "offline" when disconnecting from the broker._

### MQTT Cover: Complete configuration

_Note: If you want to guard against your GarHAge configuration breaking if a Home Assistant update changes one of its defaults, the complete configuration below can be added._

```
cover:
  - platform: mqtt
    name: "Garage Door 1"
    state_topic: "garage/door/1/status"
    command_topic: "garage/door/1/action"
    availability_topic: "GarHAge/availability"
    qos: 0
    optimistic: false
    retain: false
    payload_open: "OPEN"
    payload_close: "CLOSE"
    payload_stop: "STATE"
    state_open: "open"
    state_closed: "closed"
    payload_available: "online"
    payload_not_available: "offline"

  - platform: mqtt
    name: "Garage Door 2"
    state_topic: "garage/door/2/status"
    command_topic: "garage/door/2/action"
    availability_topic: "GarHAge/availability"
    qos: 0
    optimistic: false
    retain: false
    payload_open: "OPEN"
    payload_close: "CLOSE"
    payload_stop: "STATE"
    state_open: "open"
    state_closed: "closed"
    payload_available: "online"
    payload_not_available: "offline"
```

_Note: Setting_ `payload_stop` _to_ `STATE` _allows you to trigger a status update from GarHAge for a Door by pressing the stop button for that door in the HASS GUI. The stop button in the HASS GUI is otherwise unused._

### MQTT Binary Sensor

```
binary_sensor:
  - platform: mqtt
    name: "Garage Door 1"
    state_topic: "garage/door/1/status"
    payload_on: "open"
    payload_off: "closed"
    availability_topic: "GarHAge/availability"
    device_class: opening
    qos: 0

  - platform: mqtt
    name: "Garage Door 2"
    state_topic: "garage/door/2/status"
    payload_on: "open"
    payload_off: "closed"
    availability_topic: "GarHAge/availability"
    device_class: opening
    qos: 0  
```

_Note: the "availability_topic" configuration parameter will be available in Home Assistant as of version 0.54; it allows Home Assistant to display the binary sensor as "unavailable" if GarHAge goes offline unexpectedly. When GarHAge reconnects to your broker, the door state will again be displayed in Home Assistant. GarHAge forms its availability topic by suffixing "/availability" to the MQTT_CLIENTID parameter in config.h, and publishes "online" to that topic when connecting or reconnecting to the broker and "offline" when disconnecting from the broker._

### HASS Example Automations

In the examples that follow, replace `id: xyz` with the next sequential automation number according to your own `automations.yaml`.

#### Close garage door if open for longer than 30 minutes

Place the following in your `automations.yaml`:

```
- id: xyz
  alias: Close garage door if open for longer than 30 minutes
  trigger:
    - platform: state
      entity_id: cover.garage_door_1
      to: "open"
      for:
        minutes: 30
  action:
    - service: cover.close_cover
      entity_id: cover.garage_door_1
```

Of course, you can replace `30` with any length of time in minutes you wish. Be sure to replace `cover.garage_door_1` if the  name of your garage door in Home Assistant is different.

#### Notify iOS device when garage door opens or closes

To use this automation, you must have the Home Assistant iOS app installed on your iPhone and must have the `ios:` and `notify:` platforms in your `configuration.yaml`.

Place the following in your `automations.yaml`:

```
- id: xyz
  alias: Notify iOS device when garage door opens or closes
  trigger:
    - platform: state
      entity_id: cover.garage_door_1
  action:
    - service: notify.ios_your_device_name_here
      data_template:
        message: >
          Garage Door 1 just changed from {{ trigger.from_state.state }} to {{ trigger.to_state.state }}!
```

Replace `notify.ios_your_device_name_here` with the name assigned to your device by Home Assistant (for example, if Home Assistant knows your device as "steves_iphone", your notify statement would be: `notify.ios_steves_iphone`.

Be sure to replace `cover.garage_door_1` if the  name of your garage door in Home Assistant is different.

If you wish to notify only when the garage door either opens _or_ closes, add a `to` statement to the trigger following `entity_id` and specify either "open" or "closed", e.g.:

```
- id: xyz
  alias: Notify iOS device when garage door opens
  trigger:
    - platform: state
      entity_id: cover.garage_door_1
      to: "open"
  action:
    - service: notify.ios_your_device_name_here
      data_template:
        message: "Garage Door 1 just opened!"
```

#### Notify iOS device when garage door is open for longer than 30 minutes, with an actionable notification

An actionable notification will raise a notification on your iPhone with a "Close Garage" button allowing you to close the garage door directly from the notification (i.e. without needing to open the Home Assistant app).

To use this automation, you must have the Home Assistant iOS app installed on your iPhone. You must also have the `notify:` platform in your `configuration.yaml`.

To the `ios:` platform in `configuration.yaml`, add:

```
ios:
  push:
  categories:
    - name: Garage
      identifier: "GARAGE"
      actions:
        - identifier: "CLOSE_GARAGE"
          title: "Close Garage"
          activationMode: "background"
          authenticationRequired: no
          destructive: yes
          behavior: "default"
```

If you want to be required to authenticate (i.e. enter your passcode or unlock with TouchID) before being able to access the "Close Garage" button, change `authenticationRequired: no` to `authenticationRequired: yes`.

You will also need to add the following two automations to your `automations.yaml`:

```
- id: xyz
  alias: Notify iOS device when garage door has been open for 30 minutes
  trigger:
    - platform: state
      entity_id: cover.garage_door_1
      to: "open"
      for:
        minutes: 30
  action:
    - service: notify.ios_your_device_name_here
      data:
        message: "Garage Door 1 has been open for 30 minutes!"
        data:
          push:
            category: "GARAGE"

- id: xyz
  alias: Close garage when triggered from iOS notification
  trigger:
    - platform: event
      event_type: ios.notification_action_fired
      event_data:
        actionName: CLOSE_GARAGE
  action:
    - service: cover.close_cover
      entity_id: cover.garage_door_1
```

In the first automation, replace `notify.ios_your_device_name_here` with the name assigned to your device by Home Assistant (for example, if Home Assistant knows your device as "steves_iphone", your notify statement would be: `notify.ios_steves_iphone`.

Of course, you can replace `30` with any length of time in minutes you wish.

In both automations, be sure to replace `cover.garage_door_1` if the  name of your garage door in Home Assistant is different.

Restart Home Assistant for the configuration and automation changes to take effect.

Finally:
1. Open the Home Assistant app on your iPhone.
2. Tap the gear icon in the bottom right corner of the screen.
3. Scroll down and tap "Notification Settings".
4. Tap "Update push settings".
5. You should receive the message: "Settings Imported". Tap "OK".

Now, when your garage door has been open for 30 minutes, you will receive a Home Assistant notification saying "Garage Door 1 has been open for 30 minutes!", and the notification will contain a button labelled "Close Garage" which will close your garage when tapped.


## Configuring OpenHAB

_Forthcoming. Please submit a pull request with a working OpenHAB configuration if you can assist!_

