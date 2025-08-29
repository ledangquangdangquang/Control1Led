#include <ESP8266WiFi.h>

WiFiServer server(8080); // Port TCP

const char* ssid = "Techpro";
const char* password = "!TechproHaNoi@2021#";
const int ledPin = D1;  // hoặc LED_BUILTIN

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) delay(500);

  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client connected");  // Ghi log kết nối

    while (client.connected()) {
      if (client.available()) {
        String command = client.readStringUntil('\n');
        command.trim();

        // 👉 In chuỗi nhận được để debug
        Serial.print("Received command: [");
        Serial.print(command);
        Serial.println("]");

        if (command == "LED_ON") {
          digitalWrite(ledPin, HIGH);
          client.println("LED ON");
        } else if (command == "LED_OFF") {
          digitalWrite(ledPin, LOW);
          client.println("LED OFF");
        } else {
          client.println("UNKNOWN COMMAND");
        }
      }
    }

    client.stop();
    Serial.println("Client disconnected");
  }
}

