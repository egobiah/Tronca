#ifndef Global_h
#define Global_h
#include "src/LiquidCrystal_I2C.h"
#define I2C_LCD1 0x21
#define I2C_LCD2 0x22

class Global {


   public :
   
 LiquidCrystal_I2C lcd1 = LiquidCrystal_I2C(I2C_LCD1,16,2);
 LiquidCrystal_I2C lcd2 = LiquidCrystal_I2C(I2C_LCD2,16,2);
  // Variable sauvegardé
   int vitesseContinu = 1;
   int vitesseContinuDebut =1;
   int vitesseContinuFin = 100;

   int vitesseIpI = 1;
   int vitesseIpIDebut = 1;
   int vitesseIpIFin = 1;

   int *vitesse[2] = {&vitesseIpI, &vitesseContinu};

   int nbPasMoteurA = 1;
   int nbPasMoteurB = 1;
   int PenteAcceleration =1;
   int tempsPose = 1;

   long posAbsolue = 1;
   long posAbsolueOld = 1;
   long targetAbsolue = 1;

   long posRelatif = 1;
   long posRelatifOld = 1;
   long targetRelatif = 1;

   int nbPulseDesc;

#define nb_arg_file 8
  int * arg_file[10] = {&vitesseContinuDebut, &vitesseContinuFin, &vitesseIpIDebut, &vitesseIpIFin, &nbPasMoteurA, &PenteAcceleration, &nbPulseDesc, &tempsPose};


   int menu = 0;
   int subMenu = 0;
   int posMenu = 0;

   char codeK;
   char tamponK = -1;

   int ecritureClavier = 0;

   int refreshAbsolue = 0;
   int refreshRelatif = 0;
   int refreshVitesse = 0;

   int cs_sd;
// Fonction d'initialisation
// Pin de la carte SD
   Global(int pin);
   void lcd_init();
// Fonction carte SD
   int get_config();
   int save_config();

   int refresh = 0;
   
};

#endif
