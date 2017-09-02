/*   
 * GarHAge
 * aka the Home-Assistant-friendly ESP8266-based MQTT Garage Door Controller
 * Licensed under the MIT License, Copyright (c) 2017 marthoc
 * 
 * User-configurable Parameters 
*/

#define WIFI_SSID "your-ssid-name"
#define WIFI_PASS "your-ssid-pass"

#define STATIC_IP false
#define IP 192,168,1,100
#define GATEWAY 192,168,1,1
#define SUBNET 255,255,255,0

#define MQTT_BROKER_HOSTNAME "w.x.y.z"
#define MQTT_CLIENTID "GarHAge"
#define MQTT_USERNAME "your-mqtt-username"
#define MQTT_PASS "your-mqtt-pass"

#define DOOR1_ALIAS "Door 1"
#define MQTT_DOOR1_ACTION_TOPIC "garage/door/1/action"
#define MQTT_DOOR1_STATUS_TOPIC "garage/door/1/status"
#define DOOR1_OPEN_PIN 4
#define DOOR1_CLOSE_PIN 4
#define DOOR1_STOP_PIN 5
#define DOOR1_STATUS_PIN 14

#define DOOR2_ENABLED false
#define DOOR2_ALIAS "Door 2"
#define MQTT_DOOR2_ACTION_TOPIC "garage/door/2/action"
#define MQTT_DOOR2_STATUS_TOPIC "garage/door/2/status"
#define DOOR2_OPEN_PIN 2
#define DOOR2_CLOSE_PIN 2
#define DOOR2_STOP_PIN 12
#define DOOR2_STATUS_PIN 13
