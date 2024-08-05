# ESP8266 Telegram Notification System

This project uses an ESP8266 microcontroller to send a notification message via Telegram when a sensor value exceeds a specified threshold. The ESP8266 connects to WiFi and uses the Telegram Bot API to send messages.

## Features

- Connect to a WiFi network.
- Read analog sensor values.
- Send a Telegram message when the sensor value exceeds a threshold.

## Technologies Used

- **ESP8266**: Microcontroller used for the project.
- **Arduino IDE**: Software used for programming the ESP8266.
- **Telegram Bot API**: Used to send messages to a Telegram chat.

## Requirements

- ESP8266 microcontroller.
- Arduino IDE installed on your computer.
- Telegram bot and chat ID.
- Analog sensor connected to the ESP8266.

## Installation

1. **Clone the Repository:**

    ```sh
    git clone https://github.com/yourusername/ESP8266_Telegram_Notification
    cd ESP8266_Telegram_Notification
    ```

2. **Set Up Telegram Bot:**

    - Create a new bot on Telegram by talking to the [BotFather](https://core.telegram.org/bots#botfather).
    - Obtain the bot token and chat ID.

3. **Configure the ESP8266:**

    - Open the Arduino IDE.
    - Install the ESP8266 board package via the Boards Manager.
    - Install the required libraries: `ESP8266WiFi`, `ESP8266HTTPClient`, `WiFiClientSecure`, and `UrlEncode`.

4. **Update the Code:**

    - Replace `YOUR_CHAT_ID` and `YOUR_BOT_TOKEN` with your actual Telegram chat ID and bot token in the code.

    ```cpp
    const char* ssid = "YourSSID"; // Your WiFi network name
    const char* password = "YourPassword"; // Your WiFi network password
    const char* chatId = "YOUR_CHAT_ID"; // Replace with your Telegram chat ID
    const char* botToken = "YOUR_BOT_TOKEN"; // Replace with your Telegram bot token
    ```

5. **Upload the Code:**

    - Connect your ESP8266 to your computer.
    - Select the correct board and port in the Arduino IDE.
    - Upload the code to the ESP8266.

## Usage

1. **Power the ESP8266:**

    - Connect the ESP8266 to a power source.

2. **Monitor Serial Output:**

    - Open the Serial Monitor in the Arduino IDE to view the sensor values and status messages.

3. **Receive Notifications:**

    - When the sensor value exceeds the threshold (e.g., 700), a message ("GAS!") will be sent to your Telegram chat.

## Code

```cpp
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h> // Use WiFiClientSecure for HTTPS
#include <UrlEncode.h>

const char* ssid = "YourSSID"; // Your WiFi network name
const char* password = "YourPassword"; // Your WiFi network password
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
