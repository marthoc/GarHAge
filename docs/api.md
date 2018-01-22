## GarHAge MQTT "API"

This section explains the MQTT commands that GarHAge will respond to, and the responses that the user can expect to receive from GarHAge over MQTT. The Topics and Payloads listed in this section are _case sensitive_.

### Garage Doors

GarHAge subscribes to a configurable MQTT topic for at most two garage doors. (_By default, `garage/door/1/action`, and `garage/door/2/action` if Door 2 is enabled._)

- When the `OPEN` payload is received on either of these topics, GarHAge momentarily activates a relay connected to the relevant garage door opener to cause the door to open.

- When the `CLOSE` payload is received on either of these topics, GarHAge momentarily activates a relay connected to the relevant garage door opener to cause the door to close. (_By default, GarHAge is configured to activate the same relay for the `OPEN` and `CLOSE` payloads, as most (if not all) garage door openers operate manually by momentarily closing the same circuit to both open and close._)

- When the `STATE` payload is received on either of these topics, GarHAge publishes the status (`open` or `closed`) of the relevant garage door to a configurable MQTT topic. (_By default, `garage/door/1/status` or `garage/door/2/status`._) These messages are published at QOS 0 and with the "retain" flag set.

When the state of a garage door changes (either because GarHAge has triggered the door to open or close, or because the door has been opened or closed via a remote, pushbutton switch, or manually), GarHAge publishes the status (the payload `open` or `closed`) of the relevant garage door to `garage/door/1/status` or `garage/door/2/status`. These messages are published at QOS 0 and with the "retain" flag set.

### Auxiliary Doors

GarHAge subscribes to a configurable MQTT topic for at most two auxiliary doors. (_By default, `garage/aux_door/1/action` and `garage/aux_door/2/action` if Door 1 and Door 2 are enabled._)

- When the `STATE` payload is received on either of these topics, GarHAge publishes the status (`open` or `closed`) of the relevant auxiliary door to a configurable MQTT topic. (_By default, `garage/aux_door/1/status` or `garage/aux_door/2/status`._) These messages are published at QOS 0 and with the "retain" flag set.

When the state of an auxiliary door changes, GarHAge publishes the status (the payload `open` or `closed`) of the relevant garage door to `garage/aux_door/1/status` or `garage/aux_door/2/status`. These messages are published at QOS 0 and with the "retain" flag set.

### Temperature and Humidity

GarHAge publishes temperature and humidity readings from an attached DHT 11 or 22 sensor to a configurable MQTT topic. (_By default, `garage/dht`._) Readings are published on a configurable interval (_By default, 300 seconds._)

The temperature and humidity message is a JSON-formatted payload that contains three self-explanatory name/value pairs and looks similar to the following:

```
{"humidity":50.0,"temperatureC":10.0,"temperatureF":50}
```

The temperature and humidty message is published at QOS 0. The retain flag is _not_ set.

### "Birth" and "Last-Will-and-Testament"

GarHAge publishes "birth" and "LWT" messages so that your home automation software can respond appropriately to GarHAge being online or offline.

The "birth" message (the payload `online`) is published on connection to your MQTT broker to the topic `MQTT_CLIENTID/availability`, where `MQTT_CLIENTID` is the value set in `config.h`. (_By default, `GarHage/availability`._) This message is published at QOS 0 and with the "retain" flag set.

The "last-will-and-testament" message is set on connection to your MQTT broker and is published by your broker when GarHAge disconnects from the broker. The "LWT" message (the payload `offline`) is published to the topic `MQTT_CLIENTID/availability`, where `MQTT_CLIENTID` is the value set in `config.h`. (_As above, by default `GarHAge/availability`._) This message is set to be published at QOS 0 and with the "retain" flag set.