#include <iostream>
#include <fstream>
#include <bitset>
 
using namespace std;
 
int main() {
 
    const int ADDRESSBITS = 0xE0;
    const int TYPEBITS = 0x18;
    const int DATABITS = 0x07;
 
    int payload = 85;
    int address, type, data;
    bitset<8> sensorData{"00000000"}; //11 bits
 
    address = (payload & ADDRESSBITS) >> 5;
    type = (payload & TYPEBITS) >> 3;
    data = (payload & DATABITS);
    bitset<3> databits(data);
    bitset<11> sensorBits{"00000000000"};
 
    cout << address << " " << type << " " << data << endl;
 
    switch (type) {
    case 0:
        for (size_t i = 0; i < databits.size(); i++) {
            sensorBits[i + 8] = databits[i];
        }
        break;
    case 1:
        for (size_t i = 0; i < databits.size(); i++) {
            sensorBits[i + 5] = databits[i];
        }
        break;
    case 2:
        for (size_t i = 0; i < databits.size(); i++) {
            sensorBits[i + 2] = databits[i];
        }
        break;
    case 3:
        for (size_t i = 1; i < databits.size(); i++) {
            sensorBits[i] = databits[i];
        }
        break;
    }
 
    cout << "Integer data: " << sensorData << ", Binary data: " << sensorBits << endl;
 
    return 0;
}
