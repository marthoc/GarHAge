/*   
 * GarHAge
 * aka the Home-Assistant-friendly ESP8266-based MQTT Garage Door Controller
 * Licensed under the MIT License, Copyright (c) 2017 marthoc
*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

/*
 * Start of user-configurable parameters
 */

// Wifi details

const char* ssid = "your-ssid-name";
const char* password = "your-ssid-pass";

// Static IP details
// Set static_ip to "static" to use ip/gateway/subnet parameters below
// Set static_ip to "dhcp" to obtain ip address via DHCP and ignore ip/gateway/subnet parameters

const char* static_ip = "dhcp";
IPAddress ip(192,168,1,100);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

// MQTT server details

const char* mqtt_server = "w.x.y.z";
const char* mqtt_clientId = "garage";
const char* mqtt_username = "your-username";
const char* mqtt_password = "your-password";

// MQTT topic details

const char* mqtt_action_topic = "garage/action";
const char* mqtt_status_topic = "garage/status";

// GPIO pin details

int openPin = 4;
int closePin = 4;
int stopPin = 5;
int statusPin = 14;

/*
 * End of user-configurable parameters
 */

int lastStatusValue = 2;
int currentStatusValue;

WiFiClient espClient;
PubSubClient client(espClient);

// Wifi setup function

void setup_wifi() {

  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  if (static_ip == "static") {
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

// Callback when MQTT message is received

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  
  Serial.println();

  payload[length] = '\0';
  String payloadToProcess = (char*)payload;
  Serial.print("Action payload is ");
  Serial.print(payloadToProcess);
  Serial.println(".");
  triggerDoorAction(payloadToProcess);
}

// Function that runs in loop() to check door status (open/closed) and publish changes

void check_door_status() {
  currentStatusValue = digitalRead(statusPin);
  if (currentStatusValue != lastStatusValue) {
    if (digitalRead(statusPin) == HIGH) {
      client.publish(mqtt_status_topic, "open", true);
      Serial.println("Door is open! Publishing...");
    }
    else if (digitalRead(statusPin) == LOW) {
      client.publish(mqtt_status_topic, "closed", true);
      Serial.println("Door is closed! Publishing...");
    }
    lastStatusValue = currentStatusValue;
  }
}

// Function called by callback() when a message is received, passing the message payload as the "requestedAction" parameter

void triggerDoorAction(String requestedAction) {
  if (requestedAction == "OPEN") {
    Serial.println("Triggering OPEN relay!");
    digitalWrite(openPin, HIGH);
    delay(500);
    digitalWrite(openPin, LOW);
  }
  else if (requestedAction == "CLOSE") {
    Serial.println("Triggering CLOSE relay!");
    digitalWrite(closePin, HIGH);
    delay(500);
    digitalWrite(closePin, LOW);
  }
  else if (requestedAction == "STOP") {
    Serial.println("Triggering STOP relay!");
    digitalWrite(stopPin, HIGH);
    delay(500);
    digitalWrite(stopPin, LOW);
  }
  else { Serial.println("Unrecognized action payload... taking no action!");
  }
}

// Function that runs in loop() to connect/reconnect to the MQTT broker, and publish the current door status on connect

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(mqtt_clientId, mqtt_username, mqtt_password)) {
      Serial.println("Connected!");

      // Subscribe to the action topic to listen for action messages
      client.subscribe(mqtt_action_topic);
      Serial.print("Subscribed to ");
      Serial.print(mqtt_action_topic);
      Serial.println("...");

      // Publish the current door status on connect/reconnect to ensure HA status is synced with whatever happened while disconnected
      int currentDoorStatus = digitalRead(statusPin);
      if (currentDoorStatus == 0) {
        Serial.println("Door is closed! Publishing...");
        client.publish(mqtt_status_topic, "closed", true);
      }
      else if (currentDoorStatus == 1) {
        Serial.println("Door is open! Publishing...");
        client.publish(mqtt_status_topic, "open", true);
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
  pinMode(openPin, OUTPUT);
  digitalWrite(openPin, LOW);

  pinMode(closePin, OUTPUT);
  digitalWrite(closePin, LOW);
  
  pinMode(stopPin, OUTPUT);
  digitalWrite(stopPin, LOW);
  
  pinMode(statusPin, INPUT_PULLUP);

  // Setup serial output, connect to wifi, connect to MQTT broker
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  // Connect/reconnect to the MQTT broker and listen for messages
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  // Check door open/closed status each loop and publish changes
  check_door_status();
}
