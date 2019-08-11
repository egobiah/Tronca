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
  LedControl * lc1;
  LedControl * lc2;
  Affichage(Global * g1, EntreeSortie * es1,LedControl * lc1, LedControl * lc2);
  void affichage_absolue();
  void affichage_relatif();
  void affichage_vitesse();
  void intToLed(long num, LedControl * lc);
  void affichage_tout();
  void affichageConditionnel();
  void affichage_lc();
  
};


#endif
