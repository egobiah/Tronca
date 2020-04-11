#ifndef moteur_h
#define moteur_h

#include "src/FlexyStepper.h"
#include "VariableGlobal.h"
#include "Affichage.h"
#include "EntreeSortie.h"

#include <Arduino.h>
class Moteur {
  private:
    int moteur = 0;
    int dirMoteur = 0;
    
    int swa_1 = 0;
    int swa_2 = 0;
    int swa_3 = 0;
    int swa_4 = 0;

    int swb_1 = 0;
    int swb_2 = 0;
    int swb_3 = 0;
    int swb_4 = 0;

    int capteurLed  = A15;
    Global * g;
    Affichage * a;
    EntreeSortie * es;

    int camera;
    

  public:
    FlexyStepper stepper;
    Moteur(Global * g1, Affichage * a1, EntreeSortie * es1, int pinMoteur, int pinDirMoteur, int pin_swa_1, int pin_swa_2, int pin_swa_3, int pin_swa_4, int pin_swb_1, int pin_swb_2, int pin_swb_3, int pin_swb_4, int pinCamera);
    void pulseAvant();
    void pulseArriere();

    void callageAvant();
    void callageArriere();

    void imageAvant();
    void imageArriere();

    void avant();
    void arriere();

    void goToRelatif();
    void goToAbsolue();
    void intToSwitch(int pas, int sw);

    void calibrage();
    void configContinu();

    void configIpI();

    void configCallage();
    bool photos();


};


#endif
