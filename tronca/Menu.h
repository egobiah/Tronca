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
  int dirSubMenu = 0;
  
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

  
  int tailleMenu = 9;
  char titreMenu[9][40] = {   "Temps Pose", "Calibrage LED", "Reglage Capteur", "Seuil", "Position Absolue", "Moteur Continu", "Moteur IpI", "Moteur callage", "Delai apres cap"};
  Global * g;
  EntreeSortie * es;
  Keypad * k;
  Moteur * m;
  int ledMin;
  int ledMax;
  
  int affichage_menu();
  int retourMenu();
  void affichageMenuFromPos(int p);
  long saisieClavier(LiquidCrystal_I2C mylcd, int hauteur);
  int doubleMenu(int *a, int *b, String s1, String s2);
  int simpleMenu(int *a, String s);
  int longSimpleMenu(long *a, String s);

  int simpleEncodeur(int nbCboix, int choix[], int * valeur, String s);

  
};










#endif
