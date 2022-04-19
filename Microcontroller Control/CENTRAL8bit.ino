//Code for the Central Arduino to relay the 8-bit data to the display
#include<Wire.h>//This library is used for I2C communication

static int CENTRALNO = 8; // <----- Change to be the Central Arduino number
int dataR = 0;

void setup() {
  Serial.begin(115200);
  Wire.begin(CENTRALNO);
  Wire.onReceive(receiveEvent);
}
void receiveEvent(int bytes) {
  dataR = Wire.read();    // read one character from the I2C
}
void loop() {  
  Serial.println(dataR);
  delay(50);
}
