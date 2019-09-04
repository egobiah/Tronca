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
    eep = (EEPROM.read(28+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1) ;
    }
  }
  tempsPose = res;  
  Serial.println("tempsPose");
  Serial.println(tempsPose);

    res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(32+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1) ;
    }
  }
  ledMin = res;
    Serial.println("ledMin");
  Serial.println(ledMin);
    res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(36+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1) ;
    }
  }
  ledMax = res;

    Serial.println("ledMax");
  Serial.println(ledMax);

   res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(40+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1) ;
    }
  }
  seuil = res;
  Serial.println("Seuil");
  Serial.println(seuil);

  
   res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(48+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1) ;
    }
  }
  posRelatif = res;
  Serial.println("posRelatif");
  Serial.println(posRelatif);

  res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(52+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1) ;
    }
  }
  pasMoteur = res;
  Serial.println("pasMoteur");
  Serial.println(pasMoteur);

   res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(56+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1) ;
    }
  }
  acceleration = res;
  Serial.println("acceleration");
  Serial.println(acceleration);

   res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(60+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1) ;
    }
  }
  stepMoteurParSec = res;
  Serial.println("stepMoteurParSec");
  Serial.println(stepMoteurParSec);

    res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(64+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1) ;
    }
  }
  pasMoteurIpI = res;
  Serial.println("pasMoteurIpI");
  Serial.println(pasMoteurIpI);

   res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(68+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1) ;
    }
  }
  accelerationIpI = res;
  Serial.println("accelerationIpI");
  Serial.println(accelerationIpI);

   res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(72+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1) ;
    }
  }
  stepMoteurParSecIpI = res;
  Serial.println("stepMoteurParSecIpI");
  Serial.println(stepMoteurParSecIpI);

    res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(76+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1) ;
    }
  }
  pasMoteurCallage = res;
  Serial.println("pasMoteurCallage");
  Serial.println(pasMoteurCallage);

   res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(80+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1) ;
    }
  }
  accelerationCallage = res;
  Serial.println("accelerationCallage");
  Serial.println(accelerationCallage);

   res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(84+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1) ;
    }
  }
  stepMoteurParSecCallage = res;
  Serial.println("stepMoteurParSecCallage");
  Serial.println(stepMoteurParSecCallage);

     res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(88+i));
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1);
    }
  }
  ledMin = res;
  Serial.println("ledMin");
  Serial.println(ledMin);

     res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(92+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1);
    }
  }
  ledMax = res;
  Serial.println("ledMax");
  Serial.println(ledMax);

     res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(96+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1) ;
    }
  }
  tempsPose = res;
  Serial.println("tempsPose");
  Serial.println(tempsPose);

       res = 0;
  for (int i = 0; i < 4; i++) {
    eep = (EEPROM.read(100+i)) ;
    for(int j = 7; j >= 0; j--){
      res = (res << 1) + ((eep >> j)&1) ;
    }
  }
  delayApresPose = res;
  Serial.println("delayApresPose");
  Serial.println(delayApresPose);
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
    EEPROM.write( 31-i , (tempsPose >> (8 * i)) & 0xff);
  }

      for (int i = 0; i < 2; i++) {
    EEPROM.write( 35-i , (ledMin >> (8 * i)) & 0xff);
  }

      for (int i = 0; i < 2; i++) {
    EEPROM.write( 39-i , (ledMax >> (8 * i)) & 0xff);
  }

      for (int i = 0; i < 2; i++) {
    EEPROM.write( 43-i , (seuil >> (8 * i)) & 0xff);
  }

      for (int i = 0; i < 2; i++) {
    EEPROM.write( 51-i , (posRelatif >> (8 * i)) & 0xff);
  }

        for (int i = 0; i < 2; i++) {
    EEPROM.write( 55-i , (pasMoteur >> (8 * i)) & 0xff);
  }
        for (int i = 0; i < 2; i++) {
    EEPROM.write( 59-i , (acceleration >> (8 * i)) & 0xff);
  }
        for (int i = 0; i < 2; i++) {
    EEPROM.write( 63-i , (stepMoteurParSec >> (8 * i)) & 0xff);
  }

      for (int i = 0; i < 2; i++) {
    EEPROM.write( 67-i , (pasMoteurIpI >> (8 * i)) & 0xff);
  }
        for (int i = 0; i < 2; i++) {
    EEPROM.write( 71-i , (accelerationIpI >> (8 * i)) & 0xff);
  }
        for (int i = 0; i < 2; i++) {
    EEPROM.write( 75-i , (stepMoteurParSecIpI >> (8 * i)) & 0xff);
  }

      for (int i = 0; i < 2; i++) {
    EEPROM.write( 79-i , (pasMoteurCallage >> (8 * i)) & 0xff);
  }
        for (int i = 0; i < 2; i++) {
    EEPROM.write( 83-i , (accelerationCallage >> (8 * i)) & 0xff);
  }
        for (int i = 0; i < 2; i++) {
    EEPROM.write( 87-i , (stepMoteurParSecCallage >> (8 * i)) & 0xff);
  }

          for (int i = 0; i < 2; i++) {
    EEPROM.write( 91-i , (ledMin >> (8 * i)) & 0xff);
  }

          for (int i = 0; i < 2; i++) {
    EEPROM.write( 95-i , (ledMax >> (8 * i)) & 0xff);
  }

          for (int i = 0; i < 2; i++) {
    EEPROM.write( 99-i , (tempsPose >> (8 * i)) & 0xff);
  }

   for (int i = 0; i < 2; i++) {
    EEPROM.write( 103-i , (delayApresPose >> (8 * i)) & 0xff);
  }
  Serial.println("Sauvegardé");
}
