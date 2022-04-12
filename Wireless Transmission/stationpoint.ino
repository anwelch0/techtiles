#include <ESP8266WiFi.h>

char ssid[] = "TechtileRx";           // SSID of your AP
char pass[] = "AFlatMiner";         // password of your AP
IPAddress server(192,168,4,15);     // IP address of the AP
WiFiClient client;

uint8_t sensorData = 0;

//consider using softserial if needed

void setup() {
  Serial.begin(38400);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
   }
  Serial.println();
  Serial.println("Connected");
  Serial.println("station_bare_01.ino");
  Serial.print("LocalIP:"); Serial.println(WiFi.localIP());
  Serial.println("MAC:" + WiFi.macAddress());
  Serial.print("Gateway:"); Serial.println(WiFi.gatewayIP());
  Serial.print("AP MAC:"); Serial.println(WiFi.BSSIDstr());
}

void loop() {
  if(Serial.available() > 0){
    sensorData = Serial.read();
    Serial.flush();
    delay(50);
  }
  delay(50);
  client.connect(server, 80);
//  Serial.println("********************************");
//  Serial.print("Byte sent to the AP: ");

//The above lines are for using the ESP8266 as a standalone module
  Serial.print(client.println(sensorData));
  client.flush();
  client.stop();
  delay(1000);
}
