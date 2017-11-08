/*   
 * GarHAge
 * a Home-Automation-friendly ESP8266-based MQTT Garage Door Controller
 * Licensed under the MIT License, Copyright (c) 2017 marthoc
 * 
 * User-configurable Parameters 
*/

// Wifi Parameters

#define WIFI_SSID "your-ssid-name"
#define WIFI_PASSWORD "your-ssid-password"

// Static IP Parameters

#define STATIC_IP false
#define IP 192,168,1,100
#define GATEWAY 192,168,1,1
#define SUBNET 255,255,255,0

// MQTT Parameters

#define MQTT_BROKER "w.x.y.z"
#define MQTT_CLIENTID "GarHAge"
#define MQTT_USERNAME "your-mqtt-username"
#define MQTT_PASSWORD "your-mqtt-password"

// Relay Parameters

#define ACTIVE_HIGH_RELAY true

// Door 1 Parameters

#define DOOR1_ALIAS "Door 1"
#define MQTT_DOOR1_ACTION_TOPIC "garage/door/1/action"
#define MQTT_DOOR1_STATUS_TOPIC "garage/door/1/status"
#define DOOR1_OPEN_PIN D2
#define DOOR1_CLOSE_PIN D2
#define DOOR1_STATUS_PIN D5
#define DOOR1_STATUS_SWITCH_LOGIC "NO"

// Door 2 Parameters

#define DOOR2_ENABLED false
#define DOOR2_ALIAS "Door 2"
#define MQTT_DOOR2_ACTION_TOPIC "garage/door/2/action"
#define MQTT_DOOR2_STATUS_TOPIC "garage/door/2/status"
#define DOOR2_OPEN_PIN D1
#define DOOR2_CLOSE_PIN D1
#define DOOR2_STATUS_PIN D6
#define DOOR2_STATUS_SWITCH_LOGIC "NO"

// Temperature and Humidity Sensor Parameters

#define DHT_ENABLED false
#define DHTPIN D4
#define DHTTYPE DHT11 // or: DHT21 or DHT22
#define MQTT_DHT_STATUS_TOPIC "garage/dht"
#define DHT_PUBLISH_INTERVAL 300

