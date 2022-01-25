#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define WIFI_SSID "some network" //will be the hypothetical hospital's wifi
#define WIFI_PASS "some password"
#define UDP_PORT 4210

//define udp
WifiUDP UDP;
char packet[100];
char reply[] = "Packet received.";

bool wifiEn = false;
unsigned long resetTime = 0;
const unsigned long MSCUTOFF = 5000;
//will determine if wireless needs to be shut off

string sensorData;

void UDPsetup(){
	//set up serial
	Serial.begin(115200);
	Serial.println();
	
	//turn on WiFi
	WiFi.begin(WIFI_SSID, WIFI_PASS);
	Serial.print("Connecting to ");
	Serial.print(WIFI_SSID);
	//wait for WiFi to connect
	while(WiFi.status() !- WL_CONNECTED){
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

void sendPacket(string destIP, string destPort, string sensorData){
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
	UDPsetup();
	attachInterrupt(digitalPinToInterrupt(2), wirelessEnable(), CHANGE);
	//sets up interrupt to enable wifi, detects change on digital pin 2
	
	while(1){
		if(wifiEn){
			sendPacket("some ip", "some udp port" sensorData); //should be the ip adress and port of the computer with the display program
			delay(5000);
		}
		if(millis() - resetTime >= MSCUTOFF){
			wifiEn = false;
		}
		//calls millis() every loop, if difference is over 5s, turn off wifi
	}
	
	return 0;
}
