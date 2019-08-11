#include "VariableGlobal.h"


Global::Global(int config) {
  
}

void Global::lcd_init() {
  lcd1.init();
  lcd2.init();
  lcd1.backlight();
  lcd2.backlight();
}

int Global::get_config() {
  Serial.println("Recuperation des données en mémoire");


  // PosAbsolue = 8 byte, le reste à 2
  /* 0-7 posAbsolue
     8-11 vitesseContinuDebut
     12-15 vitesseContinuFin
     16-19 vitesseIpIDebut
     20-23 vitesseIpIFin
     24-27 penteAcceleration
     28-32 tempsPose
  */
  int res = 0;
  long resLong = 0;
  long tmp = 0;
  byte eep;
  
  for (int i = 0; i < 8; i++) {
    eep = (EEPROM.read(0+i)) ;
     for(int j = 7; j >= 0; j--){
      tmp = (tmp << 1) + ((eep >> j)&1) ;
    }
  }
  posAbsolue = tmp;
  Serial.println("PosAbsolue");
  Serial.println(posAbsolue);
  res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(8+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1) ;
    }
  }
  vitesseContinuDebut = res;
  Serial.println("vitesseContinuDebut");
  Serial.println(vitesseContinuDebut);
  
  res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(12+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1) ;
    }
  }
  vitesseContinuFin = res;
  Serial.println("vitesseContinuFin");
  Serial.println(vitesseContinuFin);

  res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(16+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1) ;
    }
  }
  vitesseIpIDebut = res;
  Serial.println("vitesseIpIDebut");
  Serial.println(vitesseIpIDebut);

  res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(20+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1) ;
    }
  }
  vitesseIpIFin = res;
  Serial.println("vitesseIpIFin");
  Serial.println(vitesseIpIFin);

  res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(24+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1) ;
    }
  }
  penteAcceleration = res;
  Serial.println("penteAcceleration");
  Serial.println(penteAcceleration);

  res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(28+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1) ;
    }
  }
  tempsPose = res;
  Serial.println("tempsPose");
  Serial.println(tempsPose);
}


int Global::save_config() {

  // PosAbsolue = 8 byte, le reste à 4
  /* 0-7 posAbsolue
     8-11 vitesseContinuDebut
     12-15 vitesseContinuFin
     16-19 vitesseIpIDebut
     20-23 vitesseIpIFin
     24-27 penteAcceleration
     28-32 tempsPose
  */

  for (int i = 0; i < 8; i++) {
    EEPROM.write( 7 - i , (posAbsolue >> (8 * i)) & 0xff);
    Serial.println((posAbsolue >> (8 * i)) & 0xff);
  }

  for (int i = 0; i < 2; i++) {
    EEPROM.write( 11-i , (vitesseContinuDebut >> (8 * i)) & 0xff);
  }

    for (int i = 0; i < 2; i++) {
    EEPROM.write( 15-i , (vitesseContinuFin >> (8 * i)) & 0xff);
  }

    for (int i = 0; i < 2; i++) {
    EEPROM.write( 19-i , (vitesseIpIDebut >> (8 * i)) & 0xff);
  }

    for (int i = 0; i < 2; i++) {
    EEPROM.write( 23-i , (vitesseIpIFin >> (8 * i)) & 0xff);
  }

    for (int i = 0; i < 2; i++) {
    EEPROM.write( 27-i, (penteAcceleration >> (8 * i)) & 0xff);
  }

    for (int i = 0; i < 2; i++) {
    EEPROM.write( 31-i , (tempsPose >> (8 * i)) & 0xff);
  }
  Serial.println("Sauvegardé");
}
