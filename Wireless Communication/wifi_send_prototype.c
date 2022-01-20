#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define WIFI_SSID "some network" //will be the hypothetical hospital's wifi
#define WIFI_PASS "some password"
#define UDP_PORT 4210

//define udp
WifiUDP UDP;
char packet[100];
char reply[] = "Packet received.";

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

//TODO: Enable interrupts in this file and turn on transmission ONLY when interrupts are triggered
//TODO: Create method to read & process the sensors in its own header and .c file

int main(){
	UDPsetup();
	while(1){
		sendPacket("some ip", "some udp port" sensorData); //should be the ip adress and port of the computer with the display program
		delay(5000);
	}
	
	return 0;
}
