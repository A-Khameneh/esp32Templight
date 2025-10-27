#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Abdollahian";
const char* password = "8805721740000";

const int potPin = 34;
const char* serverURL = "https://myflower-daxz.onrender.com/flower";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.print("در حال اتصال به WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\n✅ وصل شد!");
  Serial.print("IP دستگاه: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    int value = analogRead(potPin);

    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");

    String payload = "{\"sensor_value\": " + String(value) + "}";

    int responseCode = http.POST(payload);

    Serial.print("📤 کد پاسخ سرور: ");
    Serial.println(responseCode);

    if (responseCode > 0) {
      String response = http.getString();
      Serial.println("📥 پاسخ دریافتی از سرور:");
      Serial.println(response);
    } else {
      Serial.println("❌ ارسال ناموفق");
    }

    http.end();
  } else {
    Serial.println("⚠️ اتصال به WiFi قطع شده");
  }

  delay(5000); // هر ۵ ثانیه ارسال کن
}
