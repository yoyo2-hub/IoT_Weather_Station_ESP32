# IoT_Weather_Station_ESP32 via MQTT
# Hardware used: 
ESP32 (30 pins), DHT11, LDR, 0.96" OLED display (SSD1306), optional MQ-2 gas sensor, Dupont wires.

# Description:
Developed an IoT weather station that publishes sensor data to an MQTT broker. The DHT11 measures temperature and humidity, while an LDR measures light intensity. Data is displayed locally on an OLED via I2C and sent every 10 seconds to an MQTT server (PC or cloud). A PC client visualizes real-time charts. The project includes MQTT library integration, network reconnection handling, and structured messaging via topics. Optionally, the MQ-2 sensor triggers alert messages. This project strengthens skills in ESP32 networking and simultaneous sensor/display management.
