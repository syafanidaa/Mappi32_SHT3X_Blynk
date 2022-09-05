#define BLYNK_TEMPLATE_ID "XXXXXXXXXXXXXXXXXXXXXXXX"
#define BLYNK_DEVICE_NAME "XXXXXXX"
#define BLYNK_AUTH_TOKEN "XXXXXXXXXXXXXXXXXXXXXXXX"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h> //pembacaan mappi ke sensor

#include <SHTSensor.h>

SHTSensor sht;
String datasensor;
#define pinLED  5

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "XXXXXXXXXXXX";   // Nama Hotspot / WiFi
char pass[] = "XXXXXXXXXXXX"; // Password WiFi


BlynkTimer timer;


void myTimerEvent()
{
  Blynk.virtualWrite(V5, millis() / 1000);
}


void setup() {

  Wire.begin();
  Serial.begin(115200);
  pinMode (pinLED, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  Wire.begin();

  if (sht.init()) {
    Serial.print("init(): success\n");
  } else {
    Serial.print("init(): failed\n");
  }
  sht.setAccuracy(SHTSensor::SHT_ACCURACY_MEDIUM); // only supported by SHT3x



}

void loop() {
  Blynk.run();
  timer.run();
  float Temperature = (sht.getTemperature());
  float Humidity = (sht.getHumidity());
  datasensor = String (sht.getTemperature(), 2);
  if (sht.readSample()) {
    Serial.print("SHT:\n");
    Serial.print("  Humidity: ");
    Serial.print(sht.getHumidity(), 2);
    Serial.print("\n");
    Serial.print("  Temperature :  ");
    Serial.print(sht.getTemperature(), 2);
    Serial.print("\n");
  } else {
    Serial.print("Error in readSample()\n");
  }
  Blynk.virtualWrite(V0, Humidity);
  Blynk.virtualWrite(V1, Temperature);
  delay(1000);

  pinMode (pinLED, HIGH);
  delay(250);
  pinMode (pinLED, LOW);
  delay(250);
}
