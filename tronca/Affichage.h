#ifndef affichage_h
#define affichage_h
#include "VariableGlobal.h"
#include "EntreeSortie.h"
#include "src/LedControl.h"

class Affichage{
  private:

  public:
  Global * g;
  EntreeSortie * es;
  LedControl * lc;
  Affichage(Global * g1, EntreeSortie * es1,LedControl * lc1);
  void affichage_absolue();
  void affichage_relatif();
  void affichage_vitesse();
  void intToLed(long num);
  void affichage_tout();
  void affichageConditionnel();
  
};


#endif
