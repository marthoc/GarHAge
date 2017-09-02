/*   
 * GarHAge
 * aka the Home-Assistant-friendly ESP8266-based MQTT Garage Door Controller
 * Licensed under the MIT License, Copyright (c) 2017 marthoc
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "config.h"

// Mapping NodeMCU Ports to Arduino GPIO Pins
// Allows use of NodeMCU Port nomenclature in config.h
#define D0 16
#define D1 5
#define D2 4
#define D3 0
#define D4 2
#define D5 14
#define D6 12 
#define D7 13
#define D8 15

const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;

const boolean static_ip = STATIC_IP;
IPAddress ip(IP);
IPAddress gateway(GATEWAY);
IPAddress subnet(SUBNET);

const char* mqtt_broker = MQTT_BROKER;
const char* mqtt_clientId = MQTT_CLIENTID;
const char* mqtt_username = MQTT_USERNAME;
const char* mqtt_password = MQTT_PASSWORD;
// const int mqtt_status_update_interval = 0; // Publish a status message for each door every X seconds (default 0 (disabled); any integer > 0 to enable);

const char* door1_alias = DOOR1_ALIAS;
const char* mqtt_door1_action_topic = MQTT_DOOR1_ACTION_TOPIC;
const char* mqtt_door1_status_topic = MQTT_DOOR1_STATUS_TOPIC;
const int door1_openPin = DOOR1_OPEN_PIN;
const int door1_closePin = DOOR1_CLOSE_PIN;
const int door1_stopPin = DOOR1_STOP_PIN;
const int door1_statusPin = DOOR1_STATUS_PIN;

const boolean door2_enabled = DOOR2_ENABLED;
const char* door2_alias = DOOR2_ALIAS;
const char* mqtt_door2_action_topic = MQTT_DOOR2_ACTION_TOPIC;
const char* mqtt_door2_status_topic = MQTT_DOOR2_STATUS_TOPIC;
const int door2_openPin = DOOR2_OPEN_PIN;
const int door2_closePin = DOOR2_CLOSE_PIN;
const int door2_stopPin = DOOR2_STOP_PIN;
const int door2_statusPin = DOOR2_STATUS_PIN;

const int relayActiveTime = 500;
int door1_lastStatusValue = 2;
int door2_lastStatusValue = 2;
// unsigned int lastStatusUpdateTime = 0;

WiFiClient espClient;
PubSubClient client(espClient);

// Wifi setup function

void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  if (static_ip) {
    WiFi.config(ip, gateway, subnet);
  }

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

// Callback when MQTT message is received; calls triggerDoorAction(), passing topic and payload as parameters

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  
  Serial.println();

  String topicToProcess = topic;
  payload[length] = '\0';
  String payloadToProcess = (char*)payload;
  triggerDoorAction(topicToProcess, payloadToProcess);
}

// Functions that run in loop() to check door statuses (open/closed) each loop and publish any change

void check_door1_status() {
  int currentStatusValue = digitalRead(door1_statusPin);
  if (currentStatusValue != door1_lastStatusValue) {
    if (digitalRead(door1_statusPin) == HIGH) {
      Serial.print(door1_alias);
      Serial.print(" opened! Publishing to ");
      Serial.print(mqtt_door1_status_topic);
      Serial.println("...");
      client.publish(mqtt_door1_status_topic, "open", true);
    }
    else if (digitalRead(door1_statusPin) == LOW) {
      Serial.print(door1_alias);
      Serial.print(" closed! Publishing to ");
      Serial.print(mqtt_door1_status_topic);
      Serial.println("...");
      client.publish(mqtt_door1_status_topic, "closed", true);
    }
    door1_lastStatusValue = currentStatusValue;
  }
}

void check_door2_status() {
  int currentStatusValue = digitalRead(door2_statusPin);
  if (currentStatusValue != door2_lastStatusValue) {
    if (digitalRead(door2_statusPin) == HIGH) {
      Serial.print(door2_alias);
      Serial.print(" opened! Publishing to ");
      Serial.print(mqtt_door2_status_topic);
      Serial.println("...");
      client.publish(mqtt_door2_status_topic, "open", true);
    }
    else if (digitalRead(door2_statusPin) == LOW) {
      Serial.print(door2_alias);
      Serial.print(" closed! Publishing to ");
      Serial.print(mqtt_door2_status_topic);
      Serial.println("...");
      client.publish(mqtt_door2_status_topic, "closed", true);
    }
    door2_lastStatusValue = currentStatusValue;
  }
}

// Function that toggles the relevant relay-connected output pin

void toggleRelay(int pin) {
  digitalWrite(pin, HIGH);
  delay(relayActiveTime);
  digitalWrite(pin, LOW);
}

// Function called by callback() when a message is received 
// Passes the message topic as the "requestedDoor" parameter and the message payload as the "requestedAction" parameter

void triggerDoorAction(String requestedDoor, String requestedAction) {
  if (requestedDoor == mqtt_door1_action_topic && requestedAction == "OPEN") {
    Serial.print("Triggering ");
    Serial.print(door1_alias);
    Serial.println(" OPEN relay!");
    toggleRelay(door1_openPin);
  }
  else if (requestedDoor == mqtt_door1_action_topic && requestedAction == "CLOSE") {
    Serial.print("Triggering ");
    Serial.print(door1_alias);
    Serial.println(" CLOSE relay!");
    toggleRelay(door1_closePin);
  }
  else if (requestedDoor == mqtt_door1_action_topic && requestedAction == "STOP") {
    Serial.print("Triggering ");
    Serial.print(door1_alias);
    Serial.println(" STOP relay!");
    toggleRelay(door1_stopPin);
  }
  else if (requestedDoor == mqtt_door2_action_topic && requestedAction == "OPEN") {
    Serial.print("Triggering ");
    Serial.print(door2_alias);
    Serial.println(" OPEN relay!");
    toggleRelay(door2_openPin);
  }
  else if (requestedDoor == mqtt_door2_action_topic && requestedAction == "CLOSE") {
    Serial.print("Triggering ");
    Serial.print(door2_alias);
    Serial.println(" CLOSE relay!");
    toggleRelay(door2_closePin);
  }
  else if (requestedDoor == mqtt_door2_action_topic && requestedAction == "STOP") {
    Serial.print("Triggering ");
    Serial.print(door2_alias);
    Serial.println(" STOP relay!");
    toggleRelay(door2_stopPin);
  }
  else { Serial.println("Unrecognized action payload... taking no action!");
  }
}

// Function that runs in loop() to connect/reconnect to the MQTT broker, and publish the current door statuses on connect

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(mqtt_clientId, mqtt_username, mqtt_password)) {
      Serial.println("Connected!");

      // Subscribe to the action topics to listen for action messages
      Serial.print("Subscribing to ");
      Serial.print(mqtt_door1_action_topic);
      Serial.println("...");
      client.subscribe(mqtt_door1_action_topic);
      
      if (door2_enabled){
        Serial.print("Subscribing to ");
        Serial.print(mqtt_door2_action_topic);
        Serial.println("...");
        client.subscribe(mqtt_door2_action_topic);
      }

      // Publish the current door status on connect/reconnect to ensure HA status is synced with whatever happened while disconnected
      int door1_currentDoorStatus = digitalRead(door1_statusPin);
      if (door1_currentDoorStatus == 0) {
        Serial.print(door1_alias);
        Serial.print(" is closed! Publishing to ");
        Serial.print(mqtt_door1_status_topic);
        Serial.println("...");
        client.publish(mqtt_door1_status_topic, "closed", true);
      }
      else if (door1_currentDoorStatus == 1) {
        Serial.print(door1_alias);
        Serial.print(" is closed! Publishing to ");
        Serial.print(mqtt_door1_status_topic);
        Serial.println("...");
        client.publish(mqtt_door1_status_topic, "open", true);
      }
  
      if (door2_enabled) {
        int door2_currentDoorStatus = digitalRead(door2_statusPin);
        if (door2_currentDoorStatus == 0) {
          Serial.print(door2_alias);
          Serial.print(" is closed! Publishing to ");
          Serial.print(mqtt_door2_status_topic);
          Serial.println("...");
          client.publish(mqtt_door2_status_topic, "closed", true);
        }
        else if (door2_currentDoorStatus == 1) {
          Serial.print(door2_alias);
          Serial.print(" is closed! Publishing to ");
          Serial.print(mqtt_door2_status_topic);
          Serial.println("...");
          client.publish(mqtt_door2_status_topic, "open", true);
        }
      }
    } 
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  // Setup the output and input pins used in the sketch
  pinMode(door1_openPin, OUTPUT);
  digitalWrite(door1_openPin, LOW);

  pinMode(door1_closePin, OUTPUT);
  digitalWrite(door1_closePin, LOW);
  
  pinMode(door1_stopPin, OUTPUT);
  digitalWrite(door1_stopPin, LOW);
  
  pinMode(door1_statusPin, INPUT_PULLUP);

  if (door2_enabled) {
    pinMode(door2_openPin, OUTPUT);
    digitalWrite(door2_openPin, LOW);

    pinMode(door2_closePin, OUTPUT);
    digitalWrite(door2_closePin, LOW);
  
    pinMode(door2_stopPin, OUTPUT);
    digitalWrite(door2_stopPin, LOW);
  
    pinMode(door2_statusPin, INPUT_PULLUP);
  }

  // Setup serial output, connect to wifi, connect to MQTT broker
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_broker, 1883);
  client.setCallback(callback);
}

void loop() {
  // Connect/reconnect to the MQTT broker and listen for messages
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  // Check door open/closed status each loop and publish changes
  check_door1_status();
  if (door2_enabled) { check_door2_status(); }
}
