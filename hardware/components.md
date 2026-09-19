# Hardware Documentation

## Project Overview

The ESP32 IoT Weather Station combines local temperature
measurements with outdoor weather information retrieved
through Wi-Fi.

The system uses an ESP32-WROVER-E microcontroller,
DHT11 temperature sensor, and LCD1602 display.

## Bill of Materials

| Component | Quantity | Purpose |
|---|---:|---|
| ESP32-WROVER-E | 1 | Main microcontroller and Wi-Fi communication |
| DHT11 Sensor | 1 | Indoor temperature measurement |
| LCD1602 Display | 1 | Displays indoor and outdoor temperatures |
| Potentiometer | 1 | LCD contrast adjustment |
| Breadboard | 1 | Circuit prototyping |
| Jumper Wires | As needed | Electrical connections |
| USB Cable | 1 | Programming and power |

## ESP32 Pin Assignments

| ESP32 GPIO | Connected Component | Function |
|---|---|---|
| GPIO 4 | DHT11 DATA | Temperature sensor data |
| GPIO 14 | LCD RS | Register select |
| GPIO 12 | LCD EN | LCD enable |
| GPIO 5 | LCD D4 | LCD data |
| GPIO 18 | LCD D5 | LCD data |
| GPIO 19 | LCD D6 | LCD data |
| GPIO 21 | LCD D7 | LCD data |

## LCD1602 Configuration

The LCD1602 operates in 4-bit parallel communication mode.

```cpp
LiquidCrystal lcd(14, 12, 5, 18, 19, 21);
```

The LCD is initialized using:

```cpp
lcd.begin(16, 2);
```

The first row displays indoor temperature.

The second row displays outdoor temperature retrieved
from OpenWeatherMap.

## DHT11 Configuration

The DHT11 is connected to GPIO 4.

```cpp
#define DHTPIN 4
#define DHTTYPE DHT11
```

The firmware retrieves the temperature in Celsius
and converts it to Fahrenheit.

## Power Distribution

The ESP32 is powered through USB.

The LCD1602 uses a 5 V supply, while the DHT11
uses the ESP32's 3.3 V supply.

All components must share a common ground.

## Communication

The DHT11 communicates with the ESP32 through
a single-wire-style digital sensor interface.

The LCD1602 uses a 4-bit parallel interface.

The ESP32 connects to Wi-Fi and retrieves
outdoor weather data through HTTP requests.