# LED Control with RPi, ESP8266, and MQTT

## Overview
This project demonstrates how a **Raspberry Pi (RPi)** communicates wirelessly with an **ESP8266** using **TCP Socket** to control an LED.  
Additionally, the RPi sends the LED status to an **MQTT Broker** running on an Ubuntu server.

- **TCP Socket** → RPi ↔ ESP8266 (for LED ON/OFF commands)  
- **MQTT** → RPi → Ubuntu Server (for LED status reporting)

## System Architecture
```

\[Qt App on RPi]  <--TCP-->  \[ESP8266] (LED Control)
|
| MQTT
v
\[Ubuntu Server (Mosquitto Broker)]

```

## Features
- Connect to ESP8266 via TCP socket.
- Send LED control commands (`LED_ON` / `LED_OFF`).
- Display ESP8266 responses in the Qt UI.
- Publish LED status (`ON` / `OFF`) to MQTT broker.
- Monitor LED status on server using:
```bash
mosquitto_sub -h <broker_ip> -t device/led/status
```

## Requirements

* **Hardware**: Raspberry Pi, ESP8266, LED
* **Software**:

  * Qt (with `QTcpSocket` and `QMqttClient`)
  * Mosquitto broker on Ubuntu server
  * ESP8266 with TCP server firmware

## Setup

1. **ESP8266**

   * Run a TCP server on IP `192.168.30.65` port `8080`.
   * Accept incoming commands:

     * `LED_ON` → turn LED ON
     * `LED_OFF` → turn LED OFF

2. **Ubuntu Server**

   * Install Mosquitto:

     ```bash
     sudo apt update
     sudo apt install mosquitto mosquitto-clients
     ```
   * Run broker on port `1883`.

3. **Qt Application (on RPi)**

   * Build and run the Qt project.
   * The app will:

     * Connect to ESP8266 via TCP
     * Connect to Ubuntu MQTT broker (`3.81.129.74:1883`)
     * Provide GUI buttons to control LED.

## Usage

* Open the Qt application.
* Press **Button 1** → Send `LED_ON` → LED lights up, status "ON" published via MQTT.
* Press **Button 2** → Send `LED_OFF` → LED turns off, status "OFF" published via MQTT.
* On Ubuntu server, monitor:

```bash
mosquitto_sub -h 3.81.129.74 -t device/led/status
```


