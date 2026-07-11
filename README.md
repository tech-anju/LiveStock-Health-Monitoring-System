# 🐄 Smart Collar for Livestock Health Monitoring using IoT and Edge AI

> **An IoT-based smart livestock monitoring system that leverages Edge AI, LoRa communication, and cloud analytics to detect early health anomalies in cattle and provide real-time alerts for farmers.**

<p align="center">
  <img src="https://img.shields.io/badge/ESP32-Microcontroller-red?style=for-the-badge">
  <img src="https://img.shields.io/badge/LoRa-Communication-green?style=for-the-badge">
  <img src="https://img.shields.io/badge/TinyML-EdgeAI-orange?style=for-the-badge">
  <img src="https://img.shields.io/badge/ThingSpeak-Cloud-blue?style=for-the-badge">
  <img src="https://img.shields.io/badge/Telegram-Alerts-2CA5E0?style=for-the-badge">
</p>

---

# 📖 Overview

Livestock diseases often go unnoticed until visible symptoms appear, leading to reduced productivity and financial losses. Continuous monitoring is difficult in rural areas due to limited infrastructure and unreliable internet connectivity.

The **Smart Collar for Livestock Health Monitoring** addresses this challenge by combining **IoT sensors**, **Edge AI**, and **LoRa communication** to continuously monitor an animal's health. The system collects physiological and environmental data, detects anomalies locally, transmits data over long distances using LoRa, stores information on ThingSpeak, and sends instant Telegram notifications whenever abnormal conditions are detected.

---

# ✨ Features

- 🌡️ Real-time body temperature monitoring
- 🐄 Motion and activity tracking
- 🌤️ Ambient temperature & humidity monitoring
- 📡 Long-range LoRa communication
- 🧠 Edge AI anomaly detection
- ☁️ Cloud dashboard using ThingSpeak
- 📲 Telegram alert notifications
- 🔋 Low-power design for rural deployment

---

# 🏗 System Architecture

```
                 Smart Collar (ESP32)
                        │
      ┌─────────────────┼─────────────────┐
      │                 │                 │
      ▼                 ▼                 ▼
 MLX90614           MPU6050           DHT22
Temperature      Motion Sensor     Temp & Humidity
      │                 │                 │
      └─────────────────┼─────────────────┘
                        │
                 Data Processing
                        │
                        ▼
               LoRa Transmitter
                        │
         Long Range Wireless Communication
                        │
                        ▼
                 LoRa Receiver
                        │
        ┌───────────────┴───────────────┐
        ▼                               ▼
 ThingSpeak Dashboard          Telegram Alerts
```

---

# 🛠 Hardware Components

| Component | Purpose |
|-----------|---------|
| ESP32 | Main microcontroller |
| MLX90614 | Non-contact body temperature sensor |
| MPU6050 | Motion & activity monitoring |
| DHT22 | Ambient temperature & humidity |
| LoRa Module | Long-range wireless communication |

---

# 💻 Software Stack

- Arduino IDE
- ESP32 Framework
- TinyML
- ThingSpeak Cloud
- Telegram Bot API

---

# 📂 Project Structure

```
Smart-Collar-Livestock/
│
├── dht22_mpu6050/
│   └── Sensor reading and calibration
│
├── LoRa_init_check/
│   └── LoRa module initialization and testing
│
├── Lora_transmitter/
│   └── LoRa transmitter code
│
├── Lora_receiver/
│   └── LoRa receiver code
│
├── sensor_transmitter/
│   └── Reads sensor data and transmits via LoRa
│
├── sensor_receiver/
│   └── Receives and processes transmitted data
│
└── README.md
```

---

# ⚙ Workflow

1. ESP32 reads data from all connected sensors.
2. Sensor values are processed locally.
3. Edge AI analyzes data for health anomalies.
4. Data is transmitted through the LoRa network.
5. Receiver uploads the data to ThingSpeak.
6. If an abnormal condition is detected, Telegram alerts are sent instantly.

---

# 📊 Parameters Monitored

| Parameter | Sensor |
|-----------|--------|
| Body Temperature | MLX90614 |
| Motion | MPU6050 |
| Acceleration | MPU6050 |
| Humidity | DHT22 |
| Ambient Temperature | DHT22 |

---

# 📈 Results

- ✅ Continuous livestock health monitoring
- ✅ Long-range communication using LoRa
- ✅ Real-time cloud monitoring
- ✅ Automated Telegram notifications
- ✅ Early anomaly detection using Edge AI

---

# 🚀 Getting Started

## Clone the Repository

```bash
git clone https://github.com/yourusername/Smart-Collar-Livestock.git
cd Smart-Collar-Livestock
```

---

## Upload Sensor Code

Open

```
sensor_transmitter/
```

using Arduino IDE and upload it to the ESP32 connected to the livestock collar.

---

## Upload Receiver Code

Open

```
sensor_receiver/
```

and upload it to the receiver ESP32.

---

## Test LoRa Communication

Run

```
LoRa_init_check/
```

to verify successful communication between transmitter and receiver.

---

# 📡 Communication Flow

```
Sensors
   │
   ▼
ESP32
   │
   ▼
LoRa Transmitter
   │
~~~~~~~~~~~~~~~
 LoRa Network
~~~~~~~~~~~~~~~
   │
   ▼
LoRa Receiver
   │
   ▼
ThingSpeak Cloud
   │
   ▼
Telegram Notifications
```

---

# 🎯 Applications

- Smart Dairy Farms
- Precision Livestock Farming
- Veterinary Monitoring
- Rural IoT Systems
- Animal Welfare
- Disease Prevention

---

# 🔮 Future Scope

- GPS-based livestock tracking
- Heart rate monitoring
- Blood oxygen sensing
- Mobile application
- Solar-powered smart collar
- Multi-animal dashboard
- Disease prediction using Deep Learning

---

# 📄 Conference Paper

**Smart Collar for Livestock: A LoRa Enabled IoT System for Early Health Anomaly Detection**

*(Communicated)*

---

# 👨‍💻 Author

**Anjishnu Sarkar**

B.Tech Computer Science & Engineering

Institute of Engineering and Management

---

# ⭐ Support

If you found this project useful, consider giving it a **Star ⭐** on GitHub.
