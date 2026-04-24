# 🚦 RFID-Based Smart Traffic Control System

## 📌 Overview

This project implements a smart traffic signal system using RFID technology to identify vehicles and control signals dynamically. It prioritizes emergency vehicles, detects flagged (theft) vehicles, and handles unauthorized access.

---

## ⚙️ Features

* 🚑 Emergency vehicle detection → Automatic GREEN signal
* 🚨 Theft vehicle detection → Buzzer alert + blinking RED signal
* ❌ Unauthorized access → Warning message on LCD
* 📟 Real-time status display using LCD

---

## 🧠 How It Works

1. RFID reader scans the card/tag
2. UID is matched with predefined values
3. Based on the match:

   * Emergency → Green signal for priority passage
   * Theft → Alert system activated
   * Unknown → Access denied message

---

## 🔧 Hardware Components

* Arduino UNO
* MFRC522 RFID Module
* 16x2 LCD (I2C)
* LEDs (Red, Yellow, Green)
* Buzzer
* Jumper wires

---

## 🖥️ Software & Libraries

* Arduino IDE / VS Code
* MFRC522 Library
* LiquidCrystal_I2C Library
* SPI Library

---

## ▶️ Setup Instructions

1. Connect components as per circuit design
2. Install required libraries:

   * MFRC522
   * LiquidCrystal_I2C
3. Upload the `.ino` file to Arduino
4. Scan RFID cards to test functionality

---

## 📂 Project Structure

```
RFID-Traffic-Control-System/
│── code/
│   └── rfid_traffic_control.ino
│── README.md
│── images/ (optional)
```

---

## ⚠️ Limitations

* Uses hardcoded RFID UIDs (not scalable)
* Supports only basic traffic logic
* No real-time traffic density handling

---

## 🚀 Future Improvements

## 🚀 Future Improvements

- Replace hardcoded RFID UIDs with dynamic storage using EEPROM or a backend database for scalability
- Integrate IoT (e.g., NodeMCU / MQTT) to monitor traffic status remotely in real time
- Implement traffic density-based signal control using IR sensors or computer vision models
- Extend system to support multi-lane intersections with coordinated signal timing

---
