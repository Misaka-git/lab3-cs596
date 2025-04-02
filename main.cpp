#include <WiFi.h>
#include <HttpClient.h>
#include <DHT.h>

char ssid[] = "ATTmtSBq2N";
char pass[] = "t8rwd4u#byxa";

const char kHostname[] = "18.222.23.244";  // your EC2 IP
const int kPort = 5000;

#define DHTPIN 15
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const int kNetworkTimeout = 30 * 1000;
const int kNetworkDelay = 1000;

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Connecting to WiFi...");

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println(WiFi.localIP());

  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(5000);
    return;
  }

  String path = "/update?temp=" + String(temperature, 1) + "&hum=" + String(humidity, 1);

  WiFiClient c;
  HttpClient http(c);
  Serial.println("Sending to server: " + path);
  int err = http.get(kHostname, kPort, path.c_str());

  if (err == 0) {
    Serial.println("Request OK");
    if (http.responseStatusCode() == 200) {
      http.skipResponseHeaders();
      while (http.available()) {
        Serial.write(http.read());
      }
    } else {
      Serial.print("Bad response code: ");
      Serial.println(http.responseStatusCode());
    }
  } else {
    Serial.print("Connection failed: ");
    Serial.println(err);
  }

  http.stop();
  delay(5000);
}
