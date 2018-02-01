## Config.h Parameters

### Wifi Parameters

`WIFI_SSID "your-wifi-ssid"`

The wifi ssid GarHAge will connect to. Must be placed within quotation marks.

`WIFI_PASSWORD "your-wifi-password"`

The wifi ssid's password. Must be placed within quotation marks.

### Static IP Parameters

`STATIC_IP false`

Set to `true` to use the IP / GATEWAY / SUBNET parameters that follow. Set to `false` to use DHCP. _(Default: false)_

`IP 192,168,1,100`

The static IP you want to assign to GarHAge. _(Default: 192.168.1.100)_

`GATEWAY 192,168,1,1`

The gateway you want GarHAge to use. _(Default: 192.168.1.1)_

`SUBNET 255,255,255,0`

The subnet mask you want GarHAge to use. _(Default: 255.255.255.0)_

_Note: There are commas (,) not periods (.) in the IP / GATEWAY / SUBNET parameters above!_

### MQTT Parameters

`MQTT_BROKER "w.x.y.z"`

The IP address of your MQTT broker. Must be placed within quotation marks.

`MQTT_CLIENTID "GarHAge"`

The Client ID you want GarHAge to use. Should be unique among all the devices connected to your broker. Must be placed within quotation marks. _(Default: GarHAge)_

`MQTT_USERNAME "your-mqtt-username"`

The username required to authenticate to your MQTT broker. Must be placed within quotation marks. Use "" (i.e. a pair of quotation marks) if your broker does not require authentication.

`MQTT_PASSWORD "your-mqtt-password"`

The password required to authenticate to your MQTT broker. Must be placed within quotation marks. Use "" (i.e. a pair of quotation marks) if your broker does not require authentication.

### Relay Parameters

`ACTIVE_HIGH_RELAY true`

Set to `false` if using an active-low relay module. Set to `true` if using an active-high relay module. _(Default: true)_

### Door 1 Parameters

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

### Door 2 Parameters

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

### Auxiliary Door 1 Parameters

`AUX_DOOR1_ENABLED false`

Set to `true` to enable GarHAge to control/monitor Aux Door 1. Set to `false` to disable monitoring of Aux Door 1. _(Default: false)_

`AUX_DOOR1_ALIAS "Aux Door 1"`

The alias to be used for Aux Door 1 in serial messages. Must be placed within quotation marks. _(Default: Aux Door 1)_

`MQTT_AUX_DOOR1_ACTION_TOPIC "garage/aux_door/1/action"`

The topic GarHAge will subscribe to to receive the `STATE` command for Aux Door 1. Must be placed within quotation marks. _(Default: garage/aux\_door/1/action)_

`MQTT_AUX_DOOR1_STATUS_TOPIC "garage/aux_door/1/status"`

The topic GarHAge will publish Aux Door 1's status to. Must be placed within quotation marks. _(Default: garage/aux\_door/1/status)_

`AUX_DOOR1_STATUS_PIN D7`

The GPIO pin connected to the reed/magnetic switch attached to Aux Door 1. _(Default: NodeMCU D7 / Arduino 13)_

`AUX_DOOR1_STATUS_SWITCH_LOGIC "NO"`

The type of reed/magnetic switch used for Aux Door 1. Must be placed within quotation marks. Set to `"NO` for normally-open. Set to `"NC"` for normally-closed. _(Default: NO)_

### Auxiliary Door 2 Parameters

`AUX_DOOR2_ENABLED false`

Set to `true` to enable GarHAge to control/monitor Aux Door 2. Set to `false` to disable monitoring of Aux Door 2. _(Default: false)_

`AUX_DOOR1_ALIAS "Aux Door 2"`

The alias to be used for Aux Door 2 in serial messages. Must be placed within quotation marks. _(Default: Aux Door 2)_

`MQTT_AUX_DOOR2_ACTION_TOPIC "garage/aux_door/2/action"`

The topic GarHAge will subscribe to to receive the `STATE` command for Aux Door 2. Must be placed within quotation marks. _(Default: garage/aux\_door/2/action)_

`MQTT_AUX_DOOR2_STATUS_TOPIC "garage/aux_door/2/status"`

The topic GarHAge will publish Aux Door 2's status to. Must be placed within quotation marks. _(Default: garage/aux\_door/2/status)_

`AUX_DOOR2_STATUS_PIN D8`

The GPIO pin connected to the reed/magnetic switch attached to Aux Door 2. _(Default: NodeMCU D8 / Arduino 15)_

`AUX_DOOR1_STATUS_SWITCH_LOGIC "NO"`

The type of reed/magnetic switch used for Aux Door 1. Must be placed within quotation marks. Set to `"NO` for normally-open. Set to `"NC"` for normally-closed. _(Default: NO)_

### Temperature and Humidity Sensor Parameters

`DHT_ENABLED false`

Set to `true` to enable GarHAge to monitor temperature and humidity readings via an attached DHT11 or 22 sensor. Set to `false` to disable temperature and humidity monitoring. _(Default: false)_

`DHTPIN D4`

The GPIO pin connected to the data pin of the DHT11/22. _(Default: NodeMCU D4 / Arduino 2)_

`DHTTYPE DHT11`

The type of DHT sensor in use: DHT11 or DHT22. _(Default: DHT11)_

`MQTT_DHT_ACTION_TOPIC "garage/dht/action"`

The topic GarHAge will subscribe to to receive the `STATE` command for the DHT. Must be placed within quotation marks. _(Default: garage/dht/action)_

`MQTT_DHT_STATUS_TOPIC "garage/dht/status"`

The topic base that GarHAge will publish temperature and humidity readings to at the subtopics `/temperature`, and `/humidity`. Must be placed within quotation marks. _(Default: garage/dht/status)_

`#define DHT_PUBLISH_INTERVAL 300`

The interval between publishes of temperature and humidity readings in seconds. _(Default: 300)_