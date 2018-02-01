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
