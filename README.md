ESP32 IoT Weather Station
An ESP32-based weather station that combines indoor sensor readings with outdoor weather data from OpenWeatherMap and presents the information on a 16×2 character LCD.

I built this project to practice embedded C++, sensor integration, LCD interfacing, Wi-Fi connectivity, REST API requests, JSON parsing, and hardware/firmware debugging.

Features
-Measures indoor temperature and humidity with a DHT11 sensor.
-Connects an ESP32 to Wi-Fi to request outdoor weather information from OpenWeatherMap.
-Parses the API response and displays weather data on an LCD1602.
-Uses a non-I²C LCD1602 in 4-bit parallel mode, providing hands-on experience with LCD control and data pins.
-Uses imperial units for outdoor weather requests.

Hardware
-ESP32 development board (ESP32-WROVER-E)
-DHT11 temperature/humidity sensor
-LCD1602 (16×2, parallel interface)
-Breadboard and jumper wires
-Potentiometer
-USB cable and suitable power source

Software and Technologies
-Language: C++
-Board: ESP32
-IDE: Arduino IDE
-Libraries used: WiFi.h, HTTPClient.h, ArduinoJson.h, LiquidCrystal.h, and DHT.h
-Weather service: OpenWeatherMap API

How It Works
    1. The ESP32 reads indoor temperature and humidity from the DHT11.
    2. It connects to Wi-Fi and sends an HTTP request to OpenWeatherMap.
    3. It processes the JSON weather response to obtain outdoor conditions.
    4. It updates the LCD with information from the local sensor and the online weather service.

Instructions
    1. Connect the DHT11 and LCD1602 according to the pin assignments in the project firmware.
    2. Install ESP32 board support in Arduino IDE.
    3. Select the ESP32 board matching your development board and the correct serial port.
    4. Install the required third-party libraries for the firmware, including ArduinoJson and a compatible DHT sensor library. The ESP32 board package supplies WiFi.h and HTTPClient.h; LiquidCrystal.h is provided through an Arduino-compatible LCD library.
    5. Create an OpenWeatherMap API key and update the firmware with your Wi-Fi SSID, Wi-Fi password, API key, and location settings.

Future Improvements
-Replace the DHT11 with a more accurate environmental sensor.
-Design a custom enclosure or PCB for a more permanent build.
-Improve display navigation and make indoor/outdoor readings easier to distinguish.

Project Media
![alt text](image.png)

