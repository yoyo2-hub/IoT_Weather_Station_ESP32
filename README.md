# IoT_Weather_Station_ESP32 via MQTT
# Hardware used: 
ESP32 (30 pins), DHT11, LDR, 0.96" OLED display (SSD1306), optional MQ-2 gas sensor, Dupont wires.

# Description:
Developed an IoT weather station that publishes sensor data to an MQTT broker. The DHT11 measures temperature and humidity, while an LDR measures light intensity. Data is displayed locally on an OLED via I2C and sent every 10 seconds to an MQTT server (PC or cloud). A PC client visualizes real-time charts. The project includes MQTT library integration, network reconnection handling, and structured messaging via topics. Optionally, the MQ-2 sensor triggers alert messages. This project strengthens skills in ESP32 networking and simultaneous sensor/display management.

# Câblage du projet
**DHT11 → ESP32**

DHT11 -> ESP32

VCC -> 3.3V

GND -> GND

DATA -> GPIO 4


**LDR → ESP32**

LDR + résistance 10 kΩ → diviseur

LDR → 3.3V

Autre patte LDR → GPIO 34

Résistance 10k → GPIO 34 vers GND

**Écran OLED SSD1306 → ESP32**

OLED -> ESP32

VCC -> 3.3V

GND -> GND

SDA -> GPIO 21

SCL -> GPIO 22


