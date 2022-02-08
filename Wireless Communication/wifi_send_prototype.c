#include <dummy.h>

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <string>

using namespace std;

const char* WIFI_SSID = "some network";
const char* WIFI_PASS = "some password";
uint16_t UDP_PORT = 4210;

//define udp
WiFiUDP UDP;
char packet[100];
char reply[] = "Packet received.";

bool wifiEn = false;
unsigned long resetTime = 0;
const unsigned long MSCUTOFF = 5000;
//will determine if wireless needs to be shut off


void UDPsetup(){
  //set up serial
  Serial.begin(115200);
  Serial.println();
  
  //turn on WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  //wait for WiFi to connect
  while(WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected to IP address: ");
  Serial.println(WiFi.localIP());
  //turn on UDP
  UDP.begin(UDP_PORT);
  Serial.print("Awaiting input from UDP port: ");
  Serial.println(UDP_PORT);
}

void sendPacket(char *destIP, uint16_t destPort, char *sensorData){
  UDP.beginPacket(destIP, destPort);
    UDP.write(sensorData);
    UDP.endPacket();
}

void wirelessEnable(){
  wifiEn = true;
  resetTime = millis();
}

//TODO: Enable interrupts in this file and turn on transmission ONLY when interrupts are triggered
// make use of attachInterrupt(digitalPinToInterrupt(pin), ISR, mode)
// Consider using a boolean ENABLE value, activated during the ISR
// Will be triggered upon change of pins 2 or 3, so call will probably look like 
//attachInterrupt(digitalPinToInterrupt(2), wirelessEnable(), CHANGE);

//TODO: Create method to read & process the sensors in its own header and .c file

int main(){
  string sensorData = "10001000";
  char* dataArray; //sensor data will be cast to this array to be sent through wifi module
  UDPsetup();
  attachInterrupt(digitalPinToInterrupt(2), wirelessEnable, CHANGE);
  //sets up interrupt to enable wifi, detects change on digital pin 2
  
  while(1){
    if(wifiEn){
      dataArray = &sensorData[0];
      sendPacket("some ip", 4210, dataArray);
      delay(5000);
    }
    
    if(millis() - resetTime >= MSCUTOFF){
      wifiEn = false;
    }
    //calls millis() every loop, if difference is over 5s, turn off wifi
  }
  
  return 0;
}