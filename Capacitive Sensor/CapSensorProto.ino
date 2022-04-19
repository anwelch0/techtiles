//THIS CODE WORKS FOR THE X and Y SENSORS
#include <CapacitiveSensor.h>

static int numOfElements = 11;

int backgroundMeas = 100;

int threshold[11] = {0,0,0,0,0,0,0,0,0,0,0};

long measurement[11] = {0,0,0,0,0,0,0,0,0,0,0};

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

void setup() {
  Serial.begin(115200);
  
  long sumBackground[numOfElements] = {0,0,0,0,0,0,0,0,0,0,0};
      
  Serial.println("Press enter when ready to perform background reading. Do not touch sensors.");

  while (Serial.available() == 0) {
  }
  
  char t = Serial.read();

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
    
   
  //End of taking measurements    
  //Set threshold values

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

}

void loop() {
  
  for(int i = 0; i < numOfElements; i++) {
    measurement[i] = sensors[i].capacitiveSensorRaw(15);

//    if ((i + 1) == numOfElements) {
//      Serial.println(measurement[i]);
//    }
//    else {
//      Serial.print(measurement[i]);
//      Serial.print("\t");
//    }
    
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

}
