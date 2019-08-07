#ifndef Menu_h
#define Menu_h
#include "VariableGlobal.h"
#include "src/RotaryEncoder.h"
#include "EntreeSortie.h"
#include "Keypad.h"

class Menu{
  private:
  RotaryEncoder encoder = RotaryEncoder(46, 47);
  
  public:
  

  Menu(Global * g1, EntreeSortie * es1, Keypad * kp1);
  int tailleMenu = 8;
  char titreMenu[8][256] = {"Plage vitesse Continu", "plage image par image", "Nb pas moteur A", "Nb pas moteur B", "Pente acceleration", "nb pulse apres desc", "temps de pose", "retour <--"};
  Global * g;
  EntreeSortie * es;
  Keypad * k;
  
  int affichage_menu();
  void retourMenu();
  void affichageMenuFromPos(int p);
  long saisieClavier(LiquidCrystal_I2C mylcd, int hauteur);
  int doubleMenu(int *a, int *b, String s1, String s2);
  int simpleMenu(int *a, String s);

  
};










#endif
