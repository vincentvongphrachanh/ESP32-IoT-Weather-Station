#include <WiFi.h>                // Library for WiFi
#include <HTTPClient.h>          // Library for HTTP requests
#include <ArduinoJson.h>         // Library for parsing JSON data
#include <LiquidCrystal.h>       // Library for the LCD1602 display (parallel)
#include <DHT.h>                 // Library for DHT11 sensor

// WiFi credentials
const char* ssid = "SSID";
const char* password = "PASSWORD";

// OpenWeatherMap API settings
const char* apiKey = "PUT_API_KEY_HERE";  // Replace with your OpenWeatherMap API key
const char* city = "Memphis";          // Replace with your desired city
String apiURL = "http://api.openweathermap.org/data/2.5/weather?q=" + String(city) + "&appid=" + apiKey + "&units=imperial";

// DHT11 Sensor settings
#define DHTPIN 4           // GPIO pin for DHT11 data line
#define DHTTYPE DHT11      // Define the sensor type as DHT11
DHT dht(DHTPIN, DHTTYPE);  // Initialize the DHT sensor

// LCD1602 settings (parallel connection)
LiquidCrystal lcd(14, 12, 5, 18, 19, 21);  // RS, EN, D4, D5, D6, D7

void setup() {
  Serial.begin(115200);  // Start serial communication for debugging

  // Initialize LCD
  lcd.begin(16, 2);  // Set up the LCD's columns and rows
  lcd.setCursor(0, 0);
  lcd.print("Weather Station");
  lcd.setCursor(0, 1);
  lcd.print("Connecting...");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize the DHT sensor
  dht.begin();

  // Update the LCD to show the connection status
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Connected");
  delay(2000);
}

void loop() {
  // Fetch and display indoor temperature
  float indoorTemp = dht.readTemperature();
  
  if (isnan(indoorTemp)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    // Convert indoor temperature to Fahrenheit
    float indoorTempF = (indoorTemp * 9.0 / 5.0) + 32.0;

    Serial.println("Indoor Temp: " + String(indoorTempF) + " °F");

    // Display indoor temperature on the first row of the LCD
    lcd.clear();
    lcd.setCursor(0, 0);  // First line, reset cursor position
    lcd.print("In Temp: ");
    lcd.print(indoorTempF);
    lcd.print("F");
  }

  // Fetch and display outdoor temperature
  getWeatherData();

  // Delay before the next data fetch (e.g., every 60 seconds)
  delay(60000);  // 60 seconds
}

void getWeatherData() {
  if (WiFi.status() == WL_CONNECTED) {  // Check if the ESP32 is connected to WiFi
    HTTPClient http;
    http.begin(apiURL);  // Specify the API URL
    int httpCode = http.GET();  // Send the HTTP GET request

    if (httpCode > 0) {  // Check if the request was successful
      String payload = http.getString();  // Get the response payload
      Serial.println(payload);  // Print raw JSON for debugging

      // Parse the JSON response
      StaticJsonDocument<1024> doc;
      DeserializationError error = deserializeJson(doc, payload);
      if (!error) {
        float outdoorTemp = doc["main"]["temp"];  // Outdoor temperature in Fahrenheit

        Serial.println("Outdoor Temp: " + String(outdoorTemp) + " °F");

        // Display outdoor temperature on the second row of the LCD
        lcd.setCursor(0, 1);  // Second line
        lcd.print("Out Temp: ");
        lcd.print(outdoorTemp);
        lcd.print("F");
      } else {
        Serial.println("Failed to parse JSON");
      }
    } else {
      Serial.println("Error on HTTP request");
    }
    http.end();  // Close the connection
  }
}
