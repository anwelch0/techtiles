#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define WIFI_SSID "some network"
#define WIFI_PASS "some password"
#define UDP_PORT 4210

//define udp
WifiUDP UDP;
char packet[100];
char reply[] = "Packet received.";

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

void ParsePacket(){
	//read any received packets
	int packetSize = UDP.parsePacket();
	if(packetSize){
		Serial.print("Received packet of size: ");
		Serial.println(packetSize);
		int len = UDP.read(packet, 100);
		if (len > 0){
			packet[len] = '\0'
	}
}
	
//TODO: store reading in ParsePacket() into a string variable, then send that string to the display module



int main(){
	UDPsetup();
	while(1){
		ParsePacket();
	}
	
	return 0;
}