#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h> // Use WiFiClientSecure for HTTPS
#include <UrlEncode.h>

const char* ssid = "Sunantha";//your hotspot name
const char* password = "1234";//your hotspot password
const char* chatId = "YOUR_CHAT_ID"; // Replace with your Telegram chat ID
const char* botToken = "YOUR_BOT_TOKEN"; // Replace with your Telegram bot token

void sendMessage(String message) {
  String encodedMessage = urlEncode(message);
  String url = "https://api.telegram.org/bot" + String(botToken) + "/sendMessage?chat_id=" + String(chatId) + "&text=" + encodedMessage;

  WiFiClientSecure client; // Use WiFiClientSecure for HTTPS
  HTTPClient http;
  
  http.begin(client, url);
  int httpResponseCode = http.GET(); // Change to GET request for Telegram bot API

  if (httpResponseCode == 200) {
    Serial.println("Message sent successfully");
  } else {
    Serial.println("Error sending the message");
    Serial.print("HTTP response code: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);

  if (sensorValue >= 700) {
    sendMessage("GAS!");
  }

  delay(1000); // Adjust delay as needed for your application
}
