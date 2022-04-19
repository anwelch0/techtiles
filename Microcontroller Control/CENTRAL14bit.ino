//Code for the Central Arduino to decode the data and display the 11-bit sensor data + 3-bit Device Number
#include<Wire.h>//This library is used for I2C communication

static int CENTRALNO = 8; // <----- Change to be the Central Arduino number
int dataR = 0;

int dataMC0= 0;
int dataMC1= 2048;
int dataMC2= dataMC1 + dataMC1;
int dataMC3= dataMC2 + dataMC1;
int dataMC4= dataMC3 + dataMC1;
int dataMC5= dataMC4 + dataMC1;
int dataMC6= dataMC5 + dataMC1;
int dataMC7= dataMC6 + dataMC1;
static int trueMC0 = dataMC0;
static int trueMC1 = dataMC1;
static int trueMC2 = dataMC2;
static int trueMC3 = dataMC3;
static int trueMC4 = dataMC4;
static int trueMC5 = dataMC5;
static int trueMC6 = dataMC6;
static int trueMC7 = dataMC7;

void setup() {
  Serial.begin(115200);
  Wire.begin(CENTRALNO);
  Wire.onReceive(receiveEvent);
}
void receiveEvent(int bytes) {
  dataR = Wire.read();    // read one character from the I2C
}
void loop() {
  int address = findAddress(dataR);
  int type = findType(dataR,address);
  int data = findData(dataR,address,type);

  modify(address,type,data);
  
  Serial.println(dataMC0,BIN);
  Serial.println(dataMC1,BIN);
  Serial.println(dataMC2,BIN);
  Serial.println(dataMC3,BIN);
  Serial.println(dataMC4,BIN);
  Serial.println(dataMC5,BIN);
  Serial.println(dataMC6,BIN);
  Serial.println(dataMC7,BIN);
  Serial.println(" ");
  delay(100);
}

int rais(int num, int power){
  int output = 1;
  
  for(int i = 0; i < power; i++){ output *= num; }
  
  return output;
}

int findAddress(int dataR){
  int output = dataR/rais(2,5);
  return output;
}

int findType(int dataR, int address){
  int output = ( dataR - address*rais(2,5) )/rais(2,3);
  return output;
}

int findData(int dataR, int address, int type){
  int output = dataR - address*rais(2,5) - type*rais(2,3);
  return output;
}

void modify(int address, int type, int data){
  if (address == 0){                                                                       //CHANGE ME
    int bufferit = dataMC0 - trueMC0;                                                      //CHANGE ME
    if (type == 0){
      dataMC0 = dataMC0 - (bufferit/rais(2,8))*rais(2,8);                                  //CHANGE ME
      dataMC0 += data*rais(2,8);                                                           //CHANGE ME
    }
    else if (type == 1){
      dataMC0 = dataMC0 - ( bufferit/rais(2,5)*rais(2,5)- bufferit/rais(2,8)*rais(2,8) );  //CHANGE ME
      dataMC0 += data*rais(2,5);                                                           //CHANGE ME
    }
    else if (type == 2){
      dataMC0 = dataMC0 - ( bufferit/rais(2,2)*rais(2,2) - bufferit/rais(2,5)*rais(2,5) ); //CHANGE ME
      dataMC0 += data*rais(2,2);                                                           //CHANGE ME
    }
    else if (type == 3){
      dataMC0 = dataMC0 - ( bufferit - bufferit/rais(2,2)*rais(2,2) );                     //CHANGE ME
      dataMC0 += data;                                                                     //CHANGE ME
    }
  }

  if (address == 1){                                                                       //CHANGE ME
    int bufferit = dataMC1 - trueMC1;                                                      //CHANGE ME
    if (type == 0){
      dataMC1 = dataMC1 - (bufferit/rais(2,8))*rais(2,8);                                  //CHANGE ME
      dataMC1 += data*rais(2,8);                                                           //CHANGE ME
    }
    else if (type == 1){
      dataMC1 = dataMC1 - ( bufferit/rais(2,5)*rais(2,5)- bufferit/rais(2,8)*rais(2,8) );  //CHANGE ME
      dataMC1 += data*rais(2,5);                                                           //CHANGE ME
    }
    else if (type == 2){
      dataMC1 = dataMC1 - ( bufferit/rais(2,2)*rais(2,2) - bufferit/rais(2,5)*rais(2,5) ); //CHANGE ME
      dataMC1 += data*rais(2,2);                                                           //CHANGE ME
    }
    else if (type == 3){
      dataMC1 = dataMC1 - ( bufferit - bufferit/rais(2,2)*rais(2,2) );                     //CHANGE ME
      dataMC1 += data;                                                                     //CHANGE ME
    }
  }

  if (address == 2){                                                                       //CHANGE ME
    int bufferit = dataMC2 - trueMC2;                                                      //CHANGE ME
    if (type == 0){
      dataMC2 = dataMC2 - (bufferit/rais(2,8))*rais(2,8);                                  //CHANGE ME
      dataMC2 += data*rais(2,8);                                                           //CHANGE ME
    }
    else if (type == 1){
      dataMC2 = dataMC2 - ( bufferit/rais(2,5)*rais(2,5)- bufferit/rais(2,8)*rais(2,8) );  //CHANGE ME
      dataMC2 += data*rais(2,5);                                                           //CHANGE ME
    }
    else if (type == 2){
      dataMC2 = dataMC2 - ( bufferit/rais(2,2)*rais(2,2) - bufferit/rais(2,5)*rais(2,5) ); //CHANGE ME
      dataMC2 += data*rais(2,2);                                                           //CHANGE ME
    }
    else if (type == 3){
      dataMC2 = dataMC2 - ( bufferit - bufferit/rais(2,2)*rais(2,2) );                     //CHANGE ME
      dataMC2 += data;                                                                     //CHANGE ME
    }
  }

  if (address == 3){                                                                       //CHANGE ME
    int bufferit = dataMC3 - trueMC3;                                                      //CHANGE ME
    if (type == 0){
      dataMC3 = dataMC3 - (bufferit/rais(2,8))*rais(2,8);                                  //CHANGE ME
      dataMC3 += data*rais(2,8);                                                           //CHANGE ME
    }
    else if (type == 1){
      dataMC3 = dataMC3 - ( bufferit/rais(2,5)*rais(2,5)- bufferit/rais(2,8)*rais(2,8) );  //CHANGE ME
      dataMC3 += data*rais(2,5);                                                           //CHANGE ME
    }
    else if (type == 2){
      dataMC3 = dataMC3 - ( bufferit/rais(2,2)*rais(2,2) - bufferit/rais(2,5)*rais(2,5) ); //CHANGE ME
      dataMC3 += data*rais(2,2);                                                           //CHANGE ME
    }
    else if (type == 3){
      dataMC3 = dataMC3 - ( bufferit - bufferit/rais(2,2)*rais(2,2) );                     //CHANGE ME
      dataMC3 += data;                                                                     //CHANGE ME
    }
  }
  
  if (address == 4){                                                                       //CHANGE ME
    int bufferit = dataMC4 - trueMC4;                                                      //CHANGE ME
    if (type == 0){
      dataMC4 = dataMC4 - (bufferit/rais(2,8))*rais(2,8);                                  //CHANGE ME
      dataMC4 += data*rais(2,8);                                                           //CHANGE ME
    }
    else if (type == 1){
      dataMC4 = dataMC4 - ( bufferit/rais(2,5)*rais(2,5)- bufferit/rais(2,8)*rais(2,8) );  //CHANGE ME
      dataMC4 += data*rais(2,5);                                                           //CHANGE ME
    }
    else if (type == 2){
      dataMC4 = dataMC4 - ( bufferit/rais(2,2)*rais(2,2) - bufferit/rais(2,5)*rais(2,5) ); //CHANGE ME
      dataMC4 += data*rais(2,2);                                                           //CHANGE ME
    }
    else if (type == 3){
      dataMC4 = dataMC4 - ( bufferit - bufferit/rais(2,2)*rais(2,2) );                     //CHANGE ME
      dataMC4 += data;                                                                     //CHANGE ME
    }
  }

  if (address == 5){                                                                       //CHANGE ME
    int bufferit = dataMC5 - trueMC5;                                                      //CHANGE ME
    if (type == 0){
      dataMC5 = dataMC5 - (bufferit/rais(2,8))*rais(2,8);                                  //CHANGE ME
      dataMC5 += data*rais(2,8);                                                           //CHANGE ME
    }
    else if (type == 1){
      dataMC5 = dataMC5 - ( bufferit/rais(2,5)*rais(2,5)- bufferit/rais(2,8)*rais(2,8) );  //CHANGE ME
      dataMC5 += data*rais(2,5);                                                           //CHANGE ME
    }
    else if (type == 2){
      dataMC5 = dataMC5 - ( bufferit/rais(2,2)*rais(2,2) - bufferit/rais(2,5)*rais(2,5) ); //CHANGE ME
      dataMC5 += data*rais(2,2);                                                           //CHANGE ME
    }
    else if (type == 3){
      dataMC5 = dataMC5 - ( bufferit - bufferit/rais(2,2)*rais(2,2) );                     //CHANGE ME
      dataMC5 += data;                                                                     //CHANGE ME
    }
  }

  if (address == 6){                                                                       //CHANGE ME
    int bufferit = dataMC6 - trueMC6;                                                      //CHANGE ME
    if (type == 0){
      dataMC6 = dataMC6 - (bufferit/rais(2,8))*rais(2,8);                                  //CHANGE ME
      dataMC6 += data*rais(2,8);                                                           //CHANGE ME
    }
    else if (type == 1){
      dataMC6 = dataMC6 - ( bufferit/rais(2,5)*rais(2,5)- bufferit/rais(2,8)*rais(2,8) );  //CHANGE ME
      dataMC6 += data*rais(2,5);                                                           //CHANGE ME
    }
    else if (type == 2){
      dataMC6 = dataMC6 - ( bufferit/rais(2,2)*rais(2,2) - bufferit/rais(2,5)*rais(2,5) ); //CHANGE ME
      dataMC6 += data*rais(2,2);                                                           //CHANGE ME
    }
    else if (type == 3){
      dataMC6 = dataMC6 - ( bufferit - bufferit/rais(2,2)*rais(2,2) );                     //CHANGE ME
      dataMC6 += data;                                                                     //CHANGE ME
    }
  }

  if (address == 7){                                                                       //CHANGE ME
    int bufferit = dataMC7 - trueMC7;                                                      //CHANGE ME
    if (type == 0){
      dataMC7 = dataMC7 - (bufferit/rais(2,8))*rais(2,8);                                  //CHANGE ME
      dataMC7 += data*rais(2,8);                                                           //CHANGE ME
    }
    else if (type == 1){
      dataMC7 = dataMC7 - ( bufferit/rais(2,5)*rais(2,5)- bufferit/rais(2,8)*rais(2,8) );  //CHANGE ME
      dataMC7 += data*rais(2,5);                                                           //CHANGE ME
    }
    else if (type == 2){
      dataMC7 = dataMC7 - ( bufferit/rais(2,2)*rais(2,2) - bufferit/rais(2,5)*rais(2,5) ); //CHANGE ME
      dataMC7 += data*rais(2,2);                                                           //CHANGE ME
    }
    else if (type == 3){
      dataMC7 = dataMC7 - ( bufferit - bufferit/rais(2,2)*rais(2,2) );                     //CHANGE ME
      dataMC7 += data;                                                                     //CHANGE ME
    }
  }
}
