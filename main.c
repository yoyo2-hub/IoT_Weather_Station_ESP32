#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <DHT.h>

// ---------- CONFIG WIFI ----------
const char* ssid = "Votre_WiFi";
const char* password = "Votre_MDP";

// ---------- CONFIG MQTT ----------
const char* mqtt_server = "192.168.1.10"; // mettre l'IP du broker
WiFiClient espClient;
PubSubClient client(espClient);

// ---------- CAPTEURS ----------
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#define LDR_PIN 34
#define MQ2_PIN 35   // optionnel

// ---------- OLED ----------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ---------- TIMER ----------
unsigned long lastMsg = 0;
const long interval = 10000;

void setup_wifi() {
  delay(10);
  Serial.println("Connexion au WiFi...");
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connecté !");
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Connexion au broker MQTT...");
    if (client.connect("ESP32-Meteo")) {
      Serial.println("OK !");
      client.publish("station/ESP32/status", "online");
    } else {
      Serial.print("Échec, code : ");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

void setup() {
  Serial.begin(115200);

  // Init capteurs
  dht.begin();

  // Init OLED
  Wire.begin(21, 22);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Erreur OLED !");
    while (true);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // WiFi + MQTT
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) reconnect();
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > interval) {
    lastMsg = now;

    float t = dht.readTemperature();
    float h = dht.readHumidity();
    int lum = analogRead(LDR_PIN);
    int mq2 = analogRead(MQ2_PIN);

    // ----- Affichage OLED -----
    display.clearDisplay();
    display.setCursor(0,0);
    display.print("Temp: "); display.print(t); display.println(" C");
    display.print("Hum:  "); display.print(h); display.println(" %");
    display.print("Lum:  "); display.println(lum);
    display.display();

    // ----- Publication MQTT -----
    char msg[50];

    sprintf(msg, "%.2f", t);
    client.publish("station/ESP32/temperature", msg);

    sprintf(msg, "%.2f", h);
    client.publish("station/ESP32/humidite", msg);

    sprintf(msg, "%d", lum);
    client.publish("station/ESP32/luminosite", msg);

    if (mq2 > 2000) {
      client.publish("station/ESP32/alerte_gaz", "1");
    }
  }
}
