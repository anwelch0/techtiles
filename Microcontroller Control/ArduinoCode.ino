#include<Wire.h>//This library is used for I2C communication
#include <CapacitiveSensor.h>

static int CENTRALNO = 8;// <----- Change to the device ID for the Central Arduino
static int DEVICENO = 0; // <----- Change to a unique device ID
static int dely = 100; // delay
int dataR = 0;

////////////////////////////////////////////////////////////////////////////////
//

static int numOfElements = 11;
int backgroundMeas = 100;
int threshold[11] = {0,0,0,0,0,0,0,0,0,0,0};
int measurement[11] = {0,0,0,0,0,0,0,0,0,0,0};  // I CHANGED THIS FROM A LONG TO AN INT

CapacitiveSensor sensors[11] = 
{
  CapacitiveSensor(2,3),
  CapacitiveSensor(2,4),
  CapacitiveSensor(2,5),
  CapacitiveSensor(2,6),
  CapacitiveSensor(2,7),
  CapacitiveSensor(2,8),
  CapacitiveSensor(2,9),
  CapacitiveSensor(2,10),
  CapacitiveSensor(2,11),
  CapacitiveSensor(2,12),
  CapacitiveSensor(2,13)
};

//
////////////////////////////////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200); // Baude Rate

////////////////////////////////////////////////////////////////////////////////
//

  long sumBackground[numOfElements] = {0,0,0,0,0,0,0,0,0,0,0};

  delay(100);
  //For loop that takes background measurements
  for (int numMeas = 0; numMeas < backgroundMeas; numMeas++) {
      for(int i = 0; i<numOfElements; i++) {
        //Read values for each sensor strip
        long temp_measurement = sensors[i].capacitiveSensorRaw(15);
        
        sumBackground[i] = sumBackground[i] + temp_measurement;
        
        //Print statement to debug with
        if ((i + 1) == numOfElements) {
          Serial.println(temp_measurement);
        }
        else {
          Serial.print(temp_measurement);
          Serial.print("\t");
        }
      }
      delay(10);
    }

    for (int i = 0; i < numOfElements; i++) {
      threshold[i] = sumBackground[i] / long(backgroundMeas);
    }
    
    Serial.print("Threshold Values: ");
    
    for(int i = 0; i<numOfElements; i++) {
      
      if ((i + 1) == numOfElements) {
        Serial.println(threshold[i]);
      }
      else {
        Serial.print(threshold[i]);
        Serial.print("\t");
      }
    }

//
////////////////////////////////////////////////////////////////////////////////
  
  Wire.begin();
}
void loop() {
////////////////////////////////////////////////////////////////////////////////
//

  for(int i = 0; i < numOfElements; i++) {
    measurement[i] = sensors[i].capacitiveSensorRaw(15);
    
    if ((measurement[i] > (threshold[i] + 750)) || (measurement[i] < (threshold[i] - 750))) {
      if ((i + 1) == numOfElements) {
        Serial.println("1");
      }
      else {
        Serial.print("1");
      }
    }
    else {
      if ((i + 1) == numOfElements) {
        Serial.println("0");
      }
      else {
        Serial.print("0");
      }
    }
 
  }

  delay(10);

//
////////////////////////////////////////////////////////////////////////////////

  int measurements1[3];
  int measurements2[3];
  int measurements3[3];
  int measurements4[3];
  for(int i = 0; i <=2; i++){
    measurements1[i] = measurement[i];
    measurements2[i] = measurement[i+3];
    measurements3[i] = measurement[i+6];
    measurements4[i] = measurement[i+9];
    if (i==2)measurements4[i] = 0;
  }
  
  int data = concatinate(measurement,numOfElements);
  int data1 = concatinate1(measurements1,3);
  int data2 = concatinate2(measurements2,3);
  int data3 = concatinate3(measurements3,3);
  int data4 = concatinate4(measurements4,2);

  Serial.println("");
  Serial.println(data,BIN);
  Serial.println("");

  Wire.beginTransmission(CENTRALNO); // transmit to central tile
  Wire.write(data1);
  Wire.endTransmission();
  Serial.println(data1,BIN);
  delay(dely);
  Wire.beginTransmission(CENTRALNO); // transmit to central tile
  Wire.write(data2);
  Wire.endTransmission();
  Serial.println(data2,BIN);
  delay(dely);
  Wire.beginTransmission(CENTRALNO); // transmit to central tile
  Wire.write(data3);
  Wire.endTransmission();
  Serial.println(data3,BIN);
  delay(dely);
  Wire.beginTransmission(CENTRALNO); // transmit to central tile
  Wire.write(data4);
  Wire.endTransmission();
  Serial.println(data4,BIN);
  delay(dely);
}

//The pow() function wasn't working properly (it said 10^2 = 99), so I made my own. This code returns num^pow.
int rais(int num, int power){
  int output = 1;
  
  for(int i = 0; i < power; i++){ output *= num; }
  
  return output;
}

int concatinate(int data[], int sizeOfArray){
  int output = 0;
  sizeOfArray -= 1;

  for(int i = 0; i <= sizeOfArray; i++){
    if(data[i] > threshold[i]) data[i] = 1;
    else data[i] = 0;
    output += data[i] * rais(2, sizeOfArray-i);
  }
  output += DEVICENO * rais(2,sizeOfArray+1);
  
  return output;
}

// Turns datapoints (x, y, z, a, b, c) into integer xyzabc. sizeOfArray is the number of datapoints, in this case 6.
int concatinate1(int data[], int sizeOfArray){
  int output = 0;
  sizeOfArray -= 1;

  for(int i = 0; i <= sizeOfArray; i++){
    if(data[i] > threshold[i]) data[i] = 1;
    else data[i] = 0;
    output += data[i] * rais(2, sizeOfArray-i);
  }
  output += 0*rais(2,sizeOfArray+1);
  output += DEVICENO * rais(2,sizeOfArray+3);
  
  return output;
}

int concatinate2(int data[], int sizeOfArray){
  int output = 0;
  sizeOfArray -= 1;

  for(int i = 0; i <= sizeOfArray; i++){
    if(data[i] > threshold[i]) data[i] = 1;
    else data[i] = 0;
    output += data[i] * rais(2, sizeOfArray-i);
  }
  output += 1*rais(2,sizeOfArray+1);
  output += DEVICENO * rais(2,sizeOfArray+3);
  
  return output;
}

int concatinate3(int data[], int sizeOfArray){
  int output = 0;
  sizeOfArray -= 1;

  for(int i = 0; i <= sizeOfArray; i++){
    if(data[i] > threshold[i]) data[i] = 1;
    else data[i] = 0;
    output += data[i] * rais(2, sizeOfArray-i);
  }
  output += 2*rais(2,sizeOfArray+1);
  output += DEVICENO * rais(2,sizeOfArray+3);
  
  return output;
}

int concatinate4(int data[], int sizeOfArray){
  int output = 0;
  sizeOfArray -= 1;

  for(int i = 0; i <= sizeOfArray; i++){
    if(data[i] > threshold[i]) data[i] = 1;
    else data[i] = 0;
    output += data[i] * rais(2, sizeOfArray-i);
  }
  
  output += 3*rais(2,sizeOfArray+2);
  output += DEVICENO * rais(2,sizeOfArray+4);
  
  return output;
}
