#include "Keypad.h"
#include <Wire.h>


Keypad::Keypad(int adresse){
  I2C_KEYPAD = adresse;
  Wire.begin();
}

int Keypad::get_code(){
    int resC;
    int resR;
    int col = 32+128+8;
    int row = 64+2+4+16;
    int res;
    
    
    Wire.beginTransmission(0x20);
    Wire.write(col);
    Wire.endTransmission();
    Wire.requestFrom(0x20, 1);
    
    if(Wire.available()) {
        int tmp = Wire.read();
        
        if(tmp != col){  // Serial.println(p);
            resC = tmp;
           
        }
    }

    Wire.beginTransmission(I2C_KEYPAD);
    Wire.write(row);
    Wire.endTransmission();
    Wire.requestFrom(I2C_KEYPAD, 1);
    if(Wire.available()) {
        int tmp = Wire.read();
        if(tmp != row){
            resR = tmp;
        }
    }
 
    res = resC*100+resR;
    if(res == col*100 +row){
        res = -1;
    }
  //Serial.println(res);
  return res;
}

char Keypad::decode(int code){
    char key;
    switch(code){
        case 13622:key = '1'; break;
        case 13684: key = '4'; break;
        case 13682: key='7'; break;
        case 13670: key ='*'; break;
        case 4022:key='2'; break;
        case 4084:key='5';break;
        case 4082:key='8';break;
        case 4070:key='0';break;
        case 16022:key='3';break;
        case 16084:key='6';break;
        case 16082:key='9';break;
    default:
        // Trop de "case" dans le switch, le dernier est alors ici
        if(code == 16070){
            key='#';
        } else {
            key = '@';    
        }
    break;
  }
  return key;
}

char Keypad::get_key(){
  return decode(get_code());
}
