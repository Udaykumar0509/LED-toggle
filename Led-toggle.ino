#include <WiFi.h>
#include <WebServer.h>

// Replace with your network credentials
const char* ssid = "your_wifi_ssid";     // Your WiFi SSID
const char* password = "your_wifi_password"; // Your WiFi Password

// Create an instance of the WebServer
WebServer server(80);

// LED pin
const int ledPin = 23; // Change this to the GPIO pin you're using

// Function to handle the root URL
void handleRoot() {
  server.send(200, "text/html", "<h1>ESP32 Web Server</h1>"
                                  "<p><a href=\"/on\">Turn ON</a></p>"
                                  "<p><a href=\"/off\">Turn OFF</a></p>");
}

// Function to turn the LED on
void handleLedOn() {
  digitalWrite(ledPin, HIGH); // Turn LED ON
  server.send(200, "text/html", "<h1>LED is ON</h1><p><a href=\"/\">Go Back</a></p>");
}

// Function to turn the LED off
void handleLedOff() {
  digitalWrite(ledPin, LOW); // Turn LED OFF
  server.send(200, "text/html", "<h1>LED is OFF</h1><p><a href=\"/\">Go Back</a></p>");
}

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);
  
  // Set LED pin as output
  pinMode(ledPin, OUTPUT);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected!");

  // Start the web server
  server.on("/", handleRoot); // Handle root URL
  server.on("/on", handleLedOn); // Handle LED ON request
  server.on("/off", handleLedOff); // Handle LED OFF request
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient(); // Handle incoming client requests
}
