#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Abdollahian";
const char* password = "8805721740000";

const int potPin = 34; // پین پتانسیومتر
WebServer server(80);  // پورت پیش‌فرض HTTP

void handleRoot() {
  int value = analogRead(potPin);
  
  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'><title>Potentiometer</title></head><body>";
  html += "<h1>مقدار پتانسیومتر:</h1>";
  html += "<h2>" + String(value) + "</h2>";
  html += "</body></html>";
  
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("در حال اتصال به WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nوصل شد!");
  Serial.print("IP دستگاه: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.begin();
  Serial.println("وب‌سرور فعال شد");
}

void loop() {
  server.handleClient();
}
