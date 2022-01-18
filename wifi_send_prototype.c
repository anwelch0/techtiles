#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define WIFI_SSID "some network"
#define WIFI_PASS "some password"
#define UDP_PORT someport1234

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

int main(){
	UDPsetup();
	while(1){
		sendPacket("some ip", "some udp port" sensorData);
		delay(5000);
	}
	
	return 0;
}