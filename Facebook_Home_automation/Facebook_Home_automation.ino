
#include <ESP8266WiFi.h>

#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define D1 5 // GPIO5
#define D2 4 // GPIO5
#define D4 0 // GPIO5

String  Request;
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME  "ShinNguyen99"
#define AIO_KEY  "e44b9897dcab4cecbbca17f2158d3e38"
WiFiClient client;  

Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

Adafruit_MQTT_Subscribe myhome = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/myhome");
boolean MQTT_connect();

boolean MQTT_connect() {
  int8_t ret;
  if (mqtt.connected()) {
    return true;
  }  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) {
    mqtt.disconnect();
    delay(2000);
    retries--;
    if (retries == 0) {
      return false;
    }
  } return true;
}

void setup()
{
  Serial.begin(115200);
  Request = "";

  WiFi.disconnect();
  delay(3000);
  Serial.println("Start IoT");
  WiFi.begin("DANG NANG WIFI", "123@123Aa");
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(300);
    Serial.print(".");

  }
  Serial.println("Wifi Connected");
  Serial.println("Your IP is");
  Serial.println((WiFi.localIP().toString()));

  mqtt.subscribe(&myhome);

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D4, OUTPUT);

  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D4, HIGH);
}


void loop()
{

    if (MQTT_connect()) {
      Adafruit_MQTT_Subscribe *subscription_name;
      while ((subscription_name = mqtt.readSubscription(5000))) {
        if (subscription_name == &myhome) {
          Request = ((char *)myhome.lastread);
          Serial.println(Request);
        }
        if (Request == "L1on") {
          digitalWrite(D1,LOW);
          Serial.println("Main Light is on...");

        }
        if (Request == "L1off") {
          digitalWrite(D1,HIGH);
          Serial.println("Main Light is off...");

        }
        if (Request == "L2on") {
          digitalWrite(D2,LOW);
          Serial.println("Desk lamp is is on...");

        }
        if (Request == "L2off") {
          digitalWrite(D2,HIGH);
          Serial.println("Desk lamp is off...");

        }
        if (Request == "F1on") {
          digitalWrite(D4,LOW);
          Serial.println("Fan is on...");

        }    
        if (Request == "F1off") {
          digitalWrite(D4,HIGH);
          Serial.println("Fan is off...");

        }

      }

    }
}
