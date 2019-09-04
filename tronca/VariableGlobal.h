#ifndef Global_h
#define Global_h
#include "src/LiquidCrystal_I2C.h"
#define I2C_LCD1 0x21
#define I2C_LCD2 0x22
#include <Arduino.h>
#include <EEPROM.h>

class Global {


   public :
   
 LiquidCrystal_I2C lcd1 = LiquidCrystal_I2C(I2C_LCD1,16,2);
 LiquidCrystal_I2C lcd2 = LiquidCrystal_I2C(I2C_LCD2,16,2);
  // Variable sauvegardé
   int vitesseContinu = 5;
   int vitesseContinuDebut =5;
   int vitesseContinuFin = 10;

   int vitesseIpI = 1;
   int vitesseIpIDebut = 1;
   int vitesseIpIFin = 10;

   int *vitesse[2] = {&vitesseIpI, &vitesseContinu};

   int nbPasMoteurA = 1;
   int tempsPose = 1;

   long posAbsolue = 0;
   long posAbsolueOld = 1;
   long targetAbsolue = 0;

   long posRelatif = 1;
   long posRelatifOld = 1;
   long targetRelatif = 0;

   long target = 0;

   int nbPulseDesc;
   int penteAcceleration = 800;
   
   int pasMoteurTab[6] = {400, 800, 1600, 3200, 6400, 12800};
   
   int pasMoteur = 400;
   long acceleration = 800;
   long stepMoteurParSec = 3200;
   int pasParBoucle = 80;
   

   int pasMoteurIpI = 400;
   long stepMoteurParSecIpI = 1600;
   long accelerationIpI = 800;

   int pasMoteurCallage = 12800;
   long stepMoteurParSecCallage = 200;
   long accelerationCallage = 800;

   int delayApresPose = 100;

  int stop = 0;

  


   int menu = 0;
   int subMenu = 0;
   int posMenu = 0;

   char codeK;
   char tamponK = -1;

   int ecritureClavier = 0;

   int refreshAbsolue = 0;
   int refreshRelatif = 0;
   int refreshVitesse = 0;
   int refreshLC = 0;

   int ledMin = 300;
   int ledMax = 750;
   
   int seuil = 30;
  
// Fonction d'initialisation
// Pin de la carte SD
   Global(int config);
   void lcd_init();
// Fonction carte SD
   int get_config();
   int save_config();

   int refresh = 0;

   int backwarding = 0;

   
};

#endif
