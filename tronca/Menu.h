#ifndef Menu_h
#define Menu_h
#include "VariableGlobal.h"
#include "src/RotaryEncoder.h"
#include "EntreeSortie.h"
#include "Keypad.h"
#include "Moteur.h"
#include <Arduino.h>


class Menu{
  private:
  RotaryEncoder encoder = RotaryEncoder(46, 47);
  
  public:
  

  Menu(Global * g1, EntreeSortie * es1, Keypad * kp1, Moteur * m1);

    /* 0-7 posAbsolue
     8-11 vitesseContinuDebut
     12-15 vitesseContinuFin
     16-19 vitesseIpIDebut
     20-23 vitesseIpIFin
     24-27 penteAcceleration
     28-32 tempsPose
  */

  
  int tailleMenu = 8;
  char titreMenu[8][40] = {"Plage vitesse Continu", "plage image par image", "Choix Vitesse",  "Pente acceleration", "Calibrage LED", "Reglage Capteur", "Seuil Declanchement", "retour <--"};
  Global * g;
  EntreeSortie * es;
  Keypad * k;
  Moteur * m;
  int ledMin;
  int ledMax;
  
  int affichage_menu();
  void retourMenu();
  void affichageMenuFromPos(int p);
  long saisieClavier(LiquidCrystal_I2C mylcd, int hauteur);
  int doubleMenu(int *a, int *b, String s1, String s2);
  int simpleMenu(int *a, String s);

  
};










#endif
